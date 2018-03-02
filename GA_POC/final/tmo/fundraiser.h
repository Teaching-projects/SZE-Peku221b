#ifndef FUNDRAISER_H
#define FUNDRAISER_H

#include <stdio.h>

#define SZEK 5
#define TULAJDONSAG 6

struct gen{
    int allel[TULAJDONSAG][SZEK];
    int megsert;
};

const char *TULNEVEK[TULAJDONSAG][SZEK];


//fuggveny a tesztekhez
int HanyadikSzek(struct gen egyed, int property, int value);

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
int Teszt14(struct gen egyed);
int Teszt15(struct gen egyed);
int Teszt16(struct gen egyed);
int Teszt17(struct gen egyed);
int Teszt18(struct gen egyed);
int Teszt19(struct gen egyed);
int Teszt20(struct gen egyed);
int Teszt21(struct gen egyed);

int hanyatSert(struct gen egyed);
void egyedKiir(struct gen egyed);
void joMegoldasTeszt();

#endif
