#include <stdlib.h>

#include "nlist.h"

#include <stdio.h>

struct nlist_struct* new_nlist(enum nlist_type type)
{
  struct nlist_struct * list;
  list = malloc(sizeof(struct nlist_struct));
  list->node = NULL;
  list->type = type;

  return list;
}

void add_data_nlist(struct nlist_struct *nlist, void *data)
{
  struct nlist_node_struct *item = malloc(sizeof(struct nlist_node_struct));

  if(nlist->node == NULL) /* If the list is empty */
    {
      item->data = data;
      item->prev = NULL;
      item->next = NULL;
      nlist->node = item;
      return;
    }

  switch(nlist->type){
  case LIST:                    /* will treat list by default as stack */
  case STACK:
    item->data = data;
    item->next = nlist->node;
    item->prev = NULL;
    nlist->node->prev =item;
    nlist->node = item;
    break;

  case QUEUE:                   /* not yet implemented */
    break;
  }

}

int remove_data_nlist(struct nlist_struct *nlist, int (*remove_check) (void *data))
{
  struct nlist_node_struct *current = nlist->node, *tmp;
  while(current != NULL)
    {
      if(remove_check(current->data))
        {
          if(current->prev == NULL) // first element
            {
              nlist->node = current->next;
              nlist->node->prev = NULL;
              free(current->data);
              free(current);
              return 1;
            }
          tmp = current;
          current->prev->next = current->next;
          current->next->prev = current->prev;
          free(tmp->data);
          free((void *) tmp);
          return 1;
        }
      current = current->next;
    }
  return 0;
}

void * search_data_nlist(struct nlist_struct *nlist, int (*search_check) (void *data))
{
  struct nlist_node_struct *current = nlist->node;
  while(current != NULL)
    {
      if(search_check(current->data))
        {
          return current->data;
        }
      current = current->next;
    }
  return 0;
}

int is_empty_nlist(struct nlist_struct *nlist)
{
  if(nlist == NULL) /* to differentiate between empty and not initialized list */
    return -1;
  else if (nlist->node == NULL)
    return 1;
  return 0;
}

void * pop_data_nlist(struct nlist_struct *nlist)
{
  if(nlist->node == NULL)
    return NULL;

  struct nlist_node_struct *tmp;
  void *data;
  data = nlist->node->data;
  tmp = nlist->node;
  nlist->node = nlist->node->next;

  if(nlist->node)               /* If not null */
    nlist->node->prev = NULL;

  free(tmp);
  return data;
}

void * peak_data_nlist(struct nlist_struct *nlist)
{
  if(nlist->node == NULL)
    return NULL;
  return nlist->node->data;
}

int get_count_nlist(struct nlist_struct *nlist)
{
  struct nlist_node_struct *current = nlist->node;
  int count = 0;
  while(current != NULL)
    {
      current = current->next;
      count++;
    }
  return count;
}

void free_nlist(struct nlist_struct *nlist)
{
  struct nlist_node_struct *current = nlist->node, *tmp;
  while(current != NULL)
    {
      tmp = current;
      current = current->next;
      free(tmp->data);
      free((void *) tmp);
    }
  free(nlist);
}
