#include "reproduction.h"
#include "satiete.h"
#include "animal.h"
#include "define.h"
#include "deplacement.h"
#include "ajout_animaux.h"

extern unsigned int tour_courant;
extern Animal* map;
extern int 
	nb_plancton,
	nb_corail,
	nb_bar,
	nb_thon,
	nb_pollution,
	nb_pyranha,
	nb_requin,
	nb_orque,
	nb_baleine;


BOOLEEN appliquerReproduction(int index)
{
	Animal animal_courant = map[index];
	int future_naissance, dir, gestamob;
	unsigned int reproduc = animal_courant.derniere_reproduction + animal_courant.frequence_reproduction;

	gestamob = animal_courant.gestation * animal_courant.metabolisme;

	if ( animal_courant.satiete >= gestamob
		 &&
		 reproduc < tour_courant
		 &&
		 animal_courant.espece != t_pollution
	   )
					            /* Si l'animal peut se reproduire */
									{
										dir=choisir_direction_aleatoire();
										future_naissance = get_new_pos(dir,index);
										Type espece_c = map[future_naissance].espece;
										switch(espece_c)
														{
															case 1:
																nb_plancton++;
																break;
															case 2:
																nb_corail++;
																break;
															case 3:
																nb_bar++;
																break;
															case 4:
																nb_thon++;
																break;
															case 5:
																nb_pollution++;
																break;
															case 6:
																nb_pyranha++;
																break;
															case 7:
																nb_requin++;
																break;
															case 8:
																nb_orque++;
																break;
															case 9:
																nb_baleine++;
																break;
															default:
																break;
														}

										if ( map[future_naissance].espece == t_vide)
										{
											 ajouter_animal(animal_courant.espece,future_naissance);
											/* Regles si reproduction */
											animal_courant.satiete -=  (animal_courant.gestation * animal_courant.metabolisme);
											animal_courant.derniere_reproduction = tour_courant;
											map[future_naissance].satiete += animal_courant.satiete;
											return vrai;
										}
										else return faux;
									}
	else
		return faux;

}
