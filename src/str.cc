#include "str.h"

void free_str(Str str)
{
    free(str.data);
}
Str conbine_str(Str s1, Str s2)
{
    Str new_str = {
        .data = (char *)malloc(s1.len + s2.len),
        .len = s1.len + s2.len,
    };
    for (int i = 0; i < s1.len; i++)
    {
        new_str.data[i] = s1.data[i];
    }
    for (int i = 0; i < s2.len; i++)
    {
        new_str.data[s1.len + i] = s2.data[i];
    }
    return new_str;
}
void print_str(Str str)
{
    for (int i = 0; i < str.len; i++)
    {
        printf("%c", str.data[i]);
    }
}
void push_char(Str *str, char c)
{
    char *tmp = (char *)malloc(str->len + 1);
    for (int i = 0; i < str->len; i++)
    {
        tmp[i] = str->data[i];
    }
    tmp[str->len] = c;
    free(str->data);
    str->data = tmp;
    str->len++;
}
void push_str(Str *str, char *s)
{
    int len = strlen(s);
    char *tmp = (char *)malloc(str->len + len);
    for (int i = 0; i < str->len; i++)
    {
        tmp[i] = str->data[i];
    }
    for (int i = 0; i < len; i++)
    {
        tmp[str->len + i] = s[i];
    }
    free(str->data);
    str->data = tmp;
    str->len += len;
}