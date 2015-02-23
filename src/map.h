#ifndef _MAP_H_
#define _MAP_H_
#include "animal.h"

/********************************************//**
 * \brief Genere aleatoirement tous les animaux dans la map
 *
 * \param void
 * \return void
 *
 ***********************************************/
void genererMap(void);

/********************************************//**
 * \brief Pioche une case aleatoire entre la valeur a et b dans la carte
 *
 * \param int a
 * \param int b
 * \return int
 *
 ***********************************************/
int case_aleatoire(int, int);

/********************************************//**
 * \brief Selectionne une par une et une seule fois une case de la carte
 * \brief Au final c'est une pile qui permet de parcourir aleatoirement toute la carte
 * \brief Cette fonction renvoie une pile.
 * \param int a
 * \param int b
 * \return int*
 *
 ***********************************************/
int* alea(int,int);

#endif
