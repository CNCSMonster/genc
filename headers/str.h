#ifndef _STR_H
#define _STR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct Str
{
    char *data;
    int len;
};

void free_str(Str str);
void print_str(Str str);
Str conbine_str(Str s1, Str s2);
void push_char(Str *str, char c);
void push_str(Str *str, char *s);

#endif