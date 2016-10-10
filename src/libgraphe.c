#include <stdio.h>
#include <stdlib.h>

#include "../include/libgraphe.h"
#include "../include/libliste.h"

/* creation d'un graphe
 * param entrée :
 * retourne :
 * */
struct graph createGraphe(int oriente, int maxSommets){
    struct graph self;
    self.listesAdjacences = calloc(maxSommets, sizeof(struct list));
    self.estOriente = oriente;
    self.nbMaxSommets = maxSommets;
    int i = 0;
    for(i; i<maxSommets; i++){
        self.listesAdjacences[i] = createList();
        //fprintf(stderr,"DEBUG createGraf : self.listesAdjacences[%i] = %p\n", i, &self.listesAdjacences[i]);
    }
    return self;
}

/* creation d'un graphe
 * param entrée :
 * */
void destroyGraphe(struct graph *self){
    int i = 0;
    for(i; i<self->nbMaxSommets; i++){ //on désalloue chaque liste
        destroyList(&self->listesAdjacences[i]);
    }
    free(self->listesAdjacences);
}

/* creation d'un graphe
 * param entrée :
 * */
void createVertex(struct graph *self, int sommet){
    //TODO check sommet is < nbMaxSommets
    addNode(&self->listesAdjacences[sommet],-1, 0);
}

//lecture d'un graphe dans un fichier texte
/* creation d'un graphe
 * param entrée :
 * */
void readGraphe(const char* fileName){
    
}

//inserer un nouveau sommet
/* creation d'un graphe
 * param entrée :
 * */
void addVertex(struct graph *self){
    //TODO check il reste au moins un sommet à attribuer
    int i = 0;
    while(i < self->nbMaxSommets && self->listesAdjacences[i].first != NULL){
        i++;
    }
    createVertex(self,i);
}

//inserer une arete entre deux somets d'un graf
/* creation d'un graphe
 * param entrée :
 * */
void addEdge(struct graph* self, int src, int dest, int poids){
    //TODO check src and dest are existing states
    addNode(&self->listesAdjacences[src],dest,poids);
}

//supprimer un sommet
/* creation d'un graphe
 * param entrée :
 * */
void delVertex(struct graph *self, int state){
    //TODO check state exists
    destroyList(&self->listesAdjacences[state]);
    int i = state;
    for(i;i<self->nbMaxSommets-1; i++){ //on décale les sommets placés après celui qui vient d'être supprimé
        self->listesAdjacences[i] = self->listesAdjacences[i+1];
    }
    //TODO check if every table case contained a list, what happens with the last one
    self->nbMaxSommets--;
}

//supprimer une arete entre deux sommets d'un graphe
/* creation d'un graphe
 * param entrée :
 * */
void delEdge(struct graph *self, int src, int dest){
    //TODO check src and dest are existing states
    struct list_node node = searchNode(&self->listesAdjacences[src], dest);
    //TODO check node != NULL
    delNodeAfter(&node);
}

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
/* creation d'un graphe
 * param entrée :
 * */
void printGraphe(const struct graph *self, const char* fileName){
    
}

//enregistrer le graf dans un fichier texte
/* creation d'un graphe
 * param entrée :
 * */
void saveGraphe(const struct graph *self, const char* fileName){
    FILE* f = fopen(fileName, "w");
    if(f == NULL){
        fprintf(stderr,"Could not open file %s\n",fileName);
        return;
    }
    fputs("# nombre maximum de sommets\n", f);
    /*char* str;
    sprintf(str, "%i", self->nbMaxSommets);
    fputs(str, f);*/
    fputs("# oriente\n", f);
    if(self->estOriente == 0){
        fputs("n\n", f);
    }
    else{
        fputs("o\n", f);
    }
    fputs("# sommets : voisins\n", f);
    int i = 0;
    while(i<self->nbMaxSommets && self->listesAdjacences[i].first != NULL){
        char* str;
        //sprintf(str, "%i : %s", i, listToString(&self->listesAdjacences[i]));
        sprintf(str, "%i : temporary", i);
        //TODO debug this is causing listesAdjacence to lose their values
        //printf("listToString %s", listToString(&self->listesAdjacences[i]));
        //fputs(str, f);
        //printf("test\n");
        i++;
    }

    fclose(f);
}