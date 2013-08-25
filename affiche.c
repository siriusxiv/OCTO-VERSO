#include "constantes.h"

#include "poserMot.h" //pour inverseMinMax

void afficheJeu ( char lettresSurRail[], int sens)
{
    int i;
        if (sens ==1)
        {
            for (i=0;i<8;i=i+1)
                {
                printf("%c", lettresSurRail[i]);
                }
        }
        else if (sens==2)
        {
                for (i=7;i>=0;i=i-1)
                    {
                    printf("%c", lettresSurRail[i]);
                    }

        }
        else
        {
            printf("Valeur de sens incorrect");

        }
}

void refreshRail(char lettresSurRail[], int positionDeToutesLesLettres[])
{
    int i;
    for(i=0;i<NOMBREDELETTRES;i++){
        if(positionDeToutesLesLettres[i]>0){
            lettresSurRail[positionDeToutesLesLettres[i]-1]=inverseMinMax(i);
        }
    }
}


void afficheRail(int positionDeToutesLesLettres[]){
    char lettresSurRail[8];
    refreshRail(lettresSurRail,positionDeToutesLesLettres);
    printf("Voici le rail : ");
    afficheJeu(lettresSurRail,1);
    printf(" ou ");
    afficheJeu(lettresSurRail,2);
    printf("\n");
}

void afficheMain (int positionDeToutesLesLettres[], int joueur)
{
    int i; //pour indicer positionDeToutesLesLettres
    int j=0; //pour indicer hand
    char hand[CHAINEMAX];

    for(i=0;i<NOMBREDELETTRES;i++){
        if(positionDeToutesLesLettres[i]==-joueur){
            hand[j]=inverseMinMax(i);
            j++;
        }
    }
    hand[j]='\0'; //Pour finir la chaîne
    printf("La main du joueur %d est %s\n",joueur,hand);

}
