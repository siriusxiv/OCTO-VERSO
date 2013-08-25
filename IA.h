#ifndef IA_IA_h
#define IA_IA_h

void trouveMot(int nbLettreRail,int nbLettreJoue,char lettresSurRail[],char mot[],int positionDeToutesLesLettres[],int*stop,int sensDuMotALEndroit);

int IntA(int positionDeToutesLesLettres[],char mot[],int*methode,int*nombreDeLettresAPousser);

char* iapremiertour(int positionDeToutesLesLettres[],char mot[]);
char* aidepremiertour(int positionDeToutesLesLettres[],char mot[],int joueur);

char* detecterOcto(int positionDeToutesLesLettes[],char octo[]);

char iaJeterUneLettre(int positionDeToutesLesLettres[]);

#endif
