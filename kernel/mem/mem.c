#include "../include/stdint.h"

#include "mem.h"

void* memset(void* dst, char val, DWORD num)
{
    LPBYTE tmp = (LPBYTE) dst;

    for (DWORD i = 0; i < num; i++)
    {
        tmp[i] = (BYTE) val;
    }

    return dst;
}

int strcmp(const char *str1, const char *str2) 
{
    while (*str1 && (*str1 == *str2)) 
    {
        str1++;
        str2++;
    }
    
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

DWORD strlen(const char *str) 
{
    DWORD length = 0;
    
    while (str[length] != '\0') 
    {
        length++;
    }
    
    return length;
}

char* strcat(char* dest, const char* src) 
{
    char* ptr = dest;

    while (*ptr != '\0') 
    {
        ptr++;
    }

    while (*src != '\0') 
    {
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dest;
}

char* strncpy(char *dest, const char *src, DWORD n) 
{
    DWORD i = 0;
    
    while (i < n && src[i] != '\0') 
    {
        dest[i] = src[i];
        i++;
    }
    
    while (i < n) 
    {
        dest[i] = '\0';
        i++;
    }
    
    return dest;
}

int strncmp(const char *str1, const char *str2, DWORD n) 
{
    DWORD i = 0;

    while (i < n) 
    {
        if (str1[i] != str2[i]) 
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }

        if (str1[i] == '\0' || str2[i] == '\0') 
        {
            break;
        }

        i++;
    }

    return 0;
}

void* memcpy(void *dest, const void *src, DWORD n) 
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    
    while (n--) 
    {
        *d = *s;
        d++;
        s++;
    }
    
    return dest;
}
