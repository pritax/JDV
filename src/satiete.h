#ifndef _SATIETE_H_
#define _SATIETE_H_
#include "animal.h"

typedef enum
{
	faux,
	vrai
}BOOLEEN;

/********************************************//**
 * \brief Fonction gérant la satièté, permet de savoir si sur un animal la règle de satièté a été appliqué ou non.
 *
 * \param int : position
 * \return BOOLEEN : predation faite ou non
 *
 ***********************************************/
BOOLEEN appliquerSatiete(int);

#endif
