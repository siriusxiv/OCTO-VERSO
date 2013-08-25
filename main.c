#include <stdio.h>
#include <stdlib.h>
#include <time.h> //pour les nombres aléatoires
#include "constantes.h"
#include "reset.h"
#include "jeu.h"


int main()
{
    srand(time(NULL));
    supprDico();
    creerDico();
    int avecJoker=0,contreOrdi,recommencer=1;
    int positionDeToutesLesLettres[NOMBREDELETTRES];
    printf("Bienvenue dans le jeu OCTO-VERSO!\n");
    while (recommencer){
        printf("Voulez-vous jouer contre l'ordinateur ? ");
        choixYN(&contreOrdi);

        //printf("Souhaitez vous utiliser des jokers ? ");
        //choixYN(&avecJoker);

        initLettres(positionDeToutesLesLettres,avecJoker);
        printf("Jeu contre ");
        //if(avecJoker){ printf("avec"); }else{ printf("sans"); }
        //printf(" jokers et contre ");
        if(contreOrdi){ printf("l'ordinateur.\n"); }else{ printf("un autre joueur.\n"); }

        jeu(positionDeToutesLesLettres,contreOrdi,avecJoker);

        printf ("Voulez vous rejouer? "); // on pourrait taper n'importe quoi d'autres (entier) ca marcherait ^^
        choixYN(&recommencer);
        remove("log"); //supprime la liste des mots archivées
    }
    supprDico();
    return EXIT_SUCCESS;
}
