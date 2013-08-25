#ifndef DEF_POSERMOT
#define DEF_POSERMOT

void poserMotTour1(int positionDeToutesLesLettres[],char mot[],int joueur,int position);

void poserMot(int positionDeToutesLesLettres[],char mot[],int joueur, int methode,int nombreDeLettresAPousser);

void MinMax(int*mini,int*maxi,char lettre);

char inverseMinMax(int i);

int poserPremiersMots( int positionDeToutesLesLettres[],int contreOrdi);

int motPosableSurRail(char rail[],char mot[],int*nombreDeLettresAPousser);

int autre(int joueur);

#endif // DEF_POSERMOT
