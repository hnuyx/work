/* list
 *
 * base template of list for c
 * */

#include <stdio.h>

#include "hl-sigle-list.h"

#define HL_SIGLE_LIST_ELEMENT_MAX_SIZE   100

HLSLElem g_pool_hlsl_elems[HL_SIGLE_LIST_ELEMENT_MAX_SIZE] = {0};

static HLSList pool = {0};

/* add element in single-linked list's back
 * list: list of single-linked list
 * elem: element of single-linked list
 *
 * return 0 for success, 01 for failed
 * */
int hlsl_push_back(HLSList *list, HLSLElem *elem)
{
    if(!elem)
        return 0;

    elem->next = NULL;
    if(!list->tail)
    {
        list->head = list->tail = elem;
        return 0;
    }

    list->tail->next = elem;
    list->tail = elem;

    return 0;
}

/* pop element from single-linked list's head
 * list: list of single-linked list
 *
 * return non-null for success, null for failed
 * */
HLSLElem* hlsl_pop_front(HLSList *list)
{
    HLSLElem *ret = list->head;
    if(!ret)
        return NULL;

    list->head = list->head->next;
    if(!list->head)
        list->tail = NULL;

    return ret;
}


/* init single-linked list pool
 *
 * return 0 for success, -1 for failed
 * */
int hlsl_init_pool()
{
    pool.head = &g_pool_hlsl_elems[0];
    pool.tail = &g_pool_hlsl_elems[HL_SIGLE_LIST_ELEMENT_MAX_SIZE - 1];
    for(int i = 1; i < HL_SIGLE_LIST_ELEMENT_MAX_SIZE; i ++)
    {
        g_pool_hlsl_elems[i - 1].next = &g_pool_hlsl_elems[i];
    }
    pool.tail->next = NULL;

    return 0;
}

/* get free single-linked list element
 *
 * return non-null for success, null for failed
 * */
HLSLElem* hlsl_get_free_elem_from_pool()
{
    return hlsl_pop_front(&pool);
}

/* free single-linked list element
 * elem: sigle-linked list element
 *
 * return 0 for success, -1 for failed
 * */
int hlsl_free_elem_to_pool(HLSLElem *elem)
{
    return hlsl_push_back(&pool, elem);
}

