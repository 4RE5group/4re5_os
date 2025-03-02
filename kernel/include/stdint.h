#pragma once

typedef unsigned char  uint8_t,  BYTE, UCHAR;
typedef unsigned short uint16_t, WORD, UWORD;
typedef unsigned int   uint32_t, DWORD, UINT;
typedef unsigned long  ULONG;
typedef unsigned short USHORT;

typedef unsigned long long uint64_t, QWORD, ULLONG;

typedef BYTE*  LPBYTE;
typedef WORD*  LPWORD;
typedef DWORD* LPDWORD;

typedef const char* STRING;

#define NULL  ((void*)0)

#define TRUE  1
#define true  1

#define FALSE 0
#define false 0


void IntToString(int value, char* buffer)
{
    char temp[11];
    int i = 0;
    int isNegative = 0;

    if (value < 0) 
    {
        isNegative = 1;
        value = -value;
    }

    do 
    {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);

    if (isNegative) 
    {
        temp[i++] = '-';
    }

    temp[i] = '\0';

    int j;

    for (j = 0; j < i; j++) 
    {
        buffer[j] = temp[i - j - 1];
    }

    buffer[j] = '\0';
}