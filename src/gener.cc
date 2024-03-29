#include "gener.h"

Str gen_var(int len)
{
    Str var = {
        .data = (char *)malloc(len),
        .len = len,
    };
    static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static char number[] = "0123456789";
    static char underscore[] = "_";
    if (var.len > 0)
    {
        int choice = klee_range(0, 53, NULL);
        if (choice == 52)
        {
            var.data[0] = '_';
        }
        else
        {
            var.data[0] = alphabet[choice];
        }
    }
    for (int i = 0; i < len; i++)
    {
        int choice = klee_range(0, 63, NULL);
        if (choice < 52)
        {
            var.data[i] = alphabet[choice];
        }
        else if (choice == 52)
        {
            var.data[i] = underscore[0];
        }
        else
        {
            var.data[i] = number[choice - 53];
        }
    }
    return var;
}
Expr *gen_expr(int depth, int max_var_len)
{
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    if (depth < 2)
    {
        int choice = klee_range(0, 3, NULL);
        if (choice == 0)
        {
            int i;
            klee_make_symbolic(&i, sizeof(i), NULL);
            *expr = new_int(i);
        }
        else if (choice == 1)
        {
            float f;
            klee_make_symbolic(&f, sizeof(f), "float");
            *expr = new_float(f);
        }
        else if (choice == 2)
        {
            Str var = gen_var(klee_range(1, max_var_len, NULL));
            *expr = new_var(var);
        }
        else
        {
            exit(1);
        }
    }
    else
    {
        int choice = klee_range(0, 5, NULL);
        if (choice == 0)
        {
            int i;
            klee_make_symbolic(&i, sizeof(i), NULL);
            *expr = new_int(i);
        }
        else if (choice == 1)
        {
            float f;
            klee_make_symbolic(&f, sizeof(f), NULL);
            *expr = new_float(f);
        }
        else if (choice == 2)
        {
            Str var = gen_var(klee_range(1, max_var_len, NULL));
            *expr = new_var(var);
        }
        else if (choice == 3)
        {
            static char unops[] = "-~!";
            char op = unops[klee_range(0, 3, NULL)];
            Expr *son_expr = gen_expr(depth - 1, max_var_len);
            *expr = new_unop(op, son_expr);
        }
        else
        {
            static char binops[] = "+-*/%&|^<>";
            char op = binops[klee_range(0, 10, NULL)];
            Expr *lhs = gen_expr(depth - 1, max_var_len);
            Expr *rhs = gen_expr(depth - 1, max_var_len);
            *expr = new_binop(op, lhs, rhs);
        }
    }
    return expr;
}