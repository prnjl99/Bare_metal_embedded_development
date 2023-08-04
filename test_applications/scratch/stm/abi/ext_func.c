#include "startup.h"
#include "common.h"
#include "gpio.h"
#include "main.h"

int callee(int a, int b, int c, long long int d)
{
    (void)a;
    (void)b;
    (void)c;
    d++;

    return d;
}

struct myStruct1Word callee1(struct myStruct1Word param)
{
    param.a++;

    return param;
}

struct myStruct7Word callee7(struct myStruct7Word param)
{
    param.a++;
    param.b++;
    param.c++;
    param.d++;
    param.e++;
    param.f++;
    param.g++;

    return param;
}
