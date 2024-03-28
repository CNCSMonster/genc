#include <klee/klee.h>
#include <stdlib.h>
#include <stdio.h>

struct Expr
{
    int kind;
    union
    {
        int value;
        struct
        {
            struct Expr *left;
            struct Expr *right;
        } binop;
    } info;
};

int main()
{
    return 0;
}