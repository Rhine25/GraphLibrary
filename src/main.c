#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"
#include "../include/libgraphe.h"
//TODO del these two libs that shoult not be called directly

#include "../include/main.h"

int main()
{
  struct graph mon_graphe = createGraphe(1,9);
  addVertex(&mon_graphe);
  addVertex(&mon_graphe);
  addEdge(&mon_graphe, 0, 1, 4);
  //save(&mon_graphe, "graphe"); //TODO shit happens again
  destroyGraphe(&mon_graphe);
  return 0;
}