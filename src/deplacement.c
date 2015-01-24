#include "deplacement.h"
#include "map.h"
#include "animal.h"
#include "define.h"
#include "ajout_animaux.h"
#include "satiete.h"

extern Animal* map;

BOOLEEN moveA(int position, int nb_case)
{

	int i,pos_future;
	Direction direction_courante;

	direction_courante= choisir_direction_aleatoire();
	pos_future = get_new_pos(direction_courante,position);

	for(i=0; i< nb_case && (map+pos_future)->espece != t_mur && (map+pos_future)->espece == t_vide; i++)
	{
		map[pos_future] = map[position]; /* Déplace l'animal : copie */
		supprimer_animal(position); /* On supprime l'animal */
		if ( map[pos_future].espece != t_plancton)
			map[pos_future].satiete--;

		pos_future = get_new_pos(direction_courante,position);
	}
	return vrai;

}

Direction choisir_direction_aleatoire(void)
{

    Direction dir= HAUT+(Direction)rand()%(HAUT_GAUCHE-HAUT+1);


    return dir;

}


int get_new_pos(Direction direction_courante,int position)
{

	int pos_future;
	switch(direction_courante)
	{
		case HAUT:
					pos_future = position-_MAP_SIZE_;
					break;
		case HAUT_DROITE:
					pos_future = position-(_MAP_SIZE_+1);
					break;
		case DROITE:
					pos_future = position + 1;
					break;
		case BAS_DROITE:
					pos_future = position+(_MAP_SIZE_+1);
					break;
		case BAS:
					pos_future = position+_MAP_SIZE_;
					break;
		case BAS_GAUCHE:
					pos_future = position+(_MAP_SIZE_-1);
					break;
		case GAUCHE:
					pos_future = position - 1;
					break;
		case HAUT_GAUCHE:
					pos_future = position-(_MAP_SIZE_-1);
					break;
		default:
					pos_future = -1;
	}
	return pos_future;
}
