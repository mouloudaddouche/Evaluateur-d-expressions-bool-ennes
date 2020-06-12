#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"

//retourne 1 si c'est une parenthese, 0 sinon
int est_parenthese(char * s)
{
	if (!strcmp(s,"(") || !strcmp(s,")")) return 1;
    else return 0;
}

//retourne 1 si c'est une constante, 0 sinon
int est_constante(char * s)
{
	if(!strcmp(s,"0") || !strcmp(s,"1")) return 1;
	else return 0;
}

//retourne 1 si c'est un operateur unaire, 0 sinon
int est_operateur_unaire(char * s)
{
	if (!strcmp(s,"NON")) return 1;
    else return 0;
}

//retourne 1 si c'est un operateur binaire, 0 sinon
int est_operateur_binaire(char * s)
{
	if (!strcmp(s,"+") || !strcmp(s,".") || !strcmp(s,"=>") || !strcmp(s,"<=>")) return 1;
	else return 0;
}
//extrait une sous chaine 
char* Extraire_String(char* s,int deb,int fin){
	char* rst=malloc(((fin+1)-deb)*sizeof(char));
	int i=0;
	while(deb<=fin){
		rst[i]=s[deb];
		i++;
		deb++;
	}
	return rst;	
}

liste_token cree_element_liste()
{
	liste_token elt=malloc(sizeof(struct token));
	elt->suivant=NULL;
	return elt;
}

// return un struct token complet du bon type
liste_token type_constante(char* s, liste_token liste, int premier_passage){
	//Liste Vide
	if (premier_passage){
		liste = cree_element_liste();
		liste->type = constante;
		if (s[0] == '1')	liste->valeur = vrai;
		 else 	liste->valeur = faux;
	}
	//Liste n'est pas vide
	else {
		liste_token pointeur = liste;
		while(pointeur->suivant!=NULL){
			pointeur=pointeur->suivant;}	
					pointeur->suivant = cree_element_liste();
					pointeur->suivant->type = constante;
					if (s[0] == '1') pointeur->suivant->valeur = vrai;
					 else 	pointeur->suivant->valeur = faux;				
			}
	return liste;
}

// return un struct token complet du bon type
liste_token type_parenthese(char* s, liste_token liste, int premier_passage){
	if (premier_passage){
		liste = cree_element_liste();
		liste->type = parenthese;
		if(!strcmp(s,"("))  liste->valeur = ouvrante;
			else liste->valeur = fermante;
	}
	
	else {
		liste_token pointeur = liste;
		while(pointeur->suivant!=NULL){
			pointeur=pointeur->suivant;}
				pointeur->suivant = cree_element_liste();
				pointeur->suivant->type = parenthese;
				if(!strcmp(s,"("))  pointeur->suivant->valeur = ouvrante;
				else pointeur->suivant->valeur = fermante;	
		}
	return liste;
}

// return un struct token complet du bon type
liste_token type_operateur(char* s, liste_token liste, int premier_passage){
		if (premier_passage){
			liste = cree_element_liste();
			liste->type = operateur;	
			if (!strcmp(s,"+")) liste->valeur = OU;
			if (!strcmp(s,".")) liste->valeur = ET;
			if (!strcmp(s,"=>")) liste->valeur = implication;
			if (!strcmp(s,"<=>")) liste->valeur = equivalence;
			if (!strcmp(s,"NON")) liste->valeur = NON;
		}
		
		else {
			liste_token pointeur = liste;
			while(pointeur->suivant!=NULL){
			  pointeur=pointeur->suivant;}	
					pointeur->suivant = cree_element_liste();
					pointeur->suivant->type = operateur;
					if (!strcmp(s,"+")) pointeur->suivant->valeur = OU;
					if (!strcmp(s,".")) pointeur->suivant->valeur = ET;
					if (!strcmp(s,"=>")) pointeur->suivant->valeur = implication;
					if (!strcmp(s,"<=>")) pointeur->suivant->valeur = equivalence;
					if (!strcmp(s,"NON")) pointeur->suivant->valeur = NON;
			}	
		return liste;
		}

// transforme une chaine de caractere en une liste de token
liste_token string_to_token (char *s){
		liste_token liste = NULL;
		int premier_passage = 1;
		int longueur = strlen(s);
		int i=0;
		while(i<longueur){
			if(s[i]=='0' || s[i]=='1'){
				char* temp=Extraire_String(s,i,i);
				if (premier_passage){
					liste = type_constante(temp, liste, 1);
					premier_passage = !premier_passage;
				}
				else 	liste = type_constante(temp,liste, 0);
				i++;
			}
			
			else if(s[i]=='(' || s[i]==')'){
				char* temp=Extraire_String(s,i,i);
				if (premier_passage){
					liste = type_parenthese(temp, liste, 1);
					premier_passage = !premier_passage;
				}
				else 	liste = type_parenthese(temp, liste, 0);
				i++;
			}
			
			else if (s[i]=='+' || s[i]=='.'){
				char* temp=Extraire_String(s,i,i);
				if (premier_passage){
					liste = type_operateur(temp, liste, 1);
					premier_passage = !premier_passage;
				}
				else 	liste = type_operateur(temp, liste, 0);
				i++;
			}
			
			else if (s[i]=='N' && s[i+1]=='O' && s[i+2]=='N'){
				char* temp=Extraire_String(s,i,i+2);
				if (premier_passage){
					liste = type_operateur(temp, liste, 1);
					premier_passage = !premier_passage;
				}
				else 	liste = type_operateur(temp, liste, 0);
				i=i+3;
			}
			
			else if (s[i]=='<' && s[i+1]=='=' && s[i+2]=='>'){
				char* temp=Extraire_String(s,i,i+2);
				if (premier_passage){
					liste = type_operateur(temp, liste, 1);
					premier_passage = !premier_passage;
				}
				else 	liste = type_operateur(temp, liste, 0);
				i=i+3;
			}
			
			else if (s[i]=='=' && s[i+1]=='>'){
				char* temp=Extraire_String(s,i,i+1);
				if (premier_passage){
					liste = type_operateur(temp, liste, 1);
					premier_passage = !premier_passage;
				}
				else 	liste = type_operateur(temp, liste, 0);
				i=i+2;
			}
			else if (s[i]==' ') i++;
		}
		return liste;

	}

// fonction qui affiche notre liste de token
void affichage_liste(liste_token l){
	while(l!=NULL){
	if (l->valeur == 0 ) printf("0");
	if (l->valeur == 1 ) printf("1");
	if (l->valeur == 5 ) printf("+");
	if (l->valeur == 6 ) printf(".");
	if (l->valeur == 7 ) printf("=>");
	if (l->valeur == 8 ) printf("<=>");
	if (l->valeur == 9 ) printf("NON");
	if (l->valeur == 10 ) printf("(");
	if (l->valeur == 11 ) printf(")");
	if(l->suivant ==NULL) printf("\n");
	l=l->suivant;
	}
}

// fonction a appeler quand le pointeur de la liste arrive sur un operateur binaire 
arbre_token arbre_operateur_binaire(arbre_token arbre, liste_token* liste){
	liste_token pointeur = *liste;
	if (arbre->fils_gauche != NULL){
		// le noeud gauche contient un sous arbre complet
		arbre->type_token = pointeur->type;
		arbre->valeur_token = pointeur->valeur;
		if (pointeur->suivant == NULL) return arbre;
		pointeur = pointeur->suivant;
		*liste = pointeur;
		if(pointeur->type == constante){
			arbre->fils_droite = malloc(sizeof(arbre_token));
			arbre->fils_droite->type_token = pointeur->type;
			arbre->fils_droite->valeur_token = pointeur->valeur;
			arbre->fils_droite->fils_droite = NULL;
			arbre->fils_droite->fils_gauche = NULL;
			return arbre;
		}
		if (pointeur->type == parenthese){
			//necessairement ouvrante
			if(pointeur->valeur == ouvrante){
				arbre->fils_droite = arbre_parenthese_ouvrante(arbre->fils_droite,liste);
				pointeur = *liste;
				return arbre;
			}
		}
	}
	return arbre;
}

// fonction a appeler si l'expression commence avec au moin 3 parentheses
arbre_token arbre_plus_de_3_parenthese_ouvrantes(arbre_token arbre, liste_token* liste){
	liste_token pointeur = *liste;
	if(pointeur->type == constante){
		if(arbre != NULL){
			if(arbre->valeur_token == NON){
			arbre->fils_droite = arbre_constante(arbre->fils_droite,liste);
			pointeur = *liste;
			}else{	
				arbre = arbre_constante(arbre,liste);
				pointeur = *liste;
			}
		}
		else {
			arbre = arbre_constante(arbre,liste);
			pointeur = *liste;
		}
		if (pointeur->suivant == NULL) return arbre;		
		if((pointeur->suivant->type == parenthese) && (pointeur->suivant->valeur == fermante)){
			if (pointeur->suivant->suivant == NULL) return arbre;
			if((pointeur->suivant->suivant->valeur == fermante) && (pointeur->suivant->suivant->suivant == NULL)) return arbre;
			// on traite une nouvelle expression pour un pointeur binaire
			arbre_token arbre1 = NULL;
			
			arbre1 = malloc(sizeof(arbre_token));
			arbre1->fils_droite =NULL;
			arbre1->fils_gauche = arbre;
			pointeur = pointeur->suivant->suivant;
			*liste = pointeur;
			if(pointeur->type == operateur){
				//necessairement binaire
				if((pointeur->suivant->type == parenthese) && ((pointeur->suivant->suivant->type == constante))){
					arbre1->type_token = operateur;
					arbre1->valeur_token = pointeur->valeur;
					pointeur = pointeur->suivant->suivant;
					*liste = pointeur;
				arbre1->fils_droite = arbre_constante(arbre1->fils_droite,liste);
				pointeur = *liste;
				if((pointeur->suivant->valeur == fermante) && (pointeur->suivant->suivant->valeur == fermante)){
					pointeur = pointeur->suivant->suivant->suivant;
					*liste = pointeur;
					if(pointeur == NULL) return arbre1;
						else if(pointeur->type == operateur){
							arbre_token arbre2 = NULL;
							arbre2 = malloc(sizeof(arbre_token));
							arbre2->fils_droite =NULL;
							arbre2->fils_gauche = arbre1;
							arbre2 = arbre_operateur_binaire(arbre2,liste);
							return arbre2;
						}
					}
				}
			}
		}
	}
}

// fonction a appeler si l'expression commence par une parenthese ouvrante
arbre_token arbre_parenthese_ouvrante(arbre_token arbre, liste_token* liste){
	liste_token pointeur = *liste;
	pointeur = pointeur->suivant;
	*liste = pointeur;
	if(pointeur->type == constante){
		if(arbre != NULL){
			if(arbre->valeur_token == NON){
				arbre->fils_droite = arbre_constante(arbre->fils_droite,liste);
				pointeur = *liste;
			}else{
				arbre = arbre_constante(arbre,liste);
				pointeur = *liste;
			}
		}
		else {
			arbre = arbre_constante(arbre,liste);
			pointeur = *liste;
			}
		if (pointeur->suivant == NULL) return arbre;		
		if((pointeur->suivant->type == parenthese) && (pointeur->suivant->valeur == fermante)){
			if (pointeur->suivant->suivant == NULL) return arbre;
			if((pointeur->suivant->suivant->valeur == fermante) && (pointeur->suivant->suivant->suivant == NULL)) return arbre;
			// on traite une nouvelle expression pour binaire
			arbre_token arbre1 = NULL;
			
			arbre1 = malloc(sizeof(arbre_token));
			arbre1->fils_droite =NULL;
			arbre1->fils_gauche = arbre;
			pointeur = pointeur->suivant->suivant;
			*liste = pointeur;
			if(pointeur->type == operateur){
				//necessairement binaire
				arbre1 = arbre_operateur_binaire(arbre1,liste);
				pointeur = *liste;
			}
			else if ((pointeur->type == parenthese) && (pointeur->suivant->type == operateur)){	
				pointeur = pointeur->suivant;
				*liste = pointeur;
				arbre1 = arbre_operateur_binaire(arbre1,liste);
				pointeur = *liste;
			}
			return arbre1;
		}
	}
	else if(pointeur->type == operateur){
		if (pointeur->valeur == NON){
			if((pointeur->suivant->suivant != NULL) && 
				(pointeur->suivant->suivant->type == operateur)){
				if(arbre == NULL){
					arbre = malloc(sizeof(arbre_token));
					arbre->fils_droite = NULL;
					arbre->fils_gauche = NULL;
				}
				arbre->fils_gauche = arbre_operateur_unaire(arbre->fils_gauche, liste);
				arbre = arbre_operateur_binaire(arbre,liste);
					pointeur = pointeur->suivant;
					return arbre;
				}
				else if(pointeur->suivant->type == parenthese){
					if(pointeur->suivant->valeur == ouvrante){
						arbre = malloc(sizeof(arbre_token));
						arbre->fils_droite = NULL;
						arbre->fils_gauche = NULL;
						arbre->type_token = operateur;
						arbre ->valeur_token = NON;
						pointeur = pointeur->suivant;
						*liste = pointeur;
						arbre = arbre_parenthese_ouvrante(arbre,liste);
						pointeur = *liste;
						return arbre;
					}
				}
			}
			if((pointeur->suivant->suivant != NULL) && 
				(pointeur->suivant->suivant->type == parenthese)){
					if(pointeur->suivant->suivant->valeur == fermante){
						arbre = arbre_operateur_unaire(arbre,liste);
						if(pointeur->suivant->valeur == fermante){
							pointeur = pointeur->suivant;
							return arbre;
							}
					}
			}
		}
		else if(pointeur->type == parenthese){
			if(pointeur->valeur == ouvrante){
				if((pointeur->valeur == ouvrante) && (pointeur->suivant->valeur == ouvrante)){
					pointeur = pointeur->suivant->suivant;
					*liste = pointeur;
					arbre = arbre_plus_de_3_parenthese_ouvrantes(arbre,liste);
					pointeur = *liste;
					return arbre;
				}
				arbre = arbre_parenthese_ouvrante(arbre,liste);
				pointeur = *liste;
				// mise a jour pointeur 
				pointeur = pointeur->suivant;
				*liste = pointeur;
				//l'apres parenthese 
				if(pointeur== NULL){
				return arbre;
				}
				if(pointeur->type == operateur){
					//necessairement bianire
					// on traite une nouvelle expression pour pointeur sur operation binaire
					arbre_token arbre1 = NULL;
					arbre1 = malloc(sizeof(arbre_token));
					arbre1->fils_droite =NULL;
					arbre1->fils_gauche = arbre;
				arbre1 = arbre_operateur_binaire(arbre1,&pointeur);
				pointeur = pointeur->suivant;
				*liste = pointeur;
				if (pointeur == NULL) 	return arbre1;
				arbre = arbre1;
				arbre1 = NULL;
				while(pointeur->type == operateur){
				arbre1 = malloc(sizeof(arbre_token));
				arbre1->fils_droite =NULL;
				arbre1->fils_gauche = arbre;
				arbre1 = arbre_operateur_binaire(arbre1,&pointeur);
				pointeur = pointeur->suivant;
				*liste = pointeur;				
				if (pointeur == NULL) 	return arbre1;
				arbre = arbre1;
				arbre1 = NULL;
				return arbre;
				}
				}			
			}
		}
	return arbre;
}

// fonction a appeler si l'expression commence par une constante ouvrante
arbre_token arbre_constante(arbre_token arbre, liste_token* liste){
	liste_token pointeur = *liste;
	//noeud sans type et sans valeur
	arbre = malloc(sizeof(arbre_token));
	// si l'expression est composé que d'une constante
	if(pointeur->suivant == NULL || pointeur->suivant->valeur == fermante ){
	arbre->fils_droite = NULL;
	arbre->type_token = pointeur->type;
	arbre->valeur_token = pointeur->valeur;
	arbre->fils_gauche = NULL;
	return arbre;
	}
	arbre->fils_droite = NULL;
	// le noeud gauche sera notre constante
	arbre->fils_gauche = malloc(sizeof(arbre_token));
	arbre->fils_gauche->type_token = pointeur->type;
	arbre->fils_gauche->valeur_token = pointeur->valeur;
	//la constante est une feuille
	arbre->fils_gauche->fils_gauche = NULL;
	arbre->fils_gauche->fils_droite = NULL;
	// token suivant
	if (pointeur->suivant == NULL) return arbre;
	pointeur = pointeur->suivant;
	*liste = pointeur;
	if (pointeur->type == operateur){
		//necessairement un operateur binaire
		arbre = arbre_operateur_binaire(arbre, liste);
		pointeur = *liste;
	}
	if(pointeur->suivant == NULL || pointeur->suivant->type == parenthese) return arbre;
	pointeur = pointeur->suivant;
	*liste = pointeur;
	if(pointeur->type == operateur){
		arbre_token arbre1 = NULL;
		arbre1 = malloc(sizeof(arbre_token));
		arbre1->fils_droite =NULL;
		arbre1->fils_gauche = arbre;
		arbre1 = arbre_operateur_binaire(arbre1,liste);
		pointeur = *liste;
		arbre = arbre1;
		if(pointeur->suivant == NULL || pointeur->suivant->type == parenthese) return arbre;
		arbre1 = NULL;
		while((pointeur->type == constante) && (pointeur->suivant->type == operateur) && ( pointeur->suivant->suivant->type == constante)){
			pointeur = pointeur->suivant;
			*liste = pointeur;
			arbre1 = malloc(sizeof(arbre_token));
			arbre1->fils_droite =NULL;
			arbre1->fils_gauche = arbre;
			arbre1 = arbre_operateur_binaire(arbre1,liste);
			pointeur = *liste;
			arbre = arbre1;
			if(pointeur->suivant == NULL ) return arbre;
			arbre1 = NULL;	
		}
		return arbre;
	}
	return arbre;
}

// fonction a appeler si l'expression commence par un NON
arbre_token arbre_operateur_unaire(arbre_token arbre, liste_token* liste){
		liste_token pointeur = *liste;
		arbre = malloc(sizeof(arbre_token));
		arbre->type_token = pointeur->type;
		arbre->valeur_token = pointeur->valeur;
		arbre->fils_gauche = NULL;
		arbre->fils_droite = NULL;
		pointeur = pointeur->suivant;
		*liste = pointeur;
		if (pointeur->type == constante){
			arbre->fils_droite = malloc(sizeof(arbre_token));
			arbre->fils_droite->type_token = pointeur->type;
			arbre->fils_droite->valeur_token = pointeur->valeur;
			arbre->fils_droite->fils_droite = NULL;
			arbre->fils_droite->fils_gauche=NULL;
			if(pointeur ->suivant == NULL)return arbre;
			
			pointeur = pointeur->suivant;
			*liste = pointeur;
			if(pointeur->type == operateur){
			arbre_token arbre1 = NULL;
			arbre1 = malloc(sizeof(arbre_token));
			arbre1->fils_gauche = arbre;
			arbre1->type_token = operateur;
			arbre1->valeur_token = pointeur->valeur;
			
			if (pointeur->suivant->type == constante ){
				arbre1->fils_droite = malloc(sizeof(arbre_token));
				arbre1->fils_droite->type_token = constante;
				arbre1->fils_droite->valeur_token = pointeur->suivant->valeur;
				arbre1->fils_droite->fils_droite = NULL;
				arbre1->fils_droite->fils_gauche = NULL;
				pointeur = pointeur->suivant;
				*liste = pointeur;
				
				if(pointeur->suivant == NULL) return arbre1;
				if (pointeur->suivant->type == operateur ) {
					pointeur = pointeur->suivant;
					*liste = pointeur;
					return arbre1;
					}
			}
			if (pointeur->suivant->type == parenthese){
				pointeur = pointeur->suivant;
				*liste = pointeur;
				arbre1->fils_droite = arbre_parenthese_ouvrante(arbre1,liste);
				pointeur = *liste;
				
				return arbre1;
			}
			
			}
		}
		else if(pointeur->type == operateur){
			if (pointeur->valeur == NON){
				arbre = NULL;
				//gerer le reste comme une nouvelle expression
				if(pointeur->suivant == NULL) return arbre;
				pointeur = pointeur->suivant;
				if(pointeur->type == operateur){
				//operateur unaire NON
					if(pointeur->valeur == NON){
						arbre = arbre_operateur_unaire(arbre,liste);
					}
				}	
				if(pointeur->type == constante){
					arbre = arbre_constante(arbre,liste);
					pointeur = *liste;
				}
				if (pointeur->type == parenthese){	
				//necessairement ouvrante
					
					arbre->fils_droite = arbre_parenthese_ouvrante(arbre->fils_droite,liste);
					pointeur = *liste;
				}
				return arbre;
			}
		}
		else {
			if(pointeur->type == parenthese){
				if(pointeur->valeur == ouvrante){
					arbre->fils_droite = arbre_parenthese_ouvrante(arbre->fils_droite,liste);
					if (pointeur == NULL)	return arbre;
						if(pointeur->type == operateur){
							arbre_token arbre1 = NULL;
							arbre1 = malloc(sizeof(arbre_token));
							arbre1->fils_droite =NULL;
							arbre1->fils_gauche = arbre;
							
							return arbre1;
						}
					}
			}
		}
		return arbre;
}

// fonction qui construit l'arbre a partire de la liste de tokens
arbre_token token_to_tree(liste_token liste){
	arbre_token arbre = NULL;
	if (liste == NULL) return arbre;
	if(liste->type == operateur){
		//operateur unaire NON
		if(liste->valeur == NON){
			arbre = arbre_operateur_unaire(arbre,&liste);
		}
	}
	else if(liste->type == constante){
		arbre = arbre_constante(arbre,&liste);
	}
	else if (liste->type == parenthese){
		//necessairement ouvrante
		arbre = arbre_parenthese_ouvrante(arbre,&liste);
	}
	return arbre;
}

// verifie si c'est un token
int est_un_token(char* s){
	if(est_constante(s) || est_operateur_binaire(s) || est_operateur_unaire(s)
		|| est_parenthese(s)) return 1;
	return 0;
}

//fonction utiliser pour l'affichage 
void affiche_un_caractere(int x){
	if (x== 0 ) printf("0\n");
	if (x == 1 ) printf("1\n");
	if (x == 5 ) printf("+\n");
	if (x == 6 ) printf(".\n");
	if (x == 7 ) printf("=>\n");
	if (x== 8 ) printf("<=>\n");
	if (x == 9 ) printf("NON\n");
	if (x == 10 ) printf("(\n");
	if (x == 11 ) printf(")\n");
}

// avalyse l'arbre et retourne l'evaluation de l'expression 
int evaluation(arbre_token arbre)  
{  
    // si l'arbre est vide
    if (!arbre)  
        return 0;  
        
    // si cest une constante
    if (arbre->type_token == constante)  
        return (arbre->valeur_token);  
 
    int valeur_gauche = evaluation(arbre->fils_gauche);  
   
    int valeur_droite = evaluation(arbre->fils_droite);  
  
	if(arbre->valeur_token == ET ){
		if((valeur_gauche) && (valeur_droite)) return 1;
		else return 0;
	}
  
	if(arbre->valeur_token == OU ){
		if((!valeur_gauche) && (!valeur_droite)) return 0;
			else return 1;
	}

	if(arbre->valeur_token == implication){
		if((valeur_gauche) && (!valeur_droite)) return 0;
		else return 1;
		}
  	if(arbre->valeur_token == equivalence ){
		if((valeur_gauche) && (valeur_droite) || (!valeur_gauche) && (!valeur_droite)) return 1;
		else return 0;
		}
	else if (arbre->valeur_token == NON ) return !valeur_droite;
}  

// affiche l'arbre
void affiche_arbre(arbre_token racine, int espace) 
{ 
    if (racine == NULL) 
        return; 
    espace += cpt; 
    affiche_arbre(racine->fils_gauche, espace); 
    printf("\n"); 
    for (int i = cpt; i < espace; i++) 
        printf(" "); 
    affiche_un_caractere(racine->valeur_token);
    affiche_arbre(racine->fils_droite, espace); 
} 

// fonction utiliser par Automate
int position_caractere(int s){
	if ( s==0) return 0;
	else if ( s==1) return 1;
	else if ( s==5) return 2;
	else if ( s==6) return 3;
	else if ( s==7) return 4;
	else if ( s==8) return 5;
	else if ( s==9) return 6;
	else if ( s==10) return 7;
	else if ( s==11) return 8;
	else return 9;	
}

// fonction qui verifie si une expression est bien formée
int Automate(liste_token l){
	int nbetat=4;
	int transition[4][9]={
	{2,2,0,0,0,0,3,1,0}, // Etat 1
	{0,0,3,3,3,3,0,0,4}, // Etat 2
	{2,2,0,0,0,0,1,3,0}, //Etat 3
	{0,0,3,3,3,3,0,0,4} //Etat 4
	};
	int equilibre=0;
	int etat=1;
	int n;
	do{
	if(l->valeur ==10) equilibre++; 
	if(l->valeur ==11) equilibre--;
	if (equilibre>=0){
		n=position_caractere(l->valeur);
		if (n!=9) etat=transition[etat-1][n];
	}
	l=l->suivant;
	}while(l!=NULL && equilibre>=0 && n !=9 && etat!=0);
	
	if (equilibre ==0 && etat ==2 ) return 1;
	else if (equilibre ==0 && etat ==4 ) return 1;
	else return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("erreur, exemple faites : ./eval ""1+0""\n");
		exit(1);
		}
		printf("\n\n");
	liste_token liste = NULL;
	arbre_token arbre = NULL;
	char* s = argv[1];
	liste = string_to_token(s);
	if(!Automate(liste)) printf("expression incorrecte\n");
	else{
	printf("\n	 Evaluation d’expressions booleennes\n");
	printf("_______________________________________________________\n");
	printf("\ntoken liste : ");
	affichage_liste(liste);
	printf("_______________________________________________________\n");
	printf("\narbre de l'expression : \n");
	arbre = token_to_tree(liste);
	affiche_arbre(arbre,0);
	int val = evaluation(arbre);
	printf("_______________________________________________________\n");
	char* c; 
	if(val) c = "VRAI"; else c = "FAUX";
	printf("\nl'evaluation de l'expression donne : %s\n",c);
	printf("_______________________________________________________\n\n");
	}
	return 0;
}
