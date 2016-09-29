#ifndef LIBGRAPHE_H
#define LIBGRAPHE_H

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

#endif