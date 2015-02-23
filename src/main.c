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
		ModeDeJeu		= __VALEUR_NULLE__,
		tour_mod		= __VALEUR_NULLE__;
		
	Animal animal_courant;
	int* tab=NULL;
	TTF_Font* police;
    
    SDL_Rect posVictory;
				posVictory.x = __POS_X_HAUT_GAUCHE__;
				posVictory.y = __POS_Y_HAUT_GAUCHE__;
	SDL_Event eventquit;

	srand(time(NULL));

		if ( creerSocket() == vrai )
		printf("socket créee depuis le port %d\n",__PORT__);
	
					if(pthread_create(&thread1, NULL, thread_1, NULL) == __ERROR_CREAT__)
						{
							perror("pthread_create");
							return EXIT_FAILURE;
			
						}
					
					if(pthread_create(&thread2, NULL, thread_2, NULL) == __ERROR_CREAT__)
						{
							perror("pthread_create");
							return EXIT_FAILURE;
						}
	/* Fin déclaration variables */
	
	if(pthread_create(&thread3, NULL, thread_3, NULL) != __ERROR_CREAT__)
						__DEBUT_THREAD_MAIN__
    sdl_loader("Jeu de la vie | Try your best !");
	
	TTF_Init(); // Init de la police graphique
	
    police=TTF_OpenFont("img/calibri.ttf", 15); // On définit la police
    
	genererMap();
	
	/* affecte des animaux à l'intérieur de la map */

	ajouter_all_animaux();

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
													
									for(i=0;i<_TAILLE_TOTALE_;i++)
										__DEBUT_FOR__
											if(tour_courant % 100 != 0) break;
											 //par simplicité, déclaration d'un animal courant
													index = tab[i];
													animal_courant = map[index];
													

													if(animal_courant.espece == t_mur || animal_courant.espece == t_vide) continue;

													else
														{
															animal_courant.satiete = max(animal_courant.satiete - animal_courant.metabolisme,0);

																// si règle de surive non repsectée, l'animal meurt et est remplacé par un animal
																//de type vide (case libre)
																if ( appliquerSatiete(index) == vrai )
																	{
																		memset(buffer,'\0',__BUFFERSIZE__);
																										strcpy(buffer,"Satiété faite");
																										sendto(socket_dest, buffer, __BUFFERSIZE__, 0, (struct sockaddr *) &client_dest, sizeof(client_dest));
																	}
																	else 	{
																								// Application de la règle REPRODUCTION
																								if ( appliquerReproduction(index) == vrai )
																									{
																										memset(buffer,'\0',__BUFFERSIZE__);
																										strcpy(buffer,"Reproduction faite");
																										sendto(socket_dest, buffer, __BUFFERSIZE__, 0, (struct sockaddr *) &client_dest, sizeof(client_dest));
																									};
																								// FIN DE LA REPRODUCTION

																								// Predation
																								if ( predater(index) == vrai )
																									{
																										memset(buffer,'\0',__BUFFERSIZE__);
																										strcpy(buffer,"Predation faite");
																										sendto(socket_dest, buffer, __BUFFERSIZE__, 0, (struct sockaddr *) &client_dest, sizeof(client_dest));
																									};
																								// Fin predation

																								// Déplacement
																								if ( moveA(index, animal_courant.saut_max) == vrai )
																									{
																										memset(buffer,'\0',__BUFFERSIZE__);
																										strcpy(buffer,"Deplacement fait");
																										sendto(socket_dest, buffer, __BUFFERSIZE__, 0, (struct sockaddr *) &client_dest, sizeof(client_dest));
																									};
																								//Fin déplacement
																			}
															}

												__FIN_FOR__
														__Transition_tours__
																	
							}

		__FIN_JEU__
					__FIN_THREAD_MAIN__
					
					
									__F_FINIR_JEU
					
					if(pthread_join(thread1, NULL))
								{
									perror("pthread_join");
									return EXIT_FAILURE;
								}
					
					if(pthread_join(thread2, NULL))
						{
							perror("pthread_join");
							return EXIT_FAILURE;
						}
						
					if(pthread_join(thread3, NULL))
						{
							perror("pthread_join");
							return EXIT_FAILURE;
						}
									return EXIT_SUCCESS;
									/* fin du programme */
}
