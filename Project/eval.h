#include "liste.h"
#include "arbre.h"

#define parenthese 2
#define operateur 3
#define constante 4

#define vrai 1
#define faux 0

#define OU 5
#define ET 6
#define implication 7
#define equivalence 8
#define NON 9

#define ouvrante 10
#define fermante 11

int est_un_token(char* s);
void affiche_un_caractere(int x);
int evaluation(arbre_token arbre);
int position_caractere(int s);
int Automate(liste_token l);
