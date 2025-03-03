#pragma once

#include "stdint.h"

void outb(WORD port, BYTE value);
char inb(WORD port);
void outw(WORD port, WORD value);
WORD inw(WORD port);
void outl(WORD port, DWORD value);
DWORD inl(WORD port);