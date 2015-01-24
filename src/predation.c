#include "predation.h"
#include "animal.h"
#include "satiete.h"
#include "define.h"
#include "ajout_animaux.h"
#include "deplacement.h"
#include "design.h"

extern Animal* map;
extern unsigned int pvPecheur1;

BOOLEEN predater(int index)
{
    int future_proie, taille_FP;
    Direction dir;
    Animal animal_courant = map[index];

    dir=choisir_direction_aleatoire();
    future_proie = get_new_pos(dir,index);
    taille_FP = map[future_proie].taille;

    switch(animal_courant.espece)
    {
    case t_corail:
        if ( map[future_proie].espece == t_plancton &&
                (unsigned int)( taille_FP + animal_courant.satiete) < (unsigned int)animal_courant.taille_bide
           )
            /* Si Corail peut manger plancton */
        {
            map[future_proie] = animal_courant; /* On copie dans la case future le corail */
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;

        }
    case t_bar:
        if ( (map[future_proie].espece == t_plancton || (map[future_proie].espece == t_mur && !estMur(future_proie)))
			&&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide
           )
            /* Si bar peut manger plancton */
        {
            map[future_proie] = animal_courant; /* On copie dans la case future le bar */
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;

        }
    case t_thon:
        if ( (map[future_proie].espece == t_plancton || (map[future_proie].espece == t_mur && !estMur(future_proie)))
			&&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide
           )
            /* Si thon peut manger plancton */
        {
            map[future_proie] = animal_courant; /* On copie dans la case future le thon */
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;

        }
        if ( (map[future_proie].espece == t_pecheur) )
			{
				pvPecheur1--;
				return vrai;
			}
    case t_pollution:
        if ( map[future_proie].espece == t_corail &&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide
           )
            /* Si pollution peut manger plancton */
        {
            map[future_proie] = animal_courant; /* On copie dans la case future la pollution */
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;

        }
    case t_pyranha:
        if ( (map[future_proie].espece == t_bar &&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide)
                ||
                (map[future_proie].espece == t_thon &&
                 (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide)
           )
        {
            map[future_proie] = animal_courant;
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;
        }
        if ( (map[future_proie].espece == t_pecheur) )
			{
				pvPecheur1--;
				return vrai;
			}
    case t_requin:
        if ( map[future_proie].espece == t_bar
				&&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide
           )
        {
            map[future_proie] = animal_courant;
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;

        }
    case t_orque:
        if ( map[future_proie].espece == t_requin  &&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide
           )
        {
            map[future_proie] = animal_courant;
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;
        }
    case t_baleine:
        if ( (map[future_proie].espece == t_plancton || (map[future_proie].espece == t_mur && !estMur(future_proie)))
			&&
                (unsigned int)( taille_FP + animal_courant.taille) < (unsigned int)animal_courant.taille_bide
           )
            /* Si Baleine peut manger plancton */
        {
            map[future_proie] = animal_courant; /* On copie dans la case future la baleine */
            supprimer_animal(index);
            map[future_proie].satiete += taille_FP;
            return vrai;

        }
        if ( (map[future_proie].espece == t_pecheur) )
			{
				pvPecheur1--;
				return vrai;
			}
    default:
        return faux;
    } /* fin switch espece */
}