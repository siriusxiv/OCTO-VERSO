#include "constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //pour strlen

void initLettres(int positionDeToutesLesLettres[], int joker){
    int i;
    if(joker){
        for(i=0;i<NOMBREDELETTRES;i++){
            positionDeToutesLesLettres[i]=D_PIOCHE;
        }
    } else{
        for(i=0;i<NOMBREDELETTRES-2;i++){
            positionDeToutesLesLettres[i]=D_PIOCHE;
        }
        positionDeToutesLesLettres[i]=PAS_DE_JOKER;
        positionDeToutesLesLettres[i+1]=PAS_DE_JOKER;
    }
}

char intToChar(int n){
    return ('0'+n);
}

void creerDico(){
    FILE* f=fopen(DICO,"r");
    if(f==NULL){
        printf("Erreur, le fichier """);
        printf(DICO);
        printf(""" est absent");
        exit(EXIT_FAILURE);
    }else{
    FILE* dic[6];
    char str[6]="dico";
    str[5]='\0';
    int i;
    for(i=0;i<6;i++){
        str[4]=intToChar(i+3);
        dic[i]=fopen(str,"w");
    }

    char tempMot[30];
    while(fscanf(f,"%s",tempMot)!=EOF){
        int tailleMot = strlen(tempMot);
        if (tailleMot >= 3 && tailleMot <= 8){
            FILE *fluxFinal = dic[tailleMot - 3];
            fprintf(fluxFinal, "%s\n", tempMot);
            fflush(fluxFinal);
        }
    }

    for(i=0;i<6;i++){
        fclose(dic[i]);
    }
    }
}

void supprDico(){
    remove("dico3");
    remove("dico4");
    remove("dico5");
    remove("dico6");
    remove("dico7");
    remove("dico8");
    remove("log");
    remove("dico_temp");
}
