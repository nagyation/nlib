#include <stdlib.h>

#include "nlist.h"

#include <stdio.h>

nlist_t new_nlist(nlist_checker_t check,
                  nlist_compare_t compare, nlist_cleanup_t clean)
{
    nlist_t list;
    if (!clean) // must have a clean function
        return NULL;
    list = malloc(sizeof(*list));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->check = check;
    list->compare = compare;
    list->clean = clean;
    return list;
}

void add_nlist(nlist_t nlist, void *data)
{
    nlist_node_t *item = malloc(sizeof(nlist_node_t));
    item->data = data;
    item->next = NULL;
    if(nlist->head == NULL) {
        item->prev = NULL;
        nlist->head = item;
        nlist->tail = item;
        return;
    }

    item->prev = nlist->tail;
    nlist->tail->next = item;
    nlist->tail = item;
}

void __remove_node(nlist_t nlist, nlist_node_t *node)
{
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        nlist->head = node->next;
        if (nlist->head)
            nlist->head->prev = NULL;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        nlist->tail = node->prev;
        if (nlist->tail)
            nlist->tail->next = NULL;
    }

    nlist->clean(node->data);
    free((void *) node);
}


nlist_err_t remove_nlist(nlist_t nlist, void *value)
{
    nlist_node_t *current = nlist->head;
    while(current != NULL) {
        if(nlist->check(current->data, value) == NLIST_TRUE) {
            __remove_node(nlist, current);
            return NLIST_TRUE;
        }
        current = current->next;
    }
    return NLIST_FALSE;
}

void remove_node_nlist(nlist_t nlist, nlist_node_t *node)
{
    __remove_node(nlist, node);
}

void * search_nlist(nlist_t nlist, void *value)
{
    nlist_node_t *cur = nlist->head;
    while(cur != NULL) {
        if(nlist->check(cur->data, value) == NLIST_TRUE) {
            return cur->data;
        }
        cur = cur->next;
    }
    return NULL;
}

nlist_err_t is_empty_nlist(nlist_t nlist)
{
    if(nlist == NULL) /* to differentiate between empty and not initialized list */
        return NLIST_NOTINIT;
    else if (nlist->head == NULL)
        return NLIST_TRUE;
    return NLIST_FALSE;
}

void *dequeue_nlist(nlist_t nlist)
{
    nlist_node_t *tmp;
    void *data;
    
    if(nlist->head == NULL)
        return NULL;

    data = nlist->head->data;
    tmp = nlist->head;
    nlist->head = nlist->head->next;

    if(nlist->head)
        nlist->head->prev = NULL;
    else
        nlist->tail = NULL;

    free(tmp);
    return data;
}

void *pop_nlist(nlist_t nlist)
{
    nlist_node_t *tmp;
    void *data;
    
    if(nlist->head == NULL)
        return NULL;

    data = nlist->tail->data;
    tmp = nlist->tail;
    nlist->tail = nlist->tail->prev;
    if(nlist->tail)
        nlist->tail->next = NULL;
    else
        nlist->head = NULL;

    free(tmp);
    return data;
}

void *peak_front_nlist(nlist_t nlist)
{
    if(nlist->head == NULL)
        return NULL;
    return nlist->head->data;
}

void *peak_back_nlist(nlist_t nlist)
{
    if(nlist->head == NULL)
        return NULL;
    return nlist->tail->data;
}

size_t get_count_nlist(nlist_t nlist)
{
    nlist_node_t *current = nlist->head;
    size_t count = 0;
    while(current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

void free_nlist(nlist_t nlist)
{
    nlist_node_t *current, *tmp;
    if (!nlist)
        return;
    current = nlist->head;
    while(current != NULL) {
        tmp = current;
        current = current->next;
        nlist->clean(tmp->data);
        free((void *) tmp);
    }
    free(nlist);
}

/* Sort functions */

void __insert_sorted_nlist(nlist_t nlist, nlist_node_t *node)
{
    nlist_node_t *cur;

    cur = nlist->head;
    while (cur != NULL) {
        if (nlist->compare(cur->data, node->data) == NLIST_TRUE) {
            node->next = cur;
            node->prev = cur->prev;
            
            if (cur->prev) // if we are in the middle
                cur->prev->next = node;
            else // this is the head
                nlist->head = node;            
            cur->prev = node;
            return;
        }
        node->prev = cur; // keep updating prev
        cur = cur->next;
    }
    // this is the largest number
    node->prev->next = node;
    node->next = NULL;
    nlist->tail = node;
}


void sort_nlist(nlist_t nlist)
{
    nlist_node_t *cur, *next;
    if (!nlist || !nlist->head)
        return;
    cur = nlist->head;
    while (cur) {
        next = cur->next;
        
        if (cur->next)
            cur->next->prev = cur->prev;
        else // tail
            nlist->tail = cur->prev;
        
        if (cur->prev)
            cur->prev->next = cur->next;
        else // the head
            nlist->head = cur->next;
        
        __insert_sorted_nlist(nlist, cur);
        cur = next;
    }
}

void add_sorted_nlist(nlist_t nlist, void *data)
{
    nlist_node_t *item = malloc(sizeof(nlist_node_t));
    item->data = data;
    item->prev = NULL;
    item->next = NULL;
    if (!nlist->head) { // if empty just insert it
        nlist->head = item;
        nlist->tail = item;
    } else
        __insert_sorted_nlist(nlist, item);
}
