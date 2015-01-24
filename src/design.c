
#include "design.h"
#include "animal.h"
#include "map.h"
#include "init.h"
#include "ajout_animaux.h"
#include "satiete.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <stdio.h>

extern unsigned int sacPecheur1,pvPecheur1;
extern SDL_Surface
					*carte[][_MAP_SIZE_],
					*ecran,
					*legende[][12];
extern Animal* map;
extern int 
		*posCanne,
		taille_c,
		posPecheur1;
extern BOOLEEN activation_TabPeche;

/* dessine la map à l'écran et attribut des couleurs en focntions des espèces*/
void dessinerMap(TTF_Font* police,int position_courante)
{

	SDL_Rect position;
	SDL_Surface *pixels= SDL_CreateRGBSurface(SDL_HWSURFACE, CASE, CASE, 32, 0, 0, 0, 0);
	int L =0;

    //  Initialisation de la SDL


    reinit_params(police);

    position.x=(WIDTH /2) - (_MAP_SIZE_*SAUTDECASE /2);
    position.y=(HEIGH /2) - (_MAP_SIZE_*SAUTDECASE /2);
    int i,j,k=0;
    for(i=0; i<_MAP_SIZE_; i++)
    {
        for(j=0; j<_MAP_SIZE_; j++)
        {
            carte[i][j] = pixels;

            switch(map[k].espece)
            {

            case 1:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 141, 241, 60));
                break;
            case 2:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 234, 197, 69));
                break;
            case 3:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 15,112,137));
                break;
            case 4:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 238, 90, 215));
                break;
            case 5:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
                break;
            case 6:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 139, 139, 139));
                break;
            case 7:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 78, 65, 41));
                break;
            case 8:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 255, 255, 255));
                break;
            case 9:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 30, 4, 188));
                break;
            case 10:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 249, 5, 22));
                break;
            case -1:
                SDL_FillRect(carte[i][j], NULL,SDL_MapRGB(ecran->format, 118, 30, 3));
                break;
            default:
                SDL_FillRect(carte[i][j], NULL, SDL_MapRGB(ecran->format, 225, 207, 183));
                break;
            } // Fin switch

	    for(L=0;L<taille_c && activation_TabPeche == vrai;L++)
		{
 			if(posCanne != NULL && k == posCanne[L])
				SDL_FillRect(carte[i][j], NULL, SDL_MapRGB(ecran->format, 35, 121, 17));
		}
            SDL_BlitSurface(carte[i][j], NULL, ecran, &position);
            position.x += SAUTDECASE;
            k++;

        }
        position.x=(WIDTH /2) - (_MAP_SIZE_ *SAUTDECASE /2) ;
        position.y += SAUTDECASE;
    }

    //  FIN d'init SDL
    int f;



    position.x=0 ;
    position.y =(HEIGH /2) - (_MAP_SIZE_*SAUTDECASE /2) ;
    for(f=-1; f<12; f++)
    {
        position.x=0 ;
        legende[0][f+1] = pixels;
        switch(f)
        {

        case 1:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 141, 241, 60));

            break;
        case 2:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 234, 197, 69));

            break;
        case 3:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 15,112,137));
            break;
        case 4:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 238, 90, 215));

            break;
        case 5:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
            break;
        case 6:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 139, 139, 139));
            break;
        case 7:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 78, 65, 41));
            break;
        case 8:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 255, 255, 255));
            break;
        case 9:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 30, 4, 188));
            break;
        case 10:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 249, 5, 22));
            break;
        case 11:
            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 35, 121, 17));
            break;
        case 0:
            SDL_FillRect(legende[0][f+1], NULL, SDL_MapRGB(ecran->format, 225, 207, 183));
            break;
        default:

            SDL_FillRect(legende[0][f+1], NULL,SDL_MapRGB(ecran->format, 118, 30, 3));
            break;

        } // Fin switch
        position.y +=SAUTDECASE +5;
        position.x=SAUTDECASE+5;
        SDL_BlitSurface(legende[0][f+1], NULL, ecran, &position);
    }

    // Mise à jour de l'écran
    SDL_Flip(ecran);
    
    SDL_FreeSurface(pixels);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(legende[0][f+1]);
    
    /* Liberation des cellules */

	//memset(posCanne,-1,taille_c);
}

/* permet de savoir si la cellule est un mur ou un morceau du pont creer par le pecheur
    si la case_courante.espece == t_mur && !estMur alors c'est un pont qui peut etre mangé
    sinon, il s'agit d'un mur qu'on ne croque pas !!
*/
int estMur(int index)
{
    return (	(index+1)%(_MAP_SIZE_)	==	0 // Droite
			|| 	(index%_MAP_SIZE_)	==	0 // Gauche
			||	index<_MAP_SIZE_ // Haut
			|| 	index>=(_TAILLE_TOTALE_-_MAP_SIZE_) // Bas
			);
}


void respawn(int index)
{
    supprimer_animal(index);
    posPecheur1 = __POS_PECHEUR_INIT__;
    ajouterPecheur(posPecheur1);
    map[index].sac=__SAC_BASE__;
    pvPecheur1 = __NB_VIE__;
    
    SDL_Flip(ecran);
}

void deplacerPecheur(int index)
{
    supprimer_animal(index);
    ajouterPecheur(index);
    map[index].sac=sacPecheur1;
}



void print_values(char * chaine, int value,int x, int y,TTF_Font* police)
{
    char buffer1[128];
    char buf[32];
    strcpy(buffer1,chaine);
    sprintf(buf,"%d",value);
    strcat(buffer1,buf);
    print_screen(buffer1,x,y,police);
}

void affichage_filet(int posdebut,int taille)
{
        SDL_Surface * filet = SDL_CreateRGBSurface(SDL_HWSURFACE,taille*CASE , taille*CASE , 32, 0, 0, 0, 0);
        SDL_Rect pos;
        pos.x =0;
        pos.y=0;

        SDL_FillRect(filet, NULL,SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(filet,NULL,ecran,&pos);

        SDL_Flip(ecran);
        // SDL_FreeSurface(filet);
}

