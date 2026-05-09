#include "uint.h"
#include "video_driver/vbe.h"
#include "interapts/video.h"

float cos(float x);
float sin(float a);

float sin(float a) {
    return (a * 3.14f) / 180;
}

static const float ctbl[9] = {
    1.00000f, 0.98481f, 0.93969f, 0.86603f,
    0.76604f, 0.64279f, 0.50000f, 0.34202f, 0.17365f
};

static inline float fabsf_(float x) { return x < 0 ? -x : x; }

static inline float fmodf_(float x, float y) {
    while (x >= y) x -= y;
    while (x <  0) x += y;
    return x;
}

float cos(float x) {
    const float pi    = 3.14159265f;
    const float pi2   = 6.28318531f;
    const float pi_2  = 1.57079633f;

    x = fabsf_(x);
    x = fmodf_(x, pi2);          /* [0, 2π) */

    int sign = 1;
    if (x > pi) {                /* 2-й полу-круг */
        x = pi2 - x;
    }
    if (x > pi_2) {              /* 2-й квадрант */
        x = pi - x;
        sign = -1;
    }

    const float step = pi_2 / 8.0f;
    int idx = (int)(x / step);
    float t = (x - idx * step) / step;

    float y1 = ctbl[idx];
    float y2 = ctbl[idx + 1];
    return sign * (y1 + t * (y2 - y1));
}

typedef struct {
    float x, y;
} vector2;

vector2 randomGradient(uint32_t ix, uint32_t iy, uint32_t aa) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const uint32_t w = 8 * sizeof(uint32_t);
    const uint32_t s = w / 2;
    uint32_t a = ix, b = iy;

    

    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717+ aa;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(uint32_t ix, uint32_t iy, float x, float y, uint32_t aa) {
    // Get gradient from integer coordinates
    vector2 gradient = randomGradient(ix, iy, aa);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}


// Sample Perlin noise at coordinates x, y
float perlin(float x, float y, uint32_t aa) {

    // Determine grid cell corner coordinates
    uint32_t x0 = (uint32_t)x;
    uint32_t y0 = (uint32_t)y;
    uint32_t x1 = x0 + 1;
    uint32_t y1 = y0 + 1;

    // Compute Interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Compute and interpolate top two corners
    float n0 = dotGridGradient(x0, y0, x, y, aa);
    float n1 = dotGridGradient(x1, y0, x, y, aa);
    float ix0 = interpolate(n0, n1, sx);

    // Compute and interpolate bottom two corners
    n0 = dotGridGradient(x0, y1, x, y, aa);
    n1 = dotGridGradient(x1, y1, x, y, aa);
    float ix1 = interpolate(n0, n1, sx);

    // Final step: interpolate between the two previously interpolated values, now in y
    float value = interpolate(ix0, ix1, sy);

    return value;
}

uint32_t main_procedure(uint32_t patern)
{

    vbe_mode_info_t vbe_mode_info = {0};
    get_vbe_mode_info(&vbe_mode_info);
    uint32_t aa = patern;

    const int windowWidth = vbe_mode_info.xres;
    const int windowHeight = vbe_mode_info.yres;

    const int GRID_SIZE = 400;


    for (int x = 0; x < windowHeight; x++)
    {
        for (int y = 0; y < windowWidth; y++)
        {
            int index = (y * windowWidth + x) * 4;


            float val = 0;
            float val2 = 0;
            float val3 = 0;

            float freq = 1;
            float amp = 1;

            for (int i = 0; i < 9; i++)
            {
                val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE, aa) * amp;
                //val2 += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE, aa) * -amp;

                freq *= 2;
                amp /= 2;

            }
            val2 = val * -1;
            val3 = val;

            // Contrast
            val *= 0.9;
            val2 *= 0.8;
            val3 *= 0.7;
            // Clipping
            if (val > 1.0f)
            {
                val = 1.0f;
                val3 = 1.0f;
                val2 = -1.0f;
                
            }
            else if (val < -1.0f)
            {
                val = -1.0f;
                val3 = -1.0f;
                val2 = 1.0f;
              
            }

            // Convert 1 to -1 into 255 to 0
            int color = (int)(((val + 2.0f) * 0.5f) * 255);
            int color2 = (int)(((val2 + 2.0f) * 0.504f) * 255);
            int color3 = (int)(((val3 + 0.5f) * 0.5f) * 180);

            // Set pixel color
            set_pixel((color/16<<12) + (color/16 << 8) + (color/16 << 4), y, x);            
        }
    }
    return 0;
}