#include <stdio.h>
#include "constantes.h"
#include "pioche.h"
#include "verifierMot.h"
#include "poserMot.h"
#include "IA.h"

void afficheTab(int positionDeToutesLesLettres[],int n){
    int i;
    printf("\n");
    for(i=0;i<n;i++){
        if(positionDeToutesLesLettres[i]<0){
            printf("[%d]:%d ",i,positionDeToutesLesLettres[i]);
        }else{
            printf("[%d]: %d ",i,positionDeToutesLesLettres[i]);
        }
    }
}

int fini(int positionDeToutesLesLettres[]){
    int compteurJ1=0;
    int compteurJ2=0;
    int i;
    for(i=0;i<NOMBREDELETTRES;i++){
        if(positionDeToutesLesLettres[i]==D_MAIN1){
            compteurJ1++;
        }
        if(positionDeToutesLesLettres[i]==D_MAIN2){
            compteurJ2++;
        }
    }
    //printf("\nJoueur 1 a %d lettres en main. Joueur 2 en a %d.\n",compteurJ1,compteurJ2);
    if(compteurJ1==0){
        return 1;
    }else if(compteurJ2==0){
        return 2;
    }else{
        return 0;
    }
}

void tour(int joueur,int positionDeToutesLesLettres[],int contreOrdi){
    printf("C'est le tour du joueur %d. Voici votre main : ",joueur);
    afficheMain(positionDeToutesLesLettres,joueur);
    printf("\n                           Voici la main de votre adversaire : ",autre(joueur));
    afficheMain(positionDeToutesLesLettres,autre(joueur));
    printf("\n");
    afficheRail(positionDeToutesLesLettres);

    char mot[CHAINEMAX];
    printf("Quel mot posez-vous ? Si vous voulez passer votre tour, entrez '!'. ");
    taperPasseTour(mot);
    if(mot[0]=='!'){
        passeSonTour(positionDeToutesLesLettres,joueur);
        return 0;
    }else{
        int nombreDeLettresAPousser,methode; //On détermine ces nombres pour poser le mot avec poserMot.
        while (strlen(mot)<3 || strlen(mot)>8  || !motPosable(mot,positionDeToutesLesLettres,joueur,&nombreDeLettresAPousser,&methode) || !verifierMot(mot))
        {
            printf("Le mot n'existe pas, vous ne possédez pas les bonnes lettres ou le mot n'est pas posable : rejouez. ");
            taper(mot);
            if(mot[0]=='!'){
                passeSonTour(positionDeToutesLesLettres,joueur);
                return 0;
            }
        }
        poserMot(positionDeToutesLesLettres,mot,joueur,methode,nombreDeLettresAPousser);
        if(strlen(mot)==8){
            printf("\nFélicitation ! Vous avez posé un OCTO ! Vous pouvez vous défausser d'une lettre au choix. ");
            afficheMain(positionDeToutesLesLettres,joueur);
            enleverUneLettreAuChoix(positionDeToutesLesLettres,joueur);
        }

        //Detection d'un octo
        char octo[CHAINEMAX];
        if(contreOrdi){
            char*p;
            p=detecterOcto(positionDeToutesLesLettres,octo);
            if(p!=NULL){
                printf("L'ordinateur vous fait remarquer que pous auriez pu poser %s. L'ordinateur va donc jeter un lettre.",octo);
                char lettreJetee = iaJeterUneLettre(positionDeToutesLesLettres);
                printf("\nL'ordinateur a jeté un %c.\n",lettreJetee);
            }
        }else{
            printf("Joueur %d, pensez-vous que joueur %d aurait pu poser un octo ? Si vous pensez que c'est le cas, entrez le mot qu'il aurait pu écrire, sinon écrivez n'importe quoi. ",autre(joueur),joueur);
            taper(octo);
            if( motPosable(octo,positionDeToutesLesLettres,joueur,&nombreDeLettresAPousser,&methode) && verifierMot(octo) ){
                printf("Bien joué ! Il aurait en effer pu poser %s. Vous pouvez vous donc vous défausser d'une lettre au choix. ",octo);
                enleverUneLettreAuChoix(positionDeToutesLesLettres, autre(joueur));
            }else{
                printf("Vous faites erreur. Le mot que vous avez entrée n'existe pas ou ne peut être posé.\n");
            }
        }
    }
    //Fin du tour
}

void iatour(int positionDeToutesLesLettres[]){
    char mot[CHAINEMAX];
    int methode, nombreDeLettresAPousser;
    if(IntA(positionDeToutesLesLettres,mot,&methode,&nombreDeLettresAPousser)){
        printf("L'ordinateur pose '%s'. ",mot);
        poserMot(positionDeToutesLesLettres,mot,2,methode,nombreDeLettresAPousser);
        if(strlen(mot)==8){
            printf("L'ordinateur a posé un OCTO ! Il jette donc une lettre. ");
            char lettreJetee = iaJeterUneLettre(positionDeToutesLesLettres);
            printf("Il jette %c.\n",lettreJetee);
        }
    }else{
        printf("L'ordinateur passe son tour. ");
        char lettreJetee = iaJeterUneLettre(positionDeToutesLesLettres);
        char lettreTiree = tirageDUneLettre(positionDeToutesLesLettres,2);
        printf("Il jette %c et pioche %c.\n",lettreJetee,lettreTiree);
    }
}

void jeu(int positionDeToutesLesLettres[], int contreOrdi,int joker){
    piocheDebutDePartie(positionDeToutesLesLettres,joker);
    int premier = poserPremiersMots(positionDeToutesLesLettres,contreOrdi);
    afficheRail(positionDeToutesLesLettres);
    if(premier==1){
        tour(1,positionDeToutesLesLettres,contreOrdi);
    }

    int vainqueur;
    while((vainqueur=fini(positionDeToutesLesLettres))==0){
        if(contreOrdi){
            iatour(positionDeToutesLesLettres);
        }else{
            tour(2,positionDeToutesLesLettres,contreOrdi);
        }
        if((vainqueur=fini(positionDeToutesLesLettres))!=0){
            break;
        }
        tour(1,positionDeToutesLesLettres,contreOrdi);
    }
    printf("Le joueur %d n'a plus de lettres ! Le joueur %d a donc gagné ! La partie est terminée...\n\n",vainqueur,vainqueur);
    if(contreOrdi){
        remove("dico_temp");
    }
}
