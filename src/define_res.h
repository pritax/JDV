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
#define __HEADERSIZE__ 16
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

/* Structures reseaux  */
#define F_SET '1'


typedef struct header{
    char F_HELLOMESSAGE;
    char F_HELLOREPLY;
    char F_CHANGEOWNERREQUEST;
    char F_CHANGEOWNERREPLY;
    char F_CHANGEOWNERORDER;
    char F_GLOBALUPDATEREQUEST;
    char F_GLOBALUPDATEREPLY;
    char F_GLOBALUPDATEORDER;
    char F_GLOBALUPDATECHALLENGE;
    char F_DELETEUSER;
    char F_MOVEPECHEUR;
    char F_MOVERESSOURCE;
    char F_ADDRESSOURCE;
    /* FLAG RESERVÉES dans le cadre du possible évolution*/
    char F_RESERVEE1;
    char F_RESERVEE2;
    char F_RESERVEE3;
    
}HEADER;

enum {
    T_RESERVEE3;
    T_RESERVEE2;
    T_RESERVEE1;
    T_ADDRESSOURCE;
    T_MOVERESSOURCE;
    T_MOVEPECHEUR;
    T_DELETEUSER;
    T_GLOBALUPDATECHALLENGE;
    T_GLOBALUPDATEORDER;
    T_GLOBALUPDATEREPLY;
    T_GLOBALUPDATEREQUEST;
    T_CHANGEOWNERORDER;
    T_CHANGEOWNERREPLY;
    T_CHANGEOWNERREQUEST;
    T_HELLOREPLY;
    T_HELLOMESSAGE;
};

typedef struct data{
    char* message;
    
}DATA;

typedef struct packet{
    struct HEADER header;
    struct DATA data;
    int* p_position_r
}PAQUET;

typedef struct user{
    int id;
    char* ip;
    int port;
    
}USER;

/* liste chainée d'utilisateur */
typedef struct userList{
    struct USER user;
    struct USER* nextUser;
}USERLIST;


/* Enum */

typedef enum
{
	faux,
	vrai,
}BOOLEEN;

typedef enum 
{
	M_envoi,
	M_reception,  
}MODE;

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

/* Decoupe le message reçu et remplie les struct header et data*/
PAQUET* decoupeMsg(char*);
/* Rempli la structure paquet */
PAQUET* remplirPaquet(HEADER, DATA);

int isSet(char flag);
void apduControlleur(PAQUET*, MODE);

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
