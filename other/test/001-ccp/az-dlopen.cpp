
#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *pv = dlopen("/data/quant/lib/libLMQuant.so", RTLD_NOW | RTLD_LOCAL);
    printf("%x\n", pv);
    printf("%s\n", dlerror());

    return 0;
}
