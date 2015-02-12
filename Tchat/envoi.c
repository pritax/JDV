#include "serveur.h"

/* Fonctions */


void Qui_envoit(int position)
{
	int i;
	switch(position)
	{
		case 0:
		for(i=0;i<__NB_CLIENTS__;i++)
		{
		send(clients[i],"Le client 1 envoie : ",22,0);
		send(clients[i],buffer,_BUFFSIZE_,0);
		}
		break;
		case 1:
		for(i=0;i<__NB_CLIENTS__;i++)
		{
		send(clients[i],"Le client 2 envoie : ",22,0);
		send(clients[i],buffer,_BUFFSIZE_,0);
		}
		break;
		case 2:
		for(i=0;i<__NB_CLIENTS__;i++)
		{
		send(clients[i],"Le client 3 envoie : ",22,0);
		send(clients[i],buffer,_BUFFSIZE_,0);
		}
		break;
		case 3:
		for(i=0;i<__NB_CLIENTS__;i++)
		{
		send(clients[i],"Le client 4 envoie : ",22,0);
		send(clients[i],buffer,_BUFFSIZE_,0);
		}
		break;
		default:
		for(i=0;i<__NB_CLIENTS__;i++)
		{
		send(clients[i],"Quelqu'un envoie : ",22,0);
		send(clients[i],buffer,_BUFFSIZE_,0);
		}
		break;
	}
}

void Qui_envoitS(int position)
{
	switch(position)
	{
		case 0:
		printf("Le client 1 envoie : %s",buffer);
		break;
		case 1:
		printf("Le client 2 envoie : %s",buffer);
		break;
		case 2:
		printf("Le client 3 envoie : %s",buffer);
		break;
		case 3:
		printf("Le client 4 envoie : %s",buffer);
		break;
		default:
		printf("Quelqu'un envoie : %s",buffer);
		break;
	}
}
