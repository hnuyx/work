/* list
 * thread-unsafe
 *
 * base template of list for c
 * */

#ifndef __HL_SIGLE_LIST_H__
#define __HL_SIGLE_LIST_H__

#pragma pack(push, 4)
// sigle-linked list element
typedef struct _HL_SL_ELEM
{
    int midx;
    int nidx;
    int value;
    struct _HL_SL_ELEM *next;
} HLSLElem;

// sigle-linked list
typedef struct _HL_SLIST
{
    HLSLElem *head;
    HLSLElem *tail;
} HLSList;
#pragma pack(pop)

/* add element in single-linked list's back
 * list: list of single-linked list
 * elem: element of single-linked list
 *
 * return 0 for success, 01 for failed
 * */
int hlsl_push_back(HLSList *list, HLSLElem *elem);

/* pop element from single-linked list's head
 * list: list of single-linked list
 *
 * return non-null for success, null for failed
 * */
HLSLElem* hlsl_pop_front(HLSList *list);

/* init single-linked list pool
 *
 * return 0 for success, -1 for failed
 * */
int hlsl_init_pool();

/* get free single-linked list element
 *
 * return non-null for success, null for failed
 * */
HLSLElem* hlsl_get_free_elem_from_pool();

/* free single-linked list element
 * elem: sigle-linked list element
 *
 * return 0 for success, -1 for failed
 * */
int hlsl_free_elem_to_pool(HLSLElem *elem);

#endif

