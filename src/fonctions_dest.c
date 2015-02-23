#include "define.h"

/* Fonctions */

void initier_destinataire(void)
	{
		//client_dest.sin_addr.s_addr = inet_addr("10.42.0.1");
		client_dest.sin_family = AF_INET;
		client_dest.sin_port=htons(__PORT__);
	}

BOOLEEN envoi_paquet(void)
	{
			int 
				n, 
				on;
		
		if ( (socket_dest = socket(AF_INET, SOCK_DGRAM, 0) ) <0){
			perror("socket de demande");
			exit(1);
		}

		on = 1;
		if(setsockopt(socket_dest, SOL_SOCKET, SO_BROADCAST, &on, sizeof on)<0) {
				perror("socket opt");
				exit(1);
			  }

		ifc.ifc_len = sizeof (liste);
		ifc.ifc_buf = liste;
		if (ioctl(socket_dest, SIOCGIFCONF, (char *) &ifc) <0){
			  perror("ioctl IFCONF");
			  exit(1);
			}
		n=ifc.ifc_len/sizeof (struct ifreq);
		ifr = ifc.ifc_req;
		for (; --n>= 0; ifr++){
				printf("interface %s:\n",ifr->ifr_name);
				if (ioctl(socket_dest, SIOCGIFFLAGS, (char *) ifr)<0){
				perror("ioctl IFFLAG");
				exit(1);
				}
				if ( ((ifr->ifr_flags & IFF_UP)== 0) ||
				 (ifr->ifr_flags & IFF_LOOPBACK) ||
				 (ifr->ifr_flags &  IFF_POINTOPOINT)||
			 ((ifr->ifr_flags & IFF_BROADCAST)==0) ){
				 continue;
				}
		  
			if (ioctl(socket_dest, SIOCGIFBRDADDR, (char *) ifr)){
				perror("ioctl BROADADDR");
				exit(1);
			   }
			bcopy(&(ifr->ifr_broadaddr), &client_dest, sizeof(ifr->ifr_broadaddr));
			initier_destinataire();
			
						fgets(buffer,__BUFFERSIZE__,stdin);
						sendto(socket_dest, buffer, __BUFFERSIZE__, 0, (struct sockaddr *) &client_dest, sizeof(client_dest));
						close(socket_dest);
			}
		return vrai;
	}
