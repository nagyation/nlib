#ifndef __NLIST__
#define __NLIST__

/*
  TODO: ease the use of lamda
 */

enum nlist_type {
                LIST=0,
                STACK,
                QUEUE,          /* Not implemented yet */
};

struct nlist_node_struct {
  void * data;
  struct nlist_node_struct * next, *prev;
};

struct nlist_struct {
  struct nlist_node_struct *node;
  enum nlist_type type;
};

/*
#define _get_node(pdata) struct nlist_node_struct *(pdata - offset(nlist_node_struct,data))

#define for_each_nlist(list, pdata) for(pdata=list->node->data; _get_node(pdata) != NULL; pdata = _get_node(pdata)->next->data)
*/

struct nlist_struct* new_nlist(enum nlist_type);
void add_data_nlist(struct nlist_struct *nlist, void *data);
int remove_data_nlist(struct nlist_struct *nlist, int (*remove_check) (void *data));
void * search_data_nlist(struct nlist_struct *nlist, int (*search_check) (void *data));
void * pop_data_nlist(struct nlist_struct *nlist);
void * peak_data_nlist(struct nlist_struct *nlist);
void * dequeue_nlist(struct nlist_struct *nlist);          /* Will Not be implemented now */
int is_empty_nlist(struct nlist_struct *nlist);
int get_count_nlist(struct nlist_struct *nlist);
void free_nlist(struct nlist_struct *nlist);

#endif
