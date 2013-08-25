#include <stdio.h>
#include <stdlib.h>
#include <string.h> //pour strlen, strrev
#include "constantes.h"
#include "verifierMot.h" //pour rendreMotEgal
#include "pioche.h" //pour aLettres
#include "lecture_clavier.h" //pour conversionMaj
#include "poserMot.h" //pour revRail
#define min(a,b) (a<=b?a:b)

#define A_L_ENDROIT 1
#define A_L_ENVERS 0

void trouveMot(int nbLettreRail,int nbLettreJoue,char lettresSurRail[],char mot[],int positionDeToutesLesLettres[],int*stop,int sensDuMotALEndroit)
{
    int i,flag=0;
    char motTemp[CHAINEMAX];
    int detectFin;
    //FILE* dico_temp= NULL;
    char nom_dico[10];
    FILE* dico = NULL;

    //printf("Mots de Longueur %d... Search, starting commençant par %d lettres...",nbLettreRail+nbLettreJoue,nbLettreRail);
    sprintf(nom_dico,"dico%d",(nbLettreRail+nbLettreJoue));
    dico = fopen(nom_dico,"r");
    //printf("Dico %s ouvert.\n",nom_dico);

    if(dico==NULL){
        printf("Le dictionnaire n'est pas trouvable.");
        exit(EXIT_FAILURE);
    }

    //dico_temp = fopen("dico_temp","w");
    do
    {
        detectFin = fscanf(dico,"%s\n",motTemp); //on scanne le mot d'en dessous
        //printf("%s ",motTemp);
        //On met le mot a l'envers si nécessaire
        if(!sensDuMotALEndroit){
            strrev(motTemp);
        }

        for(i=0;i<nbLettreRail;i++)
        {
            if(motTemp[i]!=lettresSurRail[8-nbLettreRail+i]){
                flag=1;
            }
        }

        if(flag==0){
            /*printf("%s",motTemp);
            fprintf(dico_temp,"%s",motTemp);
            fflush(dico_temp);*/
            char finmot[CHAINEMAX];
            conversionMaj(motTemp);
            //printf("%s,fin du mot est : %s. \n",motTemp,finMot(motTemp,nbLettreRail,finmot));
            if(aLettres(finMot(motTemp,nbLettreRail,finmot),positionDeToutesLesLettres,2) && !estDansLog(motTemp)){
                if(!sensDuMotALEndroit){//On remet le mot correctement si cela est nécessaire
                    strrev(motTemp);
                }
                rendreMotEgal(mot,motTemp);
                //printf("mot trouve : %s ", mot);
                detectFin=EOF;
                *stop=1;
            }
        }

        flag=0;

    } while (detectFin!=EOF);


    //fclose(dico_temp);
    fclose(dico);
}

/*
int trouverMotEndroitDroite(char hand[],int nbLettreRail, int nbLettreJoue, char lettresSurRail[],char mot[])
{
    int i,j,k,l,compteLettre=0,motTrouve=0;
    char motTemp2[12];//motTemp3[12];
    char* detectFin;
    int tabTemp[12]={15,15,15,15,15,15,15,15,15,15,15,15};
    FILE* fichier3= NULL;

    fichier3 = fopen("dico_temp.txt","r");

    do {

        k=0;

        detectFin = fgets(motTemp2,CHAINEMAX,fichier3);

        for(i=nbLettreRail;i<(nbLettreRail+nbLettreJoue);i++)
        {
            for(j=0;j<12;j++)
            {
                if((motTemp2[i]==hand[j])&&(tabTemp[0]!=j)&&(tabTemp[1]!=j)&&(tabTemp[2]!=j)&&(tabTemp[3]!=j)&&(tabTemp[4]!=j)&&(tabTemp[5]!=j)&&(tabTemp[6]!=j)&&(tabTemp[7]!=j)&&(tabTemp[8]!=j)&&(tabTemp[9]!=j)&&(tabTemp[10]!=j)&&(tabTemp[11]!=j))
                {
                    tabTemp[k]=j;
                    k++;
                }
            }
        }

        compteLettre=0;

        for(l=0;l<12;l++)
        {
            if(tabTemp[l]!=15)
                compteLettre++;
        }


        if(compteLettre==nbLettreJoue)
        {
            motTrouve=1;
            for (l=0;l<12; l++)
            {
                mot[l]=motTemp2[l];
            }
        }



    } while ((detectFin!=NULL)&&(motTrouve==0));

    fclose(fichier3);

    return motTrouve;
}*/

//Renvoie 1 si elle pose un mot, 0 sinon
int IntA(int positionDeToutesLesLettres[],char mot[],int*methode,int*nombreDeLettresAPousser)
{

    int i,j;
    int stop=0;
    char hand[CHAINEMAX];
    refreshHand(hand,positionDeToutesLesLettres,2);
    char rail[8];
    refreshRail(rail,positionDeToutesLesLettres);

    //convertie en miniscules le rail :
    for(i=0;i<8;i++){
        rail[i]=rail[i]+32;
    }
/*
    printf("RAIL : ");
    affiche(rail);
    printf("  MAIN : %s\n",hand);
*/
    for(i=2;i<=7;i++) // i: Nombre de lettres du rail que l'on utilise
    {
        for(j=min(8-i,strlen(hand));j>=1;j--) // j: Nombre de lettres que l'on joue de notre main
        {
            if(stop==0)
            {
                trouveMot(i,j,rail,mot,positionDeToutesLesLettres,&stop,A_L_ENDROIT);
                if(stop==1){
                    *methode=1;
                    *nombreDeLettresAPousser=i;
                    return 1;
                }
                //Si elle n'a pas trouvé dans ce sens, on en essaye un autre :
                trouveMot(i,j,revRail(rail),mot,positionDeToutesLesLettres,&stop,A_L_ENDROIT);
                if(stop==1){
                    *methode=2;
                    *nombreDeLettresAPousser=i;
                    return 1;
                }
                //Encore un autre sens :
                trouveMot(i,j,rail,mot,positionDeToutesLesLettres,&stop,A_L_ENVERS);
                if(stop==1){
                    *methode=3;
                    *nombreDeLettresAPousser=i;
                    return 1;
                }
                //Dernier sens possible :
                trouveMot(i,j,revRail(rail),mot,positionDeToutesLesLettres,&stop,A_L_ENVERS);
                if(stop==1){
                    *methode=4;
                    *nombreDeLettresAPousser=i;
                    return 1;
                }
            }
        }
    }
    return 0;
}

char* iapremiertour(int positionDeToutesLesLettres[],char mot[]){
    //Il vaut mieux pour l'IA qu'elle mette le premier dans l'ordre alphabétique. Ainsi, elle jouera en première.
    FILE*dico=fopen("dico4","r");
    if(dico==NULL){
        printf("Impossible d'ouvrir le dictionnaire. ");
        exit(EXIT_FAILURE);
    }
    char motTemp[CHAINEMAX];
    fscanf(dico,"%s\n",motTemp);
    int fin;
    while(!aLettres(conversionMaj(motTemp),positionDeToutesLesLettres,2) && (fin=fscanf(dico,"%s\n",motTemp))!=EOF);
    fclose(dico);
    if(fin!=EOF){
        rendreMotEgal(mot,motTemp);
        return mot;
    }else{
        printf("Aucun mot n'est posable ! Recommencez la partie en redémarrant le programme.");
        exit(EXIT_SUCCESS);
    }
}

char* aidepremiertour(int positionDeToutesLesLettres[],char mot[],int joueur){
    FILE*dico=fopen("dico4","r");
    if(dico==NULL){
        printf("Impossible d'ouvrir le dictionnaire. ");
        exit(EXIT_FAILURE);
    }
    char motTemp[CHAINEMAX];
    fscanf(dico,"%s\n",motTemp);
    int fin;
    while(!aLettres(conversionMaj(motTemp),positionDeToutesLesLettres,joueur) && (fin=fscanf(dico,"%s\n",motTemp))!=EOF);
    fclose(dico);
    if(fin!=EOF){
        rendreMotEgal(mot,motTemp);
        return mot;
    }else{
        printf("Aucun mot n'est posable ! Recommencez la partie en redémarrant le programme.");
        exit(EXIT_SUCCESS);
    }
}

char* detecterOcto(int positionDeToutesLesLettes[],char octo[]){
    FILE*dico=fopen("dico8","r");
    if(dico==NULL){
        printf("Impossible d'ouvrir le dictionnaire. ");
        exit(EXIT_FAILURE);
    }
    char motTemp[CHAINEMAX];
    fscanf(dico,"%s\n",motTemp);
    int fin; int pInutile; int pInutile2;
    while(!motPosable(octo,positionDeToutesLesLettes,1,&pInutile,&pInutile2) && (fin=fscanf(dico,"%s\n",motTemp))!=EOF);
    fclose(dico);
    if(fin!=EOF){
        rendreMotEgal(octo,motTemp);
        return octo;
    }else{
        return NULL;
    }
}

char frequenceDesLettres(int i){
    switch(i){
    case 0:
        return 'E';
    case 1:
        return 'S';
    case 2:
        return 'A';
    case 3:
        return 'I';
    case 4:
        return 'T';
    case 5:
        return 'N';
    case 6:
        return 'R';
    case 7:
        return 'U';
    case 8:
        return 'L';
    case 9:
        return 'O';
    case 10:
        return 'D';
    case 11:
        return 'C';
    case 12:
        return 'P';
    case 13:
        return 'M';
    case 14:
        return 'V';
    case 15:
        return 'Q';
    case 16:
        return 'F';
    case 17:
        return 'B';
    case 18:
        return 'G';
    case 19:
        return 'H';
    case 20:
        return 'J';
    case -1:
        return '?';
    default:
        printf("Fréquence, out of range : %d.",i);
        return '?';
    }
}

char iaJeterUneLettre(int positionDeToutesLesLettres[]){
    int i=20;
    int pos; //position de la lettre dans positionDeToutesLesLettres
    while(i>=-1 && !aLettre(frequenceDesLettres(i),2,positionDeToutesLesLettres,&pos)){
        i--;
    }
    //On supprime la lettre de la main de l'ordinateur
    positionDeToutesLesLettres[pos]=D_PIOCHE;
    return frequenceDesLettres(i);
}
