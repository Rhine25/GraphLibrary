#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/libliste.h"

/* creation d'une liste
 * retourne : liste vide
 * */
struct list createList(){
    struct list self;
    self.first = NULL;
    return self;
}

/* destruction d'une liste
 * param entrée : un pointeur sur la liste à supprimer
 * libère chaque node jusqu'à que la liste soit vide
 * retourne : 0
 * */
int destroyList(struct list *self){
    while(!isEmptyList(self)){
        delFirstNode(self);
    }
    return 0;
}

/* ajout d'un node en début de liste
 * param entrée : pointeur sur une liste, valeurs à affecter au node
 * crée un nouveau node et le place au début de la liste
 * retourne : 0 ou 1 si le node n'a pas pu être ajouté
 * */
int addNode(struct list *self, int voisin, float poids){ //insertion en début de la liste chainée
    struct list_node *other = malloc(sizeof(struct list_node));
    if(other == NULL){
        return 1;
    }
    other->state = voisin;
    other->poids = poids;
    other->next = self->first;
    self->first = other;
    return 0;
}

/* suppression d'un node spécifique
 * param entrée : pointeur sur une liste, entier valeur du node à supprimer
 * retourne : entier
 */
int delNode(struct list* self, int value){
    struct list_node* node;
    node = self->first;
    if(node->state == value){
        return delFirstNode(self);
    }
    else {
        while (node->next != NULL && node->next->state != value) {
            node = node->next;
        }
        if (node->next != NULL) {
            struct list *tmp = malloc(sizeof(struct list));
            tmp->first = node->next->next;
            free(node->next);
            node->next = NULL;
            node->next = tmp->first;
            tmp->first = NULL;
            free(tmp);
            return 0;
        }
        return 1;
    }
}

/* suppression du premier node de la liste
 * param entrée : pointeur sur une liste
 * supprime le premier node et raccroche la fin de la liste
 * retourne : 0 ou 1
 * */
int delFirstNode(struct list *self){
    if(!isEmptyList(self)) {
        struct list_node *tmp = malloc(sizeof(struct list_node));
        tmp->next = self->first->next;
        free(self->first);
        self->first = NULL;
        self->first = tmp->next;
        tmp->next = NULL;
        free(tmp);
        return 0;
    }
    return 1;
}

/* test du vide
 * param entrée : pointeur sur une liste
 * retourne : 1 si la liste est vide, 0 sinon
 * */
int isEmptyList(const struct list *self){
    if (self->first == NULL){
        return 1;
    }
    return 0;
}

/* taille
 * param entrée : pointeur sur une liste
 * retourne : longueur de la liste
 * */
size_t listSize(const struct list *self){
    if(isEmptyList(self)){ //WARNING means state doesn't belong to graph. A graph's state that has no transitions has list size of 1
        return 0;
    }
    struct list visit;
    visit.first = self->first;
    size_t size = 1;
    while(visit.first->next != NULL){
        visit.first = visit.first->next;
        size++;
    }
    return size;
}

/* recherche d'un node
 * param entrée : pointeur sur une liste, entier recherché
 * retourne : le node recherché
 * */
struct list_node* searchNode(const struct list *self, int value){
    struct list_node* visit;
    visit = self->first;
    while(visit->state != value && visit->next != NULL){
        visit = visit->next;
    }
    if(visit->state != value){
        return NULL;
    }
    return visit;
}
/* écriture de la liste
 * param entrée : pointeur sur une liste
 * retourne : string contenant la liste sous la forme demandée
 * parcoure la liste et écrit les nodes séparés par des virgules
 * */
char* listToString(const struct list *self){
    static char str[100] = ""; //static pour pouvoir lire la valeur de la string dans la fonction appelante
    memset(str,0,sizeof(str)); //initialise la string à vide
    struct list visit;
    visit.first = self->first;
    while(visit.first->next != NULL && visit.first->next->state != -1){
        strcat(str, nodeToString(visit.first));
        strcat(str, ", ");
        visit.first = visit.first->next;
    }
    if(visit.first->state != -1) {
        strcat(str, nodeToString(visit.first));
    }
    strcat(str,"\n");
    return str;
}

/* écriture du node
 * param entrée : pointeur sur un node
 * retourne : string contenant le node sous la forme demandée (dest/poids)
 * */
char* nodeToString(const struct list_node *self){
    static char str[20] = "";
    memset(str,0,sizeof(str));
    sprintf(str, "(%i/%f)", self->state, self->poids);
    return str;
}
