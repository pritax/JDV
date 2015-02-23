#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "animal.h"
#include "ajout_animaux.h"

extern Animal* map;

/* créer une map, et l'initialise avec des animaux de type vide*/
void genererMap(void)
{
    int i;

    map = malloc(_TAILLE_TOTALE_*sizeof(Animal));

    if ( map == NULL ) { perror("Pas d'alloc"); exit(EXIT_FAILURE); }

        /* si aucunes erreurs */

        for(i=0;i<_TAILLE_TOTALE_;i++)
        {
            if((i+1)%(_MAP_SIZE_)==0 || (i%_MAP_SIZE_)==0||i<_MAP_SIZE_ || i>(_TAILLE_TOTALE_-_MAP_SIZE_) )
            {
                ajouter_mur(i);

            }/* on met un mur*/
            else
            supprimer_animal(i); /* affectation d'un animal vide */
        }
}

/*  pioche une case au hasard sur la map */
int case_aleatoire(int MIN, int MAX)
{
    return MIN+(int)rand()%(MAX-MIN+1);
}

int* alea(int k, int n)
{
    int i,r;

    int* val = (int*) malloc(n*sizeof(int));
    int* tab = (int*) malloc(n*sizeof(int));


    for (i=0; i<n; i++)
        val[i]=i;

    for (i=0; i<k; i++)
    {
        r = rand() % (n-i);

        tab[i] = val[r];
        val[r] = val[n-i-1];
    }

    /*free(val); // Free NON clean */
    return tab;
}


