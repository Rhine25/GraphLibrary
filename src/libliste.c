#include <stdio.h>
#include <stdlib.h>

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
 * */
void destroyList(struct list *self){
    while(!is_empty(self)){
        delFirst(self);
    }
}

/* ajout d'un node en début de liste
 * param entrée : pointeur sur une liste, valeurs à affecter au node
 * crée un nouveau node et le place au début de la liste
 * */
void addNode(struct list *self, int voisin, int poids){ //insertion en début de la liste chainée
    struct list_node *other = malloc(sizeof(struct list_node));
    other->state = voisin;
    other->poids = poids;
    other->next = self->first;
    self->first = other;
}

/* suppression du node suivant l'élément courant
 * param entrée : pointeur sur un node
 * supprime le node suivant et raccroche l'élément courant à la fin de la liste
 */
void delNodeAfter(struct list_node *node){
    struct list_node *tmp = malloc(sizeof(struct list_node));
    tmp->next = node->next->next;
    node->next->next = NULL;
    free(node->next);
    node->next = tmp;
    tmp->next = NULL;
    free(tmp);
    //TODO need to fix this
}

/* suppression du premier node de la liste
 * param entrée : pointeur sur une liste
 * supprime le premier node et raccroche la fin de la liste
 * */
void delFirstNode(struct list *self){
    struct list_node *tmp = malloc(sizeof(struct list_node));
    tmp->next = self->first->next;
    free(self->first);
    self->first = NULL;
    self->first = tmp->next;
    tmp->next = NULL;
    free(tmp);
}

/* affichage de la liste
 * param entrée : pointeur sur une liste
 * parcoure la liste et affiche ses nodes
 * */
void visitList(const struct list *self){
    struct list *visit = malloc(sizeof(struct list));
    visit->first = self->first;
    printf("Affichage de la liste : \n-> ");
    while(visit->first != NULL){
        printf("%i -> ",visit->first->state);
        visit->first = visit->first->next;
    }
    printf("NULL\n");
    free(visit);
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
    struct list_node *visit;
    visit = self->first;
    size_t size = 1;
    while(visit->next != NULL){
        visit = visit->next;
        size++;
    }
    free(visit);
    return size;
}

/* recherche d'un node
 * param entrée : pointeur sur une liste, entier successeur recherché
 * retourne : node précédent le node recherché
 * */
struct list_node searchNode(const struct list *self, int value){
    struct list_node visit;
    visit.next = self->first;
    while(visit.next != NULL && visit.next->state != value){
        visit.next = visit.next->next;
    }
    //renvoie le node précédent celui recherché, pour pouvoir supprimer celui qui est recherché avec delAfterNode
    return visit;

    //TODO check if works
}
/* affichage / string liste
 * //TODO
 * */
char* listToString(const struct list *self){

    static char str[20] = {};
    struct list_node *visit;
    visit = self->first;
    while(visit->next != NULL){
        visit = visit->next;
        sprintf(str,"%s, ", nodeToString(visit));
    }
    sprintf(str,"\n");
    return str;
}

/* affichage / string node
 * //TODO
 * */
char* nodeToString(const struct list_node *self){
    static char str[20] = {};
    sprintf(str, "(%i/%i)", self->state, self->poids);
    return str;
}