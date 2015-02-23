#include "define.h"
#include "ajout_animaux.h"
#include "animal.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

extern size_t dernier_repas;
extern Animal* map;

void ajouter_animal_alea(Type t_animal)
{

    unsigned int* compteurs = calloc((NB_ANIMAUX+1),sizeof(unsigned int)); /* 9 cases pour notre tableau de compteurs */
    int i,espece;

    switch(t_animal)
    {
    case t_plancton:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_PLANCTON_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            // Notre for est spécial : il va generer un indice de case aléatoire
            //  puis va parcourir le tableau tant que
            //  notre compteur n'est pas complet en générant à chaque fois un nouveau i
            if(map[i].espece == t_vide)
                // la case étant disponilbe, on ajoute donc un animal de type
                //  t_plancton. il y aura dès lors un plancton vivant à la case map+i

            {
                (map+i)->espece = t_plancton;
                (map+i)->duree_survie = d_plancton;
                (map+i)->taille_bide = _BIDE_PLANCTON_;
                (map+i)->metabolisme = _METABOLISME_PLANCTON_;
                (map+i)->gestation = _GESTATION_PLANCTON_;
                (map+i)->taille = _TAILLE_PLANCTON_;
                (map+i)->saut_max = _IMMOBILE_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_PLANCTON_;

                (map+i)->satiete = _SATIETE_PLANCTON;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;

                compteurs[t_animal-1]++;// un plancton a été crée, il en reste encore _NB_PLANCTON_-1 à créer
								  //pour atteindre notre pourcentage. on incrémente alors le compteur de
								  //plancton
            }
        }
        break;

		case t_corail:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_CORAIL_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(map[i].espece == t_vide)
            {
                (map+i)->espece = t_corail;
                (map+i)->duree_survie = d_corail;
                (map+i)->taille_bide = _BIDE_CORAIL_;
                (map+i)->metabolisme = _METABOLISME_CORAIL_;
                (map+i)->gestation = _GESTATION_CORAIL_;
                (map+i)->taille = _TAILLE_CORAIL_;
                (map+i)->saut_max = _IMMOBILE_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_CORAIL_;

                (map+i)->satiete = _SATIETE_CORAIL;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;

                compteurs[t_animal-1]++;
            }
        }
        break;
  /*  case t_bar:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_BAR_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(map[i].espece == t_vide)
            {
                (map+i)->espece = t_bar;
                (map+i)->duree_survie = d_bar;
                (map+i)->taille_bide = _BIDE_BAR_;
                (map+i)->metabolisme = _METABOLISME_BAR;
                (map+i)->gestation = _GESTATION_BAR_;
                (map+i)->taille = _TAILLE_BAR_;
                (map+i)->saut_max = _SAUT_MAX_PETIT_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_BAR_;

                (map+i)->satiete = _SATIETE_BAR;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;


                compteurs[t_animal-1]++;
            }
        }
        break;
 */   case t_thon:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_THON_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if( map[i].espece == t_vide)
            {
                (map+i)->espece = t_thon;
                (map+i)->duree_survie = d_thon;
                (map+i)->taille_bide = _BIDE_THON_;
                (map+i)->metabolisme = _METABOLISME_THON;
                (map+i)->gestation = _GESTATION_THON_;
                (map+i)->taille = _TAILLE_THON_;
                (map+i)->saut_max = _SAUT_MAX_PETIT_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_THON_;

                (map+i)->satiete = _SATIETE_THON;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;
                compteurs[t_animal-1]++;
            }
        }
        break;
    case t_pollution:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_POLLUTION_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(espece == t_vide)
            {
                (map+i)->espece = t_pollution;
                (map+i)->duree_survie = d_pollution;
                (map+i)->taille_bide = _BIDE_POLLUTION_;
                (map+i)->metabolisme = _METABOLISME_POLLUTION;
                (map+i)->gestation = _GESTATION_POLLUTION_;
                (map+i)->taille = _TAILLE_POLLUTION_;
                (map+i)->saut_max = _SAUT_MAX_PETIT_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_POLLUTION_;
                (map+i)->satiete = _SATIETE_POLLUTION;
                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;
                compteurs[t_animal-1]++;
            }
        }
        break;
/*		case t_pyranha:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_PYRANHA_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(espece == t_vide)
            {
                (map+i)->espece = t_pyranha;
                (map+i)->duree_survie = d_pyranha;
                (map+i)->taille_bide = _BIDE_PYRANHA_;
                (map+i)->metabolisme = _METABOLISME_PYRANHA;
                (map+i)->gestation = _GESTATION_PYRANHA_;
                (map+i)->taille = _TAILLE_PYRANHA_;
                (map+i)->saut_max = _SAUT_MAX_MOYEN_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_PYRANHA_;

                (map+i)->satiete = _SATIETE_PYRANHA;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 4;
                compteurs[t_animal-1]++;
            }
        }
        break;
    */  case t_requin:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_REQUIN_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if( espece == t_vide)
            {
                (map+i)->espece = t_requin;
                (map+i)->duree_survie = d_requin;
                (map+i)->taille_bide = _BIDE_REQUIN_;
                (map+i)->metabolisme = _METABOLISME_REQUIN;
                (map+i)->gestation = _GESTATION_REQUIN_;
                (map+i)->taille = _TAILLE_REQUIN_;
                (map+i)->saut_max = _SAUT_MAX_MOYEN_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_REQUIN_;

                (map+i)->satiete = _SATIETE_REQUIN;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 4;
                compteurs[t_animal-1]++;
            }
        }
        break;
    case t_orque:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_ORQUE_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(espece == t_vide)
            {
                (map+i)->espece = t_orque;
                (map+i)->duree_survie = d_orque;
                (map+i)->taille_bide = _BIDE_ORQUE_;
                (map+i)->metabolisme = _METABOLISME_ORQUE;
                (map+i)->gestation = _GESTATION_ORQUE_;
                (map+i)->taille = _TAILLE_ORQUE_;
                (map+i)->saut_max = _SAUT_MAX_MOYEN_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_ORQUE_;

                (map+i)->satiete = _SATIETE_ORQUE;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;
                compteurs[t_animal-1]++;
            }
        }
        break;
    case t_baleine:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_BALEINE_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(espece == t_vide)
            {
                (map+i)->espece = t_baleine;
                (map+i)->duree_survie = d_baleine;
                (map+i)->taille_bide = _BIDE_BALEINE_;
                (map+i)->metabolisme = _METABOLISME_BALEINE;
                (map+i)->gestation = _GESTATION_BALEINE_;
                (map+i)->taille = _TAILLE_BALEINE_;
                (map+i)->saut_max = _SAUT_MAX_GROS_;
                (map+i)->frequence_reproduction = _FREQUENCE_REPRODUCTION_BALEINE_;

                (map+i)->satiete = _SATIETE_BALEINE;

                (map+i)->dernier_repas = dernier_repas;
                (map+i)->derniere_reproduction = 0;
                compteurs[t_animal-1]++;
            }
        }
        break;

    case t_mur:
        for(i= case_aleatoire(0,_TAILLE_TOTALE_); compteurs[t_animal-1] < _NB_BAR_; i=case_aleatoire(0,_TAILLE_TOTALE_))
        {
            espece = map[i].espece;
            if(espece == t_vide)
            {
                (map+i)->espece = t_mur;
                (map+i)->duree_survie = 0;
                (map+i)->taille_bide = 0;
                (map+i)->metabolisme = 0;
                (map+i)->gestation = 0;
                (map+i)->taille = 0;
                (map+i)->saut_max = 0;
                (map+i)->frequence_reproduction = 0;

                (map+i)->satiete = 0;

                (map+i)->dernier_repas = 0;
                (map+i)->derniere_reproduction = 0;


                compteurs[t_animal-1]++;
            }
        }
        break;

    default:
        break;
    }
    //VIDER_POINTEUR(compteurs);
}

void ajouter_all_animaux(void)
{
    int i;
    for(i=1; i<=NB_ANIMAUX; i++)
    {
        ajouter_animal_alea(i);
    }
}
void supprimer_animal(int position_map)
/* Bien mieux que get animal vide : on prend en compte la position de la map en plus !*/
{
    map[position_map].espece = t_vide;
}

void ajouter_mur(int position_map)
/* Bien mieux que get animal vide : on prend en compte la position de la map en plus !*/
{
    map[position_map].espece = t_mur;
}

void ajouter_animal(Type t_animal, int pos)
{
    switch(t_animal)
    {
    case t_plancton:

        /* Notre for est spécial : il va generer un indice de case aléatoire
           puis va parcourir le tableau tant que
           notre compteur n'est pas complet en générant à chaque fois un nouveau i */
        if((map+pos)->espece == t_vide)
            /* la case étant disponilbe, on ajoute donc un animal de type
               t_plancton. il y aura dès lors un plancton vivant à la case map+pos
            */
        {
            (map+pos)->espece = t_plancton;
            (map+pos)->duree_survie = d_plancton;
            (map+pos)->taille_bide = _BIDE_PLANCTON_;
            (map+pos)->metabolisme = _METABOLISME_PLANCTON_;
            (map+pos)->gestation = _GESTATION_PLANCTON_;
            (map+pos)->taille = _TAILLE_PLANCTON_;
            (map+pos)->saut_max = _IMMOBILE_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_PLANCTON_;

            (map+pos)->satiete = _SATIETE_PLANCTON;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;

            /* un plancton a été crée, il en reste encore _NB_PLANCTON_-1 à créer
            				  pour atteindre notre pourcentage. on incrémente alors le compteur de
            				  plancton*/
        }

        break;

    case t_corail:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_corail;
            (map+pos)->duree_survie = d_corail;
            (map+pos)->taille_bide = _BIDE_CORAIL_;
            (map+pos)->metabolisme = _METABOLISME_CORAIL_;
            (map+pos)->gestation = _GESTATION_CORAIL_;
            (map+pos)->taille = _TAILLE_CORAIL_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_CORAIL_;

            (map+pos)->satiete = _SATIETE_CORAIL;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;


        }

        break;
    case t_bar:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_bar;
            (map+pos)->duree_survie = d_bar;
            (map+pos)->taille_bide = _BIDE_BAR_;
            (map+pos)->metabolisme = _METABOLISME_BAR;
            (map+pos)->gestation = _GESTATION_BAR_;
            (map+pos)->taille = _TAILLE_BAR_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_BAR_;

            (map+pos)->satiete = _SATIETE_BAR;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;



        }

        break;

    case t_thon:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_thon;
            (map+pos)->duree_survie = d_thon;
            (map+pos)->taille_bide = _BIDE_THON_;
            (map+pos)->metabolisme = _METABOLISME_THON;
            (map+pos)->gestation = _GESTATION_THON_;
            (map+pos)->taille = _TAILLE_THON_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_THON_;

            (map+pos)->satiete = _SATIETE_THON;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;

        }

        break;
    case t_pollution:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_pollution;
            (map+pos)->duree_survie = d_pollution;
            (map+pos)->taille_bide = _BIDE_POLLUTION_;
            (map+pos)->metabolisme = _METABOLISME_POLLUTION;
            (map+pos)->gestation = _GESTATION_POLLUTION_;
            (map+pos)->taille = _TAILLE_POLLUTION_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_POLLUTION_;

            (map+pos)->satiete = _SATIETE_POLLUTION;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;

        }

        break;
    case t_pyranha:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_pyranha;
            (map+pos)->duree_survie = d_pyranha;
            (map+pos)->taille_bide = _BIDE_PYRANHA_;
            (map+pos)->metabolisme = _METABOLISME_PYRANHA;
            (map+pos)->gestation = _GESTATION_PYRANHA_;
            (map+pos)->taille = _TAILLE_PYRANHA_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_PYRANHA_;

            (map+pos)->satiete = _SATIETE_PYRANHA;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 4;

        }

        break;
    case t_requin:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_requin;
            (map+pos)->duree_survie = d_requin;
            (map+pos)->taille_bide = _BIDE_REQUIN_;
            (map+pos)->metabolisme = _METABOLISME_REQUIN;
            (map+pos)->gestation = _GESTATION_REQUIN_;
            (map+pos)->taille = _TAILLE_REQUIN_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_REQUIN_;

            (map+pos)->satiete = _SATIETE_REQUIN;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 4;

        }

        break;
    case t_orque:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_orque;
            (map+pos)->duree_survie = d_orque;
            (map+pos)->taille_bide = _BIDE_ORQUE_;
            (map+pos)->metabolisme = _METABOLISME_ORQUE;
            (map+pos)->gestation = _GESTATION_ORQUE_;
            (map+pos)->taille = _TAILLE_ORQUE_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_ORQUE_;

            (map+pos)->satiete = _SATIETE_ORQUE;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;

        }

        break;
    case t_baleine:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_baleine;
            (map+pos)->duree_survie = d_baleine;
            (map+pos)->taille_bide = _BIDE_BALEINE_;
            (map+pos)->metabolisme = _METABOLISME_BALEINE;
            (map+pos)->gestation = _GESTATION_BALEINE_;
            (map+pos)->taille = _TAILLE_BALEINE_;
            (map+pos)->saut_max = _SAUT_MAX_;
            (map+pos)->frequence_reproduction = _FREQUENCE_REPRODUCTION_BALEINE_;

            (map+pos)->satiete = _SATIETE_BALEINE;

            (map+pos)->dernier_repas = dernier_repas;
            (map+pos)->derniere_reproduction = 0;

        }

        break;

    case t_mur:

        if((map+pos)->espece == t_vide)
        {
            (map+pos)->espece = t_mur;
            (map+pos)->duree_survie = 0;
            (map+pos)->taille_bide = 0;
            (map+pos)->metabolisme = 0;
            (map+pos)->gestation = 0;
            (map+pos)->taille = 0;
            (map+pos)->saut_max = 0;
            (map+pos)->frequence_reproduction = 0;

            (map+pos)->satiete = 0;

            (map+pos)->dernier_repas = 0;
            (map+pos)->derniere_reproduction = 0;



        }

        break;

    default:
        (map+pos)->taille = 0;
        break;
    }

}
