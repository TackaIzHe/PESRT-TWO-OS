#include "stdio.h"

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

int p_random(int start, int end) {
    uint16_t tic = 0;
    get_tic(&tic);
    return (tic+1024) % (end - start + 1) + start;
}