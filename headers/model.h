#ifndef _GENC_H
#define _GENC_H

#include <klee/klee.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *str;
    int len;
} Str;
Str gen_var_name(int len);
Str new_str(char *str);
Str combine_str(Str *str, Str *str2);
void free_str(Str *str);

typedef enum
{
    // TYPEKIND_VOID,
    // TYPEKIND_BOOL,
    // TYPEKIND_CHAR,
    // TYPEDEF_SHORT,
    TYPEKIND_INT,
    // TYPEKIND_LONG,
    // TYPEKIND_FLOAT,
    // TYPEKIND_DOUBLE,
    // TYPEKIND_POINTER,
    // TYPEKIND_ARRAY,
    // TYPEKIND_FUNCTION,
    // TYPEKIND_TYPEDEF,
    // TYPEKIND_CONST,
    // TYPEKIND_STRUCT,
    // TYPEKIND_UNION,
    // TYPEKIND_ENUM,
    TYPEKIND_UNKNOWN,
} TypeKind;

typedef struct
{
    TypeKind kind;
    void *info;
} Type;

// typedef struct
// {
//     int num_element;
//     Type *element_type;
// } TypeArrayInfo;

Type gen_type();

// typedef enum
// {
//     EXPRETYPE_CONST,
//     EXPRETYPE_VAR,
//     EXPRETYPE_OP,
// } ExprType;

// typedef struct
// {
// } Expr;
// typedef struct
// {

//     int value;
// } Const;
// } ConstExpr;

// // 类型, 变量, 表达式
// typedef struct
// {
//     int type; // type为类型id,
//     Str name; // name为变量名
// } Var;

#endif