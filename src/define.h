#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>

/* Macro pour le test si x est un poisson "réel" : ni mur, ni vide, ni pont, ni pecheur */

#define testPoisson(x) map[x].espece != t_vide &&  map[x].espece != t_mur && map[x].espece != t_pecheur && !estMur(x)

/* Quelques defines */

#define __DEHORS_MAP__ -1 /* En dehors de la map */
#define __POS_X_HAUT_GAUCHE__ 0
#define __POS_Y_HAUT_GAUCHE__ 0
#define __VALEUR_NULLE__ 0
#define __VALEUR_ERROR__ -1
#define __POS_PECHEUR_INIT__ _MAP_SIZE_ /2

// == Mode de jeu ==

#define __DEBUT_JEU__ {
#define __FIN_JEU__ }

// Define du main pour faciliter lecture
#define __Transition_tours__ tour_courant++;dessinerMap(police,0);
#define __Transition_tours__	tour_courant++;\
								dessinerMap(police,__DEHORS_MAP__);

// Condition pour la victoire version macro 

#define __Verifier_victory__ if ( posPecheur1 >= (_TAILLE_TOTALE_-_MAP_SIZE_) )\
																{\
																	victory=vrai;\
																	printf("Bravo, vous avez gagné !\n");\
																	SDL_BlitSurface(imgVictory, NULL, ecran, &posVictory);\
																	SDL_Flip(ecran);\
																	sleep(10);\
																}

#define _MAP_SIZE_ 30
#define _TAILLE_TOTALE_ _MAP_SIZE_*_MAP_SIZE_
#define __GAME_OVER__ 0
#define __NB_VIE__ 100
#define __SAC_BASE__ 0

/* Définition du nombre de cases parcourues par chaque animal */

#define _SAUT_MAX_ 1
#define _SAUT_MAX_PYRANHA_ 3
#define _SAUT_MAX_BALEINE_ 2
#define _IMMOBILE_ 0

/* Définition satiete / dernier repas et nombre de tours */

#define _NOMBRE_DE_TOURS_ 1000000

/* Définition du nombre de cases à remplir par Animal */
enum
{

    _NB_ORQUE_ = (unsigned int)(_TAILLE_TOTALE_*0.01),
    _NB_THON_ = (unsigned int)(_TAILLE_TOTALE_*0.2),
    _NB_PYRANHA_ = (unsigned int)(_TAILLE_TOTALE_*0.03),
    _NB_CORAIL_ = (unsigned int)(_TAILLE_TOTALE_*0.01),
    _NB_BAR_ = (unsigned int)(_TAILLE_TOTALE_*0.005),
    _NB_REQUIN_ = (unsigned int)(_TAILLE_TOTALE_*0.055),
    _NB_BALEINE_ = (unsigned int)(_TAILLE_TOTALE_*0.06),
    _NB_PLANCTON_ = (unsigned int)(_TAILLE_TOTALE_*0.10), /* 10% de plancton */
    _NB_POLLUTION_ = (unsigned int)(_TAILLE_TOTALE_*0.15), /* 15% de pollution */
    _NB_VIDE_ = (unsigned int)(_TAILLE_TOTALE_-(_NB_PLANCTON_+_NB_CORAIL_+_NB_BAR_+_NB_THON_+_NB_POLLUTION_+_NB_PYRANHA_+_NB_REQUIN_+_NB_ORQUE_+_NB_BALEINE_))
};

/* Définition durée de vie */

#define _DUREE_VIE_MAX_ 20

typedef enum
{
    d_vide, /* duree de vide de l'animal vide */
    d_corail = 25,
    d_bar=25,
    d_pyranha=25,
    d_requin=25,
    d_orque=25,
    d_baleine=25,
    d_thon=25,
    d_pollution=25,
    d_plancton=25,

} Duree_vie;

/* Définition du bide de chaque animal */
enum
{
    _BIDE_PLANCTON_=30,
    _BIDE_BAR_,
    _BIDE_POLLUTION_,
    _BIDE_CORAIL_,
    _BIDE_PYRANHA_,
    _BIDE_REQUIN_,
    _BIDE_ORQUE_,
    _BIDE_THON_,
    _BIDE_BALEINE_,
};

/* Définition de la taille procuré lorsqu'un animal est bouffé */
enum
{
    _TAILLE_PLANCTON_=1,
    _TAILLE_CORAIL_=1,
    _TAILLE_BAR_=1,
    _TAILLE_THON_=1,
    _TAILLE_POLLUTION_=2,
    _TAILLE_PYRANHA_=2,
    _TAILLE_REQUIN_=3,
    _TAILLE_ORQUE_=3,
    _TAILLE_BALEINE_=3,
};

/* Gestation */

enum
{

    _GESTATION_BAR_,
    _GESTATION_POLLUTION_,
    _GESTATION_THON_,
    _GESTATION_PLANCTON_,
    _GESTATION_PYRANHA_,
    _GESTATION_REQUIN_,
    _GESTATION_ORQUE_,
    _GESTATION_BALEINE_,
    _GESTATION_CORAIL_=3,

};

/* Frequence reproduction */
enum
{

    _FREQUENCE_REPRODUCTION_POLLUTION_,
    _FREQUENCE_REPRODUCTION_BALEINE_,
    _FREQUENCE_REPRODUCTION_PYRANHA_,
    _FREQUENCE_REPRODUCTION_THON_,
    _FREQUENCE_REPRODUCTION_ORQUE_,
    _FREQUENCE_REPRODUCTION_REQUIN_,
    _FREQUENCE_REPRODUCTION_BAR_,
    _FREQUENCE_REPRODUCTION_PLANCTON_=2,
    _FREQUENCE_REPRODUCTION_CORAIL_=3,
};

/* Définition des métabolisme */

enum
{

    _METABOLISME_POLLUTION,
    _METABOLISME_PLANCTON_,
    _METABOLISME_PYRANHA,
    _METABOLISME_REQUIN,
    _METABOLISME_ORQUE,
    _METABOLISME_BALEINE,
    _METABOLISME_THON,
    _METABOLISME_BAR,
    _METABOLISME_CORAIL_,

};

/* Satiete */

enum
{
    _SATIETE_POLLUTION=-1,
    _SATIETE_BALEINE,
    _SATIETE_BAR,
    _SATIETE_PYRANHA,
    _SATIETE_ORQUE,
    _SATIETE_THON,
    _SATIETE_CORAIL,
    _SATIETE_REQUIN,
    _SATIETE_PLANCTON
};

/* Définition de type */

typedef enum Type
{
    t_mur=-1,
    t_vide, /* il n'y a aucun animal dans la case */
    t_plancton, /* l'animal est un plancton */
    t_corail, /*  l'anomal est les corail */
    t_bar,
    t_thon,
    t_pollution, /* l'animal est la pollution */
    t_pyranha,
    t_requin,
    t_orque,
    t_baleine,
    t_pecheur,
    FIN
} Type;

#endif
