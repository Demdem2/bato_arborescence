#pragma once

#include "TBateau.h"

typedef struct Flotte {

    Bateau nBateau[NBBATEAU];


}Flotte;

enum etatFlotte {


    aFlot, aSombrer

}etatFlotte;



enum Bool controlFlotte(Flotte f, Case mCase);
void fPlayer(Case mCase, Flotte* f);
void afficheDebug(Flotte f);
int tailleBateau(Flotte f, int numBateau);
void attaqueBateau(Flotte* f, Case mCase, int* numBateau);
enum etatBateau etatBat(Flotte f, int numBateau);
enum etatFlotte etatFlot(Flotte f);
void saisirAttaque(Case* mCase);
enum etatJoueur etatJ(Flotte f);
int validSaisiJoueur(char val[]);
void effaceEcran();
void saisieJoueur(char valLigne[], char valCol[]);
void initFlotteJoueur(Flotte* flotteJoueur1, Flotte* flotteJoueur2, Case mCase);
void minMax(Flotte f, int* minLigne, int* maxLigne, int* minCol, int* maxCol);



