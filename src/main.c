#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"
#include "../include/libgraphe.h"
//TODO del these two libs that shoult not be called directly

#include "../include/main.h"

int main()
{
  //----------------------Tests listes--------------------
  struct list ma_liste = createList();
  addNode(&ma_liste, 3, 8);
  addNode(&ma_liste, 0, 2);
  addNode(&ma_liste, 2, 4);
  delNodeAfter(ma_liste.first);
  //delNodeAfter(ma_liste.first->next); //Del after last node
  delFirstNode(&ma_liste);
  visitList(&ma_liste);
  isEmptyList(&ma_liste);
  listSize(&ma_liste);
  addNode(&ma_liste, 5, 4);
  searchNode(&ma_liste, 5); //Search existing
  searchNode(&ma_liste, 7); //Search non existing node
  listToString(&ma_liste);
  nodeToString(ma_liste.first->next);
  destroyList(&ma_liste);

  //----------------------Tests graphes--------------------
  /*struct graph mon_graphe = createGraphe(1,9);
  addVertex(&mon_graphe);
  addVertex(&mon_graphe);
  addEdge(&mon_graphe, 0, 1, 4);
  //save(&mon_graphe, "graphe"); //TODO shit happens again
  destroyGraphe(&mon_graphe);*/
  return 0;
}