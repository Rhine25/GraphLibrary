#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/menu.h"

void createMenu(){
    graphe = NULL;
}

void creation(){
    if(graphe != NULL && !isEmptyGraphe(graphe)){
        printf("Un automate existe déjà.");
    }
    int length = 3;
    char nbMaxSommets[length];
    printf("Création d'un graphe :\n  Nombre de sommets maximum : ");
    getInput(nbMaxSommets,length+1);
    printf("Le graphe aura %d\n", atoi(nbMaxSommets));
    length = 1;
    char orientation[length];
    printf("  Le graphe est-il orienté ? Y/n ");
    getInput(orientation, length+1);
    if(strcmp(orientation,"n") == 0){
        printf("Le graphe sera non orienté\n");
        struct graph g = createGraphe(atoi(nbMaxSommets), 0);
        graphe = &g;
    }
    else{
        printf("Le graphe sera orienté\n");
        struct graph g = createGraphe(atoi(nbMaxSommets), 1);
        graphe = &g;
    }
}

void lecture(){
    //TODO
    printf("Non implemented yet, sorry\n");
}

void insertionSommet(){
    addVertex(graphe);
    printf("Nouveau sommet créé\n");
}

void insertionArete(){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    int poids = askForIntInput(NBMAXDIGITS,"De poids : ");
    addEdge(graphe, src, dest, poids);
    printf("Nouvelle arête créée\n");
}

void suppressionSommet(){
    int state = askForIntInput(NBMAXDIGITS, "Numéro de l'état : ");
    delVertex(graphe, state);
    printf("Sommet supprimé\n");
}

void suppressionArete(){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    delEdge(graphe, src, dest);
    printf("Arête supprimée\n");
}

void affichage(){
    printGraphe(graphe,stdout);
}

void sauvegarde(){
    char filename[50];
    askForStrInput(filename,"Où souhaitez-vous sauvegarder le graphe ?");
    /*FILE* f = fopen(filename, "w");
    if(f == NULL){
        fprintf(stderr,"Could not open file %s\n", filename);
        affichageMenuSeparateur();
    }*/
    saveGraphe(graphe, filename);
    printf("Graphe sauvegardé\n");
}

void quitter(){
    if(graphe != NULL) {
        destroyGraphe(graphe);
    }
    printf("Bonne journée !\n");
}

void menu(){
    createMenu();
    affichageMenu();
}

void affichageMenu() {
    printf("0 : Créer un graphe\n");
    printf("1 : Importer un graphe\n");
    printf("2 : Ajouter un sommet au graphe\n");
    printf("3 : Ajouter une transition au graphe\n");
    printf("4 : Supprimer un sommet au graphe\n");
    printf("5 : Supprimer une transition au graphe\n");
    printf("6 : Afficher le graphe\n");
    printf("7 : Sauvegarder le graphe\n");
    printf("8 : Quitter\n");

    int item = askForIntInput(1,"Que souhaitez-vous faire ?");
    switch(item){
        case 0 :
            creation();
            affichageMenuSeparateur();
            break;
        case 1 :
            lecture();
            affichageMenuSeparateur();
            break;
        case 2 :
            insertionSommet();
            affichageMenuSeparateur();
            break;
        case 3 :
            insertionArete();
            affichageMenuSeparateur();
            break;
        case 4 :
            suppressionSommet();
            affichageMenuSeparateur();
            break;
        case 5 :
            suppressionArete();
            affichageMenuSeparateur();
            break;
        case 6 :
            affichage();
            affichageMenuSeparateur();
            break;
        case 7 :
            sauvegarde();
            affichageMenuSeparateur();
            break;
        case 8 :
            quitter();
            break;
    }
}

void affichageMenuSeparateur(){
    printf("\n------------------------------------\n");
    affichageMenu();
}

void askForStrInput(char* str, char* message){
    int length = strlen(str);
    printf("%s \n", message);
    getInput(str,length+1);
}

int askForIntInput(int maxLength, char* message){
    char str[maxLength];
    printf("%s \n", message);
    getInput(str, maxLength+1);
    return atoi(str);
}