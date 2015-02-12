#ifndef _SERV_H
#define _SERV_H

#include <sys/socket.h> /* Socket */
#include <netinet/in.h> /* INADDR_ANY */
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit succes */
#include <unistd.h> /* close */
#include <string.h>
#include <pthread.h>

/* Defines */

#define SOCKET_ERROR -1
#define _PORT_ 6000
#define _BUFFSIZE_ 1024
#define __VALEUR_NULLE__ 0
#define __NB_CLIENTS__ 2
#define __INFINI__ 1

/* Structures */

typedef struct
{
   int socket;
 
   pthread_t thread_serveur;
   pthread_t thread_clients[__NB_CLIENTS__];
}
communiuquant_t;

/* Variables globales ou statiques*/
char buffer[_BUFFSIZE_]; /* ce que le serveur lira */
struct sockaddr_in client;
communiuquant_t c_serveur;

int v_client;

int clients[__NB_CLIENTS__];
int actuel;

/* Prototypes */ 
int creerSocket(void);
int* InitierConnex(int*,int,int);
void fermerDescripteurs(int,int*);
void Qui_envoit(int);
void Qui_envoitS(int);

void * fn_serveur(void* p_data);
void * fn_clients(void* p_data);

#endif
