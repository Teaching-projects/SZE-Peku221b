#include <stdio.h>

#define SZEK 4
#define TULAJDONSAG 5

/*
 * 0 - black
 * 1 - blue
 * 2 - green
 * 3 - red
 *
 * 0 - Daniel
 * 1 - Joshua
 * 2 - Nicholas
 * 3 - Ryan
 *
 * ...
 */
 
struct gen{
    int allel[TULAJDONSAG][SZEK];
    int megsert;
};

int Teszt1(struct gen egyed) {
    // Joshua is in one of the ends.
    if(egyed.allel[1][0]==1 || egyed.allel[1][3]==1) return 0;
    else return 1;
}

int Teszt2(struct gen egyed) {
    // The boy wearning the Black shirt is somewhere to the left of the youngest boy.
    return 0;
}

int hanyatSert(struct gen egyed){
    int sert=0;
    sert+=Teszt1(egyed);
    sert+=Teszt2(egyed);
    // ...
    return 0;
}

struct gen kezdetiRandom(){
    struct gen egyed;
    int sz,t;
    for(t=0;t<TULAJDONSAG;t++)
        for(sz=0;sz<SZEK;sz++)
            egyed.allel[t][sz]=sz;
    egyed.megsert=hanyatSert(egyed); // TODO neghivni majd a kiertekelo fuggvenyt.
    /*
     * ITt valahogy random beallitgatni az ize-ben levo ertekeket
     */
     return egyed;
}

void egyedKiir(struct gen egyed){
    int sz,t;
    printf("|");
    for(t=0;t<TULAJDONSAG;t++){
        for(sz=0;sz<SZEK;sz++)
            printf("%d",egyed.allel[t][sz]);
        printf("|");
    }
    printf("\n");
}

    
int main(){
    struct gen elso=kezdetiRandom();
    egyedKiir(elso);
    return 0;
}
