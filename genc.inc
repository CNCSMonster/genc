#include <klee/klee.h>
#include <stdio.h>
#include <malloc.h>

// 该程序用于生成c代码

/* 类型 定义 */

typedef struct
{
    char *str;
    int len;
} Str;

typedef enum
{
    INT_4,
    INT_8,
    CHAR,
    FLOAT,
    DOUBLE,
    VOID,
    BASICTYPE_UNKNOWN,
} BasicType;
typedef enum
{
    TYPEKIND_BASIC = 0,
    TYPEKIND_UNKNOWN
} TypeKind;
typedef struct
{
    TypeKind kind; // 使用非常小的数记录
    void *info;
} Type;

typedef struct
{
    Type type;
    Str name;
} Var;

typedef struct
{
    Str name;
    Str ret_type;
    int num_params;
    Var *params;
} Func;

// 定义表达式
typedef enum
{
    EXPRKIND_VAR = 0,
    EXPRKIND_CONST,
    EXPRKIND_OP,
    EXPRKIND_UNKNOWN
} ExprKind;

typedef struct 
{
    int pos; //记录变量在变量表中的位置
} VarExpr;

typedef struct
{
    int value; //记录常量的值
} ConstExpr;

typedef struct
{
    int op; //记录操作符的位置
    int left; //记录左操作数的位置
    int right; //记录右操作数的位置
} OpExpr;

typedef struct
{
    int kind; // 表达式类型
    void *info; // 表达式信息
} Expr;

// 定义代码块

// 定义各种语句
typedef enum
{
    STMTKIND_DECL = 0,
    STMTKIND_ASSIGN,
    STMTKIND_IF,
    STMTKIND_WHILE,
    STMTKIND_FOR,
    STMTKIND_RETURN,
    STMTKIND_UNKNOWN
} StmtKind;

// 定义声明语句
typedef struct
{
  Var* var; // 记录变量的位置
}DeclStmt;
// 定义赋值语句
typedef struct
{
    Var* var; // 记录变量的位置
    Var* expr; // 记录表达式的位置
} AssignStmt;

// 定义if语句
typedef struct
{
    int cond; // 记录条件表达式的位置
    CodeBlock* then_block; // 记录then代码块的位置
    CodeBlock* else_block; // 记录else代码块的位置
} IfStmt;

// 定义while语句
typedef struct
{
    int cond; // 记录条件表达式的位置
    CodeBlock* block; // 记录代码块的位置
} WhileStmt;

// 定义for语句
typedef struct
{
    int init; // 记录初始化表达式的位置
    int cond; // 记录条件表达式的位置
    int update; // 记录更新表达式的位置
    CodeBlock* block; // 记录代码块的位置
} ForStmt;

// 定义return语句
typedef struct
{
    int value; // 记录返回表达式的位置
} ReturnStmt;




// 定义语句
typedef struct
{
    int kind; // 语句类型
    void *info; // 语句信息
} Stmt;

// 对于代码块的定义,代码块可以嵌入代码块
typedef struct
{
   int depth; // 代码块的深度 (记录最外层也就是刚进入函数的代码块的深度为0)
    // 记录代码块中的不可覆盖变量,不可覆盖变量是指在该层代码块中定义的变量,在该层代码中 不可被覆盖(定义同名变量)
   int num_uncovered_vars; // 代码块中的不可覆盖变量数
   Var *uncovered_vars; // 代码块中的不可覆盖变量,按照顺序存储
   // 代码块中的变量,包括所有变量,包括可覆盖的变量 以及 不可覆盖的变量
   int num_vars; // 代码块中的变量数,记录代码块中定义的变量数
   Var *vars; // 代码块中的变量,按照顺序存储,刚进入函数的时候 入参即为变量
   int num_exprs; // 代码块中的表达式数
   Expr *exprs; // 代码块中的表达式,按照顺序存储
   CodeBlock* sub_blocks[2]; // 子代码块,代码块可以嵌套,但是子代码块最多只有两个
   int num_stmts; // 代码块中的语句数
   Stmt* stmts; // 代码块中的语句,按照顺序存储,包括定义语句和执行语句
} CodeBlock;


/* 函数声明 */
void gen_str(Str *s, int len);
void gen_basic(BasicType *b);
void gen_type(Type *t);
void gen_var(Var *v, int len_name);
void print_type(Type *t);
void print_basic(BasicType *b);
void print_var(Var *v);
void print_func(Func *f);


/* 函数实现 */

// 生成 符号量 驱动的 类型

void gen_str(Str* s,int len)
{
    s->str = (char *)malloc(len);
    klee_make_symbolic(s->str, len-1, NULL);
    s->str[len-1] = '\0';
    s->len = len;
}
void gen_basic(BasicType *b)
{
    *b = klee_range(INT_4, BASICTYPE_UNKNOWN, "b");
}
void gen_type(Type *t)
{
    t->kind = TYPEKIND_BASIC;
    BasicType *b = (BasicType *)malloc(sizeof(BasicType));
    *b = klee_range(0, 5, "b");
    t->info = b;
}

void gen_var(Var *v,int len_name)
{
    Str* name = &(v->name);
    // TODO gen name
    // gen_str(name,len_name);
    v->type.kind = TYPEKIND_BASIC;
    BasicType *b = (BasicType *)malloc(sizeof(BasicType));
    *b = klee_range(0, 5, "b");
    v->type.info = b;
}

// 打印 生成 的 代码块
void print_type(Type *t)
{
    if (t->kind == TYPEKIND_BASIC)
    {
        BasicType *b = (BasicType *)t->info;
        switch (*b)
        {
        case INT_4:
            printf("int");
            break;
        case INT_8:
            printf("long");
            break;
        case CHAR:
            printf("char");
            break;
        case FLOAT:
            printf("float");
            break;
        case DOUBLE:
            printf("double");
            break;
        case VOID:
            printf("void");
            break;
        case BASICTYPE_UNKNOWN:
            printf("unknown");
            break;
        }
    }
}

void print_basic(BasicType *b)
{
    switch (*b)
    {
    case INT_4:
        printf("int\n");
        break;
    case INT_8:
        printf("long\n");
        break;
    case CHAR:
        printf("char\n");
        break;
    case FLOAT:
        printf("float\n");
        break;
    case DOUBLE:
        printf("double\n");
        break;
    case VOID:
        printf("void\n");
        break;
    case BASICTYPE_UNKNOWN:
        printf("unknown\n");
        break;
    }
}
