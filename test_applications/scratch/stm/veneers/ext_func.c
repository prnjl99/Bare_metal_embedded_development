#include "startup.h"
#include "common.h"
#include "gpio.h"

int extern_file_scope_var = 0;
__attribute__((section(".veneer"))) int extern_function(int p1)
{
    (void)p1;

    return 1;
};
