#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
struct graph readGraphe(const char* fileName){
    struct graph g;
    //Premier parcours : création du graphe avec ses sommets
    FILE* f = fopen(fileName, "r");
    if(f == NULL){
        fprintf(stderr,"Could not open file %s\n",fileName);
        return g;
    }
    size_t max = 100; //max size of path to file
    char str[100]; //path to file
    int maxSommets; //nbMaxSommets found in file
    int oriente = 0; //orientation found in file
    if(fgets(str, max, f) == NULL){ //# nombre maximum de sommets
        fprintf(stderr, "Erreur lors de l'importation 0\n");
        return g;
    }
    fgets(str, max, f); //get nb sommets
    maxSommets = atoi(str);
    if(fgets(str, max, f) == NULL){ //# oriente
        fprintf(stderr, "Erreur lors de l'importation 1\n");
        return g;
    }
    fgets(str, max, f); //get orientation
    if(str[0] == 'o'){
        oriente = 1;
    }
    g = createGraphe(oriente, maxSommets);
    if(fgets(str, max, f) == NULL){ //# sommets : voisins
        fprintf(stderr, "Erreur lors de l'importation");
        return g;
    }
    while(fgets(str, max, f) != NULL) { //création des sommets
        addVertex(&g);
    }
    fclose(f);

    //Second parcours : création des arêtes du graphe
    f = fopen(fileName, "r");
    int i = 0; //variable de compteur
    for(i = 0; i<5; i++){ //on retourne aux specs des sommets
        fgets(str, max, f);
    }

    int sommet = 0; //compteur de sommet courant
    int nb = 0; //numéro de transition
    int dest[100] = {}; //tableau des destinations pour chaque arete
    int poids[100] = {}; // tableau des poids pour chaque arete
    while(fgets(str, max, f) != NULL) { //pour chaque sommet
        int j = 0; //variable compteur indice dans les deststr et poidsstr
        int l = 0; //compteur indice dans str
        int strln = strlen(str) - 1;
        while(l<strln-1) { //jusqu'à fin de ligne sommet
            //-------------------------Destination----------------------
            char deststr[NBMAXDIGITS] = ""; //string numéro de sommet destination
            char poidsstr[10] = ""; //string poids de l'arete

            while (str[l] != '(' && l<strln) { //jusqu'à (
                l++;
            }
            if(l<strln){
                l++;
            }
            j = 0;
            while (str[l] != '/' && l<strln) { //jusqu'à /
                deststr[j] = str[l];
                j++;
                l++;
            }
            if(l< strln){l++;}
            dest[nb] = atoi(deststr);
            //fprintf(stderr,"nb = %d, deststr = '%s', dest[nb] = %d, j = %d, l = %d, strlen = %d\n", nb, deststr, dest[nb], j, l, strln);
            //fprintf(stderr, "destination : %d, ", dest[nb]);
            //-------------------------Poids----------------------------
            j = 0;
            while (str[l] != ')' && l<strln) { //jusqu'à )
                poidsstr[j] = str[l];
                j++;
                l++;
            }
            poids[nb] = atoi(poidsstr);
            nb++;
        }
        for(nb = nb-1;nb>=0;nb--){ //ajout des aretes provenant du sommet courant au graphe
            addEdge(&g, sommet, dest[nb], poids[nb]);
        }
        nb = 0;
        sommet ++;
    }
    fclose(f);
    return g;
}

//inserer un nouveau sommet
/* creation d'un graphe
 * param entrée :
 * */
int addVertex(struct graph *self){
    int i = 0;
    while(belongsToGrapheState(self, i)){
        i++;
    }
    createVertex(self,i);
    return i;
}

//inserer une arete entre deux somets d'un graf
/* creation d'un graphe
 * param entrée :
 * */
int addEdge(struct graph* self, int src, int dest, int poids){
    int c = 1;
    if(belongsToGrapheEdge(self, src, dest)){
        return 3;
    }
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)) {
        c = addNode(&self->listesAdjacences[src], dest, poids);
    }
    if(!self->estOriente && !belongsToGrapheEdge(self, dest, src)){
        addEdge(self, dest, src, poids);
    }
    return c;
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
                delNode(&self->listesAdjacences[i],state);
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
        delNode(&self->listesAdjacences[src], dest);
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
    fprintf(out,"# nombre maximum de sommets\n%d\n",self->nbMaxSommets);
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
int saveGraphe(const struct graph *self, const char* fileName){
    FILE* f = fopen(fileName, "w");
    if(f == NULL){
        fprintf(stderr,"Could not open file %s\n",fileName);
        return 1;
    }
    printGraphe(self,f);
    fclose(f);
    return 0;
}

int belongsToGrapheState(const struct graph *self, int state){
    if(state < self->nbMaxSommets && !isEmptyList(&self->listesAdjacences[state])){
        return 1;
    }
    return 0;
}

int belongsToGrapheEdge(const struct graph *self, int src, int dest){
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)){
        struct list_node *tmp;
        tmp = searchNode(&self->listesAdjacences[src], dest);
        if(tmp != NULL){ //on cherche si dest existe dans la liste des successeurs de src
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