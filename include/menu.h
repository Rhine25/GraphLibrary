#ifndef MENU_H
#define MENU_H

struct graph creation();
struct graph lecture();
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
void askForStrInput(char* str, int maxLength, char* message);
int askForIntInput(int maxLength, char* message);
int isPositiveNumber(int);

#endif //MENU_H