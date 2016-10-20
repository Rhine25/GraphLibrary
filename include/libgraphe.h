#ifndef LIBGRAPHE_H
#define LIBGRAPHE_H

#define NBMAXSOMMETS 999
#define NBMAXDIGITS 3

struct graph{
    int estOriente;
    int nbMaxSommets;
    struct list* listesAdjacences;
};

//création du graphe avec un nombre de sommet demandé
struct graph createGraphe(int orientation, int maxSommets);

void destroyGraphe(struct graph*);

void createVertex(struct graph*, int);

//lecture d'un graphe dans un fichier texte
void readGraphe(const char* fileName, struct graph*);

//inserer un nouveau sommet
int addVertex(struct graph*);

//inserer une arete entre deux somets d'un graf
int addEdge(struct graph*, int, int, int);

//supprimer un sommet
void delVertex(struct graph*, int v);

//supprimer une arete entre deux somets d'un graf
void delEdge(struct graph*, int src, int dest);

//parcours en profondeur
void dfs(const struct graph *self);

//parcours en largeur
void bfs(const struct graph *self);

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
void printGraphe(const struct graph*, FILE* out);

//enregistrer le graf dans un fichier texte
int saveGraphe(const struct graph*, const char* fileName);

int belongsToGrapheState(const struct graph*, int state);

int belongsToGrapheEdge(const struct graph*, int src, int dest);

int isEmptyGraphe(const struct graph*);

#endif