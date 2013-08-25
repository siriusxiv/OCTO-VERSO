#include <stdio.h>
#include "constantes.h"

#define MM(a,b) *mini=a; *maxi=b;

void MinMax(int*mini,int*maxi,char lettre){
            switch(lettre)
        {
            case 'A' :
            {
                MM(0,8)
                break;
            }

            case 'B' :
            {
                MM(9,9)
                break;
            }

            case 'C' :
            {
                MM(10,11)
                break;
            }

            case 'D' :
            {
                MM(12,14)
                break;
            }

            case 'E' :
            {
                MM(15,28)
                break;
            }

            case 'F' :
            {
                MM(29,29)
                break;
            }

            case 'G' :
            {
                MM(30,30)
                break;
            }

            case 'H' :
            {
                MM(31,31)
                break;
            }

            case 'I' :
            {
                MM(32,38)
                break;
            }

            case 'J' :
            {
                MM(39,39)
                break;
            }

            case 'L' :
            {
                MM(40,44)
                break;
            }

            case 'M' :
            {
                MM(45,47)
                break;
            }

            case 'N' :
            {
                MM(48,53)
                break;
            }

            case 'O' :
            {
                MM(54,58)
                break;
            }

            case 'P' :
            {
                MM(56,60)
                break;
            }

            case 'Q' :
            {
                MM(61,61)
                break;
            }

            case 'R' :
            {
                MM(62,67)
                break;
            }

            case 'S' :
            {
                MM(68,74)
                break;
            }

            case 'T' :
            {
                MM(75,80)
                break;
            }

            case 'U' :
            {
                MM(81,85)
                break;
            }

            case 'V' :
            {
                MM(86,87)
                break;
            }

            case '?' :
            {
                MM(88,89)
                break;
            }
            default:
                MM(0,89)
                printf("Erreur, pas la bonne lettre dans MinMax. Valeur : %d\n",lettre);
        }
}

char inverseMinMax(int i){
    int j;
    for(j=0;j<NOMBREDELETTRES;j++){
        if(i<9){
            return 'A';
        }else if(i<10){
            return 'B';
        }else if(i<12){
            return 'C';
        }else if(i<15){
            return 'D';
        }else if(i<29){
            return 'E';
        }else if(i<30){
            return 'F';
        }else if(i<31){
            return 'G';
        }else if(i<32){
            return 'H';
        }else if(i<39){
            return 'I';
        }else if(i<40){
            return 'J';
        }else if(i<45){
            return 'L';
        }else if(i<48){
            return 'M';
        }else if(i<54){
            return 'N';
        }else if(i<59){
            return 'O';
        }else if(i<61){
            return 'P';
        }else if(i<62){
            return 'Q';
        }else if(i<68){
            return 'R';
        }else if(i<75){
            return 'S';
        }else if(i<81){
            return 'T';
        }else if(i<86){
            return 'U';
        }else if(i<88){
            return 'V';
        }else{
            return '?';
        }
    }
}

void refreshHand(char hand[],int positionDeToutesLesLettres[],int joueur){
    int i; //pour positionDeToutesLesLettres
    int j=0; //pour hand
    for(i=0;i<NOMBREDELETTRES;i++){
        if(positionDeToutesLesLettres[i]==-joueur){
            hand[j]=inverseMinMax(i);
            j++;
        }
    }
    hand[j]='\0'; //Pour finir la chaîne
}

void remplacerBonneLettre(int positionDeToutesLesLettres[],int mini,int joueur,int position){
    int i=mini;
    while(positionDeToutesLesLettres[i]!=-joueur){//On trouve la position de la lettre qu'on pose
        i++;
    }
    positionDeToutesLesLettres[i]=position+1;//poser sur le rail
}


#include "verifierMot.h"
void poserMotTour1(int positionDeToutesLesLettres[],char mot[],int joueur,int position){
    char hand[CHAINEMAX];
    refreshHand(hand,positionDeToutesLesLettres,joueur);
    int mini,maxi;
    int i=0; //pour mot
    while(mot[i]!='\0'){
        MinMax(&mini,&maxi,mot[i]);
        remplacerBonneLettre(positionDeToutesLesLettres,mini,joueur,position+i);
        i++;
    }

    refreshHand(hand,positionDeToutesLesLettres,joueur);

    //Ajout dans les logs du mot posé. (pas le droit de poser 2 fois le même mot)
    logAjout(mot);
}

#include "lecture_clavier.h"
#include "pioche.h"
#include "IA.h"

int poserPremiersMots( int positionDeToutesLesLettres[],int contreOrdi)//Renvoie le joueur qui joue en premier
{
    char mot1[CHAINEMAX];
    char mot2[CHAINEMAX];
    afficheMain(positionDeToutesLesLettres,1);
    afficheMain(positionDeToutesLesLettres,2);
    printf("\nJoueur 1, vous devez choisir un mot de 4 lettres à partir de votre pioche : ");
    taper(mot1);
    while (strlen(mot1)!=4 || !aLettres(mot1,positionDeToutesLesLettres,1) || !verifierMot(mot1))
    {
        printf("Le mot n'existe pas, vous ne possédez pas les bonnes lettres ou le mot ne contient pas 4 lettres : rejouez.  Si vous êtes sûr de ne pas pouvoir jouer, taper '!', sinon entrez un mot. ");
        taperPasseTour(mot1);
        if(mot1[0]=='!'){
            aidepremiertour(positionDeToutesLesLettres,mot1,1);
            printf("Vous auriez pu faire attention ! Vous pouviez poser '%s' !\n",mot1);
        }
    }

    afficheMain(positionDeToutesLesLettres,2);
    afficheMain(positionDeToutesLesLettres,1);
    if(!contreOrdi){
        printf("\nJoueur 2, vous devez choisir un mot de 4 lettres à partir de votre pioche : ");
        taper(mot2);
        while (strlen(mot2)!=4 || !aLettres(mot2,positionDeToutesLesLettres,2) || !verifierMot(mot2))
        {
            printf("Le mot n'existe pas, vous ne possédez pas les bonnes lettres ou le mot ne contient pas 4 lettres : rejouez.  Si vous êtes sûr de ne pas pouvoir jouer, taper '!', sinon entrez un mot. ");
            taperPasseTour(mot2);
            if(mot2[0]=='!'){
                aidepremiertour(positionDeToutesLesLettres,mot2,2);
                printf("Vous auriez pu faire attention ! Vous pouviez poser '%s' !\n",mot2);
            }
        }
    }else{
        printf("L'ordinateur choisit un mot... ");
        iapremiertour(positionDeToutesLesLettres,mot2);
    }
    printf("Les mots choisis sont %s et %s. ",mot1,mot2);
    if(strcmp(mot1,mot2)<=0){
        printf("Le joueur 1 débutera.");
        //poser sur le rail
        poserMotTour1(positionDeToutesLesLettres,mot1,1,0);
        poserMotTour1(positionDeToutesLesLettres,mot2,2,4);
        return 1;
    }else{
        if(contreOrdi){
            printf("L'ordinateur débutera.");
        }else{
            printf("Le joueur 2 débutera.");
        }
        poserMotTour1(positionDeToutesLesLettres,mot2,2,0);
        poserMotTour1(positionDeToutesLesLettres,mot1,1,4);
        return 2;
    }
}

char* revRail(char rail[]){
    char rev[8];
    int i;
    for(i=0;i<8;i++){
        rev[i]=rail[7-i];
    }
    return rev;
}

//Pour tests
void affiche(char rail[]){
    int i;
    for(i=0;i<8;i++){
        printf("%c",rail[i]);
    }
}

int finDeRail_egal_debutDeMot(char rail[],char mot[], int i){
    int j;
    int b=1;
    for(j=0;j++;j<i){
        b=(b && (rail[7-j]=='?' || rail[7-j]==mot[i-j]) );
    }
    return b;
}

//renvoie le nombre de lettre que l'on va pousser s'il est posable sur le rail
//(au minimum 2 pour que le mot soit posable)
int posableSurLaFinDuRail(char rail[],char mot[]){
    int n = strlen(mot);
    //printf("RAIL : ");
    //affiche(rail);
    //printf("  MOT : %s\n",mot);
    int i;//i est le nombre de lettre que l'on a en commun entre le rail et le mot. (n-i) vaut donc le nombre de lettres qui vont tomber
    for(i=2;i<=n-1;i++){
        switch(i){
    case 2:
        if(rail[6]==mot[0] && rail[7]==mot[1]){
            return i;
        }
        break;
    case 3:
        if(rail[5]==mot[0] && rail[6]==mot[1] && rail[7]==mot[2]){
            return i;
        }
        break;
    case 4:
        if(rail[4]==mot[0] && rail[5]==mot[1] && rail[6]==mot[2] && rail[7]==mot[3]){
            return i;
        }
        break;
    case 5:
        if(rail[3]==mot[0] && rail[4]==mot[1] && rail[5]==mot[2]&& rail[6]==mot[3]&& rail[7]==mot[4]){
            return i;
        }
        break;
    case 6:
        if(rail[2]==mot[0] && rail[3]==mot[1] && rail[4]==mot[2]&& rail[5]==mot[3]&& rail[6]==mot[4]&& rail[7]==mot[5]){
            return i;
        }
        break;
    case 7:
        if(rail[1]==mot[0] && rail[2]==mot[1] && rail[3]==mot[2]&& rail[4]==mot[3]&& rail[5]==mot[4]&& rail[6]==mot[5]&& rail[7]==mot[5]){
            return i;
        }
        break;
        }
    }

    //Dans ce cas, le mot n'est pas posable sur la fin du rail (on a tout essayé avant)
    return 0;
}

int maximum(int a,int b,int*changementDeMax,int methode){
    if(a>b){
        *changementDeMax=methode;
        return a;
    }else{
        return b;
    }
}

//Renvoie le nombre correspondant à la façon dont on peut poser le mot sur le rail.
int motPosableSurRail(char rail[],char mot[],int*nombreDeLettresAPousser){
    int maxi = 0;//maxi contient le nombre maxi de lettre que l'on peut pousser
    int temp;
    int methodeGagnante=0;
    if((temp=posableSurLaFinDuRail(rail,mot))>0){
        maxi=maximum(temp,maxi,&methodeGagnante,1);
        //printf("Methode : %d - Nombre de lettres à pousser : %d",methodeGagnante,*nombreDeLettresAPousser);
    }
    if((temp=posableSurLaFinDuRail(revRail(rail),mot))>0){
        maxi=maximum(temp,maxi,&methodeGagnante,2);
        //printf("Methode : %d - Nombre de lettres à pousser : %d",methodeGagnante,*nombreDeLettresAPousser);
    }
    if((temp=posableSurLaFinDuRail(rail,strrev(mot)))>0){
        maxi=maximum(temp,maxi,&methodeGagnante,3);
        //printf("Methode : %d - Nombre de lettres à pousser : %d",methodeGagnante,*nombreDeLettresAPousser);
    }
    if((temp=posableSurLaFinDuRail(revRail(rail),mot))>0){ //mot est déjà subit la fonction strrev
        maxi=maximum(temp,maxi,&methodeGagnante,4);
        //printf("Methode : %d - Nombre de lettres à pousser : %d",methodeGagnante,*nombreDeLettresAPousser);
    }

    if(nombreDeLettresAPousser!=NULL){
        *nombreDeLettresAPousser=maxi;
    }
    strrev(mot); //retour à la position normale du mot
    return methodeGagnante;
}
//Renvoie l'adversaire
int autre(int joueur){
    if(joueur==1){ return 2;}else{ return 1;}
}

int findInTab(int element,int tab[],int taille){
    int i=0;
    while(i<taille && tab[i]!=element){
        i++;
    }
    return i;
}


void revPositionDeToutesLesLettres(int positionDeToutesLesLettres[]){
    int i;
    int valeur;
    for(i=0;i<NOMBREDELETTRES;i++){
        if((valeur=positionDeToutesLesLettres[i])>0){
            positionDeToutesLesLettres[i]=9-valeur;
        }
    }
}


//ajoute sur le rail le caractère c dans la case k (k de 1 à 8) du rail, le tout posé par le joueur "joueur".
void ajouterRail(int positionDeToutesLesLettres[],int k,char c,int joueur){
    int mini,maxi;
    //printf("Appel de MinMax avec %c. ",c);
    MinMax(&mini,&maxi,c);
    int i = mini;
    while(positionDeToutesLesLettres[i]!=-joueur){
        i++;
    }
    positionDeToutesLesLettres[i]=k;
}

void translaterRail(int positionDeToutesLesLettres[],int valeurRemplacee,int valeurParLaquelleOnRemplace){
    int i=0;
    while(positionDeToutesLesLettres[i]!=valeurRemplacee){
        i++;
    }
    positionDeToutesLesLettres[i]=valeurParLaquelleOnRemplace;
}

void pousser(char rail[],char mot[],int positionDeToutesLesLettres[],int nombreDeLettresAPousser,int joueur){
    int i;//pour rail
    int j;//pour positionDeToutesLesLettres

    /*printf("Commence le poussage... RAIL : ");
    affiche(rail);
    printf("        MOT : %s\n",mot);
    */

    //afficheTab(positionDeToutesLesLettres,NOMBREDELETTRES);
    //On "donne" les lettres en trop à l'adversaire
    for(i=0;i<strlen(mot)-nombreDeLettresAPousser;i++){
        j=0;
        while(positionDeToutesLesLettres[j]!=i+1){//on cherche une lettre pour la donner à l'adversaire
            j++;
        }
        positionDeToutesLesLettres[j]=-autre(joueur);//l'autre joueur récupère les lettres
    }


    //printf("\n");
    //afficheTab(positionDeToutesLesLettres,NOMBREDELETTRES);
    int finDeTranslation = 8-(strlen(mot)-nombreDeLettresAPousser);
    //translation
    for(i=0;i<finDeTranslation;i++){
        translaterRail(positionDeToutesLesLettres,i+strlen(mot)-nombreDeLettresAPousser+1,i+1);
    }

    //printf("\n");
    //afficheTab(positionDeToutesLesLettres,NOMBREDELETTRES);
    //Copie du mot à la fin du rail
    int k=0;
    for(i=finDeTranslation;i<8;i++){
            char d=mot[k+nombreDeLettresAPousser];//on place le mot sur le rail
            ajouterRail(positionDeToutesLesLettres,i+1,d,joueur);
            k++;
    }

    //printf("\n");
    //afficheTab(positionDeToutesLesLettres,NOMBREDELETTRES);
}

//On pose le mot de sorte à pousser le plus de lettres possibles
void poserMot(int positionDeToutesLesLettres[],char mot[],int joueur, int methode,int nombreDeLettresAPousser){
    char rail[8];
    refreshRail(rail,positionDeToutesLesLettres);
    switch(methode){
    case 1:
        pousser(rail,mot,positionDeToutesLesLettres,nombreDeLettresAPousser,joueur);
        break;
    case 2:
        revPositionDeToutesLesLettres(positionDeToutesLesLettres);
        pousser(revRail(rail),mot,positionDeToutesLesLettres,nombreDeLettresAPousser,joueur);
        break;
    case 3:
        pousser(rail,strrev(mot),positionDeToutesLesLettres,nombreDeLettresAPousser,joueur);
        strrev(mot); //on remet le mot normalement
        break;
    case 4:
        revPositionDeToutesLesLettres(positionDeToutesLesLettres);
        pousser(revRail(rail),strrev(mot),positionDeToutesLesLettres,nombreDeLettresAPousser,joueur);
        strrev(mot); //on remet le mot normalement
    }

    refreshRail(rail,positionDeToutesLesLettres);
    logAjout(mot);
}
