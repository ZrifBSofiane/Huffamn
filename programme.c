#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "liste.h"
#include "fichier.h"
#include <math.h>

void lancement()
{
    printf("Bonjour : \nCe programme permet de compresser un fichier en suivant l'algorithme de Huffman");

    printf("\n-------------------------------------------------------------\n");
    printf("Le texte a compresser de situe dans le fichier \"crypter.txt\" qui se situe a la racine du dossier du programme");
    printf("\nCe fichier n'est pas vide, mais si vous voulez le modifier, faites-le et relancez le programme :)\n");

    printf("\n**********MENU***************");
    printf("\n 1 --> Compression\n 2 --> Decompression\n");
    int choix = 0;
    printf("\nVotre choix : ");
    scanf("%d",&choix);
    if(choix == 1)
    {
        printf("\n**********SOUS - MENU***************");
        printf("\n 1 --> HUFFMAN\n 2 --> BINAIRE\n");
        printf("\nVotre choix : ");
        scanf("%d",&choix);
        if(choix == 1)
        {
            affichage_texte_a_crypter("crypter.txt"); // Affiche le texte

            liste* new_liste = calcul_occurence("crypter.txt"); // calcul les occurences

            printf("\nLe tableau des occurences est cree, veuillez patienter pendant le tri de ce tableau ...");
            printf("\nVoulez-vous voir ce tableau ?\n----OUI : 1\n----NON : n'importe quelle touche sauf 1");

            scanf("%d",&choix);
            liste* liste_triee = trier_liste(new_liste); // On tri la liste
            listeArbre * newListeArbre = NULL;
            newListeArbre = creer_liste_pour_larbre(liste_triee); // On transforme en arbre
            if(choix == 1)
            {
                printf("\n**********************************************************************");
                printf("\n                  SOUS FORME DE LISTE\n");
                affichage_liste(liste_triee);
                printf("\n**********************************************************************");
                printf("\n                  SOUS FORME D'ARBRE\n");
                afficher_liste_arbre(newListeArbre);
            }
            printf("\n\nCreation de l'abre en cours, veuillez patienter ...");
            printf("\n\nVoules vous voir l'abre ?\n----OUI : 1\n----NON : n'importe quelle touche sauf 1");
            choix = 0;
            scanf("%d",&choix);
            listeArbre* arbre1 = creer_arbre_liste(newListeArbre);
            if(choix == 1)
            {
                printf("\n\nNe pas faire attention aux \"x\" \n");
                affichage_arborescence(arbre1,0);
            }
            liste* code_lettre = NULL;
            code_lettre = ecriture_code_lettre("codeLettre.txt",arbre1,0,code_lettre);
            printf("\nLe code est maintenant associe a chaque caractere !");
            printf("\nVoulez-vous voir ce code ?\n----OUI : 1\n----NON : n'importe quelle touche sauf 1");
            choix = 0;
            scanf("%d",&choix);
            if(choix == 1)
            {
            affichage_code_lettre(code_lettre,"codeLettre.txt",newListeArbre);
            }
            ecriture_mot_crypte();
            printf("\n*************************************************************\n");
            printf("\n                       Voila le resultat : \n");
            affichage_mot_crypte();
            printf("\nL'algorithme est maintenant termine :)");
            printf("\nLe code compresse se situe dans le fichier \"mot_crypte.txt\" et le code de chaque lettre \ndans le dossier \"codeLettre.txt\"\n BONNE JOURNEE :) ");
        }
        else
        {
            if (choix == 2)
            {
                affichage_texte_a_crypter("crypter.txt");
                conversion_mot_binaire();
                printf("\n");
                fichier_binaire_sens_correct();
                printf("\n");
                affichage_mot_binaire();
            }
            else
            {
                printf("\nVotre choix n'existe pas, je ferme le programme ...");
            }
        }
    }
    else
    {
        if(choix == 2)
        {
            printf("\n**********SOUS - MENU***************");
            printf("\n 1 --> HUFFMAN\n 2 --> BINAIRE\n");
            printf("\nVotre choix : ");
            scanf("%d",&choix);
            if(choix == 1)
            {
                decompression_mot_crypte();
            }
            else
            {
                if(choix == 2)
                {
                    conversion_binaire_mot();
                }
                else
                {
                    printf("\nVotre choix ne correspond a aucune option !!\nPar consequent le programme est termine : au revoir ...");
                }
            }
        }
        else
        {
                printf("\nVotre choix ne correspond a aucune option !!\nPar consequent le programme est termine : au revoir ...");
        }
    }

        printf("\n\n****************************************************************************");
        printf("\nCe programme a ete realise par BOURAGBA SOFIANE ESILV annee 3 - GROUPE TD C \n\n\n");
}


void conversion_mot_binaire() // C'est en binaire mais du mauvais sens
{

    FILE* fichier_binaire = fopen("motBinaireTemp.txt","w");
    FILE* fichier_texte = fopen("crypter.txt","r");
    if(fichier_texte != NULL)
    {
        char c = fgetc(fichier_texte);
        if(c == EOF)
        {
            printf("\nIl n'y a rien a convertir ...");
        }
        else
        {
            while(c!=EOF)
            {
                int nb_caractere = (int)c;
                int nb_fois = 0;
                int quotient = nb_caractere / 2;
                while(quotient != 0)
                {
                    int reste = nb_caractere%2;
                    if(reste == 0)
                    {
                        fputc(48,fichier_binaire);
                    }
                    else
                    {
                        fputc(49,fichier_binaire);
                    }
                    nb_fois+=1;
                  //  printf("%d",nb_caractere%2);
                    quotient = nb_caractere / 2;
                    nb_caractere = quotient;
                }
                int i=0;
                for(i=1;i<=8-nb_fois;i++)
                {
                   // printf("%d",0);
                    fputc(48,fichier_binaire);
                }

                c=fgetc(fichier_texte);
            }
        }
    }
    fclose(fichier_binaire);
    fclose(fichier_texte);
}

void fichier_binaire_sens_correct() // On lit a partir de la fin pour le mettre dans le bon sens
{
    FILE* fichier_binaire_faux = fopen("motBinaireTemp.txt","r");
    FILE* fichier_binaire = fopen("motBinaire.txt","w");

    fseek(fichier_binaire_faux,-1,SEEK_END);

    char c = fgetc(fichier_binaire_faux);
   // printf("%c",c);
    if(c == '0')
    {
        fputc(48,fichier_binaire);
    }
    else
    {
        fputc(49,fichier_binaire);
    }
    long position = ftell(fichier_binaire_faux);
    while(position != 1)
    {
        fseek(fichier_binaire_faux,-2,SEEK_CUR);
        c = fgetc(fichier_binaire_faux);
       // printf("%c",c);
        if(c == '0')
        {
            fputc(48,fichier_binaire);
        }
        else
        {
            fputc(49,fichier_binaire);
        }
        position = ftell(fichier_binaire_faux);
        if(position<0)
        {
            position = 0;
        }
    }
    fclose(fichier_binaire);
    fclose(fichier_binaire_faux);
}

void affichage_mot_binaire()
{
    FILE* fichier = fopen("motBinaire.txt","r");
    if(fichier != NULL)
    {
        printf("\nLe code converti en binaire ce situe dans le fichier \"motBinaire.txt\" situe a la racine du projet\n\n********** Voici le code **********\n");
        char c = fgetc(fichier);
        while(c != EOF)
        {
            printf("%c",c);
            c = fgetc(fichier);
        }
    }
    fclose(fichier);
}

int taille_binaire()
{
    FILE* fichier = fopen("motBinaire.txt","r");
    int taille = 0;
    if(fichier != NULL)
    {
        char c = fgetc(fichier);
        while(c != EOF)
        {
            taille +=1;
            c = fgetc(fichier);
        }
    }
    fclose(fichier);
    //printf("\nIl y a %d caracteres",taille);
    return taille;
}


void conversion_binaire_mot()
{
    affichage_mot_binaire();
    int taille_caractere = taille_binaire();
    int taille_tableau = taille_caractere / 8;
    char tableau_mot[taille_tableau+1];
    int position = taille_tableau-1;
    tableau_mot[taille_tableau] = '\0'; // Fin de la chaine de caractere
    FILE* fichier = fopen("motBinaire.txt","r");
    if(fichier != NULL)
    {
        char c = 'a';
        int groupe = 0;
        int puissance = 7;
        int nombre = 0;
        while(c != EOF)
        {
            c = fgetc(fichier);
            if(c == '1')
            {
                nombre += (int)pow(2,puissance);
            }
            puissance -=1;
            groupe +=1;
            if(groupe == 8)
            {
                tableau_mot[position]= (char)nombre;
                position-=1;
                //printf("%c",(char)nombre);
                groupe = 0;
                nombre = 0;
                puissance = 7;
            }
        }

    }
    printf("\nLe resultat de la decompression est : ");
    printf("%s",tableau_mot);
    fclose(fichier);
}













