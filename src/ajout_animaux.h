#ifndef _AJOUT_ANIMAUX_
#define _AJOUT_ANIMAUX_
#include "define.h"
#include "animal.h"
#define NB_ANIMAUX FIN-1 /* FIN = 10 */

/********************************************//**
 * @brief Ajout un animal dans une case aléatoire de notre map
 *
 * @param Type
 * @return void
 *
 ***********************************************/
void ajouter_animal_alea(Type);

/********************************************//**
 * @brief Ajouter un animal à partir de sa position dans la map
 *
 * @param int
 * @return void
 *
 ***********************************************/
void ajouter_animal(Type, int);


/********************************************//**
 * @brief Supprime un animal à partir de sa position dans la map
 *
 * @param int
 * @return void
 *
 ***********************************************/
void supprimer_animal(int);


/********************************************//**
 * @brief Ajoute tous les animaux dans la map (à l'initialisation)
 *
 * @param void
 * @return void
 *
 ***********************************************/
void ajouter_all_animaux(void);


/********************************************//**
 * @brief Ajout un mur dans une case donnée (mur ou pont)
 *
 * @param int
 * @return void
 *
 ***********************************************/
void ajouter_mur(int);


/********************************************//**
 * @brief Ajout un pecheur à partir de sa position dans la map
 *
 * @param int
 * @return void
 *
 ***********************************************/
void ajouterPecheur(int);

#endif

