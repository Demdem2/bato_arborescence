#pragma once

#include "TCase.h"

typedef struct Bateau {


    Case nCase[MAXCASE];



}Bateau;

enum positionBateau {

    enLigne, enColonne, enDiag

}positionBateau;



enum etatBateau {

    toucher, couler

}etatBateau;

Bateau createBateau(Case nCase, int taille);
enum Bool controlCase(Bateau mBat, Case mCase);
