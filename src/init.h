#ifndef _INIT_H
#define _INIT_H
#include "constantes.h"
#include "define.h"
#include "animal.h"
#include "deplacement.h"

/********************************************//**
 * @brief Initialise les composants graphiques SDL au démarrage du programme
 *
 * @param char*
 * @return void
 *
 ***********************************************/
void sdl_loader(char*);

/********************************************//**
 * @brief Initialise la map, avec le quadrillage et les bordures
 *
 * @param SDL_Rect*
 * @return void
 *
 ***********************************************/
void init_map(SDL_Rect* );

/********************************************//**
 * @brief Décharge la surface ecran et reblit les logos, img sur celui-ci
 *
 * @param void
 * @return void
 *
 ***********************************************/
void reinit_params(TTF_Font*);

/********************************************//**
 * @brief Affiche le logo du sac du pêcheur ansi que sa contenance
 *
 *
 * @param void
 * @return void
 *
 ***********************************************/
void print_sac(TTF_Font*);

/********************************************//**
 * \brief Affiche une image à l'ecran
 *
 * \param char*
 * \param int x
 * \param int y
 * \return void
 *
 ***********************************************/
void print_img_onScreen(char*,int,int);

/********************************************//**
 * @brief Affiche le texte de la légende sur l'écran
 *
 * @param void
 * @return void
 *
 ***********************************************/
void print_legend(TTF_Font*);

/********************************************//**
 * \brief Affiche en coordonnee x,y le texte
 *
 * \param char* chaine
 * \param int x
 * \param int y
 * \param int taillePolice
 * \return void
 *
 ***********************************************/
void print_screen(char* ,int , int, TTF_Font*);

/********************************************//**
 * @brief Ecoute les évènement SDL et les traites un par un, fonction non bloquante ( mvt pêcheur, peche ...)
 *
 * @param  Animal*
 * @param SDL_Event
 * @return void
 *
 ***********************************************/
void SDL_event_listener(SDL_Event,TTF_Font*);
/********************************************//**
 * \brief Permet d'afficher a l'ecran le menu de peche et de renvoyer le choix fait par le joueur
 *
 * \param void
 * \return int
 *
 ***********************************************/
int choixPeche(TTF_Font*);

/********************************************//**
 * \brief Permet le choix de la peche et de choisir une direction par l'appui d'une touche a l'ecran
 *
 * \param int positionDuPecheur
 * \return void
 *
 ***********************************************/
void pecheravecdirection(int,TTF_Font*);

/********************************************//**
 * \brief Affiche l'aide a droite de la carte
 *
 * \param void
 * \return void
 *
 ***********************************************/
void print_help(TTF_Font*);

/********************************************//**
 * @brief Affiche les points de vie actuels du pêcheur (sous forme de coeur)
 *
 * @param TTF_Font*
 * @return void
 *
 ***********************************************/
void afficher_pvPecheur(TTF_Font*);

/********************************************//**
 * @brief Affiche le menu de départ du jeu
 *
 * @param TTF_Font*
 * @return void
 *
 ***********************************************/
int afficher_menu(TTF_Font*);

#endif
