#include <stdio.h>
#include <stdlib.h>

#include "../include/libgraphe.h"
#include "../include/libliste.h"

//création du graphe avec un nombre de sommet demandé
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

void destroyGraphe(struct graph *self){
    int i = 0;
    for(i; i<self->nbMaxSommets; i++){ //on désalloue chaque liste
        destroy(&self->listesAdjacences[i]);
    }
    free(self->listesAdjacences);
}

void createVertex(struct graph *self, int sommet){
    add(&self->listesAdjacences[sommet],-1, 0);
    //TODO check sommet < nbMaxSommets
}

//lecture d'un graphe dans un fichier texte
void read(const char* fileName){
    
}

//inserer un nouveau sommet
void addVertex(struct graph *self){
    //TODO check il reste au moins un sommet à attribuer
    int i = 0;
    while(i < self->nbMaxSommets && self->listesAdjacences[i].first != NULL){
        i++;
    }
    createVertex(self,i);
}

//inserer une arete entre deux somets d'un graf
void addEdge(struct graph* self, int src, int dest, int poids){
    add(&self->listesAdjacences[src],dest,poids);
}

//supprimer un sommet
void delVertex(struct graph *self, int v){
    destroy(&self->listesAdjacences[v]);
    int i = v;
    for(i;i<self->nbMaxSommets-1; i++){ //on décale les sommets placés après celui qui vient d'être supprimé
        self->listesAdjacences[i] = self->listesAdjacences[i+1];
    }
    //TODO check if every table case contained a list, what happens with the last one
    self->nbMaxSommets--;
}

//supprimer une arete entre deux sommets d'un graphe
void delEdge(struct graph *self, int src, int dest){
    struct list_node node = search(&self->listesAdjacences[src], dest);
    delAfter(&node);
}

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
void print(const struct graph *self, const char* fileName){
    
}

//enregistrer le graf dans un fichier texte
void save(const struct graph *self, const char* fileName){
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