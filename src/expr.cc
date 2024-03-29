
#include "expr.h"

Expr new_int(int val)
{
    Expr expr = {
        .kind = ExprKind::INT,
        .int_val = val,
    };
    return expr;
}
Expr new_float(float val)
{
    Expr expr = {
        .kind = ExprKind::FLOAT,
        .float_val = val,
    };
    return expr;
}
Expr new_var(Str var)
{
    Expr expr = {
        .kind = ExprKind::VAR,
        .var = var,
    };
    return expr;
}
Expr new_binop(char op, struct Expr *lhs, struct Expr *rhs)
{
    Expr expr;
    expr.kind = ExprKind::BINOP;
    expr.binop.op = op;
    expr.binop.lhs = lhs;
    expr.binop.rhs = rhs;
    return expr;
}
Expr new_unop(char op, struct Expr *expr)
{
    Expr new_expr;
    new_expr.kind = ExprKind::UNOP;
    new_expr.unop.op = op;
    new_expr.unop.expr = expr;
    return new_expr;
}
void free_expr(struct Expr *expr)
{
    if (expr->kind == ExprKind::BINOP)
    {
        free_expr(expr->binop.lhs);
        free_expr(expr->binop.rhs);
    }
    else if (expr->kind == ExprKind::UNOP)
    {
        free_expr(expr->unop.expr);
    }
    else if (expr->kind == ExprKind::VAR)
    {
        free_str(expr->var);
    }
    free(expr);
}

void print_expr(struct Expr *expr)
{
    if (expr->kind == ExprKind::INT)
    {
        printf("%d", expr->int_val);
    }
    else if (expr->kind == ExprKind::FLOAT)
    {
        printf("%f", expr->float_val);
    }
    else if (expr->kind == ExprKind::VAR)
    {
        print_str(expr->var);
    }
    else if (expr->kind == ExprKind::BINOP)
    {
        printf("(");
        print_expr(expr->binop.lhs);
        printf("%c", expr->binop.op);
        print_expr(expr->binop.rhs);
        printf(")");
    }
    else if (expr->kind == ExprKind::UNOP)
    {
        printf("%c", expr->unop.op);
        print_expr(expr->unop.expr);
    }
}