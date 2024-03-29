#ifndef _EXPR_H
#define _EXPR_H

#include "str.h"

enum ExprKind
{
    INT,
    FLOAT,
    VAR,
    BINOP,
    UNOP,
    UNKNOWN,
};

struct Expr
{
    enum ExprKind kind;
    union
    {
        int int_val;
        float float_val;
        Str var;
        struct
        {
            char op;
            struct Expr *lhs;
            struct Expr *rhs;
        } binop;
        struct
        {
            char op;
            struct Expr *expr;
        } unop;
    };
};

Expr new_int(int val);
Expr new_float(float val);
Expr new_var(Str var);
Expr new_binop(char op, struct Expr *lhs, struct Expr *rhs);
Expr new_unop(char op, struct Expr *expr);
void free_expr(struct Expr *expr);
void print_expr(struct Expr *expr);

#endif