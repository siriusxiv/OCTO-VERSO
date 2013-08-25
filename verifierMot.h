//
//  FonctionOliv.h
//  TA
//
//  Created by Nguyen Quoc on 24/04/13.
//  Copyright (c) 2013 Nguyen Quoc. All rights reserved.
//

#ifndef TA_FonctionOliv_h
#define TA_FonctionOliv_h

#include "constantes.h"

int verifierMot(char* mot);

void logAjout(char mot[]);
int estDansLog(char mot[]);

int motPosable(char mot[],int positionDeToutesLesLettres[],int joueur,int*nombreDeLettresAPousser,int* methode);

void rendreMotEgal(char motTest[],char mot[]);

#endif
