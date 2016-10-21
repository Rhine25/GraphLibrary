#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/menu.h"

#define PATH_LENGTH 50

struct graph creation(){
    int length = 3;
    char nbMaxSommets[length];
    printf("Création d'un graphe :\n  Nombre de sommets maximum : ");
    getInput(nbMaxSommets,length+1);
    int nb = atoi(nbMaxSommets);
    while(nb <= 0){
        printf("La valeur que vous avez rentrée n'est pas acceptable, veuillez réessayer\n");
        getInput(nbMaxSommets,length+1);
        nb = atoi(nbMaxSommets);
    }
    printf("Le graphe aura %d sommets\n", nb);
    length = 1;
    char orientation[length];
    printf("  Le graphe est-il orienté ? Y/n ");
    getInput(orientation, length+1);
    while(strcmp(orientation,"N") != 0 && strcmp(orientation,"n") != 0 &&
          strcmp(orientation,"Y") != 0 && strcmp(orientation,"y") != 0 && strcmp(orientation,"") != 0){
        printf("La valeur rentrée n'est pas acceptable, veuillez réessayer\n");
        getInput(orientation, length+1);
    }
    if(strcmp(orientation,"N") == 0 || strcmp(orientation,"n") == 0){
        printf("Le graphe sera non orienté\n");
        return createGraphe(0, atoi(nbMaxSommets));
        //graphe = &g;
    }
    else{
        printf("Le graphe sera orienté\n");
        return createGraphe(1, atoi(nbMaxSommets));
    }
}

struct graph lecture(){
    //TODO
    //printf("Non implemented yet, sorry\n");
    char str[PATH_LENGTH];
    askForStrInput(str, PATH_LENGTH, "Où se trouve le graphe ?\n");
    fprintf(stderr,"%s\n",str);
    return readGraphe(str);
}

void insertionSommet(struct graph* graphe){
    int i = addVertex(graphe);
    if(belongsToGrapheState(graphe, i)) {
        printf("Nouveau sommet créé : %d\n", i);
    }
    else{
        printf("Le nouveau sommet n'a pas pu être créé : ");
        if(i == graphe->nbMaxSommets){
            printf("le nombre maximal de sommets à été atteint\n");
        }
        else{
            printf("erreur inconnue\n");
        }
    }
}

void insertionArete(struct graph* graphe){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    while(src < 0){
        src = askForIntInput(NBMAXDIGITS,"Veuillez rentrer une valeur acceptable\n");
    }
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    while(dest < 0){
        src = askForIntInput(NBMAXDIGITS,"Veuillez rentrer une valeur acceptable\n");
    }
    int poids = askForIntInput(NBMAXDIGITS,"De poids : ");
    int c = addEdge(graphe, src, dest, poids);
    if(c ==0){
        printf("Nouvelle arête créée\n");
    }
    else{
        printf("Erreur lors de la création de l'arête. ");
        if(c == 3){
            printf("L'arête existe déjà.\n");
        }
            else if(c == 1){
            printf("Les états n'existent pas.\n");
        }
        else{
            printf("\n");
        }
    }
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
    char filename[PATH_LENGTH] = {};
    askForStrInput(filename, PATH_LENGTH, "Où souhaitez-vous sauvegarder le graphe ?");
    int c = saveGraphe(graphe, filename);
    if(c == 0) {
        printf("Graphe sauvegardé\n");
    }
    else if(c == 1){
        printf("Le graphe n'a pas pu être sauvegardé\n");
    }
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
            graphe = lecture();
            affichageMenuSeparateur(&graphe);
            break;
        case 2 :
            quitter(NULL);
            break;
        default:
            printf("Désolé, je n'ai pas compris.\n");
            affichageMenuInit();
            break;
    }
}

void affichageMenuAction(struct graph* graphe){
    printf("0 : Afficher le graphe\n");
    printf("1 : Ajouter un sommet au graphe\n");
    printf("2 : Ajouter une arête au graphe\n");
    printf("3 : Supprimer un sommet au graphe\n");
    printf("4 : Supprimer une arête au graphe\n");
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
        default:
            printf("Désolé, je n'ai pas compris.\n");
            affichageMenuAction(graphe);
            break;
    }
}

void affichageMenuSeparateur(struct graph* graphe){
    printf("\n------------------------------------\n");
    affichageMenuAction(graphe);
}

void askForStrInput(char* str, int maxLength, char* message){
    printf("%s \n", message);
    getInput(str,maxLength+1);
}

int askForIntInput(int maxLength, char* message){
    char str[maxLength];
    printf("%s \n", message);
    getInput(str, maxLength+1);
    int value = atoi(str);
    if(value == 0 && strcmp(str,"0") != 0){
        value = askForIntInput(maxLength, "Veuillez entrer une valeur acceptable\n");
    }
    return value;
}

int isPositiveNumber(int n){
    if(n >= 0){
        return 1;
    }
    return 0;
}