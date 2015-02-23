#include "define.h"

/* Fonctions */

void *thread_1(void *arg)
	{
		while(CONTINUER)
			if ( envoi_paquet() == vrai )
							printf("Envoi effectué.\n");
		
		(void) arg;
		pthread_exit(NULL);
	}

void *thread_2(void *arg)
	{
		while(CONTINUER)
			if ( reception_paquet() == vrai )
						printf("Reception effectuée.\n");
		
		(void) arg;
		pthread_exit(NULL);
	}
void *thread_3(void *arg)
	{


		(void) arg;
		pthread_exit(NULL);
	}