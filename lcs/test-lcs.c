
#include <stdio.h>
#include <string.h>

#include "hl-sigle-list.h"

int test_lcs(const char *src, const char *dest)
{
    int m = strlen(src);
    int n = strlen(dest);
    if(m == 0 || n == 0) return 0;

    HLSList list = {0};
    HLSLElem *elem;
    int ret = 0;

    // init list
    elem = hlsl_get_free_elem_from_pool();
    if(!elem) return 0;

    elem->midx = 0;
    elem->nidx = 0;
    if(src[0] == dest[0])
    {
        elem->value = 1;
        ret = 1
    }
    else
    {
        elem->value = 0;
    }
    hlsl_push_back(&list, elem);

    while(elem = hlsl_pop_front(&list))
    {

        hlsl_free_elem_to_pool(elem);
    }

    return ret;
}

int main()
{
    return 0;
}
