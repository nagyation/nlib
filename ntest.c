#include <stdio.h>
#include <stdlib.h>

#include "nlist.h"

int main()
{
  struct nlist_struct *stack;
  int x, y;
  x = 5;
  y = 3;
  stack = new_nlist(STACK);
  add_data_nlist(stack, &x);
  pop_data_nlist(stack);
  add_data_nlist(stack, &y);
  add_data_nlist(stack, &x);
  
  /* struct nlist_struct *p; */
  /*   for_each_nlist(stack, p){ */
  /*   printf("%d\n",*(int *)p->data); */
  /* } */

  while(!is_empty_nlist(stack)){
    int z;
    z = *((int*)pop_data_nlist(stack));
    printf("%d\n", z);
  }

}
