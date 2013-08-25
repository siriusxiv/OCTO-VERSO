#include <stdlib.h>		// pour rand ()
#include "constantes.h"
#include "pioche.h"
#include "poserMot.h"

// Voici la m�me focntion que dans le TP fourrmis pour generer des nombres al�atoires entre 0 et max -1
int nalea( int maxi)
{
	// la fonction rand() renvoit un entier entre 0 et RAND_MAX-1
	return (rand()%maxi) ;
}

//renvoie la lettre pioch�e
char tirageDUneLettre(int positionDeToutesLesLettres[],int joueur)
{
    int i;
    i=nalea(90); // on selctionne une des cases du tableau
    while ( positionDeToutesLesLettres[i]!=0) // il faut prendre une lettre qui se trouve sur la pioche et si pas joker -3 donc ne sera pas pris
    {
        i=nalea(90);
    }
    positionDeToutesLesLettres[i]=-joueur;
    return inverseMinMax(i);
}

void piocheDebutDePartie(int positionDeToutesLesLettres[],int joker)//J'ai rajout� les Jokers qui ont �t� oubli�s la premi�re fois
{
    int taillemax;
    if(joker){
        taillemax=11;
        positionDeToutesLesLettres[NOMBREDELETTRES-2]=-1;
        positionDeToutesLesLettres[NOMBREDELETTRES-1]=-2;
    }else{
        taillemax=12;
    }
    int k = 0;
    while (k<taillemax)
    {
        tirageDUneLettre(positionDeToutesLesLettres,1);
        k=k+1;
    }
    k=0;
    while (k<taillemax)
    {
        tirageDUneLettre(positionDeToutesLesLettres,2);
        k=k+1;
    }
}


// Fonction qui remet la lettre s�lectionner dans la pioche
// La lettre � d�ja �t� choisie et les nombres correspondant � la lettre dans le tableau positionDeToutesLesLettres sont connues (Intervalles [positionDebut;postionFin])
void reposeLettre(int positionDeToutesLesLettres[],int positionDebut, int positionFin,int joueur,int* flag)
{
    int i;

    for(i=positionDebut;i<=positionFin;i++)
    {
        if((positionDeToutesLesLettres[i]==-joueur)&&(*flag==0))
        {
            positionDeToutesLesLettres[i]=0;
            *flag=1;
        }
    }
}

#include "lecture_clavier.h"
void passeSonTour(int positionDeToutesLesLettres[], int joueur)
{

    int i,flag;
    char lettre;

    flag=0;

    //flag sert � dire si lettre s�lectionn�e est bien une commande valide et une lettre qui appartient au joueur
    //Si l'algorithme ne trouve pas la lettre parmi la main du joueur (voir fonction "reposeLettre" alors flag rest � 0. Le message d'erreur s'affiche et le choix est repropos�
    while(flag==0)
    {

    printf("Quelle lettre voulez-vous �changer ? (Taper la lettre ou ? pour un joker) ");
    lettre=taperLettre();

    int mini,maxi;
    MinMax(&mini,&maxi,lettre);
    reposeLettre(positionDeToutesLesLettres,mini,maxi,joueur,&flag);
        if(flag==0){
            printf("Vous n'avez pas la lettre s�lectionn�e");
        }
    }
    char lettreTiree = tirageDUneLettre(positionDeToutesLesLettres,joueur);
    printf("Vous avez pioch� un %c et jet� un %c.\n",lettreTiree,lettre);
}

//renvoie le bool�en (c appartient � positionDeToutesLesLettres[]) et si c'est le cas, sa position i.
int aLettre(char c, int joueur,int positionDeToutesLesLettres[],int*i){
    int mini,maxi;
    MinMax(&mini,&maxi,c);
    while(positionDeToutesLesLettres[mini]!=-joueur && mini<=maxi){
        mini++;
    }
    if(mini>maxi){
        if(i!=NULL){
            *i=-1;
        }
        return 0;
    }else{
        if(i!=NULL){
            *i=mini;
        }
        return 1;
    }
}

void enleverUneLettreAuChoix( int positionDeToutesLesLettres[], int joueur)
{
    char c;
    int i;//pour positionDeToutesLesLettres
    printf("Quelle lettre voulez vous remettre dans la pioche? ");
    do{
        c=taperLettre();
    }while(!aLettre(c,joueur,positionDeToutesLesLettres,&i));
    positionDeToutesLesLettres[i]=D_PIOCHE;
}

int compteLettresDansMot(char mot[],char c){
    int i=0;//pour mot
    int compteur=0;
    while(mot[i]!='\0'){
        if(mot[i]==c){
            compteur++;
        }
        i++;
    }
    return compteur;
}

int aLettres(char mot[],int positionDeToutesLesLettres[], int joueur){
    char hand[CHAINEMAX];
    refreshHand(hand,positionDeToutesLesLettres,joueur);
    //printf("MAIN : %s",hand);
    int i=0;
    int b=1;
    int aJoker=compteLettresDansMot(hand,'?');
    //printf("Vous avez %d joker\n",aJoker);
    while(mot[i]!='\0'){
        char c = mot[i];
        b*=(compteLettresDansMot(mot,c)<=compteLettresDansMot(hand,c));
        //printf("Vous avez %d %c et le mot a %d %c.\n",compteLettresDansMot(hand,c),c,compteLettresDansMot(mot,c),c);
        if(b==0 && aJoker>=1){
            b=1;
            aJoker--;
        }
        i++;
    }
    if(b==0){
        //printf("Vous n'avez pas les lettres pour poser ce mot. ");
    }else{
        //printf("Vous avez les lettres pour poser ce mot. ");
    }
    return b;
}
