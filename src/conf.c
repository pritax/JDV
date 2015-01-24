#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf.h"

//tout est stoclé dans cette super structure qui est globale

/* GLOBAL CFG STRUCT*/
CONFIG CFG = {0};


/* tableaux locaux à la fonctions permettant de stocker temporairement les infos
    tableau permet de simplifier les fonctions setXXXX en permettant le copier/coller :)
*/
static char* tableau[10]= {"BAR","PYRANHA","CORAIL","THON","BALEINE","REQUIN","ORQUE","PLANCTON","POLLUTION","VIDE"};
static char *result[2];

/*  fonction permettant de chercher une cle dans le fichier
    et de charger dans la structure CFG les données relatives */

void getKEYandVALUE(char*,char* tab[2]);
void setMAP(void);
void setSAUTMAX(void);
void setIMMO(void);
void setPOPULATION(void);
void setDUREEVIE(void);
void setBIDE(void);
void setTAILLE(void);
void setGESTATION(void);
void setREPRODUCTION(void);
void setMETABOLISME(void);
void setTYPE(void);
void setSATIETE(void);

/*  fonction de test de chargement qui affiches les 93 variables !*/
void test(void);
/* fichier global pour l'ouverture du .cfg */
static FILE *file ;

/* var global, stock la ligne courante  */
char line [ 128 ];


/* main de cfg.c, permet d'appeller toutes les fonctions  */
void loadCFG( void )
{

   static const char filename[] = "parametres.cfg";
   file = fopen ( filename, "r" );
   /* ouverture du fichier de conf*/
   if ( file != NULL )
   {

     /* Tant qu'on est pas à la fin du fichier, on lit
        d'ou l'importance du global car toute action dans
        une fonction entraine le déplacement du curseur général
     */
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
          /* on recupere la clé de la ligne courante et sa valeur qu'on stock dans result
            result[0] = la clé
            result[1]=la valeur
          */
          getKEYandVALUE(line,result);

          /* si la clé est un tag dans le fichier, on appel la fonction correspondante */
          if( strncmp(result[0],"//----MAP",strlen(result[0] - 1)) == 0) setMAP();
          if( strncmp(result[0],"//----SAUTMAX",strlen(result[0] - 1)) == 0) setSAUTMAX();
          if( strncmp(result[0],"//----IMMOBILITE",strlen(result[0] - 1)) == 0) setIMMO();
          if( strncmp(result[0],"//----POPULATION",strlen(result[0] - 1)) == 0) setPOPULATION();
          if( strncmp(result[0],"//----DUREE_VIE",strlen(result[0] - 1)) == 0) setDUREEVIE();
          if( strncmp(result[0],"//----BIDE",strlen(result[0] - 1)) == 0) setBIDE();
          if( strncmp(result[0],"//----TAILLE",strlen(result[0] - 1)) == 0) setTAILLE();
          if( strncmp(result[0],"//----GESTATION",strlen(result[0] - 1)) == 0) setGESTATION();
          if( strncmp(result[0],"//----METABOLISME",strlen(result[0] - 1)) == 0) setMETABOLISME();
          if( strncmp(result[0],"//----SATIETE",strlen(result[0] - 1)) == 0) setSATIETE();
          if( strncmp(result[0],"//----TYPE",strlen(result[0] - 1)) == 0) setTYPE();

            /* on reset le buffer line*/
          line[0]='\0';
      }
      fclose ( file );
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
   }
   /*test(); //affiche la structure remplie*/
}

void getKEYandVALUE(char* str,char * tab[2])
{

        char *KEY,*VALUE;
        KEY = strtok(str," ");
        VALUE = strtok(NULL,"\0");

        if (KEY!= NULL)
            tab[0]=KEY;

        if (VALUE!= NULL)
            tab[1]=VALUE;
        else
            tab[1]=NULL;
}

void setMAP(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],"MAP_SIZE") == 0)
            CFG.MAP_SIZE = atoi(result[1]);
        if(strcmp(result[0],"TOTALE") == 0)
            CFG.TAILLE_TOTALE = atoi(result[1]);
        if(strcmp(result[0],"NOMBRE_DE_TOURS") == 0)
            CFG.NOMBRE_DE_TOURS = atoi(result[1]);
        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setSAUTMAX(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {


        if(strcmp(result[0],"SAUTMAX") == 0)
            CFG.SAUT_MAX = atoi(result[1]);
        if(strcmp(result[0],"SAUTMAX_PYRANHA") == 0)
            CFG.SAUT_MAX_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],"SAUTMAX_BALEINE") == 0)
            CFG.SAUT_MAX_BALEINE = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }

}
void setIMMO(void)
{

    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);
    if(strcmp(result[0],"IMMOBILE") == 0)
        CFG.IMMOBILE = atoi(result[1]);
}

void setPOPULATION(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.NB_BAR = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.NB_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.NB_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.NB_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.NB_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.NB_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.NB_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.NB_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.NB_POLLUTION = atoi(result[1]);
        if(strcmp(result[0],tableau[9]) == 0)
            CFG.NB_VIDE = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setDUREEVIE(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {
        if(strcmp(result[0],"DUREE_VIE_MAX") == 0)
            CFG.DUREE_VIE_MAX = atoi(result[1]);
        if(strcmp(result[0],tableau[0]) == 0)
            CFG.d_bar = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.d_pyranha = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.d_corail = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.d_thon = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.d_Baleine = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.d_requin = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.d_orque = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.d_plancton = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.d_pollution = atoi(result[1]);
        if(strcmp(result[0],tableau[9]) == 0)
            CFG.d_vide = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setBIDE(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.BIDE_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.BIDE_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.BIDE_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.BIDE_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.BIDE_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.BIDE_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.BIDE_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.BIDE_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.BIDE_POLLUTION = atoi(result[1]);


        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}


void setTAILLE(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.TAILLE_BAR = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.TAILLE_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.TAILLE_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.TAILLE_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.TAILLE_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.TAILLE_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.TAILLE_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.TAILLE_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.TAILLE_POLLUTION = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setGESTATION(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.GESTATION_BAR = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.GESTATION_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.GESTATION_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.GESTATION_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.GESTATION_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.GESTATION_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.GESTATION_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.GESTATION_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.GESTATION_POLLUTION = atoi(result[1]);


        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setREPRODUCTION(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.FREQUENCE_REPRODUCTION_BAR = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.FREQUENCE_REPRODUCTION_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.FREQUENCE_REPRODUCTION_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.FREQUENCE_REPRODUCTION_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.FREQUENCE_REPRODUCTION_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.FREQUENCE_REPRODUCTION_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.FREQUENCE_REPRODUCTION_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.FREQUENCE_REPRODUCTION_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.FREQUENCE_REPRODUCTION_POLLUTION = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setMETABOLISME(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.METABOLISME_BAR = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.METABOLISME_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.METABOLISME_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.METABOLISME_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.METABOLISME_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.METABOLISME_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.METABOLISME_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.METABOLISME_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.METABOLISME_POLLUTION = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setTYPE(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.t_bar = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.t_pyranha = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.t_corail = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.t_thon = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.t_baleine = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.t_requin = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.t_orque = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.t_plancton = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.t_pollution = atoi(result[1]);
        if(strcmp(result[0],tableau[9]) == 0)
            CFG.t_vide = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}

void setSATIETE(void)
{
    fgets ( line, sizeof line, file );
    getKEYandVALUE(line,result);

    while(strncmp(result[0],"#",1) != 0)
    {

        if(strcmp(result[0],tableau[0]) == 0)
            CFG.SATIETE_BAR = atoi(result[1]);
        if(strcmp(result[0],tableau[1]) == 0)
            CFG.SATIETE_PYRANHA = atoi(result[1]);
        if(strcmp(result[0],tableau[2]) == 0)
            CFG.SATIETE_CORAIL = atoi(result[1]);
        if(strcmp(result[0],tableau[3]) == 0)
            CFG.SATIETE_THON = atoi(result[1]);
        if(strcmp(result[0],tableau[4]) == 0)
            CFG.SATIETE_BALEINE = atoi(result[1]);
        if(strcmp(result[0],tableau[5]) == 0)
            CFG.SATIETE_REQUIN = atoi(result[1]);
        if(strcmp(result[0],tableau[6]) == 0)
            CFG.SATIETE_ORQUE = atoi(result[1]);
        if(strcmp(result[0],tableau[7]) == 0)
            CFG.SATIETE_PLANCTON = atoi(result[1]);
        if(strcmp(result[0],tableau[8]) == 0)
            CFG.SATIETE_POLLUTION = atoi(result[1]);

        fgets ( line, sizeof line, file );
        getKEYandVALUE(line,result);
    }
}
void test(void)
{
int tab[100]={CFG.MAP_SIZE,CFG.TAILLE_TOTALE,CFG.NOMBRE_DE_TOURS,CFG.SAUT_MAX,CFG.SAUT_MAX_PYRANHA,CFG.SAUT_MAX_BALEINE,CFG.IMMOBILE,CFG.NB_BAR,CFG.NB_PYRANHA,CFG.NB_CORAIL,CFG.NB_THON,CFG.NB_BALEINE,CFG.NB_REQUIN,CFG.NB_ORQUE,CFG.NB_PLANCTON,CFG.NB_POLLUTION,CFG.NB_VIDE,CFG.DUREE_VIE_MAX,CFG.d_vide,CFG.d_plancton,CFG.d_pyranha,CFG.d_thon,CFG.d_bar,CFG.d_corail,CFG.d_requin,CFG.d_orque,CFG.d_Baleine,CFG.d_pollution,CFG.BIDE_PLANCTON,CFG.BIDE_CORAIL,CFG.BIDE_PYRANHA,CFG.BIDE_BAR,CFG.BIDE_THON,CFG.BIDE_POLLUTION,CFG.BIDE_REQUIN,CFG.BIDE_ORQUE,CFG.BIDE_BALEINE,CFG.TAILLE_PLANCTON,CFG.TAILLE_CORAIL,CFG.TAILLE_BAR,CFG.TAILLE_THON,CFG.TAILLE_POLLUTION,CFG.TAILLE_PYRANHA,CFG.TAILLE_REQUIN,CFG.TAILLE_ORQUE,CFG.TAILLE_BALEINE,CFG.GESTATION_BAR,CFG.GESTATION_THON,CFG.GESTATION_POLLUTION,CFG.GESTATION_CORAIL,CFG.GESTATION_PYRANHA,CFG.GESTATION_REQUIN,CFG.GESTATION_ORQUE,CFG.GESTATION_BALEINE,CFG.GESTATION_PLANCTON,CFG.FREQUENCE_REPRODUCTION_POLLUTION,CFG.FREQUENCE_REPRODUCTION_PLANCTON,CFG.FREQUENCE_REPRODUCTION_BAR,CFG.FREQUENCE_REPRODUCTION_CORAIL,CFG.FREQUENCE_REPRODUCTION_THON,CFG.FREQUENCE_REPRODUCTION_BALEINE,CFG.FREQUENCE_REPRODUCTION_REQUIN,CFG.FREQUENCE_REPRODUCTION_ORQUE,CFG.FREQUENCE_REPRODUCTION_PYRANHA,CFG.METABOLISME_POLLUTION,CFG.METABOLISME_REQUIN,CFG.METABOLISME_ORQUE,CFG.METABOLISME_BALEINE,CFG.METABOLISME_THON,CFG.METABOLISME_PLANCTON,CFG.METABOLISME_BAR,CFG.METABOLISME_CORAIL,CFG.METABOLISME_PYRANHA,CFG.SATIETE_POLLUTION,CFG.SATIETE_PYRANHA,CFG.SATIETE_ORQUE,CFG.SATIETE_BAR,CFG.SATIETE_BALEINE,CFG.SATIETE_REQUIN,CFG.SATIETE_THON,CFG.SATIETE_CORAIL,CFG.SATIETE_PLANCTON,CFG.t_mur,CFG.t_vide,CFG.t_plancton,CFG.t_corail,CFG.t_bar,CFG.t_thon,CFG.t_pollution,CFG.t_pyranha,CFG.t_requin,CFG.t_orque,CFG.t_baleine,CFG.t_pecheur};
int i=0;
for(i=0;i<100;i++)
    printf("%i: %i \n",i,tab[i]);
}
