#include "define.h"
#include "satiete.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#ifndef _CST_H_
#define _CST_H_

#define WIDTH 750 //don't touch this one
#define HEIGH 700
#define CASE 5
#define SAUTDECASE (CASE + 5)
#define POSITION_PANIER_X (WIDTH/2)-(_MAP_SIZE_/2*SAUTDECASE) - 120
#define POSITION_PANIER_Y (HEIGH/2)+(_MAP_SIZE_/2*SAUTDECASE)


/********************************************//**
 * @brief Permet d'initialiser la carte en vérifiant que tout est ok
 *
 * @param void
 * @return BOOLEEN
 *
 ***********************************************/
 
BOOLEEN init_carte(void);

#endif // _CST_H_
