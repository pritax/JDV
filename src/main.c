#include "define.h"
#include "init.h"
#include "map.h"
#include "design.h"
#include "constantes.h"
#include "ajout_animaux.h"
#include "deplacement.h"
#include "satiete.h"
#include "reproduction.h"
#include "predation.h"
#include "constantes.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>


unsigned int
				tour_courant  = __INIT_VALEUR_JEU__,
				dernier_repas = __INIT_VALEUR_JEU__,
				posPecheur1;
Animal* map;
BOOLEEN victory = faux;

extern unsigned int sacPecheur1,pvPecheur1;

extern SDL_Surface 
					*imgVictory,
					*ecran;

int main(int argc, char* argv[])
{
	int 
		i				= __VALEUR_NULLE__,
		j				= __VALEUR_NULLE__,
		index			= __VALEUR_NULLE__,
		degradation		= __VALEUR_NULLE__,
		ModeDeJeu		= __VALEUR_NULLE__,
		tour_mod		= __VALEUR_NULLE__;
		
	Animal animal_courant;
	int* tab=NULL;
	TTF_Font* police;
    SDL_Event eventquit;
    
    SDL_Rect posVictory;
				posVictory.x = __POS_X_HAUT_GAUCHE__;
				posVictory.y = __POS_Y_HAUT_GAUCHE__;

	srand(time(NULL));

	/* Fin déclaration variables */
    sdl_loader("Jeu de la vie | Try your best !");
    
    
	/* ############################################## Début prog ############################################## */
	
	TTF_Init(); // Init de la police graphique
	
    police=TTF_OpenFont("img/calibri.ttf", 15); // On définit la police
    
	genererMap();
	
	/* affecte des animaux à l'intérieur de la map */

	ajouter_all_animaux();
	posPecheur1=__POS_PECHEUR_INIT__;
	
	
	posPecheur1 = __POS_PECHEUR_INIT__;
    respawn(posPecheur1);

    // === Definition mode de jeu ===

    ModeDeJeu=afficher_menu(police);

	switch(ModeDeJeu)
	__DEBUT_JEU__
		case 2:
				// Config du jeu
				printf("Pas de config actuellement.\n");
				break;
		case 1:
				// Mode flag fish
				printf("Ce mode sera disponible dans la prochaine version du Jeu de La vie, re-testez le d'ici là. A+\n");
				break;
		default:
				// Mode normal

			dessinerMap(police,__DEHORS_MAP__); //  on dessine la map avec les animaux qui viennent de naître

					while(tour_courant <= _NOMBRE_DE_TOURS_ && victory == faux )
							{
								// on traite les évènements SDL, clavier, souris, fentre ...
									if(tour_mod == 30){ tour_mod=0;}
									else 
									{
										tour_mod++;
										continue;
									}
								SDL_event_listener(eventquit,police);
								tab = alea(_TAILLE_TOTALE_,_TAILLE_TOTALE_);
								
								// == Test Pecheur ==
								
								printf("Vie du pecheur %d\n",pvPecheur1);
								if ( pvPecheur1 <= 0 )
												{
													printf("Vous êtes DEAD (mdr), vous allez respawn\n");
													respawn(posPecheur1);
													//SDL_Flip(ecran);
													sacPecheur1 = 0;
													sleep(1);
												}
									else
										printf("Vous êtes encore ALIVE\n");
													
								// == Fin test Pecheur ==
													
									for(i=0;i<_TAILLE_TOTALE_;i++)
										{
											if(tour_courant % 10 != 0) break;
											if((degradation == 87) && sacPecheur1 >20) {sacPecheur1--;degradation =0;}
											else
												degradation++;
											 //par simplicité, déclaration d'un animal courant
													index = tab[i];
													animal_courant = map[index];

													if(animal_courant.espece == t_mur || animal_courant.espece == t_vide) continue;

													if (animal_courant.espece == t_pecheur)
														{
															animal_courant.sac = sacPecheur1;
															continue;
														}

													else
														{
															animal_courant.satiete = max(animal_courant.satiete - animal_courant.metabolisme,0);

																// si règle de surive non repsectée, l'animal meurt et est remplacé par un animal
																//de type vide (case libre)
																if ( appliquerSatiete(index) == vrai );

																	else 	{
																								// Application de la règle REPRODUCTION
																								if ( appliquerReproduction(index) == vrai ){};
																								// FIN DE LA REPRODUCTION

																								// Predation
																								if ( predater(index) == vrai ){};
																								// Fin predation

																								// Déplacement
																								if ( moveA(index, animal_courant.saut_max) == vrai ){};
																								//Fin déplacement
																			}
															}

												}

														__Transition_tours__
															__Verifier_victory__
							}

		__FIN_JEU__
									free(map);
									TTF_CloseFont(police);
									TTF_Quit();
									SDL_Quit();
									return EXIT_SUCCESS;
									/* fin du programme */
}
