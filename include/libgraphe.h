#ifndef LIBGRAPHE_H
#define LIBGRAPHE_H

struct graph{
    int estOriente;
    int nbMaxSommets;
    struct list* listesAdjacences;
};

//création du graphe avec un nombre de sommet demandé
struct graph createGraphe(int, int);

void destroyGraphe(struct graph*);

void createVertex(struct graph*, int);

//lecture d'un graphe dans un fichier texte
void readGraphe(const char* fileName);

//inserer un nouveau sommet
void addVertex(struct graph*);

//inserer une arete entre deux somets d'un graf
void addEdge(struct graph*, int, int, int);

//supprimer un sommet
void delVertex(struct graph*, int v);

//supprimer une arete entre deux somets d'un graf
void delEdge(struct graph*, int src, int dest);

//parcours en profondeur
void dfs(const struct graph *self);

//parcours en largeur
void bfs(const struct graph *self);

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
void printGraphe(const struct graph*, const char* fileName);

//enregistrer le graf dans un fichier texte
void saveGraphe(const struct graph*, const char* fileName);

#endif