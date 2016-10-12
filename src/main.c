#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"
#include "../include/libgraphe.h"
//TODO del these two libs that shoult not be called directly

#include "../include/main.h"

int main()
{
  //----------------------Tests listes--------------------
  /*struct list ma_liste = createList();
  addNode(&ma_liste, 3, 8);
  addNode(&ma_liste, 0, 2);
  addNode(&ma_liste, 2, 4);
  printf("Liste 1 : %s", listToString(&ma_liste));
  delNodeAfter(ma_liste.first);
  delNodeAfter(ma_liste.first->next); //Del after last node
  delFirstNode(&ma_liste);
  isEmptyList(&ma_liste);
  listSize(&ma_liste);
  addNode(&ma_liste, 5, 4);
  searchNode(&ma_liste, 5); //Search existing
  searchNode(&ma_liste, 7); //Search non existing node
  printf("Liste 2 : %s", listToString(&ma_liste));
  //nodeToString(ma_liste.first->next);
  destroyList(&ma_liste);*/

  //----------------------Tests graphes--------------------
  struct graph mon_graphe = createGraphe(1,9);
  addVertex(&mon_graphe);
  addVertex(&mon_graphe);
  addVertex(&mon_graphe);
  addVertex(&mon_graphe);
  addEdge(&mon_graphe, 0, 1, 42);
  addEdge(&mon_graphe, 3, 2, 6);
  addEdge(&mon_graphe, 3, 3, 5);
  addEdge(&mon_graphe, 2, 0, 3);
  saveGraphe(&mon_graphe,"grafPrint"); //TODO test with empty graf
  printGraphe(&mon_graphe, NULL);
  addEdge(&mon_graphe, 6, 7, 4); //add edge to src/dest that doesn't exist
  delVertex(&mon_graphe, 1);
  delVertex(&mon_graphe, 10); //del vertex that doesn't exist
  delEdge(&mon_graphe, 3, 2);
  delEdge(&mon_graphe, 2, 2); //del edge that doesn't exist
  delEdge(&mon_graphe, 7, 2); //del edge that doesn't exist on vertex non existant
  destroyGraphe(&mon_graphe);
  return 0;
}