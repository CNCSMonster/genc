#ifndef _GENER_H
#define _GENER_H

#include <klee/klee.h>
#include "str.h"
#include "expr.h"

/* Generate a random variable name */
Str gen_var(int len);
Expr *gen_expr(int depth, int max_var_len);

#endif