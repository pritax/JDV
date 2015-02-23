#include "serveur.h"

int main ()
{
	int 
		i				=	__VALEUR_NULLE__,
		ret				=	__VALEUR_NULLE__; // Thread 
	
	/* Début script */
	
	printf("En attente de connexion ...\nPort: %i\n",_PORT_);
	
	/* Ouverture de la socket */
	c_serveur.socket = creerSocket();
	
	// Nos threads
	
	ret = pthread_create(&c_serveur.thread_serveur,NULL,fn_serveur,NULL);
	
	if (! ret)
		{
			for(i=0;i<__NB_CLIENTS__;i++)
				{
					ret = pthread_create(&c_serveur.thread_clients[i],NULL,fn_clients,(void *) i);
				}
			if (ret)
				perror("Erreur thread client");
		}
	else
			perror("Erreur thread serveur");
			
	// Attente de la fin des threads 
	
	i = 0;
		for(i=0;i<__NB_CLIENTS__;i++)
			pthread_join(c_serveur.thread_clients[i],NULL);
		pthread_join(c_serveur.thread_serveur,NULL);
	
	// Fin
	write(v_client,"Aurevoir.\n",11);
	fermerDescripteurs(__NB_CLIENTS__,&clients[0]);
	close(c_serveur.socket);
	return EXIT_SUCCESS;
}
