#ifndef MENU_H
#define MENU_H

static const int NBMAXSOMMETS = 999;
static const int NBMAXDIGITS = 3;

struct graph* graphe;

void createMenu();
void creation();
void lecture();
void insertionSommet();
void insertionArete();
void suppressionSommet();
void suppressionArete();
void affichage ();
void sauvegarde();
void quitter();
void menu();
void affichageMenu();
void affichageMenuSeparateur();
void askForStrInput(char* str, char* message);
int askForIntInput(int maxLength, char* message);

#endif //MENU_H