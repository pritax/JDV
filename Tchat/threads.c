#include "serveur.h"

/* Fonctions */

void * fn_serveur(void* p_data)
{
	int 
		i,
		n;
		
			for(i=0;i<__NB_CLIENTS__;i++)
				{
					//printf("Connexion établie avec %s\n",inet_ntoa(client.sin_addr));
						while(__INFINI__)
							{
								bzero(buffer,_BUFFSIZE_);
									n = read(v_client,buffer,_BUFFSIZE_);
										if (n < 0) { perror("ERROR reading from socket"); exit(EXIT_FAILURE); }
							}
				}
	return NULL;
}

void * fn_clients(void* p_data)
	{
		int 
			nb			= (int) p_data,
			n;
		socklen_t l= sizeof(struct sockaddr_in);
		
		char 
			*message		=	"=== Bienvenue dans le tchat ! ===\n\n",
			*msg_fin		=	"J'ai reçu ton message.\n";
		int 
		l_message		=	strlen(message),
		l_msg_fin		=	strlen(msg_fin);
			
			v_client = accept(c_serveur.socket,(struct sockaddr*)&client,&l);
			
			clients[actuel] = v_client;
			actuel++;
			
			send(v_client,message,l_message,0);
			printf("%s vient de se connecter sur le tchat.\n",inet_ntoa(client.sin_addr));
				while(__INFINI__)
					{
						bzero(buffer,_BUFFSIZE_);
							n = read(v_client,buffer,_BUFFSIZE_);
								if (n < 0) { perror("ERROR reading from socket"); exit(EXIT_FAILURE); }
								
					Qui_envoit(nb); // Msg pr les clients
					Qui_envoitS(nb); // Msg pr le serveur
								n = write(v_client,msg_fin,l_msg_fin);
									if (n < 0) { perror("Erreur writing to socket"); exit(EXIT_FAILURE); }
					}
		return NULL;
	}
