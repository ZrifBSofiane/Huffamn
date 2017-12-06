#include <stdio.h>
#include "liste.h"
#include "arbre.h"
liste* creer_liste(int valeur, char caractere)
{
    liste* new_liste = (liste*)malloc(sizeof(liste));
    if(new_liste != NULL)
    {
        new_liste->lettre = caractere;
        new_liste->nb_occu = valeur;
        new_liste->suivante = NULL;
    }
    else
    {
        printf("\nErreur d'allocation mémoire lors de la creation de la liste");
    }
    return new_liste;
}

liste* ajouter_element(liste* debut,int valeur, char caractere)
{
    liste* liste_ajout = creer_liste(valeur,caractere);
    if(debut == NULL)
    {
        return liste_ajout;
    }
    else
    {
        liste* temp = debut;
        while(temp->suivante!=NULL)
        {
            temp = temp->suivante;
        }
        temp->suivante = liste_ajout;

        return debut;
    }
}

int recherche_caractere(char caractere,liste* debut)
{
    int trouve = 0;
    if(debut != NULL)
    {
        liste* temp = debut;
        while(temp!= NULL && !trouve)
        {
            if(temp->lettre == caractere)
            {
                trouve = 1;
            }
            temp=temp->suivante;
        }
    }
    return trouve;
}

void affichage_liste(liste* debut)
{
    if(debut == NULL)
    {
        printf("\nIl n'y a rien a afficher");
    }
    else
    {
        liste* temp = debut;
        printf("\nVOILA LE TABLEAU D'OCCURENCE");
        printf("\n*********************************");
        printf("\n**  CARACTERE *****  OCCURENCE **");
        printf("\n---------------------------------");
        while(temp != NULL)
        {
            if(temp->lettre == ' ')
            {
                printf("\n|      Space\t | \t %d \t",temp->nb_occu);
                printf("\n---------------------------------");
            }
            else
            {
                if(temp->lettre == '\n')
                {
                    printf("\n|  RetourLigne   | \t %d \t",temp->nb_occu);
                    printf("\n---------------------------------");
                }
                else
                {
                    printf("\n|\t %c  \t | \t %d \t",temp->lettre,temp->nb_occu);
                    printf("\n---------------------------------");

                }
            }

            temp=temp->suivante;

        }
    }
}

liste* calcul_occurence(char nom_fichier[])
{
    FILE* fichier = ouverture_fichier_a_crypter(nom_fichier);
    if(fichier != NULL)
    {
        int nb_caractere = nombre_caractere(nom_fichier);
        int i =1;
        liste* liste_chaine = NULL;
        for(i=0;i<nb_caractere;i++)
        {
            int nb_occurence = 0;
            fseek(fichier,i,SEEK_SET); // Permet de changer le caractere a comparer
            char caractere_compare = fgetc(fichier);
            fseek(fichier,0,SEEK_SET); // On remet le curseur au debut du fichier pour pouvoir comparer
            char caractere_comparant = fgetc(fichier);

            if( !recherche_caractere(caractere_compare,liste_chaine)) // On regarde si on a deja calculer l'occurence de la lettre
            {
                while(caractere_comparant != EOF)                   // Si c'est pas le cas alors on le fait
                {
                    if(caractere_comparant == caractere_compare)
                    {
                        nb_occurence += 1;
                    }
                    caractere_comparant = fgetc(fichier);
                }
                liste_chaine = ajouter_element(liste_chaine,nb_occurence,caractere_compare);
            }
        }
        fclose(fichier);
        return liste_chaine;
    }
}

int taille_liste(liste* debut)
{
    int taille = 0;
    if(debut != NULL)
    {
        liste* temp = debut;
        while(temp->suivante != NULL)
        {
            taille+=1;
            temp=temp->suivante;
        }
        taille +=1;
    }
    return taille;
}

liste* copie_liste(liste* debut)
{
    if(debut == NULL)
    {
        printf("\nIl n'y a rien a copier");
    }
    else
    {
        liste* temp = debut;
        liste* copie = NULL;
        while(temp!=NULL)
        {
            copie = ajouter_element(copie,temp->nb_occu,temp->lettre);
            temp = temp->suivante;
        }
        return copie;
    }
}


liste* supprimer_element_nb(liste* debut,int valeur)
{

    if(debut == NULL)
    {
        printf("\nIl n'y a rien a supprimer");
    }
    else
    {
        liste* temp = debut;
        int continuer = 1;
        if(temp->nb_occu == valeur)
        {
            return temp->suivante;
        }
        else
        {
            while(temp->suivante!= NULL && continuer)
            {

                if(temp->suivante->nb_occu == valeur)
                {
                    if(temp->suivante->suivante == NULL)
                    {
                        temp->suivante = NULL;
                        continuer = 0;
                        break;
                    }
                    else
                    {
                        temp->suivante = temp->suivante->suivante;
                        continuer = 0;
                    }
                }
                temp=temp->suivante;
            }
            return debut;
        }
    }
}


int recherche_occurence(int nombre, liste* debut)
{
    int trouve = 0;
    if(debut != NULL)
    {
        liste* temp = debut;
        while(temp!= NULL && !trouve)
        {
            if(temp->nb_occu == nombre)
            {
                trouve = 1;
            }
            temp=temp->suivante;
        }
    }
    return trouve;
}

liste* trier_liste(liste* debut)
{
    liste* liste_trie = NULL;

    if(debut == NULL)
    {
        printf("\nIn n'y a rien a trier");
    }
    else
    {
        liste* temp_liste = debut;
        int valeur=1;
        while(temp_liste != NULL)
        {


            while(recherche_occurence(valeur,temp_liste))
            {
                //printf("\nJe suis dans le premier while");
                liste* temp_recherche = temp_liste;
                while(temp_recherche !=NULL )
                {
                    //printf("\nJe suis dans le deuxieme while");
                    if(temp_recherche->nb_occu == valeur)
                    {

                        liste_trie = ajouter_element(liste_trie,temp_recherche->nb_occu,temp_recherche->lettre);
                        temp_liste = supprimer_element_nb(temp_liste,temp_recherche->nb_occu);
                       // printf("\nListe temp :");
                        //affichage_liste(temp_liste);
                        //affichage_liste(liste_trie);

                    }
                    temp_recherche = temp_recherche->suivante;
                    //printf("\nRecherche valeur %d resultat : %d",valeur,recherche_occurence(valeur,temp_liste));
                }
            }
            valeur += 1;
        }


    }
    return liste_trie;
}


listeArbre* creer_liste_pour_arbre(int valeur, char caractere)
{
    listeArbre* new_liste = (listeArbre*)malloc(sizeof(listeArbre));
    if(new_liste != NULL)
    {
        new_liste->caractere = caractere;
        new_liste->occurence = valeur;
        new_liste->poids = valeur;
        new_liste->fils_gauche=NULL;
        new_liste->fils_droit = NULL;
        new_liste->suivant = NULL;
    }
    else
    {
        printf("\nErreur d'allocation mémoire lors de la creation de la listeArbre");
    }
    return new_liste;
}


listeArbre* ajouter_element_pour_arbre(listeArbre* debut,int valeur, char caractere)
{
    listeArbre* liste_ajout = creer_liste_pour_arbre(valeur,caractere);
    if(debut == NULL)
    {
        return liste_ajout;
    }
    else
    {
        listeArbre* temp = debut;
        while(temp->suivant!=NULL)
        {
            temp = temp->suivant;
        }
        temp->suivant = liste_ajout;

        return debut;
    }
}


listeArbre* creer_liste_pour_larbre(liste* debut)
{
    listeArbre* nouveau = NULL;
    if(debut == NULL)
    {
        printf("\nIl n'y a rien a faire ...");
    }
    else
    {
        liste* temp = debut;
        while(temp!= NULL)
        {
            nouveau = ajouter_element_pour_arbre(nouveau,temp->nb_occu,temp->lettre);
            temp = temp->suivante;
        }
    }
    return nouveau;
}


void afficher_liste_arbre(listeArbre* debut)
{
    if(debut == NULL)
    {
        printf("\nIl n'y a rien a afficher");
    }
    else
    {
        listeArbre* temp = debut;
        while(temp!= NULL)
        {
            printf("\nFeuille : %c  -> Occurence : %d   -> Poids : %d",temp->caractere,temp->occurence,temp->poids);
            temp=temp->suivant;
        }
    }
}


listeArbre* supprimer_tete_liste_arbre(listeArbre* debut)
{
    if(debut == NULL)
    {
        printf("\nIl n'y a rien a supprimer");
    }
    else
    {
        if(debut->suivant == NULL)
        {
            return NULL;
        }
        else
        {
            return debut->suivant;
        }
    }
}

listeArbre* creer_pere_avec_feuille(listeArbre* feuille1, listeArbre* feuille2)
{
    listeArbre * nouveau = (listeArbre*)malloc(sizeof(listeArbre));
    if(nouveau != NULL)
    {
        nouveau->fils_droit = feuille1;
        nouveau->fils_gauche = feuille2;
        nouveau->occurence = feuille1->occurence + feuille2 ->occurence;
        nouveau->poids = feuille1->occurence + feuille2 ->occurence;


    }
    return nouveau;
}

int taille_listeArbre(listeArbre* debut)
{
    int taille = 0;
    if(debut != NULL)
    {
        listeArbre* temp = debut;
        while(temp!=NULL)
        {
            taille+=1;
            temp = temp->suivant;
        }
    }
    return taille;
}


listeArbre* copie_liste_arbre(listeArbre* debut)
{
    listeArbre* nouveau= NULL;
    listeArbre* temp = debut;
    while(temp!= NULL)
    {
        nouveau=ajouter_element_pour_arbre(nouveau,temp->occurence,temp->caractere);
        temp=temp->suivant;
    }
    return nouveau;
}

void affichage_arborescence(listeArbre* arbre,int compteur)
{
  if(arbre != NULL)
  {
        int i=0;
         printf("\n");
        for(i = 0; i<= compteur;i++)
        {
            printf("   ");
        }

      if(arbre->caractere == ' ')
      {
          printf("|-%d space",arbre->poids);
          affichage_arborescence(arbre->fils_gauche,compteur+1);
          affichage_arborescence(arbre->fils_droit,compteur+1);
      }
      else
      {
        if(arbre->caractere == '\n')
        {
            printf("|-%d Saut de Ligne",arbre->poids);
            affichage_arborescence(arbre->fils_gauche,compteur+1);
            affichage_arborescence(arbre->fils_droit,compteur+1);
        }
        else
        {
            printf("|-%d %c",arbre->poids,arbre->caractere);
            affichage_arborescence(arbre->fils_gauche,compteur+1);
            affichage_arborescence(arbre->fils_droit,compteur+1);
        }
      }


  }
  if( arbre == NULL)
  {
       /* int i=0;
         printf("\n");
        for(i = 0; i<= compteur;i++)
            printf("   ");

      printf("|-x ");*/
  }

}

listeArbre* creer_arbre_liste(listeArbre* debut)
{
    listeArbre* nouveau = (listeArbre*)malloc(sizeof(listeArbre));

    if(nouveau != NULL)
    {
        nouveau->occurence=0;
        nouveau->poids=0;
        nouveau->fils_droit= NULL;
        nouveau->fils_gauche=NULL;
        nouveau->suivant=NULL;

        listeArbre* temp = debut;
        while(temp!= NULL)
        {
            nouveau = creer_pere_avec_feuille(nouveau,temp);
            temp=temp->suivant;
        }
    }
    return nouveau;
}

listeArbre* est_feuille(listeArbre* noeud)
{
    int resultat = 0;
    if(noeud->fils_droit == NULL && noeud->fils_gauche==NULL)
    {
        resultat = 1;
    }
    return resultat;
}

liste* ecriture_code_lettre(char nom_fichier[],listeArbre* arbre,int occurence,liste* debut)
{
    int recommencer = 0;
    FILE* fichier = fopen(nom_fichier,"a");
    if(fichier != NULL)
    {

        if(!(est_feuille(arbre)))
        {
            //printf("%d",0);
            //fputc(48,fichier);
            debut = ajouter_element(debut,0,'■');
            ecriture_code_lettre(nom_fichier,arbre->fils_gauche,occurence+1,debut);
            int i=0;
            for(i=0; i<= occurence;i++)
            {
                //fputc(49,fichier);
                //printf("%d",1);
                debut = ajouter_element(debut,1,'■');
            }

            ecriture_code_lettre(nom_fichier,arbre->fils_droit,occurence+1,debut);
        }
        else
        {
                debut = ajouter_element(debut,-1,arbre->caractere);
                //fputc(arbre->caractere,fichier);
                //fputc(13,fichier); // Saut de ligne
               // printf("%c\n",arbre->caractere);

        }
    }
    fclose(fichier);
    return debut;
}

void affichage_code_lettre(liste* debut,char nom_fichier[],listeArbre* debut_arbre) // zffichage et ecriture
{
    if(debut != NULL)
    {
        FILE* fichier = fopen(nom_fichier,"w"); // on efface le fichier a chaque fois
        liste* temp = debut;
        printf("\nVOILA LE TABLEAU QUI ASSOCIE UN CODE A CHAQUE CARACTERE");
        printf("\n*********************************");
        printf("\n******\t  CODE\t******************  CARACTERE ***");
        printf("\n-------------------------------------------------\n");
        int taille=taille_listeArbre(debut_arbre);
        int continuer = 1;
        int compteur = 0;
        while(temp!=NULL && continuer)
        {

            if(temp->nb_occu==-1)
            {
                printf("\t\t\t\t||\t%c\t|\n",temp->lettre);
                fputc(temp->lettre,fichier);
                fputc(13,fichier); // Saut de ligne
                compteur += 1; // nombre de caractere
            }
            else
            {
                printf("%d",temp->nb_occu);
                if(temp->nb_occu==0)
                {
                    fputc(48,fichier);
                }
                else
                {
                    fputc(49,fichier);
                }
            }
            if(compteur == taille)
            {
                continuer = 0;
            }

            temp=temp->suivante;
        }
        fclose(fichier);

    }
}

void ecriture_mot_crypte()
{
    FILE* fichier_lecture = fopen("crypter.txt","r");
    FILE* fichier_code = fopen("codeLettre.txt","r");
    FILE* fichier_crypte = fopen("mot_crypte.txt","w");

    if(fichier_lecture!=NULL)
    {
        char c_lecture = fgetc(fichier_lecture);
        while(c_lecture != EOF)
        {
            int position = 0;
            char c_code = fgetc(fichier_code);
            while(c_code != c_lecture) // On cherche le caractere
            {
                if(c_code=='\r')
                {
                    position +=1;
                }
                c_code = fgetc(fichier_code);
            } // On a la position, il faut se decaller de position +2 pour etre en debut de ligne, car triangle rectangle
            //On se remet au debut de la ligne :
            fseek(fichier_code,((-1*position)-2),SEEK_CUR);
            //On ecrit dans le fichier crypte
            int j=0;
            for(j=0;j<position+1;j++)
            {
                c_code = fgetc(fichier_code);
                fputc(c_code,fichier_crypte);
            }
            rewind(fichier_code); // On remet au debut
            c_lecture = fgetc(fichier_lecture);
        }
    }
    fclose(fichier_code);
    fclose(fichier_crypte);
    fclose(fichier_lecture);
}

void affichage_mot_crypte()
{
    FILE* fichier=fopen("mot_crypte.txt","r");
    if(fichier!= NULL)
    {
       // rewind(fichier);
        printf("\nVoila la phrase cryptee grace a l'algo d'Huffman :\n");
        char c = 'a';

        while (c!= EOF)
        {
            c = fgetc(fichier);
            printf("%c",c);
        }
    }
    fclose(fichier);
}

void decompression_mot_crypte()
{
    FILE* fichier_code = fopen("mot_crypte.txt","r");
    FILE* fichier_lettre = fopen("codeLettre.txt","r");

    char c = fgetc(fichier_code);
    if(c== EOF)
    {
        printf("\nIl n'y a rien a decompresser, le fichier est vide...");
    }
    else
    {
        printf("\nResultat de la decompression : \n\n");
        rewind(fichier_code);
        char c = fgetc(fichier_code);
        while( c != EOF)
        {
            int nombre_de_un = 0;
            int position = 0;
            while(c!='0')
            {
                c=fgetc(fichier_code);
                nombre_de_un+=1;
            }
            int i = 0;
            for( i=3;i<=nombre_de_un+2;i++)
            {
                position = position +i;
            }
            fseek(fichier_lettre,position + nombre_de_un+1,SEEK_SET);
            char lettre = fgetc(fichier_lettre);
            printf("%c",lettre);
            rewind(fichier_lettre);
            c=fgetc(fichier_code);
        }
    }
    printf("\n\n");
    fclose(fichier_code);
    fclose(fichier_lettre);
}
















