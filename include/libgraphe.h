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

int destroyGraphe(struct graph*);

int createVertex(struct graph*, int);

//lecture d'un graphe dans un fichier texte
struct graph readGraphe(const char* fileName);

//inserer un nouveau sommet
int addVertex(struct graph*);

//inserer une arete entre deux somets d'un graf
int addEdge(struct graph*, int src, int dest, float poids);

//supprimer un sommet
int delVertex(struct graph*, int v);

//supprimer une arete entre deux somets d'un graf
int delEdge(struct graph*, int src, int dest);

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
void printGraphe(const struct graph*, FILE* out);

//enregistrer le graf dans un fichier texte
int saveGraphe(const struct graph*, const char* fileName);

int belongsToGrapheState(const struct graph*, int state);

int belongsToGrapheEdge(const struct graph*, int src, int dest);

int isEmptyGraphe(const struct graph*);

//nombre de sommets du graphe
int lengthGraphe(const struct graph *self);

//parcours en profondeur
void dfs(const struct graph *self, int state, int* parcours);
void dfs2(const struct graph *self, int state, int* visited, int* parcours, int parcoursCourant);

//parcours en largeur
/*void bfs(const struct graph *self);*/

#endif