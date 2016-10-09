#ifndef LIBLISTE_H
#define LIBLISTE_H

/*
 * Trucs à replace
 * list_node = TypVoisins
 * state = voisin
 */

struct list_node {
	int state; //name of the current elem
	int poids;
	struct list_node *next;
};

struct list {
	struct list_node *first;
};

//creation
struct list createList();

//destruction
void destroy(struct list*);

//ajout
void add(struct list*, int, int);

//suppression après l'élément courant
void delAfter(struct list_node*);

//suppression du premier node
void delFirst(struct list*);

//parcours
void visit(const struct list*);

//vide
int is_empty(const struct list*);

//taille
size_t size(const struct list*);

//recherche
struct list_node search(const struct list*, int);

char* listToString(const struct list*);

char* nodeToString(const struct list_node*);

#endif
