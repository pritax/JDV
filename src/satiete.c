#include "animal.h"
#include "satiete.h"
#include "ajout_animaux.h"

extern unsigned int tour_courant;
extern Animal* map;

BOOLEEN appliquerSatiete(int index)
{
	Animal animal_courant = map[index];
	unsigned int balance = tour_courant - animal_courant.dernier_repas;
		if( (animal_courant.satiete <= 0) &&
										( balance > animal_courant.duree_survie)
										)
										/* On compare tour - date du dernier repas à duree de survie*/
								{
									supprimer_animal(index);
									return vrai;
								}
		else return faux;
}
