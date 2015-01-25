#include "peche.h"
#include "ajout_animaux.h"
#include "animal.h"
#include "satiete.h"

extern unsigned int 
					sacPecheur1,
					tour_courant;
extern Animal* map;
static int last_build;
SDL_Surface 
			*carte[][_MAP_SIZE_],
			*ecran;
int 
	*posCanne=NULL,
	taille_c=5;
BOOLEEN activation_TabPeche = faux;
	
/* Fonctions */

int construire_pont(int position,Direction d,TTF_Font* police)
{

	if(sacPecheur1<=0)
	{
		pecher(position,d,police);
		last_build=tour_courant;
		return __VALEUR_NULLE__;
	}

	else
	{
		/* si la case sur laquel on veut construire le pont n'est pas une case vide
		   ou que le joueur à déja construit un morceau de pont ce tour, on ne fait rien*/
		if(map[position].espece != t_vide || last_build >= tour_courant)
			return __VALEUR_ERROR__;
		else
		{
			supprimer_animal(position);
			ajouter_mur(position);
			last_build=tour_courant;
			if(sacPecheur1 > 0) sacPecheur1--;
			else;
			return __INIT_VALEUR_JEU__;
		}
	}
}

int** lancer_filet(int position,Direction d)
{

	int i,j;
	int cmp,first,next = position,m,n;
	int ** filet = malloc( TAILLE_FILET*sizeof(int*) );
	for ( i = 0; i<TAILLE_FILET; i++ )
	{
		filet[i] = (int *) malloc( TAILLE_FILET*sizeof(int) );
			for ( j = 0; j<TAILLE_FILET; j++ )
				filet[i][j] = -1;
	}

	/* on se déplace sur la bonne case */
	for(cmp=0; !estMur(next) && cmp < DISTANCE_FILET; cmp++)
	{
		next = get_new_pos(d,next);
	}

	if(estMur(next)) return NULL;
	for(m=0; m<TAILLE_FILET; m++)
	{
		for(n=0; n<TAILLE_FILET; n++)
		{
			filet[m][n]=next;
			next = get_new_pos(DROITE,next);
			if(estMur(next))
			{

				break;
			}
		}
		first = filet[m][0];
		next = get_new_pos(BAS,first);


	}

	return filet;
}

void traitement_sur_poisson_peches_au_filet(int** tab_2dim)
{
	int 
		maPrise[CAPACITE_FILET],
		indices[TAILLE_FILET*TAILLE_FILET],
		i			=0,
		j			=0,
	    t			=0,
	    cp 			=0,
	    k  			=0,
	    selected	=0;
	    
	int val = 0;
	//Type test;
	    
	memset(maPrise,0,CAPACITE_FILET);

	for(i=0; i<TAILLE_FILET; i++)
		for(j=0; j<TAILLE_FILET; j++,k++)
		{
			indices[k]=tab_2dim[i][j];
			//printf("Indices k : %d\n",indices[k]);
		}
			
	
	
	t=(TAILLE_FILET*TAILLE_FILET)-1;
	//printf("Indices de t avant : %d\n",indices[t]);
	for(cp=0; cp<CAPACITE_FILET; cp++)
	{
		val = (int)(rand()%(t));
		//printf("Indices val avant : %d\n",indices[val]);
		maPrise[cp]=indices[val];
		indices[val]=indices[t];
		//printf("Indices val après : %d\n",indices[val]);
		t--;
	}

	/*  A ce stade les CAPACITE_FILET poissons pechés sont dans maPrise 8 .
	    supprimons les pour les ajouter à notre panier
	 */

	for(cp=0; cp<CAPACITE_FILET; cp++)
	{
		selected = maPrise[cp];
		Animal current = map[selected];
		//printf("%d ",maPrise[cp]);
		if( PECHE_INTERDITE )
		{
			// test vocation de debeuggage
			//test = current.espece;
			sacPecheur1 += current.taille;

			supprimer_animal(selected);
		}
	}
}

int lancer_canne(int position,int taille_canne,TTF_Font* police)
{
	int 
		pos			=0,
		posCurseur	=position,
		maPos		=0,
		done		=0,
		dir			=4;
	SDL_Event event_canne;
	if(posCanne != NULL)
		free(posCanne);
	else
		posCanne = malloc(taille_canne*sizeof(int));
		
	memset(posCanne,-1,taille_canne);
	printf("\n\n peche.c: taille_canne = %d  taille_c = %d \n",taille_canne,taille_c);	
	/*SDL_Surface * pixel = */
	printf("event : %p \n",&event_canne);
	/* on se déplace sur la bonne case */
	//SDL_WaitEvent(&event_canne);
	
	while( !done  )
	{
		printf("Attente d'un event\n");
		if ( SDL_WaitEvent(&event_canne) != 1 ) { perror("SDL wait"); exit(EXIT_FAILURE); }
		
		switch(event_canne.type)
				{
					// 0 --> HAUT, 1 --> haut-droite, 2--> droite ...
					case SDL_KEYDOWN:
						printf("Touche pressee\n");
						switch(event_canne.key.keysym.sym)
						{
							case SDLK_q:
							case SDLK_LEFT:
								if(dir == 8)
									dir=0;
								else
									dir++;
								break;

							case SDLK_d:
							case SDLK_RIGHT:
								if(dir == 1)
									dir=7;
								else
									dir--;
								break;
							case SDLK_RETURN:
								done = 1;
								printf("touche entree\n");
								break;
							default:break;

						}
						break;
					case SDL_QUIT:
						done=1;
						break;
					default:break;
				}
			maPos = posCurseur;
				for(pos=0;pos<taille_canne;pos++)
					{
						maPos = get_new_pos(dir,maPos);
						posCanne[pos]=maPos;
					}
		
		// On peche maintenant l'animal sélectionné
		
		if(!estMur(posCanne[pos-1]))
		{
			supprimer_animal(posCanne[pos-1]);
			sacPecheur1	+= map[pos-1].taille;
		}
		dessinerMap(police,__DEHORS_MAP__);
	}

	// on peche ici en recuperant la derniere case du tableau
	if(!estMur(posCanne[taille_c]))
		return posCanne[taille_c];
	else 
		return __VALEUR_ERROR__;
}
void pecher(int position,Direction d,TTF_Font* police)
{
	/* peche au filet*/
	int 
		choix 			= choixPeche(police),
		poisson_peche	= __VALEUR_ERROR__;
	
	int **indices_poisson_peches;

	if(choix==0)
	{
		indices_poisson_peches=lancer_filet(position,d);

		if(indices_poisson_peches != NULL )
			traitement_sur_poisson_peches_au_filet(indices_poisson_peches);

	}
	else
		{
			activation_TabPeche = vrai;
			poisson_peche = lancer_canne(position,5,police);
			activation_TabPeche = faux;
			if ( testPoisson(poisson_peche) )
				{
					sacPecheur1 += map[poisson_peche].taille;
					supprimer_animal(poisson_peche);
				}
		}
	

}
