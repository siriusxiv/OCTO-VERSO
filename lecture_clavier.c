#include <stdio.h>
#include <string.h>
#include "constantes.h"

//vide le buffers
void clean()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

//renvoie un booléen indiquant si la conversion a réussi ou pas
char* conversionMaj(char mot[]){
    int i=0;
    char c=mot[i];
    while(c!='\0' && i<CHAINEMAX){
        if(c=='?'){
            //On ne fait rien, on laisse le Joker tel quel
        }else if(c<65 || (c>90 && c<97) || c>122){//en dehors des lettres de l'alphabet
            return NULL;
        }else{
            if(c>96){ //c'est une minuscule
                mot[i]=mot[i]-32;//transforme en majuscule
            }
        }
        i++;
        c=mot[i];
    }
    mot[CHAINEMAX-1]='\0';
    return mot;
}

int taper(char mot[]){
    while((scanf("%s",mot))>=CHAINEMAX);
    clean();
    char* pasDeCharBizarre = conversionMaj(mot);
    if(pasDeCharBizarre!=NULL){
        return 1;
    }else{
        return 0;
    }
}

int conversionMajPasseTour(char mot[]){
    int i=0;
    char c=mot[i];
    while(c!='\0' && i<CHAINEMAX){
        if(c=='?' || c=='!'){
            //On ne fait rien, on laisse le Joker ou le passage de tour tel quel
        }else if(c<65 || (c>90 && c<97) || c>122){//en dehors des lettres de l'alphabet
            return 0;
        }else{
            if(c>96){ //c'est une minuscule
                mot[i]=mot[i]-32;//transforme en majuscule
            }
        }
        i++;
        c=mot[i];
    }
    mot[CHAINEMAX-1]='\0';
    return 1;
}

int taperPasseTour(char mot[]){
    while((scanf("%s",mot))>=CHAINEMAX);
    clean();
    int pasDeCharBizarre = conversionMajPasseTour(mot);
    if(pasDeCharBizarre){
        return 1;
    }else{
        return 0;
    }
}

//choix oui/non. renvoie un booléen
void choixYN(int* b){
    char entree[2]=" ";
    do{
        printf(" O/N : ");
        fgets(entree,2,stdin);
        clean();
    }while(entree[0]!='O' && entree[0]!='o' && entree[0]!='N' && entree[0]!='n');

    if(entree[0]=='O'||entree[0]=='o'){
        *b=1;
    }else{
        *b=0;
    }
}

char taperLettre(){
    char entree[2]=" ";
    do{
        printf("Quelle lettre choisissez-vous ? ");
        fgets(entree,2,stdin);
        clean();
        if(entree[0]=='?'){
            break;
        }
    }while(entree[0]<65 || (entree[0]>90 && entree[0]<97) || entree[0]>122);
    if(entree[0]>96){ //c'est une minuscule
        return entree[0]-32;
    }else{
        return entree[0];
    }
}
