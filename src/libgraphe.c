#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libgraphe.h"
#include "../include/libliste.h"

/* creation d'un graphe
 * param entrée : entier orientation, entier nombre max de sommets
 * crée le graphe, alloue la mémoire pour les listes d'adjacence
 * retourne : le graphe créé
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
 * param entrée : pointeur sur le graphe à supprimer
 * libère la mémoire des listes d'adjacence et du graphe
 * retourne : entier
 * */
int destroyGraphe(struct graph *self){
    int i = 0;
    int c = 0;
    for(i=0; i<self->nbMaxSommets; i++){ //on désalloue chaque liste
        c += destroyList(&self->listesAdjacences[i]);
    }
    free(self->listesAdjacences);
    self->listesAdjacences = NULL;
    return c;
}

/* creation d'un graphe
 * param entrée : pointeur sur le graphe, entier sommet à ajouter
 * ajoute un node à la liste d'adjacence du sommet
 * retourne : entier
 * */
int createVertex(struct graph *self, int sommet){
    if(sommet<self->nbMaxSommets && isEmptyList(&self->listesAdjacences[sommet])) {
        return addNode(&self->listesAdjacences[sommet], -1, 0);
    }
    return 1;
}

/* lecture d'un graphe dans un fichier texte
 * param entrée : le nom du fichier dans lequel est le graphe à importer
 * crée un graphe à partir d'un fichier
 * retourne le graphe
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

/* inserer un nouveau sommet
 * param entrée : pointeur sur le graphe
 * parcourt le graphe jusqu'à un sommet non attribué, crée le sommet
 * retourne : entier sommet créé
 * */
int addVertex(struct graph *self){
    int i = 0;
    while(belongsToGrapheState(self, i)){
        i++;
    }
    createVertex(self,i);
    return i;
}

/* inserer une arete entre deux sommets d'un graphe
 * param entrée : pointeur sur le graphe, entiers source destination et poids de l'arete
 * retourne : entier
 * */
int addEdge(struct graph* self, int src, int dest, int poids){
    int c = 1;
    if(belongsToGrapheEdge(self, src, dest)){
        return 3;
    }
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)) {
        c = addNode(&self->listesAdjacences[src], dest, poids);
    }
    else{
        return 1;
    }
    if(!self->estOriente && !belongsToGrapheEdge(self, dest, src)){
        addEdge(self, dest, src, poids);
    }
    return c;
}

/* supprimer un sommet
 * param entrée : pointeur sur le graphe, entier sommet à supprimer
 * libère la mémoire des nodes et des listes
 * retourne : 0 ou 1
 * */
int delVertex(struct graph *self, int state){
    if(belongsToGrapheState(self, state)) {
        int i;
        //suppression des arêtes qui vont vers le sommet à supprimer
        for(i = 0; i<self->nbMaxSommets; i++){
            if(!isEmptyList(&self->listesAdjacences[i])){
                delNode(&self->listesAdjacences[i],state);
            }
        }
        //suppression du sommet
        destroyList(&self->listesAdjacences[state]);
        return 0;
    }
    else{
        return 1;
    }
}

/* supprimer une arete entre deux sommets d'un graphe
 * param entrée : pointeur sur le graphe
 * supprime l'arete ainsi que l'arete inverse si le graphe n'est pas oriente
 * retourne : entier
 * */
int delEdge(struct graph *self, int src, int dest){
    int c = 0;
    if(belongsToGrapheState(self, src) && belongsToGrapheState(self, dest)) {
        c += delNode(&self->listesAdjacences[src], dest);
    }
    else{
        return 4;
    }
    if(!self->estOriente){
        c += delNode(&self->listesAdjacences[dest], src);
    }
    return c;
}

/* afficher le graphe dans le meme format que celui du fichier texte d'entrée
 * param entrée : pointeur sur le graphe, fichier de sortie de l'écriture
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
    for(i = 0; i<self->nbMaxSommets; i++) {
        if(belongsToGrapheState(self, i)) {
            fprintf(out, "%i : %s", i, listToString(&self->listesAdjacences[i]));
        }
    }
}

/* enregistrer le graf dans un fichier texte
 * param entrée : pointeur sur le graphe, fichier de sortie
 * ouvre le fichier, écrit le graphe, ferme le fichier
 * retourne : 0 ou 1
 * */
int saveGraphe(const struct graph *self, const char* fileName){
    //TODO check if file exists, ask for confirmation to overwrite it
    FILE* f = fopen(fileName, "w");
    if(f == NULL){
        fprintf(stderr,"Could not open file %s\n",fileName);
        return 1;
    }
    printGraphe(self,f);
    fclose(f);
    return 0;
}

/* vérifie si un sommet appartient au graphe
 * param entrée : pointeur sur le graphe, entier sommet
 * retourne : 0 ou 1
 */
int belongsToGrapheState(const struct graph *self, int state){
    if(state < self->nbMaxSommets && !isEmptyList(&self->listesAdjacences[state])){
        return 1;
    }
    return 0;
}

/* vérifie si une arete appartient au graphe
 * param entrée : pointeur sur le graphe, entiers source et destination de l'arete
 * retourne : 0 ou 1
 */
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

/* vérifie si le graphe est vide
 * param entrée : pointeur sur le graphe
 * retourne : 0 ou 1
 */
int isEmptyGraphe(const struct graph *self){
    int i;
    for(i=0;i<self->nbMaxSommets;i++){
        if(belongsToGrapheState(self,i)){
            return 0;
        }
    }
    return 1;
}

/* compte le nombre de sommets d'un graphe
 * param entrée : pointeur sur le graphe
 * retourne : entier nombre de sommets
 */
int lengthGraphe(const struct graph *self){
    int l = 0;
    while(self->listesAdjacences[l].first != NULL){
        l ++;
    }
    return l;
}

//parcours en profondeur
/*void dfs(const struct graph *self, int state){
    int visited[lengthGraphe(self)] = {};
    subDfs(self, visited, state);
    printf("\n");
}

void subDfs(const struct graph *self, int *visited, int state){
    visited[state] = 1;
    printf("%d ", state);
    //pour tous les adjacents
    struct list *tmp = self->listesAdjacences[state].first;
    while(tmp != NULL && tmp->first->next != NULL) {
        int adjacent = tmp->first->state;
        tmp = tmp->first->next;
        if (visited[adjacent] == 0) {
            subDfs(self, visited, adjacent);
        }
    }
}

//parcours en largeur
void bfs(const struct graph *self);*/