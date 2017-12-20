#include <stdio.h>

#define EMBER 4
#define TULAJDONSAG 5

struct gen{
    int allel[TULAJDONSAG][EMBER];
    int megsert;
};

int hanyatSert(struct gen egyed){
    return 0;
}

struct gen kezdetiRandom(){
    struct gen egyed;
    int e,t;
    for(t=0;t<TULAJDONSAG;t++)
        for(e=0;e<EMBER;e++)
            egyed.allel[t][e]=e;
    egyed.megsert=hanyatSert(egyed); // TODO neghivni majd a kiertekelo fuggvenyt.
    /*
     * ITt valahogy random beallitgatni az ize-ben levo ertekeket
     */
     return egyed;
}

void egyedKiir(struct gen egyed){
    int e,t;
    printf("|");
    for(t=0;t<TULAJDONSAG;t++){
        for(e=0;e<EMBER;e++)
            printf("%d",egyed.allel[t][e]);
        printf("|");
    }
    printf("\n");
}

    
int main(){
    struct gen elso=kezdetiRandom();
    egyedKiir(elso);
    return 0;
}
