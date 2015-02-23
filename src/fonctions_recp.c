#include "define.h"

/* Fonctions */


BOOLEEN creerSocket(void)
	{
		int liaison_recp;
		/* Debut */
		
		socket_recp = socket(AF_INET, SOCK_DGRAM,__CHOIX_DEFAUT__);
		if ( socket_recp < __SUCCESS_ERRNO__ ) { perror("Prob socket");
													return faux;
												  }
		
		initier_recepteur();
		
		liaison_recp = bind(socket_recp,\
							(const struct sockaddr*)&client_recp,\
							sizeof(client_recp));
		if ( liaison_recp < __SUCCESS_ERRNO__ ) { perror("Prob socket : bind"); \
												  return faux; }
		
		return vrai;
		/* Fin */
	}
	
void initier_recepteur(void)
	{
		client_recp.sin_family = AF_INET;
		client_recp.sin_addr.s_addr= htonl(INADDR_ANY);
		client_recp.sin_port=htons(__PORT__);
	}

BOOLEEN reception_paquet(void)
	{
		int 
			longueur_dest,
			accuse_recp;
		
		/* Début */
		
		longueur_dest = sizeof(client_dest);
		accuse_recp = recvfrom(socket_recp, buffer, __BUFFERSIZE__,\
								__CHOIX_DEFAUT__,\
								(struct sockaddr*)&client_dest,\
								(socklen_t*)&longueur_dest);
		if ( accuse_recp <= __SUCCESS_ERRNO__ ) { perror("Erreur reception");\
												  return faux; }
		printf("serveur recoit:");
		printf("%s\n",buffer);
		printf("...de la part de %s(%d)\n",inet_ntoa(client_dest.sin_addr),htons(client_dest.sin_port));
		return vrai;
		/* Fin */	
	}
