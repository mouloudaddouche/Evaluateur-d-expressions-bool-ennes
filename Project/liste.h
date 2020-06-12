struct token {
    int type;
	int valeur;
	struct token* suivant; 
};

typedef struct token* liste_token;

// return un struct token complet du bon type
liste_token type_constante(char* s, liste_token liste, int premier_passage);

// return un struct token complet du bon type
liste_token type_parenthese(char* s, liste_token liste, int premier_passage);

// return un struct token complet du bon type
liste_token type_operateur(char* s, liste_token liste, int premier_passage);

//transforme une chaine de caractere en une liste de token
liste_token string_to_token (char *string);

liste_token cree_element_liste();

char* Extraire_String(char* s,int deb,int fin);

int est_operateur_binaire(char * s);

void affichage_liste(liste_token l);

int est_operateur_unaire(char * s);
int est_constante(char * s);
int est_parenthese(char * s);
