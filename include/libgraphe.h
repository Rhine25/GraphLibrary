#ifndef LIBGRAPH_H
#define LIBGRAPH_H

struct TypVoisins{
    int voisin;
    int poids;
    TypVoisin* voisinSuivant;
    TypVoisin* voisinPrecedent;
}

struct TypGraph{
    int estOriente;
    int nbMaxSommets;
    TypVoisins* listesAdjacences;
}

//création du graphe avec un nombre de sommet demandé
void create();

//lecture d'un graphe dans un fichier texte
void read();

//inserer un nouveau sommet
void addSommet(int s);

//inserer une arete entre deux somets d'un graf
void addArete(int src, int dest);

//supprimer un sommet
void delSommet(int s);

//supprimer une arete entre deux somets d'un graf
void delArete(int src, int dest);

//afficher le graf dan le meme format que celui du fichier textee d'entrée
void print();

//enregistrer le graf dans un fichier texte
void save();

//quitter le programme et liberer toute la memoire
void exitProg();



#endif
