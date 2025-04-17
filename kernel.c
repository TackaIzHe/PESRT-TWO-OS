int *videoMem = 0;
int intToChar;
long long int second;
char keyBuffer[256];

extern long getTackt();
extern char keyboard_interrupt_handler();
extern void keybord_init();

long ticks (long delay){
    unsigned long long tik = getTackt();
    unsigned long long tik1 = getTackt();
    while (1){
        tik1 = getTackt();
        if(tik1 - tik >=delay){
            break;
        }
    }
    return  tik1 - tik;
}

void printf(char* mess, int color ){
    if(color == 0){
        color = 0x0f;
    }
    int i =0;
    int *j = videoMem;
    while(*(mess + i) != 0)
    {
        *(char*)*j  = *(mess + i);
        *j += 1;
        *(char*)*j  = color;
        *j += 1;
        i++;   
    }
}

void print(long mess){
    char *i[1]; 
    *i = 0;
    if(mess<10){
        *i = (intToChar + mess);
        printf(i,0);    
    }
    else{ 
        *i = (intToChar + (mess % 10));
        print(mess / 10);
        printf(i,0);
    }
}

void clearScrin()
{
    int *j = videoMem;
    while(*j != 0xb8000)
    {
        *(char*)*j = 0;
        *j -= 2;
    }
}

char presKey(){
    return keyboard_interrupt_handler();
}

void init()
{
    *videoMem = 0xb8000;
    intToChar = 48;
    second = 999999999999999999;
    keybord_init();

}



int main(){
    init();
    clearScrin();

    printf(presKey(),0);

    printf("Hello, World!!!",0x0a);
   
    return 0;
}
