#ifndef _PECHE_H
#define _PECHE_H
#include "animal.h"
#include "deplacement.h"
#include "init.h"
#include "design.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define TAILLE_FILET 8
#define CAPACITE_FILET 8
#define DISTANCE_FILET 4
#define PECHE_INTERDITE (current.espece != t_pollution) && (current.espece != t_mur) && (current.espece != t_pecheur) && (current.espece != t_vide) && (current.espece != t_plancton)


/********************************************//**
 * \brief Construit un pont sur la future case ou appel la fonction peche si le sac est vide
 *
 * \param int
 * \param Direction
 * \param TTF_Font*
 * \return int
 *
 ***********************************************/
int construire_pont(int,Direction,TTF_Font*);


/********************************************//**
 * \brief Permet de lancer le filet dans une direction sur la map et de récupèrer un tableau avec les indices des poissons dans le filet
 * \brief Utilise la variable DISTANCE_FILET et TAILLE_FILET
 *
 * \param int
 * \param Direction
 * \return int**
 *
 ***********************************************/
int** lancer_filet(int,Direction);

int lancer_canne(int,int,TTF_Font*);

/********************************************//**
 * \brief Permet de tirer au sort CAPACITE_FILET poissons dans le filet. par exemple si le filet contient 25 cases, seulement 8 possont au plus pourront être pechés.
 *
 * \param  int**
 * \return void
 *
 ***********************************************/
void traitement_sur_poisson_peches_au_filet(int **);


/********************************************//**
 * \brief Permet de pecher reellement les poissons dans le filet
 *
 * \param int
 * \param Direction
 * \param TTF_Font*
 * \return void
 *
 ***********************************************/
void pecher(int,Direction,TTF_Font*);


#endif
