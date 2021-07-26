#include <stdlib.h>

static void test_assert(bool b)
{
    if (!b)
    {
        exit(1);
    }
}