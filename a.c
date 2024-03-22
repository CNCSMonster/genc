#include <klee/klee.h>
#include "genc.inc"
int main()
{
    BasicType b = klee_range(0, 5, "b");
    print_basic(&b);
}