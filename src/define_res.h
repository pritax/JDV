#ifndef _HEADER_MAIN_
#define _HEADER_MAIN_

#define _GNU_SOURCE

/* Include locaux */

/* Include globaux  */

// Basique

#include <features.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// Systeme

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <fcntl.h>

// Reseau 

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>


#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>


/* Defines */

#define CONTINUER 1

#define __BUFFERSIZE__ 1024
#define __TEST_LIMITE__ 5000
#define __SUCCESS_ERRNO__ 0
#define __ERROR_CREAT__ -1
#define __ERROR_FORK__ -1
#define __ATTENTE__ sleep(2);
#define __CHOIX_DEFAUT__ 0
#define __PORT__ 5011
#define __NB_SOCKETS__ 1

#define __DEBUT_THREAD_MAIN__ {
#define __FIN_THREAD_MAIN__ }

/* Enum */

typedef enum
{
	faux,
	vrai
}BOOLEEN;


/* Prototypes */

void fin_programme(void);

BOOLEEN creerSocket(void); /* socket + bind */
void initier_recepteur(void);
BOOLEEN reception_paquet(void); /* Reception de paquet en broadcast */

void initier_destinataire(void);
BOOLEEN envoi_paquet(void);

void *thread_1(void *);
void *thread_2(void *);
void *thread_3(void *);
/* Variabls */

struct sockaddr_in 
					client_recp, 
					client_dest;
char
			buffer[__BUFFERSIZE__],
			liste[__BUFFERSIZE__];

int 
	socket_recp,
	socket_dest;

struct ifconf ifc;
struct ifreq *ifr;

pthread_t 
			thread1, 
			thread2,
			thread3;

/* Extern */

extern int errno;
extern char **environ;


#endif
