#ifndef _ANIMAL_H_
#define _ANIMAL_H_
#include <sys/types.h>

#include "define.h"

/* type enuméré -> Duree_vie, permet de saisir la durée
de chaque animal. Represente l'enrgie total de l'animal
*/

/*  structure animal, definie toutes les caractéristiques d'un animal*/
typedef struct Animal
{

    int dernier_repas; /**<  nombre de tours depuis dernier repas*//* nombre de tours depuis dernier repas */
    unsigned int derniere_reproduction; /**<  nombre de tours depuis derniere reproduction*//* nombre de tours depuis derniere reproduction */
    int satiete; /**< nombre de tours de survie supp du dernier repas *//* nombre de tours de survie supp du dernier repas */
    /************************** Constantes ***************************************/
    Duree_vie duree_survie; /**< Nombre de tours pendant lesquels l'animal survit sans manger *//* Nombre de tours pendant lesquels l'animal survit sans manger. */
    int taille_bide;/**< la taille que l'animal peut avoir de rempli *//* la taille que l'animal peut avoir de rempli. */
    Type espece;/**< Numero specifique à l'animal représente sons type */ /* Numero specifique à l'animal représente sons type */
    int metabolisme; /**< Energie dépensée pour vivre *//* Energie dépensée pour vivre. */
    int gestation;/**< Energie déprnsée par reproduction */ /* Energie déprnsée par reproduction */
    unsigned int taille; /**< taille procurée aux prédateurs *//* taille procurée aux prédateurs. */
    int saut_max;/**< Nombre de déplacement max */ /* Nombre de déplacement max */
    unsigned int frequence_reproduction; /**< Frequence a laquelle l'animal se reproduit */

    unsigned int sac; /**< Si l'animal est un pecheur, contenance du sac *//* pr le pecheur */

}Animal;

/********************************************//**
 * \brief Donne le maximum entre a et b
 *
 * \param a int
 * \param b int
 * \return int
 *
 ***********************************************/
int max(int,int);

#endif
