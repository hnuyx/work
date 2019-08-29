/* test
 *
 * */

#include <stdio.h>

#include "hl-sigle-list.h"

void test_hlsl_list()
{
    hlsl_init_pool();
    int i = 0;

    HLSList list = {0};
    HLSLElem *elem;
    while(elem = hlsl_get_free_elem_from_pool())
    {
        elem->value = ++ i;
        hlsl_push_back(&list, elem);
    }

    while(elem = hlsl_pop_front(&list))
    {
        printf("%d ", elem->value);
        hlsl_free_elem_to_pool(elem);
    }
    printf("\n");
}

void test_hlsl_list_n(int n)
{
    for(int i = 0; i < n; i ++)
    {
        test_hlsl_list();
    }
}

int main()
{
    test_hlsl_list();
    test_hlsl_list_n(10);

    return 0;
}
