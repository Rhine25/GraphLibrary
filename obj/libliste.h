#ifndef LIBLISTE_H
#define LIBLISTE_H

struct list_node {
	int data;
	struct list_node *next;
        struct list_node *previous;
}list_node;
struct list {
	struct list_node *first;
}list;

//creation
struct list create();

//destruction
void destroy(struct list);

//ajout
void add(struct list, int);

//suppression
void del(struct list_node);

//parcours en profondeur
void dfs(const struct list); //depth first search

//parcours en largeur
void bfs(const struct list); //breadth first search

//vide
int is_empty(const struct list);

//taille
size_t size(const struct list);

//recherche
struct list_node search(const struct list, int);

#endif
