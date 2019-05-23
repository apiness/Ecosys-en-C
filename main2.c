#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


  /* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.5;
float d_proie=1;
float d_predateur=1;
float p_manger=1;
float p_reproduce=0.01;
float energie=50;


int main(void) {

	srand(time(NULL));
	//Initialisation de la liste des proies
	Animal *proies=NULL;
	Animal *proie;
	proie=creer_animal(13,6,energie);
	proies=ajouter_en_tete_animal(proies, proie);
	Animal *proie2;
	proie2=creer_animal(4,18,energie);
	proies=ajouter_en_tete_animal(proies, proie2);
	Animal *proie3;
	proie3=creer_animal(0,14,energie);
	proies=ajouter_en_tete_animal(proies, proie3);
	Animal *proie4;
	proie4=creer_animal(19,0,energie);
	proies=ajouter_en_tete_animal(proies, proie4);
	Animal *proie5;
	proie5=creer_animal(9,16,energie);
	proies=ajouter_en_tete_animal(proies, proie5);
	
	
 	//Initialisation de la liste des predateurs
	Animal *predateurs=NULL;
	Animal *preda;
	preda=creer_animal(0,0,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda);
	Animal *preda2;
	preda2=creer_animal(7,9,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda2);
	Animal *preda3;
	preda3=creer_animal(18,3,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda3);
	Animal *preda4;
	preda4=creer_animal(15,1,energie);
	predateurs=ajouter_en_tete_animal(predateurs, preda4);
	
	
	afficher_ecosys(proies,predateurs); 
	printf("Il y a %d proies.\n",compte_animal_it(proies));
	printf("Il y a %d prédateurs.\n",compte_animal_rec(predateurs));
	while(1){
		if(proies && predateurs){
			rafraichir_proies(&proies);
			rafraichir_predateurs(&predateurs, &proies);
			afficher_ecosys(proies,predateurs); 
			printf("Il y a %d proies.\n",compte_animal_it(proies));
			printf("Il y a %d prédateurs.\n",compte_animal_rec(predateurs));
			usleep(100000);
		}else{
			break;
		}
	}if(!compte_animal_it(proies)){
		printf("Toutes les proies sont mortes par manque d'énergie ou ont été mangées !\n");
	}else{
		if(!compte_animal_it(predateurs)){
			printf("Tous les prédateurs sont morts par manque d'énergie !\n");
		}
	}
			
return 0;
}


