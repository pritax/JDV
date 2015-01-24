#ifndef CFG_FILE_H
#define CFG_FILE_H

typedef struct CONFIG
{

//----MAP
int MAP_SIZE;
int TAILLE_TOTALE;
int NOMBRE_DE_TOURS;

//----SAUTMAX
int SAUT_MAX;
int SAUT_MAX_PYRANHA;
int SAUT_MAX_BALEINE;

//----IMMOBILITE
int IMMOBILE;

//----POPULATION
int NB_BAR;
int NB_PYRANHA;
int NB_CORAIL;
int NB_THON;
int NB_BALEINE;
int NB_REQUIN;
int NB_ORQUE;
int NB_PLANCTON; /* 5% de plancton */
int NB_POLLUTION; /* 5% de pollution */
int NB_VIDE;

//----DUREE_VIE
int DUREE_VIE_MAX;
int d_vide; /* duree de vide de l'animal vide */
int d_plancton;
int d_pyranha;
int d_thon;
int d_bar;
int d_corail;
int d_requin;
int d_orque;
int d_Baleine;
int d_pollution;

//----BIDE
int BIDE_PLANCTON;
int BIDE_CORAIL;
int BIDE_PYRANHA;
int BIDE_BAR;
int BIDE_THON;
int BIDE_POLLUTION;
int BIDE_REQUIN;
int BIDE_ORQUE;
int BIDE_BALEINE;

//----TAILLE
int TAILLE_PLANCTON;
int TAILLE_CORAIL;
int TAILLE_BAR;
int TAILLE_THON;
int TAILLE_POLLUTION;
int TAILLE_PYRANHA;
int TAILLE_REQUIN;
int TAILLE_ORQUE;
int TAILLE_BALEINE;

//----GESTATION
int GESTATION_BAR;
int GESTATION_THON;
int GESTATION_POLLUTION;
int GESTATION_CORAIL;
int GESTATION_PYRANHA;
int GESTATION_REQUIN;
int GESTATION_ORQUE;
int GESTATION_BALEINE;
int GESTATION_PLANCTON;

//----REPRODUCTION
int FREQUENCE_REPRODUCTION_POLLUTION;
int FREQUENCE_REPRODUCTION_PLANCTON;
int FREQUENCE_REPRODUCTION_BAR;
int FREQUENCE_REPRODUCTION_CORAIL;
int FREQUENCE_REPRODUCTION_THON;
int FREQUENCE_REPRODUCTION_BALEINE;
int FREQUENCE_REPRODUCTION_REQUIN;
int FREQUENCE_REPRODUCTION_ORQUE;
int FREQUENCE_REPRODUCTION_PYRANHA;

//----METABOLISME
int METABOLISME_POLLUTION;
int METABOLISME_REQUIN;
int METABOLISME_ORQUE;
int METABOLISME_BALEINE;
int METABOLISME_THON;
int METABOLISME_PLANCTON;
int METABOLISME_BAR;
int METABOLISME_CORAIL;
int METABOLISME_PYRANHA;

//----SATIETE
int SATIETE_POLLUTION;
int SATIETE_PYRANHA;
int SATIETE_ORQUE;
int SATIETE_BAR;
int SATIETE_BALEINE;
int SATIETE_REQUIN;
int SATIETE_THON;
int SATIETE_CORAIL;
int SATIETE_PLANCTON;

//----TYPE
int t_mur;
int t_vide; /* il n'y a aucun animal dans la case */
int t_plancton; /* l'animal est un plancton */
int t_corail; /*  l'anomal est les corail */
int t_bar;
int t_thon;
int t_pollution; /* l'animal est la pollution */
int t_pyranha;
int t_requin;
int t_orque;
int t_baleine;
int t_pecheur;

}CONFIG;



#endif // CFG_FILE_H
