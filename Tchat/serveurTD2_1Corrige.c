/* isockl.c -- set up an INTERNET STREAM socket and listen on it */
/* (C) 1991 Blair P. Houghton, All Rights Reserved, copying and */
/* distribution permitted with copyright intact.                */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

main( argc, argv )
int argc; char *argv[];
{
    int sock;				
    int ear;			
    fd_set	fdlire;	
    int		ret;
    struct sockaddr_in sockaddr;	
    struct sockaddr_in caller;
    int sockaddr_in_length = sizeof(struct sockaddr_in);
    char buf[BUFSIZ];
    int read_ret;
    int fromlen = sizeof(struct sockaddr_in);




    if ( (sock = socket( AF_INET, SOCK_STREAM, 0 )) < 0 ) {
			char s[BUFSIZ];
			sprintf( s, "%s: can't assign fd for socket", argv[0] );
			perror(s);
			exit(__LINE__);
    }

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
    sockaddr.sin_port = 0;

    if ( bind( sock, (struct sockaddr *) &sockaddr, sizeof sockaddr ) < 0 ) {
			char s[BUFSIZ];
			sprintf( s, "%s: can't bind socket (%d)", argv[0], sock );
			perror(s);
			exit(__LINE__);
    }


    printf("opened socket as fd (%d) on port (%d) for stream i/o\n",
	    sock, ntohs(sockaddr.sin_port) );

    printf(
		"struct sockaddr_in {\n\
				sin_family		= %d\n\
				sin_addr.s_addr	= %s\n\
				sin_port		= %d\n\
		} sockaddr;\n"
		, sockaddr.sin_family
		, inet_ntoa(sockaddr.sin_addr)
		, ntohs(sockaddr.sin_port)
    );
		
	printf("\n");
		getsockname(sock, (struct sockaddr *)&sockaddr, (socklen_t*) &sockaddr_in_length);
	    printf(
		"struct sockaddr_in {\n\
				sin_family		= %d\n\
				sin_addr.s_addr	= %s\n\
				sin_port		= %d\n\
		} sockaddr;\n"
		, sockaddr.sin_family
		, inet_ntoa(sockaddr.sin_addr)
		, ntohs(sockaddr.sin_port)
    );

  struct sockaddr_in tmp;
	char buffer[BUFSIZ];
	bzero(buffer,BUFSIZ);
	while(1)
	{
		if(listen(sock,1)!=-1)
		{
			//sock est le file descriptor de la socket d'attente du serveur
			// le deuxième argument est la structure sockaddr associé à ce socket
			// le troisième argument est la taille de la structure sockaddr
			ear = accept(sock, (struct sockaddr *) &sockaddr, (socklen_t*) &sockaddr_in_length);
			if(ear!= -1)
			{
				printf("Connection acceptée\n");
				//inet_ntoa permet de transformer le bit sur 32bits en adresse ip (chaine). IP_v4 est sur 4 octets, soit 32 bits.
				// la fonction ntohs converti un unsigned short integer netshort(uint16_t) en port(uint16_t lui aussi) - signifie Network To Host Short.
				getsockname(ear, (struct sockaddr *)&tmp, (socklen_t*) &sockaddr_in_length);
					printf(
				"connexion sur la socket ayant le fd %d\nstruct sockaddr_in {\n\
						sin_family		= %d\n\
						sin_addr.s_addr	= %s\n\
						sin_port		= %d\n\
				} sockaddr;\n"
				, ear
				, tmp.sin_family
				, inet_ntoa(tmp.sin_addr)
				, ntohs(tmp.sin_port)
				);
				// read retourne le nombre de caractères lus. Si on met "test" via la connexion telnet on aura 6 caractères (t-e-s-t-\n-\0)
				int red = read(ear,buffer,BUFSIZ);
				printf("résultat du read = %d, message : %s\n", red, buffer);
				// au lieu de strlen(buffer) pour réécrire ce que l'on a reçu, on peut utiliser red ici, soit la valeur retournée par le read
				// si le write n'écrit pas tout, le destinataire aura un message erroné
				if(write(ear,buffer,red)<0)
					printf("erreur\n");
				// Brute force pour tenter de trouver la limite d'écriture du write
				// char megabuf[1024*1024];
				// bzero(megabuf,1024*1024);
				// int count = 0, write_retour;
				// do
				//{
				//	megabuf[count]='a';
				//	write_retour = write(ear,buffer, count+1);
				//	if(write_retour<0)
				//		printf("erreur2\n");
				//	count++;
					//printf("count = %d, write = %d", count, write_retour);
				//} while (count == write_retour);
				//printf("count final : %d\n",count);
				
			}
			else
				perror("Erreur accept ");
		}
		else
		{
			perror("Erreur listen ");
			break;
		}
	}
}
