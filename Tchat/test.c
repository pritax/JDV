#include <sys/socket.h> /* Socket */
#include <netinet/in.h> /* INADDR_ANY */
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit succes */
#include <unistd.h> /* close */
#include <string.h>

#define SOCKET_ERROR -1

struct sockaddr_in serveur =
{
	sin_port = 0;
}

int creerSocket(void)
{
	int descripteur_socket= socket(PF_INET,SOCK_STREAM,0);
	if( descripteur_socket == -1 ){ perror("Socket"); exit(EXIT_FAILURE); }
	/* Socket crée */
	
	memset(&serveur,0,sizeof(serveur));
	if ( bind(descripteur_socket,(struct sockaddr*)&serveur,sizeof(serveur)) == SOCKET_ERROR )
		{
		perror("Bind");
		}
	
	/* Bind fait */
	
	if ( listen(descripteur_socket,100) == SOCKET_ERROR ) { perror("Listen"); exit(EXIT_FAILURE); }
	
	/* Ecoute faite sur notre socket !! */
	
	printf("En attente de connexion ...\nPort: %i\n",ntohs(serveur.sin_port));
	
	return descripteur_socket;
}

void fermerDescripteurs(int nb_client,int* tab_client)
{
	int i;
	for(i=0;i<nb_client;i++)
	{
		if ( tab_client[i] != SOCKET_ERROR )
		close(tab_client[i]);
	}
}

int main (void)
{
	
	int i,n,socket_ecoute = creerSocket();
	socklen_t l= sizeof(struct sockaddr_in);
	
	char *message = "=== Bienvenue chez moi! ===\n\n";
	int l_message = strlen(message);
	struct sockaddr_in client;
	char buffer[256]; /* ce que le serveur lira */
	
	int liste_client[4],nb_clients=4;
	i=0;
	liste_client[i] = accept(socket_ecoute,(struct sockaddr*)&client,&l);
	
		printf("Connexion établie avec %s\n",inet_ntoa(client.sin_addr));
		send(liste_client[i],message,l_message,0);
		bzero(buffer,256);
		n = read(liste_client[i],buffer,255);
		if (n < 0) { perror("ERROR reading from socket"); exit(EXIT_FAILURE); }
		printf("Le client renvoit: %s",buffer);
	
	fermerDescripteurs(nb_clients,&liste_client[0]);
	close(socket_ecoute);
	return EXIT_SUCCESS;
}
