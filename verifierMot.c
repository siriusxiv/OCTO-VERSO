//
//  FonctionOliv.c
//  TA
//
//  Created by Nguyen Quoc on 24/04/13.
//  Copyright (c) 2013 Nguyen Quoc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

//On suppose que la chaine de caractère que l'on envoie est valide.
//Retourne la longueur de la chaine si tout s'est passé correctement, 0 sinon.
int convertToinf(char motaconvertir[],char mot[],int* joker,int* positionJoker){
    int i=0;
    char c=motaconvertir[i];
    while(c!='\0'){
        if(c=='?'){
            mot[i]=motaconvertir[i];//On ne fait rien, on laisse le Joker tel quel
            *joker=1;
            *positionJoker=i;
        }else if(c<65 || (c>90 && c<97) || c>122){//en dehors des lettres de l'alphabet
            return 0;
        }else{
            if(c<91){ //c'est une minuscule
                mot[i]=motaconvertir[i]+32;//transforme en minuscule
            }else{ //c'est une majuscule
                mot[i]=motaconvertir[i];
            }
        }
        i++;
        c=motaconvertir[i];
    }
    mot[i]='\0';
    return i;
}


//vérifier un mot dans le dictionnaire
int verifierMot(char* mot_)
{
    if(estDansLog(mot_)){ //Si le mot a déjà été posé, on s'arrête tout de suite.
        printf("Le mot '%s' a déjà été posé par le passé !",mot_);
        return 0;
    }

    int joker=0;
    int positionJoker;
    char mot[CHAINEMAX];
    int longueurMot = convertToinf(mot_,mot,&joker,&positionJoker);

    char motTemp[CHAINEMAX];
    FILE* fichier = NULL;
    int flag=0;
    int i;
    char* detectFin;

    //ouverture du fichier (on doit ouvrir le fichier correspondant à la bonne taille de notre mot à vérifier)
    switch(longueurMot){
        case 3:
            fichier=fopen("dico3","r");
        break;
        case 4:
            fichier=fopen("dico4","r");
        break;
        case 5:
            fichier=fopen("dico5","r");
        break;
        case 6:
            fichier=fopen("dico6","r");
        break;
        case 7:
            fichier=fopen("dico7","r");
        break;
        case 8:
            fichier=fopen("dico8","r");
        break;
    }

	if(fichier != NULL)
	{

        if(!joker){//Si on joue sans les Jokers

        do {

            flag=1; // Détecte la présence du mot sur la ligne qu'on lit

            detectFin=fgets(motTemp,CHAINEMAX,fichier); //on scane le mot d'en dessous

            i=0;
            //on regarde si les lettres correspondent lettre par lettre jusqu'a l'un des mot que l'on compare soit fini
            while((motTemp[i] != '\0')&&(mot[i] != '\0'))
            {

                if(motTemp[i] != mot[i])
                {
                    flag=0; // si une lettre diffère : ce n'est pas le bon mot
                }
                i++;
            }

        } while ((flag==0) && (detectFin!=NULL));
        //on passe en revu tous les mots tant que le mot n'a pas été trouvé et que le fichier n'est pas fini

        //on regarde si le mot est bien complet
        if(motTemp[i+1] != '\0')
        {
            flag=0;
        }

        // /!\ Fin de LA VERIF : PLACE AU RENVOIE FINAL
        }else{// Si on joue sans les Jokers
            mot[positionJoker]='a'; //on essaye chaque lettre à la suite

            while(mot[positionJoker]!='{' && flag==0){ //'{' est situé juste après 'z' dans le code ASCII


            do {

            flag=1; // Détecte la présence du mot sur la ligne qu'on lit

            detectFin=fgets(motTemp,CHAINEMAX,fichier); //on scane le mot d'en dessous

            i=0;
            //on regarde si les lettres correspondent lettre par lettre jusqu'a l'un des mot que l'on compare soit fini
            while((motTemp[i] != '\0')&&(mot[i] != '\0'))
            {

                if(motTemp[i] != mot[i])
                {
                    flag=0; // si une lettre diffère : ce n'est pas le bon mot
                }
                i++;
            }

        } while ((flag==0) && (detectFin!=NULL));
        //on passe en revu tous les mots tant que le mot n'a pas été trouvé et que le fichier n'est pas fini

         // /!\ Fin de LA VERIF : Si flag==0, on reboucle
        mot[positionJoker]=mot[positionJoker]+1; // On passe à la lettre suivante
        rewind(fichier);   //On remet le curseur au début du fichier
        }

        }



        if(flag==1)
        {
            printf("Le mot '%s' est dans le dictionnaire \n", mot );
        }
        else
        {
            printf("Le mot '%s' n'est pas dans le dictionnaire \n", mot);
        }

        fclose(fichier);
        return flag;

	}
	else
	{
		printf("Impossible d'ouvrir le fichier dictionnaire : \n");

        return 0;
	}

}


void logAjout(char mot[]){
    FILE*log=fopen("log","a");
    fprintf(log,"%s\n",mot);
    fclose(log);
}

int estDansLog(char mot[]){
    char temp[CHAINEMAX];
    FILE*log=fopen("log","r");
    while(fscanf(log,"%s",temp)!=EOF){
        if(strcmp(temp,mot)==0){
            fclose(log);
            return 1;
        }
    }
    fclose(log);
    return 0;
}

char* finMot(char mot[],int nombreDeLettresAPousser,char finmot[]){
    int i=0;
    while(mot[i+nombreDeLettresAPousser]!='\0'){
        finmot[i]=mot[i+nombreDeLettresAPousser];
        i++;
    }
    finmot[i]='\0';
    //printf("Fin du mot : %s",finmot);
    return finmot;
}

void rendreMotEgal(char motTest[],char mot[]){
    int i=0;
    while(mot[i]!='\0'){
        motTest[i]=mot[i];
        i++;
    }
    motTest[i]='\0';
}

void revRailInt(char rail[]){
    char temp[8];
    int i;
    for(i=0;i<8;i++){
        temp[i]=rail[7-i];
    }
    for(i=0;i<8;i++){
        rail[i]=temp[i];
    }
}

//Cette fonction vérifie tout, qu'il est posable sur le rail et qu'on a les bonnes lettres
//Renvoie finmot (ce sont les lettres que l'on doit poser et que l'on va donc retirer de la main du joueur)
int motPosable(char mot[],int positionDeToutesLesLettres[],int joueur,int*nombreDeLettresAPousser,int* methode){
    char rail[8];
    refreshRail(rail,positionDeToutesLesLettres);
    *methode = motPosableSurRail(rail,mot,nombreDeLettresAPousser);
    //printf("Nombre de lettres à pousser : %d",*nombreDeLettresAPousser);
    char motTest[CHAINEMAX];
    switch(*methode){
    case 0:
        //printf("Ce mot ne peut être posé sur le rail. ");
        return 0;//On ne peut pas poser le mot
    case 1:
        rendreMotEgal(motTest,mot);
        break;
    case 2:
        rendreMotEgal(motTest,mot);
        revRailInt(rail);
        break;
    case 3:
        rendreMotEgal(motTest,strrev(mot));
        break;
    case 4:
        rendreMotEgal(motTest,strrev(mot));
        revRailInt(rail);
        break;
    }

    //On vérifie que l'on a les bonnes lettres
    char finmot[CHAINEMAX];
    if(aLettres(finMot(mot,*nombreDeLettresAPousser,finmot),positionDeToutesLesLettres,joueur)){
        printf("Vous avez les bonnes lettres pour poser ce mot. ");
        //Remet le mot correctement s'il a été retourné.
        if(*methode>=3){
            strrev(mot);
        }
        return 1;
    }else{
        printf("Vous n'avez pas les lettres pour poser ce mot ! ");
        //Remet le mot correctement s'il a été retourné.
        if(*methode>=3){
            strrev(mot);
        }
        return 0;
    }
}

