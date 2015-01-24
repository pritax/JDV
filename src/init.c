#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "init.h"
#include "peche.h"
#include "design.h"
#include "ajout_animaux.h"
#include "deplacement.h"
#include "animal.h"

extern SDL_Surface
					*carte[][_MAP_SIZE_],/**< tableau a deux dimensions contenant chaque surface, chaque petit carre de la carte */
					*ecran,/**<  Pointeur sur la surface globale de l'ecran, affichage principal*/
					*logo,/**<  Pointeur sur la surface globale contenant le logo */
					*imgSac1,/**<  Pointeur sur la surface globale contenant l'image du sac*/
					*imageDeFond,/**<  Pointeur sur la surface globale contenant l'image de fond*/
					*legende[][12],/**< tableau contenant les petits carres de couleurs de la legende */
					*imgPanier0,*imgPanier1,*imgPanier2,*imgPanier3,
					*imgVictory,
					*imgCoeur;

extern int continuer;/**< variable permettant de sortir d'une boucle d'evenement SDL */

extern SDL_Rect
				positionPecheur,/**< Permet le positionnement du pecheur a l'ecran */
				position,/**<  Permet le positionnement de l'ecran (depreciated)*/
				positionFond;/**<  Permet le positionnement du fond a l'ecran*/


extern SDL_Event event; /* Variable permettant l'ecoute d'evenements SDL La variable contenant l'Ã©vÃ©nement */
extern unsigned int 
					posPecheur1,/**<  Position courante du pecheur 1*/
					tour_courant;
unsigned int 
				sacPecheur1 = __SAC_BASE__, 
				pvPecheur1=__NB_VIE__;

extern Animal* map;


/********************************************//**
 * @brief Initialise les parametres SDL Ã  chaque tour, surface ecran, surface logo ...
 *
 * @param void
 * @return void
 *
 ***********************************************/
void reinit_params(TTF_Font* police)
{
		SDL_Rect positionSac1,positionFond,positionLogo;
		int val,valy;

		positionFond.x = 0;
		positionFond.y = 0;


		val =(WIDTH /2) ;
		valy =  (HEIGH /2) - (_MAP_SIZE_*SAUTDECASE /2);
		positionLogo.x=val - 92;
		positionLogo.y= valy - 81;
		positionSac1.x= POSITION_PANIER_X ;
		positionSac1.y= POSITION_PANIER_Y +10;


        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);//< Blittage de l'image de fond
        SDL_BlitSurface(logo, NULL, ecran, &positionLogo); //< Bittage du logo
        SDL_BlitSurface(imgSac1, NULL, ecran, &positionSac1); //< Blittage de l'image du sac


		print_sac(police); //< Affichage du sac et de sa contenance, mise a jour du logo variant
        print_legend(police);// Affiche le texte de la lÃ©gende
        print_help(police);
//        print_values("n du tour: ",tour_courant,POSITION_PANIER_X + 220 , POSITION_PANIER_Y + 40,30);


        // rÃ©initialisation d'une carte vide*/

}


void sdl_loader(char* str)
{
    //SDL_putenv("SDL_VIDEO_CENTERED=center");
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }
    if (!(ecran = SDL_SetVideoMode(WIDTH, HEIGH, 32, SDL_DOUBLEBUF|SDL_HWSURFACE)))
    {
        printf("Unable to set 1000x1000 video: %s\n", SDL_GetError());
        SDL_Quit();
    }

    SDL_WM_SetCaption(str, NULL);
     /* Chargement d'une image Bitmap dans une surface */

    imageDeFond = SDL_LoadBMP("img/fond.bmp");
    logo        = SDL_LoadBMP("img/logo.bmp");
    imgSac1     = SDL_LoadBMP("img/panier0.bmp");
    imgPanier0 	= SDL_LoadBMP("img/panier0.bmp");
    imgPanier1  = SDL_LoadBMP("img/panier1.bmp");
    imgPanier2  = SDL_LoadBMP("img/panier2.bmp");
    imgPanier3  = SDL_LoadBMP("img/panier3.bmp");
    imgVictory	= SDL_LoadBMP("img/VictoryBanner.bmp");
    imgCoeur	= SDL_LoadBMP("img/coeur.bmp");


    if (	imageDeFond	== NULL 
		||	logo		== NULL 
		||	imgSac1		== NULL 
		||	imgVictory 	== NULL
		||	imgCoeur 	== NULL	) { printf("Erreur chargement des images"); exit(EXIT_FAILURE); }
    SDL_EnableKeyRepeat(100,100);

    SDL_SetColorKey(logo, SDL_SRCCOLORKEY, SDL_MapRGB(logo->format, 0, 0, 255));
	SDL_SetColorKey(imgVictory,SDL_SRCCOLORKEY, SDL_MapRGB(imgVictory->format, 255, 255, 255));
	SDL_SetColorKey(imgCoeur,SDL_SRCCOLORKEY, SDL_MapRGB(imgCoeur->format, 255, 255, 255));
}

void print_legend(TTF_Font* police)
{

    int j;
    char* liste[]= {"PONT","VIDE","PLANCTON","CORAIL","BAR","THON","POLLUTION","REQUIN","PYRANAH","ORQUE","BALEINE","PECHEUR","CURSEUR"};
    SDL_Rect posTemp;

    posTemp.y=(HEIGH /2) - (_MAP_SIZE_*SAUTDECASE /2) + SAUTDECASE ;
    posTemp.x=45;



    for(j=0;j<13;j++)
    {
       print_screen(liste[j],posTemp.x,posTemp.y,police);
       posTemp.y += SAUTDECASE+5;
    }



}


void print_screen(char* str,int x, int y,TTF_Font* police)
{
    SDL_Rect posTexte;
    SDL_Surface* masurf;

    posTexte.x=x;
    posTexte.y=y;

    SDL_Color bleu = {102, 0, 255};

    masurf=TTF_RenderText_Blended(police, str, bleu);

    SDL_BlitSurface(masurf, NULL, ecran, &posTexte); // Blit du texte
    //SDL_Flip(ecran);

}


void print_sac(TTF_Font* police)
{
    switch(sacPecheur1)
    {
    case 0:
        imgSac1 = imgPanier0;
        break;
    case 1:
        imgSac1 = imgPanier1;
        break;
    case 2:
        imgSac1 = imgPanier2;
        break;
    default:
            imgSac1 = imgPanier3;
        break;
    }
    print_values("Poissons peches:",sacPecheur1,POSITION_PANIER_X + 10,POSITION_PANIER_Y +93,police);

}
void SDL_event_listener(SDL_Event eventquit,TTF_Font* police)
{
     /* tant qu'il reste des Ã©vÃ¨nements dans la pile Ã  Ã©vÃ¨nement
            on les dÃ©piles un par un et on regarde quel Ã©vÃ¨nement
            a Ã©tÃ© appellÃ©
	     */
        while(SDL_PollEvent(&eventquit) != 0)
        {   int nextPos;
            switch(eventquit.type)
            {
                case SDL_QUIT:
                    tour_courant=_NOMBRE_DE_TOURS_;
                    break;
                case SDL_KEYDOWN:
                    switch(eventquit.key.keysym.sym)
                    {
                        case SDLK_z:
                        case SDLK_UP: // FlÃ¨che haut
                            nextPos=get_new_pos(HAUT,posPecheur1);
                            if((estMur(nextPos) || map[nextPos].espece == t_mur) && nextPos>0)
                            {
                                supprimer_animal(posPecheur1);
                                map[posPecheur1].espece=t_mur;
                                deplacerPecheur(nextPos);
                                posPecheur1=nextPos;
                            }
                            else if (nextPos < _TAILLE_TOTALE_)
                            {
                                construire_pont(nextPos,HAUT,police);
                            }
                            break;
                        case SDLK_s:
                        case SDLK_DOWN: // FlÃ¨che bas
                            nextPos=get_new_pos(BAS,posPecheur1);
                            if( (estMur(nextPos) || map[nextPos].espece == t_mur) && nextPos < _TAILLE_TOTALE_)
                            {
                                supprimer_animal(posPecheur1);
                                map[posPecheur1].espece=t_mur;
                                deplacerPecheur(nextPos);
                                posPecheur1=nextPos;
                            }
                            else if (nextPos < _TAILLE_TOTALE_)
                            {
                                construire_pont(nextPos,BAS,police);
                            }
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT: // FlÃ¨che droite
                            nextPos=get_new_pos(DROITE,posPecheur1);
                            if( (estMur(nextPos) || map[nextPos].espece == t_mur) && (((nextPos+1)%(_MAP_SIZE_)) != 0) )
                            {
                                supprimer_animal(posPecheur1);
                                map[posPecheur1].espece=t_mur;
                                deplacerPecheur(nextPos);
                                posPecheur1=nextPos;
                            }
                            else if (nextPos < _TAILLE_TOTALE_)
                            {
                                construire_pont(nextPos,DROITE,police);
                            }
                            break;
                        case SDLK_q:
                        case SDLK_LEFT: // FlÃ¨che gauche
                            nextPos=get_new_pos(GAUCHE,posPecheur1);
                            if((estMur(nextPos) || map[nextPos].espece == t_mur) && ((nextPos%(_MAP_SIZE_)) != 0))
                            {
                                supprimer_animal(posPecheur1);
                                map[posPecheur1].espece=t_mur;
                                deplacerPecheur(nextPos);
                                posPecheur1=nextPos;
                            }
                            else if (nextPos < _TAILLE_TOTALE_)
                            {
                                construire_pont(nextPos,GAUCHE,police);
                            }
                            break;
                        case SDLK_SPACE:
                            pecheravecdirection(posPecheur1,police);
                            break;
                        default: break;
                    }
                    break;
                // clic gauche de la souris
                case SDL_MOUSEBUTTONDOWN:
                    break;
                default: break;
            }
        }
}

void print_img_onScreen(char* path,int x,int y)
{
	SDL_Rect mapos;
	SDL_Surface* masurf;

    mapos.x=x;
    mapos.y=y;

    masurf = SDL_LoadBMP(path);
    SDL_BlitSurface(masurf,NULL,ecran,&mapos);
}

int choixPeche(TTF_Font* police)
{
    SDL_Rect posmenu1,posmenu2,monTxt;
    char buf[32]="";
    char buf2[32]="";
    SDL_Surface* menu1=NULL;
    SDL_Surface* menu2=NULL;
    SDL_Surface* menu3=NULL;
    SDL_Event event;

    SDL_Color couleurNoire = {0,0,0};
    SDL_Color jaune = {255, 255, 0};

    sprintf(buf,"> Peche a la canne a peche.");
    sprintf(buf2,"> Peche au filet de peche.");

    menu2 = TTF_RenderText_Solid(police, buf, couleurNoire);
    menu1 = TTF_RenderText_Solid(police,buf2, couleurNoire);
    menu3 = TTF_RenderText_Solid(police,"Entree pour valider votre choix ...",couleurNoire );

    monTxt.x=(WIDTH / 2 ) - _MAP_SIZE_*CASE;
    monTxt.y= (HEIGH - 100);

    int continuer=1,pos =0;

    while(continuer){


        SDL_WaitEvent(&event);



        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_z:
                    case SDLK_UP: // FlÃ¨che haut
                        pos=0;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN: // FlÃ¨che bas
                        pos=1;
                        break;
                    case SDLK_RETURN:
                        continuer=0;
                        break;
                    default: break;
                }
                break;
        }

		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        posmenu2.x=(WIDTH/2) - (_MAP_SIZE_*CASE )  ;
        posmenu2.y=(HEIGH / 2) - 50;
        posmenu1.x=(WIDTH/2) - (_MAP_SIZE_*CASE ) ;
        posmenu1.y=(HEIGH / 2);

        if(pos != 1)
        {
            menu2 = TTF_RenderText_Solid(police, buf2, jaune); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu1 = TTF_RenderText_Solid(police, buf, couleurNoire); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
        }
        else
        {
            menu2 = TTF_RenderText_Solid(police, buf2, couleurNoire); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu1 = TTF_RenderText_Solid(police, buf, jaune); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
        }
		SDL_FreeSurface(ecran);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 69, 120, 214));
        SDL_BlitSurface(menu2, NULL, ecran, &posmenu2); /* Blit du texte */
        SDL_BlitSurface(menu1, NULL, ecran, &posmenu1); /* Blit du texte */
        SDL_BlitSurface(menu3,NULL,ecran,&monTxt);




        SDL_Flip(ecran);
    }
		SDL_FreeSurface(menu1);
		SDL_FreeSurface(menu2);
		SDL_FreeSurface(menu3);
    return pos;
}


void pecheravecdirection(int position,TTF_Font* police)
{
    SDL_Rect posmenu1,positionArrow2;
    char buf[32]="";
    char buf2[32]="";
    SDL_Surface* menu1=NULL;
    SDL_Surface* menu2=NULL;
    SDL_Event event;
    SDL_Surface *arrow  = SDL_LoadBMP("img/arrow.bmp");
    positionArrow2.x=(WIDTH/2) - (_MAP_SIZE_*CASE ) - 50 ;
    positionArrow2.y=(HEIGH / 2) -290;
    SDL_Color jaune = {255, 255, 0};

    sprintf(buf,"Veuillez appuyer sur une touche");
    sprintf(buf2,"Entrer pour annuler.");

    menu1 = TTF_RenderText_Blended(police, buf, jaune);
    menu2 = TTF_RenderText_Blended(police,buf2, jaune);

    posmenu1.x=(WIDTH / 2 ) - _MAP_SIZE_*CASE;
    posmenu1.y= (HEIGH - 100);

    int continuer=1;

    while(continuer){

        posmenu1.x=(WIDTH/2) - (_MAP_SIZE_*CASE ) ;
        posmenu1.y=(HEIGH / 2);
        SDL_WaitEvent(&event);



        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_z:
                    case SDLK_UP: // FlÃ¨che haut
                        continuer=0;
                        pecher(position,HAUT,police);
                        break;
                    case SDLK_s:
                    case SDLK_DOWN: // FlÃ¨che bas
                        continuer=0;
                        pecher(position,BAS,police);
                        break;
                    case SDLK_q:
                    case SDLK_LEFT: // FlÃ¨che haut
                        continuer=0;
                        pecher(position,GAUCHE,police);
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT: // FlÃ¨che bas
                        continuer=0;
                        pecher(position,DROITE,police);
                        break;
                    case SDLK_RETURN:
                        continuer=0;
                        break;
                    default: break;
                }
                break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 69, 120, 214));
        SDL_BlitSurface(menu1, NULL, ecran, &posmenu1); /* Blit du texte */

        posmenu1.x=(WIDTH/2) - (_MAP_SIZE_*CASE ) ;
        posmenu1.y=(HEIGH / 2) + 30;
        SDL_BlitSurface(menu2, NULL, ecran, &posmenu1); /* Blit du texte */
        SDL_BlitSurface(arrow,NULL,ecran,&positionArrow2);

        SDL_Flip(ecran);
    }
        SDL_FreeSurface(arrow);
		SDL_FreeSurface(menu1);
		SDL_FreeSurface(menu2);

}

void print_help(TTF_Font* police)
{
    int x,y;
    x=(WIDTH /2) + (_MAP_SIZE_ * SAUTDECASE /2) + SAUTDECASE;
    y=(HEIGH /2) - (_MAP_SIZE_ * SAUTDECASE /2)  ;
    print_screen("============ Move ============",x,y,police);y+=20;
    print_screen("= HAUT        : Fleche du haut           =",x,y,police);y+=20;
    print_screen("= BAS           : Fleche du bas              =",x,y,police);y+=20;
    print_screen("= GAUCHE  : Fleche de gauche      =",x,y,police);y+=20;
    print_screen("= DROITE    : Fleche de droite        =",x,y,police);y+=20;
    print_screen("==============================",x,y,police);y+=20;
    print_screen("=========== Actions  ===========",x,y,police);y+=20;
    print_screen("= ESPACE  : Lancer la peche            =",x,y,police);y+=20;
    print_screen("==============================",x,y,police);y+=20;
    print_screen("========= BUT du jeu  ==========",x,y,police);y+=20;
    print_screen("=   Pecher un maximum de             =",x,y,police);y+=20;
    print_screen("=   poisson sur le nombre de          =",x,y,police);y+=20;
    print_screen("=   tours impartis.                                =",x,y,police);y+=20;
    print_screen("=    /!\\ un poiscail, ca mord !            =",x,y,police);y+=20;
    print_screen("==============================",x,y,police);
    
    afficher_pvPecheur(police);
    
}

void afficher_pvPecheur(TTF_Font *police)
	{
		int i;
		SDL_Rect posCoeur;
		posCoeur.x = _TAILLE_TOTALE_/3;
		posCoeur.y = (_TAILLE_TOTALE_/2)+(3*_MAP_SIZE_);
		for(i=0;i<(pvPecheur1/10);i++)
		{
			posCoeur.x += _MAP_SIZE_;
			SDL_BlitSurface(imgCoeur, NULL, ecran, &posCoeur);//< Blittage de l'image du coeur
		}
		print_values("Points de vie :",pvPecheur1,POSITION_PANIER_X +(_TAILLE_TOTALE_/4)+10,POSITION_PANIER_Y+75,police);
		print_screen(" %",POSITION_PANIER_X +(_TAILLE_TOTALE_/4)+116,POSITION_PANIER_Y+75,police);
	}

int afficher_menu(TTF_Font* police)
{
    SDL_Rect
			posmenu1,
			posmenu2,
			posmenu3,
			posmenuIntro,
			posLogo,
			posFond,
			monTxt;
	int
		posX,
		posY,
		valy,
		val;
    char
			*intro="Jeu de la vie V7.5",
			buf[32]="",
			buf2[32]="",
			buf3[32]="";

    SDL_Surface
				*menuIntro=NULL,
				*menu1=NULL,
				*menu2=NULL,
				*menu3=NULL,
				*menu4=NULL,
				*imageDeFondIntro=NULL;
    SDL_Event event;

    TTF_Font
			*policeTitre,
			*policeLancer,
			*policeMenu;

	// Fond
	imageDeFondIntro = SDL_LoadBMP("img/mer.bmp");
	posFond.x = 0;
	posFond.y = 0;
    SDL_BlitSurface(imageDeFond, NULL, ecran, &posFond);//< Blittage de l'image de fond

	// ============== Design ================
    SDL_Color jaune 			= {255, 255, 0};
    SDL_Color rouge				= {204, 0, 0};
    SDL_Color vert 				= {0, 102, 0};
    SDL_Color violet			= {153, 0, 76};
    policeTitre 				= TTF_OpenFont("img/waltographUI.ttf", 25);
    policeMenu					= TTF_OpenFont("img/waltographUI.ttf", 20);
    policeLancer				= TTF_OpenFont("img/waltographUI.ttf", 23);

	// === Logo & Intro ===
	val =(WIDTH /2) - 50;
	valy =  (HEIGH /2) - (_MAP_SIZE_*SAUTDECASE /2);
    posLogo.x=val - 92;
	posLogo.y= valy - 81;
	posmenuIntro.x = val-130;
	posmenuIntro.y = valy;

	// == Pos ==

		posX = (WIDTH/2)-80;
		posY = (HEIGH / 2)-50;

		posmenu1.x	= 	posX-170;
        posmenu1.y	=	posY;

        posmenu2.x	=	posX;
        posmenu2.y	=	posY;

        posmenu3.x	=	posX+200;
        posmenu3.y	=	posY;

        monTxt.x= posX-230;
		monTxt.y= posY+100;


		sprintf(buf,"Mode normal");
		sprintf(buf2,"Mode FF");
		sprintf(buf3,"Config");

		menuIntro = TTF_RenderText_Solid(policeTitre, intro, rouge);
		menu1 = TTF_RenderText_Solid(policeMenu, buf, violet);
		menu2 = TTF_RenderText_Solid(policeMenu, buf2, violet);
		menu3 = TTF_RenderText_Solid(policeMenu, buf3, jaune);
		menu4 = TTF_RenderText_Solid(policeLancer,"Tapez entree pour valider votre choix !",vert);

    int continuer=1,pos =0;

    while(continuer){


        SDL_WaitEvent(&event);



        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_d:
                    case SDLK_RIGHT: // FlÃ¨che haut
                        if ( pos < 2 )
                        pos++;
                        break;
                    case SDLK_q:
                    case SDLK_LEFT: // FlÃ¨che bas
						if ( pos > 0 )
                        pos--;
                        break;
                    case SDLK_RETURN:
                        continuer=0;
                        break;
                    default: break;
                }
                break;
        }

		//SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

        if(pos == 1)
        {
			menu1 = TTF_RenderText_Solid(policeMenu, buf, violet); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu2 = TTF_RenderText_Solid(policeMenu, buf2, jaune); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu3 = TTF_RenderText_Solid(policeMenu, buf3, violet);
        }
        else if (pos == 2)
        {
            menu1 = TTF_RenderText_Solid(policeMenu, buf, violet); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu2 = TTF_RenderText_Solid(policeMenu, buf2, violet); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu3 = TTF_RenderText_Solid(policeMenu, buf3, jaune);
        }
        else
        {
			menu1 = TTF_RenderText_Solid(policeMenu, buf, jaune); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu2 = TTF_RenderText_Solid(policeMenu, buf2, violet); /* On Ã©crit la chaÃ®ne temps dans la SDL_Surface */
            menu3 = TTF_RenderText_Solid(policeMenu, buf3, violet);
		}

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 69, 120, 214));

        SDL_BlitSurface(imageDeFondIntro, NULL, ecran, &posFond);//< Blittage de l'image de fond

        SDL_BlitSurface(menuIntro, NULL, ecran, &posmenuIntro); /* Blit du texte */
        SDL_BlitSurface(menu1, NULL, ecran, &posmenu1); /* Blit du texte */
        SDL_BlitSurface(menu2, NULL, ecran, &posmenu2); /* Blit du texte */
        SDL_BlitSurface(menu3, NULL, ecran, &posmenu3); /* Blit du texte */
		SDL_BlitSurface(logo, NULL, ecran, &posLogo); //< Bittage du logo
        SDL_BlitSurface(menu4,NULL,ecran,&monTxt);


        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menuIntro),
	SDL_FreeSurface(menu1),
	SDL_FreeSurface(menu2),
	SDL_FreeSurface(menu3),
	SDL_FreeSurface(menu4),
	SDL_FreeSurface(imageDeFondIntro);

    return pos;
}
