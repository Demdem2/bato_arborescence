#pragma once


#define NBBATEAU 3
#define MAXCASE 3

#define MINL 1
#define MAXL 50
#define MINC 1
#define MAXC 50
#define VALMIN 1
#define VALMAX 50

typedef struct Case {


    int ligne;
    int col;


}Case;

enum Bool {

    True, False

}Bool;


enum etatJoueur {

    gagne, perd

}etatJoueur;

//Prototypes
void createCase(int l, int c, Case* mCase);
enum Bool cmpCase(Case mCase, Case tCase);



