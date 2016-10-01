#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"

//creation
struct list create(){
    struct list self;// = malloc(sizeof(struct list));
    self.first = NULL;
    return self;
}

//destruction
void destroy(struct list *self){
    while(!is_empty(self)){
        delAfter(self->first);
    }
    //free(self);
    //TODO how do I delete self->first, therefor how can self be empty ? infinite loop ahead
}

//ajout
void add(struct list *self, int value){ //insertion en début de la liste chainée
    struct list_node *other = malloc(sizeof(struct list_node));
    other->next = self->first;
    self->first = other;
}

//suppression
void delAfter(struct list_node *node){
    struct list_node *tmp = malloc(sizeof(struct list_node));
    tmp->next = node->next->next;
    node->next->next = NULL;
    free(node->next);
    node->next = tmp;
    tmp->next = NULL;
    free(tmp);
}

//parcours
void visit(const struct list *self){
    struct list_node *visit = malloc(sizeof(struct list_node));
    visit->next = self->first;
    while(visit->next != NULL){
        visit->next = visit->next->next;
    }
    visit->next = NULL;
    free(visit);
}
/*
//parcours en profondeur
void dfs(const struct list *self){ //depth first search
    //TODO
}

//parcours en largeur
void bfs(const struct list *self){ //breadth first search
    //TODO
}
*/

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
    struct list_node visit; // = malloc(sizeof(struct list_node));
    int found = 0;
    while(visit.next != NULL && visit.next->data != value){
        visit.next = visit.next->next;
    }
    return visit;
}