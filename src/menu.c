#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/menu.h"

#define PATH_LENGTH 50

struct graph creation(){
    int length = 3;
    char nbMaxSommets[length];
    fprintf(stdout,"Création d'un graphe :\n  Nombre de sommets maximum : ");
    getInput(nbMaxSommets,length+1);
    int nb = atoi(nbMaxSommets);
    while(nb <= 0){
        fprintf(stderr, "La valeur que vous avez rentrée n'est pas acceptable, veuillez réessayer\n");
        getInput(nbMaxSommets,length+1);
        nb = atoi(nbMaxSommets);
    }
    fprintf(stdout, "Le graphe aura %d sommets\n", nb);
    length = 1;
    char orientation[length];
    fprintf(stdout, "  Le graphe est-il orienté ? Y/n ");
    getInput(orientation, length+1);
    while(strcmp(orientation,"N") != 0 && strcmp(orientation,"n") != 0 &&
          strcmp(orientation,"Y") != 0 && strcmp(orientation,"y") != 0 && strcmp(orientation,"") != 0){
        fprintf(stderr, "La valeur rentrée n'est pas acceptable, veuillez réessayer\n");
        getInput(orientation, length+1);
    }
    if(strcmp(orientation,"N") == 0 || strcmp(orientation,"n") == 0){
        fprintf(stdout, "Le graphe sera non orienté\n");
        return createGraphe(0, atoi(nbMaxSommets));
    }
    else{
        fprintf(stdout, "Le graphe sera orienté\n");
        return createGraphe(1, atoi(nbMaxSommets));
    }
}

struct graph lecture(){
    char str[PATH_LENGTH];
    askForStrInput(str, PATH_LENGTH, "Où se trouve le graphe ? : ");
    fprintf(stderr,"%s\n",str);
    return readGraphe(str);
}

void insertionSommet(struct graph* graphe){
    int i = addVertex(graphe);
    if(belongsToGrapheState(graphe, i)) {
        fprintf(stdout, "Nouveau sommet créé : %d\n", i);
    }
    else{
        fprintf(stderr, "Le nouveau sommet n'a pas pu être créé : ");
        if(i == graphe->nbMaxSommets){
            fprintf(stderr, "le nombre maximal de sommets à été atteint\n");
        }
        else{
            fprintf(stderr, "erreur inconnue\n");
        }
    }
}

void insertionArete(struct graph* graphe){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    while(src < 0){
        src = askForIntInput(NBMAXDIGITS,"Veuillez rentrer une valeur acceptable : ");
    }
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    while(dest < 0){
        src = askForIntInput(NBMAXDIGITS,"Veuillez rentrer une valeur acceptable : ");
    }
    int poids = askForIntInput(NBMAXDIGITS,"De poids : ");
    int c = addEdge(graphe, src, dest, poids);
    if(c == 0){
        fprintf(stdout, "Nouvelle arête créée\n");
    }
    else{
        fprintf(stderr, "Erreur lors de la création de l'arête. ");
        if(c == 3){
            fprintf(stderr, "L'arête existe déjà.\n");
        }
        else if(c == 1){
            fprintf(stderr, "Les états n'existent pas.\n");
        }
        else{
            fprintf(stderr, "\n");
        }
    }
}

void suppressionSommet(struct graph* graphe){
    int state = askForIntInput(NBMAXDIGITS, "Numéro de l'état : ");
    int c = delVertex(graphe, state);
    if(c == 0){
        fprintf(stdout, "Sommet supprimé\n");
    }
    else{
        fprintf(stderr, "Le sommet n'a pas pu être supprimé. Il n'existe pas.\n");
    }
}

void suppressionArete(struct graph* graphe){
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    int c = delEdge(graphe, src, dest);
    if(c == 0){
        fprintf(stdout, "Arête supprimée\n");
    }
    else{
        fprintf(stderr, "L'arête n'a pas été supprimée.\n");
    }
}

void affichage(struct graph* graphe){
    printGraphe(graphe,stdout);
}

int sauvegarde(struct graph* graphe){
    char filename[PATH_LENGTH] = {};
    askForStrInput(filename, PATH_LENGTH, "Où souhaitez-vous sauvegarder le graphe ? : ");
    int c = saveGraphe(graphe, filename);
    if(c == 0) {
        fprintf(stdout, "Graphe sauvegardé\n");
    }
    else if(c == 1){
        fprintf(stderr, "Le graphe n'a pas pu être sauvegardé\n");
    }
    return c;
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
    printf(" ____________________________________\n");
    printf("|                                    |\n");
    printf("| 0 : Créer un graphe                |\n");
    printf("| 1 : Importer un graphe             |\n");
    printf("| 2 : Quitter                        |\n");
    printf("|____________________________________|\n");

    struct graph graphe;

    int item = askForIntInput(1,"Que souhaitez-vous faire ? : ");
    switch(item){
        case 0 :
            graphe = creation();
            affichageMenuSeparateur(&graphe);
            break;
        case 1 :
            graphe = lecture();
            if(graphe.nbMaxSommets == 0){
                affichageMenuInit();
            }
            else{
                affichageMenuSeparateur(&graphe);
            }
            break;
        case 2 :
            quitter(NULL);
            break;
        default:
            fprintf(stderr, "Désolé, je n'ai pas compris.\n");
            affichageMenuInit();
            break;
    }
}

void affichageMenuAction(struct graph* graphe){
    printf(" _______________________________________\n");
    printf("|                                       |\n");
    printf("| 0 : Afficher le graphe                |\n");
    printf("| 1 : Ajouter un sommet au graphe       |\n");
    printf("| 2 : Ajouter une arête au graphe       |\n");
    printf("| 3 : Supprimer un sommet au graphe     |\n");
    printf("| 4 : Supprimer une arête au graphe     |\n");
    printf("| 5 : Sauvegarder le graphe et quitter  |\n");
    printf("| 6 : Quitter                           |\n");
    printf("|_______________________________________|\n");

    int item = askForIntInput(1,"Que souhaitez-vous faire ? : ");
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
            if(sauvegarde(graphe) == 0){
                quitter(graphe);
            }
            else{
                affichageMenuSeparateur(graphe);
            }
            break;
        case 6 :
            quitter(graphe);
            break;
        default:
            fprintf(stderr, "Désolé, je n'ai pas compris.\n");
            affichageMenuAction(graphe);
            break;
    }
}

void affichageMenuSeparateur(struct graph* graphe){
    affichageMenuAction(graphe);
}

void askForStrInput(char* str, int maxLength, char* message){
    printf("%s", message);
    getInput(str,maxLength+1);
}

int askForIntInput(int maxLength, char* message){
    char str[maxLength];
    printf("%s", message);
    getInput(str, maxLength+1);
    int value = atoi(str);
    if(value == 0 && strcmp(str,"0") != 0){
        value = askForIntInput(maxLength, "Veuillez entrer une valeur acceptable : ");
    }
    return value;
}