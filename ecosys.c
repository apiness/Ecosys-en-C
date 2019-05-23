
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include <time.h>

/* Pour utiliser la correction automatique:
cavecorrector 6-7 repertoire
 */
 


Animal *creer_animal(int x, int y, float energie) {
  Animal *animal=malloc(sizeof(Animal)) ;
  if (animal == NULL) {
	  printf("Probleme d'allocation\n") ; 
	  return NULL;
	}
	if((x>=0)&&(x<SIZE_X)&&(y>=0)&&(y<SIZE_Y)){
		animal->x=x ;
		animal->y=y ;
		animal->energie=energie ;
		//tirage aléatoire entre -1 et 1
		animal->dir[0]=-1 + rand()%3;
		animal->dir[1]=-1 + rand()%3;
		animal->precedent=NULL;
		animal->suivant=NULL;
	
		return animal;
	}
	printf("Erreur de placement\n");
	return NULL;
}

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
	//si la liste est vide on retourne l'animal
	if(!liste){
		liste=animal;
		return liste;
	}
	//si l'animal n'est pas vide on le met en tete en modifiant le paramètre suivant et precedent
	if(animal){
		liste->precedent=animal;
		animal->suivant=liste;
		animal->precedent=NULL;
		return animal;	
	}
  return NULL;
}

void ajouter_animal(int x, int y, Animal **liste_animal) {
	if((x>=0)&&(x<SIZE_X)&&(y>=0)&&(y<SIZE_Y)){
		*liste_animal=ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
	}
	
}


void enlever_animal(Animal **liste, Animal *animal) {

	//si l'animal n'est pas en debut de liste
	if(animal->precedent) {
		animal->precedent->suivant = animal->suivant;
	}
 
	//si l'animal n'est pas en fin de liste
	if (animal->suivant) {
		animal->suivant->precedent = animal->precedent;
	}
	
	//si l'animal est en debut de liste
	if (*liste == animal) {
		*liste=animal->suivant;
	}
	 
	free(animal);
 
}

unsigned int compte_animal_rec(Animal *la) {
	if(la==NULL){
		return 0;
	}
	
	//si c'est le seul element de la
	if(la->suivant==NULL){
		return 1;
	}
	return compte_animal_rec(la->suivant)+1;
}

unsigned int compte_animal_it(Animal *la) {
	int cpt=0;
	while(la){
		la=la->suivant;
		cpt++;
	} return cpt;
}

void bouger_animaux(Animal *la) {
	while(la){
		if(la->energie!=0.0){
			if(((float)rand()/RAND_MAX)<p_ch_dir){
				la->x=((SIZE_X+(la->x+la->dir[0]))%SIZE_X);
				la->y=((SIZE_Y+(la->y+la->dir[1]))%SIZE_Y);
				
			}
		}
			la=la->suivant;
	}
}

void reproduce(Animal **liste_animal) {
        Animal *ani = * liste_animal;
        while(ani) {
                if (rand()/(float) RAND_MAX < p_reproduce) {
                        ajouter_animal(ani->x,ani->y,liste_animal);
                }
                ani=ani->suivant;
        }
}
	


void rafraichir_proies(Animal **liste_proie) {
	Animal *proie;
	bouger_animaux(*liste_proie);
	for(proie=*liste_proie;proie;proie=proie->suivant){
		if(proie->energie>0.0){
			proie->energie-=d_proie;
        }
		else enlever_animal(liste_proie,proie);    
    }
	reproduce(liste_proie);
}


Animal *animal_en_XY(Animal *l, int x, int y) {
	while(l){
		if((l->x==x)&&(l->y==y)){
			return l;
		}
		l=l->suivant;	
		
	}
	return NULL;
} 

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
	Animal *predateur;
	Animal *proie;
	bouger_animaux(*liste_predateur);
	for(predateur=*liste_predateur;predateur;predateur=predateur->suivant){
		if(predateur->energie>0.0){
			predateur->energie-=d_predateur; 
			proie=animal_en_XY(*liste_proie, predateur->x, predateur->y);
			if(proie){
				if(((float) rand()/RAND_MAX)<p_manger){
					predateur->energie=proie->energie;
					enlever_animal(liste_proie, proie);
				}
			}
		}
		else enlever_animal(liste_predateur,predateur);
	}
    
	reproduce(liste_predateur);
}

void afficher_ecosys(Animal *liste_proie,Animal *liste_predateur) {
	char tab[SIZE_X][SIZE_Y];
	int i,j ;
	for(i=0;i<SIZE_X;i++){
		for(j=0;j<SIZE_Y;j++){
			tab[i][j]=' ';

		}
	}	
	while(liste_proie){
		tab[liste_proie->x][liste_proie->y]='*';
		liste_proie=liste_proie->suivant;
	}
	while(liste_predateur){
		if(tab[liste_predateur->x][liste_predateur->y]=='*'){
			tab[liste_predateur->x][liste_predateur->y]='@';
			
		}
		else{
			tab[liste_predateur->x][liste_predateur->y]='O';
		}
		liste_predateur=liste_predateur->suivant;
	}
    printf("__________________________________________\n");
	for(i=0;i<SIZE_X;i++){
		printf("|");
		for(j=0;j<SIZE_Y;j++){
				printf("%c ",tab[i][j]);
		}
		printf("|");
		
			printf("\n");
	}
	printf("__________________________________________\n");

}
	

	
		

void clear_screen() {
	
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}










