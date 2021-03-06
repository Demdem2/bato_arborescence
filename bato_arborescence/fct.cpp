#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<ctype.h>
#include<string.h>

#include "TCase.h"
#include "TFlotte.h"



//Proc?dure Creation Cases bateaux
void createCase(int l, int c, Case* mCase) {


    mCase->ligne = l; //cr?ation ligne
    mCase->col = c; //cr?ation colonne


}

//Fct de comparaison de cases
//Return True si 2 case ligne et col sont =
enum Bool cmpCase(Case mCase, Case tCase) {


    if (mCase.col == tCase.col && mCase.ligne == tCase.ligne)
        return True;
    else
        return False;

}

//Fct de cr?ation de bateau
//Return une structure bateau
Bateau createBateau(Case nCase, int taille) {

    Bateau res;


    enum positionBateau pos;

    int nPosition = rand() % 3;

    switch (nPosition) {
    case 0:pos = positionBateau::enLigne; break;
    case 1:pos = positionBateau::enColonne; break;
    case 2:pos = positionBateau::enDiag; break;

    }


    int i;
    for (i = 0; i < MAXCASE; i++) {
        if (i < taille) {
            res.nCase[i].ligne = nCase.ligne;
            res.nCase[i].col = nCase.col;
        }
        else {

            res.nCase[i].ligne = 0;
            res.nCase[i].col = 0;
        }
        if (pos == enLigne) {

            nCase.col++;

        }
        else if (pos == enColonne) {

            nCase.ligne++;

        }
        else if (pos == enDiag) {

            nCase.ligne++;
            nCase.col++;
        }

    }
    return res;
}


//Return True si la case pass? en param?tre appartient bien ? un bateau
enum Bool controlCase(Bateau mBat, Case mCase) {


    int i;
    enum Bool valTest = False;
    for (i = 0; i < MAXCASE; i++) {

        if (cmpCase(mBat.nCase[i], mCase) == True)
            valTest = True;


    }

    return valTest;


}

//return True si la case pass? en param?tre appatient bien ? un bateau d'une flotte
enum Bool controlFlotte(Flotte f, Case mCase) {

    int i;
    enum Bool valTest = False;
    for (i = 0; i < NBBATEAU; i++) {
        if (controlCase(f.nBateau[i], mCase) == True)
            valTest = True;


    }

    return valTest;




}

//construit la flotte d'un joueur
void fPlayer(Case mCase, Flotte* f) {

    int i;
    int valRandPosLigne = 0;
    int valRandPosCol = 0;
    int valRandTailleBateau = 0;



    for (i = 0; i < NBBATEAU; i++) {

        valRandPosLigne = rand() % (MAXL - MAXCASE) + 1;
        valRandPosCol = rand() % (MAXC - MAXCASE) + 1;
        valRandTailleBateau = rand() % MAXCASE + 1;
        createCase(valRandPosLigne, valRandPosCol, &mCase);
        f->nBateau[i] = createBateau(mCase, valRandTailleBateau);


    }



}

//initFlotteJoueur
void initFlotteJoueur(Flotte* flotteJoueur1, Flotte* flotteJoueur2, Case mCase) {


    printf_s("Initialisation Bateaux Player 1\n");

    fPlayer(mCase, flotteJoueur1);

    puts("Appuyer sur enter pour continuer\n");
    getchar();
    fflush(stdin);


    printf_s("Initialisation Bateaux Player 2\n");

    fPlayer(mCase, flotteJoueur2);

    puts("Appuyer sur enter pour continuer\n");
    getchar();
    fflush(stdin);





}

//return la taille d'un bateau d'une flotte pass? en param?tre
int tailleBateau(Flotte f, int numBateau) {

    int i;
    int tailleBat = 0;

    for (i = 0; i < MAXCASE; i++) {

        if (f.nBateau[numBateau].nCase[i].col > 0 && f.nBateau[numBateau].nCase[i].ligne > 0)
            tailleBat++;

    }

    return tailleBat;

}

//Proc?dure attaque bateau

void attaqueBateau(Flotte* f, Case mCase, int* numBateau) {

    int i, j;


    for (i = 0; i < NBBATEAU; i++) {
        for (j = 0; j < MAXCASE; j++) {
            if (f->nBateau[i].nCase[j].ligne == mCase.ligne && f->nBateau[i].nCase[j].col == mCase.col) {
                f->nBateau[i].nCase[j].ligne = 0;
                f->nBateau[i].nCase[j].col = 0;
                *numBateau = i;


            }

        }
    }

    if (etatBat(*f, *numBateau))
        printf_s("Couler!!!\n");

    else
        printf_s("Toucher!!!\n");

}

//retourne etat bateau

enum etatBateau etatBat(Flotte f, int numBateau) {


    if (tailleBateau(f, numBateau) == 0) {

        return couler;

    }
    else {


        return toucher;

    }

}

//retourne etat flotte
enum etatFlotte etatFlot(Flotte f) {

    int i, j;
    enum etatFlotte st = aFlot;

    for (i = 0; i < NBBATEAU; i++) {
        for (j = 0; j < MAXCASE; j++) {

            if (f.nBateau[i].nCase[j].ligne == 0 && f.nBateau[i].nCase[j].col == 0)
                st = aSombrer;
            else {
                st = aFlot;
                return st;

            }


        }

    }

    return st;

}

//retourne  etat du joueur
enum etatJoueur etatJ(Flotte f) {


    if (etatFlot(f) == aSombrer)
        return perd;
    else
        return gagne;


}

//procedure Attaque bateau de flotteJoueur
void saisirAttaque(Case* mCase) {

    char valLigne[4], valCol[4];

    saisieJoueur(valLigne, valCol);



    while (!validSaisiJoueur(valLigne) || !validSaisiJoueur(valCol) || (atoi(valLigne) < MINL || atoi(valLigne) > MAXL)
        || (atoi(valCol) < MINC || atoi(valCol) > MAXC)) {

        effaceEcran();
        printf_s("Mauvaise saisie, recommencer vous devez saisir une val numerique comprise entre %d et %d\n", VALMIN, VALMAX);

        saisieJoueur(valLigne, valCol);


    }
    mCase->ligne = atoi(valLigne);
    mCase->col = atoi(valCol);

}

//fct valide saisie joueur
int validSaisiJoueur(char val[]) {

    int i;


    for (i = 0; i < strlen(val); i++) {

        if (!isdigit(val[i]))
            return 0;
    }

    return 1;


}

//proc?dure saisie val joueur

void saisieJoueur(char valLigne[], char valCol[]) {


    printf_s("Entrez votre tir\n");

    printf_s("Entrez ligne :\n");
    scanf_s("%d", valLigne);
    fflush(stdin);

    printf_s("Entrez Colonne :\n");
    scanf_s("%d", valCol);
    fflush(stdin);


}

//procedure efface
void effaceEcran() {

    puts("Appuyer sur enter pour continuer\n");
    getchar();
    system("cls");

}

//Set val min, max de ligne et colonne d'une flotte de bateaux
void minMax(Flotte f, int* minLigne, int* maxLigne, int* minCol, int* maxCol) {


    int i, j;

    *maxLigne = *maxCol = VALMIN - 1;
    *minLigne = *minCol = VALMAX;

    for (i = 0; i < NBBATEAU; i++) {
        for (j = 0; j < MAXCASE; j++) {

            if (f.nBateau[i].nCase[j].ligne < *minLigne && f.nBateau[i].nCase[j].ligne>0)
                *minLigne = f.nBateau[i].nCase[j].ligne;
            else if (f.nBateau[i].nCase[j].ligne > *maxLigne && f.nBateau[i].nCase[j].ligne > 0)
                *maxLigne = f.nBateau[i].nCase[j].ligne;
            if (f.nBateau[i].nCase[j].col < *minCol && f.nBateau[i].nCase[j].col>0)
                *minCol = f.nBateau[i].nCase[j].col;
            else if (f.nBateau[i].nCase[j].col > *maxCol && f.nBateau[i].nCase[j].col > 0)
                *maxCol = f.nBateau[i].nCase[j].col;



        }
    }




}

//Affichage val col et ligne bateau pour debug
void afficheDebug(Flotte f) {

    int i, j;
    for (i = 0; i < NBBATEAU; i++) {
        for (j = 0; j < MAXCASE; j++) {
            printf_s("ligne : %d\n", f.nBateau[i].nCase[j].ligne);
            printf_s("col : %d\n", f.nBateau[i].nCase[j].col);
        }
        printf_s("\n");
    }


}
