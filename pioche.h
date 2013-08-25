#ifndef PIOCHE_H_INCLUDED
#define PIOCHE_H_INCLUDED

// genere des nombres aleatoires jusqu'� 90 ( voir TP fourmis)
int nalea( int maxi);
// on prend une lettre dans la pioche et on l'attribue au joueur en modifiant le tableau positionDeToutesLesLettres
char tirageDUneLettre(int positionDeToutesLesLettres[],int joueur);
//on pioche les 12 permi�res lettres pour chaque joueur
void piocheDebutDePartie(int positionDeToutesLesLettres[],int joker);

// on �change une lettre de sa main avec une lettre de la pioche
void passeSonTour(int positionDeToutesLesLettres[], int joueur);

//renvoie le bool�en (c appartient � positionDeToutesLesLettres[]) et si c'est le cas, sa position i.
int aLettre(char c, int joueur,int positionDeToutesLesLettres[],int*i);

void enleverUneLettreAuChoix( int positionDeToutesLesLettres[], int joueur);

int aLettres(char mot[],int positionDeToutesLesLettres[], int joueur);
#endif // PIOCHE_H_INCLUDED
