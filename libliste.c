#include <stdio.h>
#include <stdlib.h>

#include "libliste.h"

//TODO vérifier les passages du début à la fin des listes pour les next
//TODO does a list finish with null or returns to the first node?

//creation
struct list create(){
    struct list *self = malloc(sizeof(struct list));
    self->first = NULL;
    return self;
}

//destruction
void destroy(struct list *self){
    while(!is_empty(self)){
        del(self->previous);
    }
    free(self);
}

//ajout
void add(struct list *self, int value){ //insertion en dbut de la liste doublement chainée
    struct list_node *other = malloc(sizeof(struct list_node));
    other->next = self->first;
    self->first = other;
    //TODO penser à gérer le previous
}

//suppression
void del(struct list_node *node){
    node->previous->next = node->next;
    node->next = NULL;
    free(node);
    //TODO gérer l'autre chainage
    //TODO check s'il reste un node, sinon mettre le list first à nul ?
}

//parcours en profondeur
void dfs(const struct list *self){ //depth first search
    //TODO
}

//parcours en largeur
void bfs(const struct list *self){ //breadth first search
    //TODO
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
    struct list_node *visit = malloc(sizeof(struct list_node));
    visit->next = self->first;
    size_t size = 0;
    while(visit->next != NULL){
        visit->next = visit->next->next;
        size++;
    }
    visit->next = NULL;
    free(visit);
    return size;
}

//recherche
struct list_node search(const struct list *self, int value){
    struct list_node *visit = malloc(sizeof(struct list_node));
    int found = 0;
    while(visit->next != NULL && visit->next->data != value){
        visit->next = visit->next->next;
    }
    return visit;
}