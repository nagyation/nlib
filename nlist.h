#ifndef __NLIST__
#define __NLIST__

#include <stddef.h>

typedef enum {
    NLIST_NOTINIT = -1,
    NLIST_FALSE,
    NLIST_TRUE,
} nlist_err_t;

typedef nlist_err_t (*nlist_checker_t) (void *, void*);
typedef nlist_err_t (*nlist_compare_t) (void *, void*);
typedef void (*nlist_cleanup_t) (void *);

enum nlist_type {
    NLIST_LIST = 0,
    NLIST_STACK,
    NLIST_QUEUE,          /* not implemented yet */
};

struct nlist_node_t {
    void * data;
    struct nlist_node_t *next, *prev;
};

typedef struct nlist_node_t nlist_node_t;

typedef struct {
    nlist_node_t *head;
    enum nlist_type type;
    nlist_checker_t check;
    nlist_compare_t compare;
    nlist_cleanup_t clean;
} *nlist_t;

#define get_node_nlist(pdata) (( nlist_node_t *)((char *)pdata - offsetof( nlist_node_t, data)))
#define for_each_nlist(list, type, pdata)                               \
    for(pdata = (type **) &list->head->data; pdata != NULL;             \
        pdata = &get_node_nlist(pdata)->next != NULL ? (type **) &get_node_nlist(pdata)->next->data : NULL)

nlist_t new_nlist(enum nlist_type, nlist_checker_t check, nlist_compare_t compare);
void add_nlist(nlist_t nlist, void *data);
void add_sorted_nlist( nlist_t nlist, void *data);
nlist_err_t remove_nlist(nlist_t nlist, void *value);
void remove_node_nlist(nlist_t nlist, nlist_node_t *node);
void *search_nlist(nlist_t nlist, void *value);
void *pop_nlist(nlist_t nlist);
void *peak_nlist(nlist_t nlist);
void *dequeue_nlist(nlist_t nlist);    /* not implemented yet */
nlist_err_t is_empty_nlist(nlist_t nlist);
size_t get_count_nlist(nlist_t nlist);
void free_nlist(nlist_t nlist);
void sort_nlist(nlist_t nlist);

#define default_checker_nlist(checker_name, data_type, member, member_type) static nlist_err_t checker_name(void *data, void *value) \
    {                                                                   \
        if (((data_type * ) data)->member == *((member_type *) value))  \
            return NLIST_TRUE;                                          \
        return NLIST_FALSE;                                             \
    }                                                                   \


#define default_compare_nlist(compare_name, data_type, member) static nlist_err_t compare_name(void *d1, void *d2) \
    {                                                                   \
        if (((data_type * ) d1)->member > ((data_type * ) d2)->member)  \
            return NLIST_TRUE;                                          \
        return NLIST_FALSE;                                             \
    }                                                                   \

#define default_cleanup_nlist(cleanup_name) static void cleanup_name(void *data) \
    {                                                                   \
        free(data);                                                     \
    } 

#define CHECKER_NLIST(checker_name, hay, needle) nlist_err_t checker_name(void *hay, void *needle)
#define COMPARE_NLIST(compare_name, big, small) nlist_err_t compare_name(void *big, void *small)
#define CLEANUP_NLIST(cleanup_name, data) void cleanup_name(void *data)

#endif
