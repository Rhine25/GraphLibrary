#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/menu.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PATH_LENGTH 50

struct graph creation(){
    int length = 3;
    char nbMaxSommets[length];
    fprintf(stdout,"Création d'un graphe :\n  Nombre de sommets maximum : ");
    getInput(nbMaxSommets,length+1);
    int nb = atoi(nbMaxSommets);
    while(nb <= 0){
        fprintf(stderr, ANSI_COLOR_RED "La valeur que vous avez rentrée n'est pas acceptable, veuillez réessayer\n" ANSI_COLOR_RESET);
        getInput(nbMaxSommets,length+1);
        nb = atoi(nbMaxSommets);
    }
    fprintf(stdout, ANSI_COLOR_GREEN "Le graphe aura %d sommets\n" ANSI_COLOR_RESET, nb);
    length = 1;
    char orientation[length];
    fprintf(stdout, "  Le graphe est-il orienté ? Y/n ");
    getInput(orientation, length+1);
    while(strcmp(orientation,"N") != 0 && strcmp(orientation,"n") != 0 &&
          strcmp(orientation,"Y") != 0 && strcmp(orientation,"y") != 0 && strcmp(orientation,"") != 0){
        fprintf(stderr, ANSI_COLOR_RED "La valeur rentrée n'est pas acceptable, veuillez réessayer\n" ANSI_COLOR_RESET);
        getInput(orientation, length+1);
    }
    if(strcmp(orientation,"N") == 0 || strcmp(orientation,"n") == 0){
        fprintf(stdout, ANSI_COLOR_GREEN "Le graphe sera non orienté\n" ANSI_COLOR_RESET);
        return createGraphe(0, atoi(nbMaxSommets));
    }
    else{
        fprintf(stdout, ANSI_COLOR_GREEN "Le graphe sera orienté\n" ANSI_COLOR_RESET);
        return createGraphe(1, atoi(nbMaxSommets));
    }
}

struct graph lecture(){
    char str[PATH_LENGTH];
    askForStrInput(str, PATH_LENGTH, "Où se trouve le graphe ? : ");
    fprintf(stdout, ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET,str);
    return readGraphe(str);
}

void insertionSommet(struct graph* graphe){
    int i = addVertex(graphe);
    if(belongsToGrapheState(graphe, i)) {
        fprintf(stdout, ANSI_COLOR_GREEN "Nouveau sommet créé : %d\n" ANSI_COLOR_RESET, i);
    }
    else{
        fprintf(stderr, ANSI_COLOR_RED "Le nouveau sommet n'a pas pu être créé : " ANSI_COLOR_RESET);
        if(i == graphe->nbMaxSommets){
            fprintf(stderr, ANSI_COLOR_RED "le nombre maximal de sommets à été atteint\n" ANSI_COLOR_RESET);
        }
        else{
            fprintf(stderr, ANSI_COLOR_RED "erreur inconnue\n" ANSI_COLOR_RESET);
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
    float poids = askForFloatInput(NBMAXDIGITS,"De poids : ");
    int c = addEdge(graphe, src, dest, poids);
    if(c == 0){
        fprintf(stdout, ANSI_COLOR_GREEN "Nouvelle arête créée\n" ANSI_COLOR_RESET);
    }
    else{
        fprintf(stderr, ANSI_COLOR_RED "Erreur lors de la création de l'arête. " ANSI_COLOR_RESET);
        if(c == 3){
            fprintf(stderr, ANSI_COLOR_RED "L'arête existe déjà.\n" ANSI_COLOR_RESET);
        }
        else if(c == 1){
            fprintf(stderr, ANSI_COLOR_RED "Les sommets n'existent pas.\n" ANSI_COLOR_RESET);
        }
        else{
            fprintf(stderr, ANSI_COLOR_RED "\n" ANSI_COLOR_RESET);
        }
    }
}

void suppressionSommet(struct graph* graphe){
    //TODO suppressing last state segfaults
    int state = askForIntInput(NBMAXDIGITS, "Numéro du sommet : ");
    int c = delVertex(graphe, state);
    if(c == 0){
        fprintf(stdout, ANSI_COLOR_GREEN "Sommet supprimé\n" ANSI_COLOR_RESET);
    }
    else{
        fprintf(stderr, ANSI_COLOR_RED "Le sommet n'a pas pu être supprimé. Il n'existe pas.\n" ANSI_COLOR_RESET);
    }
}

void suppressionArete(struct graph* graphe){
    //TODO try delete -1
    int src = askForIntInput(NBMAXDIGITS,"De : ");
    int dest = askForIntInput(NBMAXDIGITS,"Vers : ");
    int c = delEdge(graphe, src, dest);
    if(c == 0){
        fprintf(stdout, ANSI_COLOR_GREEN "Arête supprimée\n" ANSI_COLOR_RESET);
    }
    else{
        fprintf(stderr, ANSI_COLOR_RED "L'arête n'a pas été supprimée. " ANSI_COLOR_RESET);
        if(c == 4){
            fprintf(stderr, ANSI_COLOR_RED "Les sommets n'existent pas.\n" ANSI_COLOR_RESET);
        }
        else if(c == 1){
            fprintf(stderr, ANSI_COLOR_RED "L'arête n'existe pas.\n" ANSI_COLOR_RESET);
        }
        else{
            fprintf(stderr, ANSI_COLOR_RED "\n" ANSI_COLOR_RESET);
        }
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
        fprintf(stdout, ANSI_COLOR_GREEN "Graphe sauvegardé\n" ANSI_COLOR_RESET);
    }
    else if(c == 1){
        fprintf(stderr, ANSI_COLOR_RED "Le graphe n'a pas pu être sauvegardé\n" ANSI_COLOR_RESET);
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
    printf("|     Toutes les valeurs entières    |\n");
    printf("|     sont tronquées à %d chiffres    |\n", NBMAXDIGITS);
    printf("|____________________________________|\n");
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
            fprintf(stderr, ANSI_COLOR_RED "Désolé, je n'ai pas compris.\n" ANSI_COLOR_RESET);
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
            fprintf(stderr, ANSI_COLOR_RED "Désolé, je n'ai pas compris.\n" ANSI_COLOR_RESET);
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
    if((value == 0 && strcmp(str,"0") != 0) || value < 0){
        value = askForIntInput(maxLength, "Veuillez entrer une valeur acceptable : ");
    }
    return value;
}

float askForFloatInput(int maxLength, char* message){
    char str[maxLength];
    printf("%s", message);
    getInput(str, maxLength+1);
    float value = atof(str);
    if((value == 0.0 && strcmp(str,"0.0") != 0) || value < 0.0){
        value = askForIntInput(maxLength, "Veuillez entrer une valeur acceptable : ");
    }
    return value;
}