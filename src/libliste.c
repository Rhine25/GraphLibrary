#include <stdio.h>
#include <stdlib.h>

#include "../include/libliste.h"

//creation
struct list create(){
    struct list *self;
    self->first = NULL;
    return *self;
}

//destruction
void del(struct list_node){
	printf("test");
}

//ajout
void add(struct list *self, int value){ //insertion en debut de la liste doublement chainée
    struct list_node *other = malloc(sizeof(struct list_node));
    other->next = self->first;
    self->first = other;
    //TODO penser à gérer le previous
}

//suppression
void del(struct list_node){
    
}

//parcours en profondeur
void dfs(const struct list){ //depth first search

}

//parcours en largeur
void bfs(const struct list){ //breadth first search
    
}

//vide
int is_empty(const struct list){
    
}

//taille
size_t size(const struct list){
    
}

//recherche
struct list_node search(const struct list, int){
    
}
