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
int 
	nb_plancton,
	nb_corail,
	nb_bar,
	nb_thon,
	nb_pollution,
	nb_pyranha,
	nb_requin,
	nb_orque,
	nb_baleine;

int main(int argc, char* argv[])
{
	int 
		i				= __VALEUR_NULLE__,
		index			= __VALEUR_NULLE__,
		degradation		= __VALEUR_NULLE__,
		ModeDeJeu		= __VALEUR_NULLE__,
		tour_mod		= __VALEUR_NULLE__;
		
	Animal animal_courant;
	int* tab=NULL;
	Type espece_c;
	TTF_Font* police;
    SDL_Event eventquit;
    
    SDL_Rect posVictory;
				posVictory.x = __POS_X_HAUT_GAUCHE__;
				posVictory.y = __POS_Y_HAUT_GAUCHE__;
				
	/* CSV */
	FILE* fichier = fopen("data.csv",__EN_ECRITURE__);
	fprintf(fichier, "nb_tour;plancton;corail;bar;thon;pollution;pyranha;requin;orque;baleine\n");
	/* FIn CSV */

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
									if(tour_mod == 500){ tour_mod=0;}
									else 
									{
										tour_mod++;
										continue;
									}
								SDL_event_listener(eventquit,police);
								tab = alea(_TAILLE_TOTALE_,_TAILLE_TOTALE_);
								
								// == Test Pecheur ==
								
								printf("Vie du pecheur %d\n",pvPecheur1);
								if ( pvPecheur1 < 1 )
												{
													printf("Vous êtes DEAD (mdr), vous allez respawn\n");
													sleep(3);
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
											
											
											if((degradation == 87) && sacPecheur1 >__SAC_BASE__) {sacPecheur1--;degradation =0;}
											else
												degradation++;
											 //par simplicité, déclaration d'un animal courant
													index = tab[i];
													animal_courant = map[index];
													
													/* CSV */
													espece_c = animal_courant.espece;
													switch(espece_c)
														{
															case 1:
																nb_plancton++;
																break;
															case 2:
																nb_corail++;
																break;
															case 3:
																nb_bar++;
																break;
															case 4:
																nb_thon++;
																break;
															case 5:
																nb_pollution++;
																break;
															case 6:
																nb_pyranha++;
																break;
															case 7:
																nb_requin++;
																break;
															case 8:
																nb_orque++;
																break;
															case 9:
																nb_baleine++;
																break;
															default:
																break;
														}
														/* CSV */
													

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
																if ( appliquerSatiete(index) == vrai )
																		{
																			/* CSV */
																			espece_c = map[index].espece;
																			switch(espece_c)
														{
															case 1:
																nb_plancton--;
																break;
															case 2:
																nb_corail--;
																break;
															case 3:
																nb_bar--;
																break;
															case 4:
																nb_thon--;
																break;
															case 5:
																nb_pollution--;
																break;
															case 6:
																nb_pyranha--;
																break;
															case 7:
																nb_requin--;
																break;
															case 8:
																nb_orque--;
																break;
															case 9:
																nb_baleine--;
																break;
															default:
																break;
														}
														/* Fin CSV */
																		}

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
																if(tour_courant % 10 == 0) {__RESET_0__}
																else{
																	__LOGS__}
																	
							}

		__FIN_JEU__
									free(map);
									fclose(fichier);
									TTF_CloseFont(police);
									TTF_Quit();
									SDL_Quit();
									return EXIT_SUCCESS;
									/* fin du programme */
}
