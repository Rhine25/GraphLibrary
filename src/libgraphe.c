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
    for(i=0; i<maxSommets; i++){
        self.listesAdjacences[i] = createList();
    }
    return self;
}

/* creation d'un graphe
 * param entrée :
 * */
void destroyGraphe(struct graph *self){
    int i = 0;
    for(i=0; i<self->nbMaxSommets; i++){ //on désalloue chaque liste
        destroyList(&self->listesAdjacences[i]);
    }
    free(self->listesAdjacences);
    self->listesAdjacences = NULL;
}

/* creation d'un graphe
 * param entrée :
 * */
void createVertex(struct graph *self, int sommet){
    if(sommet<self->nbMaxSommets && isEmptyList(&self->listesAdjacences[sommet])) {
        addNode(&self->listesAdjacences[sommet], -1, 0);
    }
}

//lecture d'un graphe dans un fichier texte
/* creation d'un graphe
 * param entrée :
 * */
void readGraphe(const char* fileName){
    //TODO
}

//inserer un nouveau sommet
/* creation d'un graphe
 * param entrée :
 * */
void addVertex(struct graph *self){
    //TODO check what happens when graf has max sommets attribués
    int i = 0;
    while(belongsToGrapheState(self, i)){
        i++;
    }
    createVertex(self,i);
}

//inserer une arete entre deux somets d'un graf
/* creation d'un graphe
 * param entrée :
 * */
void addEdge(struct graph* self, int src, int dest, int poids){
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)) {
        addNode(&self->listesAdjacences[src], dest, poids);
    }
    if(self->estOriente && !belongsToGrapheEdge(self, dest, src)){
        addEdge(self, dest, src, poids);
    }
}

//supprimer un sommet
/* creation d'un graphe
 * param entrée :
 * */
void delVertex(struct graph *self, int state){
    if(belongsToGrapheState(self, state)) {
        int i;
        for(i = 0; i<self->nbMaxSommets; i++){
            if(!isEmptyList(&self->listesAdjacences[i])){
                delNodeAfter(searchNode(&self->listesAdjacences[i],state));
            }
        }
        destroyList(&self->listesAdjacences[state]);
    }
}

//supprimer une arete entre deux sommets d'un graphe
/* creation d'un graphe
 * param entrée :
 * */
void delEdge(struct graph *self, int src, int dest){
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)) {
        struct list_node *node = searchNode(&self->listesAdjacences[src], dest);
        delNodeAfter(node);
    }
    if(self->estOriente){
        delEdge(self, dest, src);
    }
}

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
/* creation d'un graphe
 * param entrée :
 * */
void printGraphe(const struct graph *self, FILE* out){
    if(out == NULL){
        out = stdout;
    }
    fprintf(out,"# nombre maximum de sommets\n");
    fprintf(out,"# oriente\n");
    if(self->estOriente == 0) {
        fprintf(out,"n\n");
    }
    else{
        fprintf(out,"o\n");
    }
    fprintf(out,"# sommets : voisins\n");
    int i = 0;
    while(belongsToGrapheState(self, i)) {
        fprintf(out,"%i : %s", i, listToString(&self->listesAdjacences[i]));
        i++;
    }
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
    printGraphe(self,f);
    fclose(f);
}

int belongsToGrapheState(const struct graph *self, int state){
    if(state < self->nbMaxSommets && !isEmptyList(&self->listesAdjacences[state])){
        return 1;
    }
    return 0;
}

int belongsToGrapheEdge(const struct graph *self, int src, int dest){
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)){
        if(searchNode(&self->listesAdjacences[src], dest)->next->state == dest){ //on cherche si dest existe dans la liste des successeurs de src
            return 1;
        }
    }
    return 0;
}

int isEmptyGraphe(const struct graph *self){
    int i;
    for(i=0;i<self->nbMaxSommets;i++){
        if(belongsToGrapheState(self,i)){
            return 1;
        }
    }
    return 0;
}