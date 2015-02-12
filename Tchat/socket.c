#include "serveur.h"

/* Fonctions */

int creerSocket()
{
	int descripteur_socket= socket(PF_INET,SOCK_STREAM,0);
	if( descripteur_socket == -1 ){ perror("Socket"); exit(EXIT_FAILURE); }
	/* Socket crée */

	struct sockaddr_in serveur;
	memset(&serveur,0,sizeof(serveur));
	serveur.sin_family = AF_INET;
	serveur.sin_port = htons(_PORT_);
	serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	if ( bind(descripteur_socket,(struct sockaddr*)&serveur,sizeof(serveur)) == SOCKET_ERROR )
		{
		perror("Bind");
		}

	/* Bind fait */

	if ( listen(descripteur_socket,100) == SOCKET_ERROR ) { perror("Listen"); exit(EXIT_FAILURE); }

	/* Ecoute faite sur notre socket !! */

	return descripteur_socket;
}

void fermerDescripteurs(int nb_clients,int* tab_client)
{
	int i;
	for(i=0;i<nb_clients;i++)
	{
		if ( tab_client[i] != SOCKET_ERROR )
		close(tab_client[i]);
	}
}

