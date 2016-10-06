#include <stdio.h>
#include <stdlib.h>

#include "../include/libgraphe.h"
#include "../include/libliste.h"

//création du graphe avec un nombre de sommet demandé
struct TypGraphe createGraphe(int oriente, int maxSommets){
    struct TypGraphe self;
    self.estOriente = oriente;
    self.nbMaxSommets = maxSommets;
    int i = 0;
    for(i; i<maxSommets; i++){ //on initialise le tableau de listes avec pour chaque sommet du graphe une liste terminant par -1
        createVertex(&self, i);
    }
}

void destroyGraphe(struct TypGraphe *self){
    int i = 0;
    for(i; i<self->nbMaxSommets; i++){ //on désalloue chaque liste
        destroy(&self->listesAdjacences[i]);
    }
}

void createVertex(struct TypGraphe *self, int sommet){
    struct list list = createList();
    add(&list,-1, NULL);
    self->listesAdjacences[sommet] = list;
}

//lecture d'un graphe dans un fichier texte
void read(const char* fileName){
    
}

//inserer un nouveau sommet
void addVertex(struct TypGraphe *self){
    self->nbMaxSommets ++;
    createVertex(self,self->nbMaxSommets-1);
}

//inserer une arete entre deux somets d'un graf
void addEdge(struct TypGraphe* self, int src, int dest, int poids){
    add(&self->listesAdjacences[src],dest,poids);
}

//supprimer un sommet
void delVertex(struct TypGraphe *self, int v){
    destroy(&self->listesAdjacences[v]);
    int i = v;
    for(i;i<self->nbMaxSommets-1; i++){ //on décale les sommets placés après celui qui vient d'être supprimé
        self->listesAdjacences[i] = self->listesAdjacences[i+1];
    }
    //TODO check if every table case contained a list, what happens with the last one
    self->nbMaxSommets--;
}

//supprimer une arete entre deux sommets d'un graphe
void delEdge(struct TypGraphe *self, int src, int dest){
    struct list_node node = search(&self->listesAdjacences[src], dest);
    delAfter(&node);
}

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
void print(const struct TypGraphe self, const char* fileName){
    
}

//enregistrer le graf dans un fichier texte
void save(const struct TypGraphe self, const char* fileName){
    
}