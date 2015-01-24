#ifndef _DESIGN_H
#define _DESIGN_H

#include "animal.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


/********************************************//**
 * \brief Genere les composantes graphiques de la carte et tous les petits carres et les textures
 *
 * \param TTF_Font* // la police
 * \param int
 * \return void
 *
 ***********************************************/
void dessinerMap(TTF_Font*,int);

/********************************************//**
 * \brief Permet de savoir si la case INDEX fait partie du bord de carte ou non (renvoie 1 si oui, 0 sinon).
 *
 * \param int INDEX
 * \return int
 *
 ***********************************************/
int estMur(int);

/********************************************//**
 * \brief Permet de Spawn le pecheur ou une animal a la case INDEX sur la carte
 *
 * \param int INDEX
 * \return void
 *
 ***********************************************/
void respawn(int index);

/********************************************//**
 * \brief Permet de déplacer le pecheur ou une animal a la case INDEX sur la carte
 *
 * \param int INDEX
 * \return void
 *
 ***********************************************/
 
void deplacerPecheur(int index);

/********************************************//**
 * \brief Permet d'afficher et de concatener la chaine et la value sur l'ecran.
 *
 * \param chaine char*
 * \param value int
 * \param x int
 * \param y int
 * \param police TTF_Font*
 * \return void
 *
 ***********************************************/
void print_values(char*,int,int,int,TTF_Font*);

/********************************************//**
 * \brief Permet d'afficher un filet sur l'ecran
 *
 * \param int
 * \param int
 * \return void
 *
 ***********************************************/
void affichage_filet(int,int);

#endif
