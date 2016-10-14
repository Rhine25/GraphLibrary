#ifndef MENU_H
#define MENU_H

static const int NBMAXSOMMETS = 999;
static const int NBMAXDIGITS = 3;

struct graph creation();
void lecture(struct graph*);
void insertionSommet(struct graph*);
void insertionArete(struct graph*);
void suppressionSommet(struct graph*);
void suppressionArete(struct graph*);
void affichage (struct graph*);
void sauvegarde(struct graph*);
void quitter(struct graph*);
void menu();
void affichageMenuInit();
void affichageMenuAction(struct graph* graphe);
void affichageMenuSeparateur(struct graph* graphe);
void askForStrInput(char* str, char* message);
int askForIntInput(int maxLength, char* message);

#endif //MENU_H