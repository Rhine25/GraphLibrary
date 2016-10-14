#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/menu.h"

struct graph creation(){
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
        return createGraphe(0, atoi(nbMaxSommets));
        //graphe = &g;
    }
    else{
        printf("Le graphe sera orienté\n");
        return createGraphe(1, atoi(nbMaxSommets));
        //graphe = &g;
    }
}

void lecture(struct graph* graphe){
    //TODO
    printf("Non implemented yet, sorry\n");
}

void insertionSommet(struct graph* graphe){
    addVertex(graphe);
    printf("Nouveau sommet créé\n");
}

void insertionArete(struct graph* graphe){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    int poids = askForIntInput(NBMAXDIGITS,"De poids : ");
    addEdge(graphe, src, dest, poids);
    printf("Nouvelle arête créée\n");
}

void suppressionSommet(struct graph* graphe){
    int state = askForIntInput(NBMAXDIGITS, "Numéro de l'état : ");
    delVertex(graphe, state);
    printf("Sommet supprimé\n");
}

void suppressionArete(struct graph* graphe){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    delEdge(graphe, src, dest);
    printf("Arête supprimée\n");
}

void affichage(struct graph* graphe){
    printGraphe(graphe,stdout);
}

void sauvegarde(struct graph* graphe){
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

void quitter(struct graph* graphe){
    if(graphe != NULL) {
        destroyGraphe(graphe);
    }
    printf("Bonne journée !\n");
}

void menu(){
    affichageMenuInit();
}

void affichageMenuInit() {
    printf("0 : Créer un graphe\n");
    printf("1 : Importer un graphe\n");
    printf("2 : Quitter\n");

    struct graph graphe;

    int item = askForIntInput(1,"Que souhaitez-vous faire ?");
    switch(item){
        case 0 :
            graphe = creation();
            affichageMenuSeparateur(&graphe);
            break;
        case 1 :
            lecture(&graphe);
            affichageMenuSeparateur(&graphe);
            break;
        case 2 :
            quitter(&graphe);
            break;
    }
}

void affichageMenuAction(struct graph* graphe){
    printf("0 : Afficher le graphe\n");
    printf("1 : Ajouter un sommet au graphe\n");
    printf("2 : Ajouter une transition au graphe\n");
    printf("3 : Supprimer un sommet au graphe\n");
    printf("4 : Supprimer une transition au graphe\n");
    printf("5 : Sauvegarder le graphe et quitter\n");
    printf("6 : Quitter\n");

    int item = askForIntInput(1,"Que souhaitez-vous faire ?");
    switch(item){
        case 0 :
            affichage(graphe);
            affichageMenuSeparateur(graphe);
            break;
        case 1 :
            insertionSommet(graphe);
            affichageMenuSeparateur(graphe);
            break;
        case 2 :
            insertionArete(graphe);
            affichageMenuSeparateur(graphe);
            break;
        case 3 :
            suppressionSommet(graphe);
            affichageMenuSeparateur(graphe);
            break;
        case 4 :
            suppressionArete(graphe);
            affichageMenuSeparateur(graphe);
            break;
        case 5 :
            sauvegarde(graphe);
            quitter(graphe);
            break;
        case 6 :
            quitter(graphe);
            break;
    }
}

void affichageMenuSeparateur(struct graph* graphe){
    printf("\n------------------------------------\n");
    affichageMenuAction(graphe);
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