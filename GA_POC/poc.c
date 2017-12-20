#include <stdio.h>

#define SZEK 4
#define TULAJDONSAG 5
#define POPMERET 100

/*
 * 0 -- Shirt
 *  0 - black
 *  1 - blue
 *  2 - green
 *  3 - red
 *
 * 1 -- Name
 *  0 - Daniel
 *  1 - Joshua
 *  2 - Nicholas
 *  3 - Ryan
 *
 * ...
 */
 
struct gen{
    int allel[SZEK][TULAJDONSAG];
    int megsert;
};

int Teszt1(struct gen egyed) {
    // Joshua is in one of the ends.
    if(egyed.allel[0][1]==1 || egyed.allel[3][1]==1) return 0;
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
            egyed.allel[sz][t]=sz;
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
            printf("%d",egyed.allel[sz][t]);
        printf("|");
    }
    printf("\n");
}

struct gen Mutal(struct gen egyed){
    // valahol csereljen meg kettot a blokkon belul
    return egyed;
}

struct gen Keresztez(struct gen egyed1, struct gen egyed2){
    struct gen egyed;
    // Az egyednek az elejebe masolja bele az egyed 1 dolgait, a vegebe meg az egyed 2 dolgait
    return egyed;
}
    
int main(){

    // Kezdeti populacio inicializalasa
    struct gen populacio[POPMERET];
    int i;
    for(i=0;i<POPMERET;i++) {
        populacio[i]=kezdetiRandom();
        populacio[i].megsert = hanyatSert(populacio[i]);
    }

    struct gen temp[POPMERET+50];
    // Iteralasok
    int k;
    for(i=0;i<50;i++){
        k=0;
        // Mutaljyunk meg nehany egyedet
        //  temp[k]=Mutal(populacio[j]); temp[k].megsert=hanyarSert(temp[k]); k++;
        // CSinaljunk par crossovert
        //  temp[k]=Keresztez(populacio[j],populacio[j2]);temp[k].megsert=hanyarSert(temp[k]) k++
        // Valasszuk ki, kik maradnak
        //  populacio[l]=temp[m]
    }
    return 0;
}
