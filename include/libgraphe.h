#ifndef LIBGRAPHE_H
#define LIBGRAPHE_H

struct TypVoisins{
    int voisin;
    int poids;
    struct TypVoisins* voisinSuivant;
    struct TypVoisins* voisinPrecedent;
};

struct TypGraphe{
    int estOriente;
    int nbMaxSommets;
    struct TypVoisins* listesAdjacences;
};

//création du graphe avec un nombre de sommet demandé
struct TypGraphe createGraphe();

void destroyGraphe();

//lecture d'un graphe dans un fichier texte
void read(const char* fileName);

//inserer un nouveau sommet
void addVertex(struct TypGraphe g, int v);

//inserer une arete entre deux somets d'un graf
void addEdge(struct TypGraphe g, int src, int dest);

//supprimer un sommet
void delVertex(struct TypGraphe g, int v);

//supprimer une arete entre deux somets d'un graf
void delEdge(struct TypGraphe g, int src, int dest);

//parcours en profondeur
void dfs(const struct TypGraphe *self);

//parcours en largeur
void bfs(const struct TypGraphe *self);

//afficher le graphe dans le meme format que celui du fichier textee d'entrée
void print(const struct TypGraphe g, const char* fileName);

//enregistrer le graf dans un fichier texte
void save(const struct TypGraphe g, const char* fileName);

#endif