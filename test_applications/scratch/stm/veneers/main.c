/* https://embeddedsecurity.io/sec-c#sec:c-veneers */

/* Observe generated veneer in <ROOT_DIR>/test_applications/build/stm/$(APP)/$(APP).s */

#include "startup.h"
#include "common.h"
#include "gpio.h"

int global_linkage_file_scope_var = 1;
extern int extern_file_scope_var;
static int static_file_scope_defined_var = 3;

extern int extern_function(int p1) __attribute__((section(".veneer")));

int main()
{
        int local_var = extern_function( extern_file_scope_var) + extern_function(static_file_scope_defined_var);
        return local_var;
}

void User_intr_handler(void)
{
    while(1){};
}

