#ifndef _MOVE_H_
#define _MOVE_H_
#include "animal.h"
#include "satiete.h"
#include <stdlib.h>

typedef enum Direction
{
    HAUT, // 0
    HAUT_DROITE, // 1
    DROITE, // 2
    BAS_DROITE, // 3
    BAS, // 4
    BAS_GAUCHE, // 5
    GAUCHE, // 6
    HAUT_GAUCHE // 7

}Direction;


/********************************************//**
 * @brief Fait déplacer l'animal dans une case vide
 *
 * @param int
 * @param int
 * @return BOOLEEN
 *
 ***********************************************/
BOOLEEN moveA(int,int);

/********************************************//**
 * \brief Permet de choisir une direction aleatoire
 *
 * \param void
 * \return Direction
 *
 ***********************************************/
Direction choisir_direction_aleatoire(void); /* génére une direction aléatoire */

/********************************************//**
 * \brief Permet de se deplacer sur la prochaine case de la map dans la direction d
 *
 * \param d Direction
 * \param caseCourante int
 * \return int
 *
 ***********************************************/
int get_new_pos(Direction d,int caseCourante);

#endif
