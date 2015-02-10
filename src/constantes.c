#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "satiete.h"


 /* initialisation d'un tableau de surface */
SDL_Surface* carte[_MAP_SIZE_][_MAP_SIZE_];
SDL_Surface *ecran,*logo,*imgSac1,*imageDeFond;
SDL_Surface *imgPanier0,*imgPanier1,*imgPanier2,*imgPanier3,*imgVictory,*imgCoeur;
SDL_Surface* legende[1][12];

BOOLEEN init_carte()
{
    if ( memset(carte,0,sizeof(carte)) && memset(legende,0,sizeof(legende)) )
    return vrai;
    else return faux;
}

/* creation des SDL_Rect permettant le positionnement des elements */
SDL_Rect positionSac1,positionArrow,positionFond,positionLogo;
SDL_Event event; /* La variable contenant l'événement */
