#ifndef MOVIE_H
#define MOVIE_H

#define SZEK 4
#define TULAJDONSAG 5
#define SHIRT 0
    #define BLACK 00
    #define BLUE 01
    #define GREEN 02
    #define RED 03

#define NAME 1
    #define DANIEL 10
    #define JOSHUA 11
    #define NICHOLAS 12
    #define RYAN 13

#define MOVIE 2
    #define ACTION 20
    #define COMEDY 21
    #define HORROR 22
    #define THRILLER 23

#define SNACK 3
    #define CHIPS 30
    #define COOKIES 31
    #define CRACKERS 32
    #define POPCORN 33

#define AGE 4
    #define ELEVEN 40
    #define TWELVE 41
    #define THIRTEEN 42
    #define FOURTEEN 43

struct gen{
    int allel[TULAJDONSAG][SZEK];
    int megsert;
};

const char *TULNEVEK[TULAJDONSAG][SZEK];


int Teszt1(struct gen egyed);
int Teszt2(struct gen egyed);
int Teszt3(struct gen egyed);
int Teszt4(struct gen egyed);
int Teszt5(struct gen egyed);
int Teszt6(struct gen egyed);
int Teszt7(struct gen egyed);
int Teszt8(struct gen egyed);
int Teszt9(struct gen egyed);
int Teszt10(struct gen egyed);
int Teszt11(struct gen egyed);
int Teszt12(struct gen egyed);
int Teszt13(struct gen egyed);

int hanyatSert(struct gen egyed);
void egyedKiir(struct gen egyed);

void joMegoldasTeszt();

#endif
