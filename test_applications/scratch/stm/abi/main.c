/* https://embeddedsecurity.io/sec-arm-abi#passing-arguments */

/* Observe caller function dissassembly in <ROOT_DIR>/test_applications/build/stm/$(APP)/$(APP).s */

#include "startup.h"
#include "common.h"
#include "gpio.h"
#include "main.h"

extern struct myStruct1Word callee1(struct myStruct1Word);
extern struct myStruct7Word callee7(struct myStruct7Word);
extern int callee(int a, int b, int c, long long int d);

void caller1(void)
{
    struct myStruct1Word s;
    s.a = 1111;
    callee1(s);
    struct myStruct7Word t;
    t.a = 2222;
    t.g = 0xFF;
    callee7(t);
}

void caller(void)
{
    callee(0,1,2,3);
}

int main()
{
    caller();
    caller1();
}

void User_intr_handler(void)
{
    while(1){};
}

