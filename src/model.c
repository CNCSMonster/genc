#include "model.h"

Str gen_var_name(int len)
{
    Str name;
    name.str = malloc(len + 1);
    static char char_set[] = "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    name.str[0] = char_set[klee_range(10, strlen(char_set), NULL)];
    for (int i = 1; i < len; i++)
    {
        name.str[i] = char_set[klee_range(0, strlen(char_set), NULL)];
    }
    name.str[len] = '\0';
    return name;
}
Str new_str(char *str)
{
    Str new_str;
    new_str.len = strlen(str);
    new_str.str = malloc(new_str.len + 1);
    memcpy(new_str.str, str, new_str.len);
    new_str.str[new_str.len] = '\0';
    return new_str;
}
Str combine_str(Str *str, Str *str2)
{
    Str new_str;
    new_str.len = str->len + str2->len;
    new_str.str = malloc(new_str.len + 1);
    memcpy(new_str.str, str->str, str->len);
    memcpy(new_str.str + str->len, str2->str, str2->len);
    new_str.str[new_str.len] = '\0';
    return new_str;
}
void free_str(Str *str)
{
    free(str->str);
    str->str = NULL;
    str->len = 0;
}

Type gen_type()
{
    Type type;
    type.kind = klee_range(0, TYPEKIND_UNKNOWN, NULL);
    switch (type.kind)
    {
    case TYPEKIND_INT:
        type.info = NULL;
        break;
        // case TYPEKIND_CHAR:
        //     type.info = NULL;
        //     break;
        // case TYPEKIND_LONG:
        //     type.info = NULL;
        //     break;
        // case TYPEKIND_ARRAY:
        // break;
    default:
        break;
    }
    return type;
}
