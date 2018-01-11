#include <stdio.h>
#include <stdlib.h>

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
 * 2 -- Movie
 *  0 - action
 *  1 - comedy
 *  2 - horror
 *  3 - thriller
 *
 * 3 -- Snack
 *  0 - chips
 *  1 - cookies
 *  2 - crackers
 *  3 - popcorn
 *
 * 4 -- Age
 *  0 - 11 years
 *  1 - 12 years
 *  2 - 13 years
 *  3 - 14 years
 */


const char *TULNEVEK[5][4] = {
        {"black","blue","green","red"},
        {"Daniel", "Joshua", "Nicholas", "Ryan"},
        {"action", "comedy", "horror", "thriller"},
        {"chips", "cookies", "crackers", "popcorn"},
        {"11", "12", "13", "14"}
    };

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
    if(egyed.allel[3][4]==0 && egyed.allel[2][0]==0) return 0;
    else if(egyed.allel[2][4]==0 && egyed.allel[1][0]==0) return 0;
    else if(egyed.allel[1][4]==0 && egyed.allel[0][0]==0) return 0;
    else return 1;

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

 //Rendezés (növekvő)
void Rendezes(struct gen populacio[]){
	struct gen X;
    int i,j;
	for (i=1;i<POPMERET;i++){
 		X=populacio[i];
  		j=i-1;
  		while((j>=0) && (populacio[j].megsert>X.megsert)){
  			populacio[j+1]=populacio[j];
  			j=j-1;
  		}
        populacio[j+1]=X;
	}
}

struct gen Mutal(struct gen egyed){
    // valahol csereljen meg kettot a blokkon belul
     /* x=szek, y=tulajdonságok*/
    int x=rand()%SZEK;
    int y=rand()%4;
    int temp=egyed.allel[x][y];
    egyed.allel[x][y]=egyed.allel[x][(y+3)%3];
    egyed.allel[x][(y+3)%3]=temp;

    return egyed;
}

struct gen Keresztez(struct gen egyed1, struct gen egyed2){
	int sz,t;
	struct gen egyed;
	for (sz=0;sz<SZEK;sz++){
		for (t=0;t<TULAJDONSAG;t++){
			if (t<TULAJDONSAG/2){
                egyed.allel[sz][t]=egyed1.allel[sz][t];
			} else {
                egyed.allel[sz][t]=egyed2.allel[sz][t];
			}
		}
    // Az egyednek az elejebe masolja bele az egyed 1 dolgait, a vegebe meg az egyed 2 dolgait
	}
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

    struct gen temp[POPMERET*2];
    // Iteralasok
    int k;
    int j;
    for(i=0;i<50;i++){
        k=0;
        // Mutaljunk meg nehany egyedet (100 db)
        //  temp[k]=Mutal(populacio[j]); temp[k].megsert=hanyarSert(temp[k]); k++;
        // Crossover 1.0
        temp[k]=Keresztez(populacio[POPMERET],populacio[0]);
        temp[k].megsert=hanyatSert(temp[k]);
        k++;
        for (j=0;j<POPMERET-1;j++){
			temp[k]=Keresztez(populacio[j],populacio[j+1]);
			temp[k].megsert=hanyatSert(temp[k]);
			k++;
		}
		
		/* Crossover 2.0
		 * for (j=0;j<POPMERET;j++){
		 * 	int x=rand()%POPMERET;
		 * 	int y=rand()%POPMERET;
		 * 	temp[k]=Keresztez(populacio[x],populacio[y]);
		 * 	k++;
		 * }
		 */
		 
        // Valasszuk ki, kik maradnak
        Rendezes(temp);
        //Nagyobb esellyel maradnak a jok, de azert rosszak is bekerulhetnek.
        for (j=0;j<POPMERET;j++){
			k=rand()%((int) (POPMERET*1.2));
			if (k<POPMERET){
			populacio[j]=temp[j];
			} else {
			populacio[j]=temp[k];
			}
		}
    }
    return 0;
}
