
void memset(char* dest, char data, int size) {
    for (int i = 0; i < size; i++)
        dest[i] = data;
    return;
}

int strlen(const char* str) {
    int i = 0;
    while (*str != '\0')
        i++;

    return i;
}

int strcmp(const char* str1, const char* str2) {
    int res = -1;
    if (strlen(str1) != strlen(str2))
        goto _exit;
    
    while((*str1 != '\0') && (*str2 != '\0'))
    {
        if (*str1 != *str2)
            goto _exit;
        
        str1++;
        str2++;
    }
    res = 0;
_exit:
    return res;
}