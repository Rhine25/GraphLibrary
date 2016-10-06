#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"

//creation
struct list createList(){
    struct list self;
    self.first = NULL;
    return self;
}

//destruction
void destroy(struct list *self){
    while(!is_empty(self)){
        delFirst(self);
    }
}

//ajout au début de la liste
void add(struct list *self, int voisin, int poids){ //insertion en début de la liste chainée
    struct list_node *other = malloc(sizeof(struct list_node));
    other->state = voisin;
    other->poids = poids;
    other->next = self->first;
    self->first = other;
    //visit(self);
    //printf("size : %lu\n", size(self));
}

//suppression après l'élément courant //doesn't work
void delAfter(struct list_node *node){
    struct list_node *tmp = malloc(sizeof(struct list_node));
    tmp->next = node->next->next;
    node->next->next = NULL;
    free(node->next);
    node->next = tmp;
    tmp->next = NULL;
    free(tmp);
    //TODO need to fix this
}

//suppression du premier node
void delFirst(struct list *self){
    struct list_node *tmp = malloc(sizeof(struct list_node));
    tmp->next = self->first->next;
    free(self->first);
    self->first = NULL;
    self->first = tmp->next;
    tmp->next = NULL;
    free(tmp);
}

//parcours / affichage de la liste
void visit(const struct list *self){
    struct list *visit = malloc(sizeof(struct list));
    visit->first = self->first;
    printf("Affichage de la liste : \n-> ");
    while(visit->first != NULL){
        printf("%i -> ",visit->first->state);
        visit->first = visit->first->next;
    }
    printf("NULL\n");
    visit->first = NULL;
    free(visit);
}

//vide
int is_empty(const struct list *self){
    if (self->first == NULL){
        return 1;
    }
    return 0;
}

//taille
size_t size(const struct list *self){
    if(is_empty(self)){
        return 0;
    }
    struct list_node *visit = malloc(sizeof(struct list_node));
    visit = self->first;
    size_t size = 1;
    while(visit->next != NULL){
        visit = visit->next;
        printf("size visit data = %i", visit->state);
        size++;
    }
    free(visit);
    return size;
}

//recherche
struct list_node search(const struct list *self, int value){
    struct list_node visit; // = malloc(sizeof(struct list_node));
    visit.next = self->first;
    while(visit.next != NULL && visit.next->state != value){
        visit.next = visit.next->next;
    }
    //renvoie le node précédent celui recherché
    return visit;

    //TODO check if works
}