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
void readGraphe(const char* fileName, struct graph* graphe){

    //Premier parcours : création du graphe avec ses sommets
    FILE* f = fopen(fileName, "r");
    if(f == NULL){
        fprintf(stderr,"Could not open file %s\n",fileName);
        return;
    }
    size_t max = 100; //max size of path to file
    char str[100]; //path to file
    int maxSommets; //nbMaxSommets found in file
    int oriente = 0; //orientation found in file
    if(fgets(str, max, f) == NULL){ //# nombre maximum de sommets
        fprintf(stderr, "Erreur lors de l'importation 0\n");
        return;
    }
    fgets(str, max, f); //get nb sommets
    maxSommets = atoi(str);
    if(fgets(str, max, f) == NULL){ //# oriente
        fprintf(stderr, "Erreur lors de l'importation 1\n");
        return;
    }
    fgets(str, max, f); //get orientation
    if(strcmp(str,"o") == 0){
        oriente = 1;
    }
    struct graph g = createGraphe(oriente, maxSommets);
    graphe = &g;
    if(fgets(str, max, f) == NULL){ //# sommets : voisins
        fprintf(stderr, "Erreur lors de l'importation");
        return;
    }
    while(fgets(str, max, f) != NULL) { //création des sommets
        addVertex(graphe);
    }
    fclose(f);

    //Second parcours : création des arêtes du graphe
    f = fopen(fileName, "r");
    int i = 0; //variable de compteur
    int sommet = 0; //compteur de sommet courant
    for(i = 0; i<4; i++){ //on retourne aux specs des sommets
        fgets(str, max, f);
    }

    /*Pour chaque sommet : OK
        * jusqu'à tomber la fin de ligne : OK
            * cherche une ( OK
            * lis la valeur jusqu'à / et stocke dans dest tab OK
            * lis la valeur jusqu'à ) et stocke dans poids tab
     * création des aretes depuis la fin des tableaux
     * */
    while(fgets(str, max, f) != NULL) { //pour chaque sommet
        int dest[100]; //tableau des destinations pour chaque arete
        int poids[100]; // tableau des poids pour chaque arete
        int nb = 0; //numéro de transition
        int j = 0; //variable compteur
        int tmp; //debug
        while((tmp=fgetc(f)) != '\n') { //jusqu'à fin de ligne sommet
            fprintf(stderr,"Cherche fin de ligne : '%c'\n", (unsigned char)tmp);
            //-------------------------Destination----------------------
            char deststr[NBMAXDIGITS] = ""; //string numéro de sommet destination
            char poidsstr[10] = ""; //string poids de l'arete
            while ((tmp = fgetc(f)) != '(' && tmp != EOF) { //jusqu'à (
                fprintf(stderr,"Cherche '(' : '%c'\n", (unsigned char)tmp);
            }
            fprintf(stderr,"Found '(' : '%c'\n", (unsigned char)tmp);
            while ((tmp = fgetc(f)) != '/' && tmp != EOF) { //jusqu'à /
                fprintf(stderr,"Cherche '/' : '%c'\n", (unsigned char)tmp);
                deststr[j] = tmp;
                j++;
            }
            dest[nb] = atoi(deststr);
            fprintf(stderr, "J'ai trouvé comme destination : %d\n", dest[nb]);
            //-------------------------Poids----------------------------
            j = 0;
            while ((tmp = fgetc(f)) != ')') { //jusqu'à )
                fprintf(stderr,"Cherche ')' : '%c'\n", (unsigned char)tmp);
                poidsstr[j] = tmp;
                j++;
            }
            poids[nb] = atoi(poidsstr);
            nb++;
        }
        for(;nb>=0;nb--){ //ajout des aretes provenant du sommet courant au graphe
            addEdge(graphe, sommet, dest[nb], poids[nb]);
        }
        sommet ++;
    }
    printGraphe(graphe,stdout);
    /*
    # nombre maximum de sommets
    4
    # oriente
    n
    # sommets : voisins
    0 : (2/4), (-1/0)
    1 : (3/5), (-1/0)
    2 : (3/3), (0/4), (-1/0)
    3 : (1/5), (2/3), (-1/0)
    */
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