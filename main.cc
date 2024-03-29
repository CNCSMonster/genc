#include <klee/klee.h>
#include <stdlib.h>
#include <stdio.h>
#include "str.h"
#include "expr.h"
#include "gener.h"

int main()
{
    Expr *expr = gen_expr(1, 2);
    print_expr(expr);
    free_expr(expr);
    return 0;
}