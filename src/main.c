#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"
#include "../include/libgraphe.h"

int main()
{
  struct list ma_liste = createList();
  add(&ma_liste, 3);
  add(&ma_liste, 2);
  add(&ma_liste, 42);
  visit(&ma_liste);
  //size(&ma_liste); SHIT HAPPENS
  search(&ma_liste,2);
  //delAfter(ma_liste.first->next); SHIT HAPPENS, and one extra free
  destroy(&ma_liste);

  return 0;
}