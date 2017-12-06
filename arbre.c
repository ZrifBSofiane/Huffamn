#include <stdio.h>
#include "arbre.h"


arbre* creer_feuille(int occurence,char caractere)
{
    arbre* feuille = (arbre*)malloc(sizeof(arbre));
    if(feuille != NULL)
    {
        feuille->caractere = caractere;
        feuille->occurence = occurence;
        feuille->poids = 0;
        feuille->fils_droit = NULL;
        feuille->fils_gauche = NULL;
    }
    return feuille;
}
