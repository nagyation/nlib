#include <stdio.h>
#include <stdlib.h>

#include "nlist.h"

struct xy {
    int x;
};

default_checker_nlist(nlist_check, struct xy, x, int);
default_compare_nlist(nlist_compare, struct xy, x);
default_cleanup_nlist(nlist_cleanup);
    
int main()
{
  nlist_t stack;
  struct xy *z,*y, *l, *o, **p;
  z = malloc(sizeof(struct xy));
  y = malloc(sizeof(struct xy));
  l = malloc(sizeof(struct xy));
  o = malloc(sizeof(struct xy));
  z->x = 5;
  y->x = 6;
  l->x = 15;
  o->x = 25;
  stack = new_nlist(nlist_check, nlist_compare, nlist_cleanup);
  add_sorted_nlist(stack, y);
  add_sorted_nlist(stack, l);
  add_sorted_nlist(stack, z);
  /* remove_nlist(stack, (void *) &y->x); */
  /* /\* sort_nlist(stack); *\/ */
  /* add_sorted_nlist(stack, o); */

  for_each_nlist(stack, struct xy, p) {
      printf("%d\n", (*p)->x);
  }
  /* int oe = 15; */
  /* o = search_nlist(stack, (void *) &oe); */
  /* printf("%d\n", o->x); */
  /* o = peak_nlist(stack); */
  /* printf("%d\n", o->x); */
  while(!is_empty_nlist(stack)){
    int t;
    t = *((int*)dequeue_nlist(stack));
    printf("%d\n", t);
  }

}
