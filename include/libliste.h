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
void destroyList(struct list*);

//ajout
int addNode(struct list*, int voisin, int poids);

//suppression après l'élément courant
void delNodeAfter(struct list_node*);

//supression de la valeur
void delNode(struct list*, int value);

//suppression du premier node
void delFirstNode(struct list*);

//vide
int isEmptyList(const struct list*);

//taille
size_t listSize(const struct list*);

//recherche
struct list_node* searchNode(const struct list*, int);

char* listToString(const struct list*);

char* nodeToString(const struct list_node*);

#endif
