#define cpt 5

struct arbre{
	int type_token;
	int valeur_token;
	struct arbre* fils_gauche;
	struct arbre* fils_droite;	
};

typedef struct arbre* arbre_token;


arbre_token cree_element_arbre();
arbre_token token_to_tree(liste_token liste);

arbre_token arbre_operateur_unaire(arbre_token, liste_token*);
arbre_token arbre_constante(arbre_token, liste_token*);
arbre_token arbre_parenthese_ouvrante(arbre_token, liste_token*);
arbre_token arbre_plus_de_3_parenthese_ouvrantes(arbre_token arbre, liste_token* liste);
arbre_token arbre_operateur_binaire(arbre_token, liste_token*);

void affiche_arbre(arbre_token racine, int espace);
