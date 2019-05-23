#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_PROIES 20
#define NB_PREDATEURS 20

  /* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float d_proie=1;
float d_predateur=1;
float p_manger=0.2;
float p_reproduce=0.01;
float energie=50;


int main(void) {

  	srand(time(NULL));
  	
	//Initialisation de la liste des proies
 	Animal *proies=NULL;
	Animal *proie;
	proie=creer_animal(0,9,energie);
	proies=ajouter_en_tete_animal(proies, proie);
	Animal *proie2;
	proie2=creer_animal(15,0,energie);
	proies=ajouter_en_tete_animal(proies, proie2);
	Animal *proie3;
	proie3=creer_animal(11,19,energie);
	proies=ajouter_en_tete_animal(proies, proie3);
 	
 	
 	//Initialisation de la liste des predateurs
	Animal *predateurs=NULL;
	Animal *preda;
	preda=creer_animal(0,11,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda);
	Animal *preda2;
	preda2=creer_animal(0,9,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda2);
	Animal *preda3;
	preda3=creer_animal(18,3,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda3);
	
	afficher_ecosys(proies,predateurs); 
	printf("Il y a %d proies.\n",compte_animal_it(proies));
	printf("Il y a %d prédateurs.\n",compte_animal_rec(predateurs));
	

  	return 0;
}
