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
    int allel[TULAJDONSAG][SZEK];
    int megsert;
};

int Teszt1(struct gen egyed) {
    // Joshua is in one of the ends.
    if(egyed.allel[1][0]==1 || egyed.allel[1][3]==1) return 0;
    else return 1;
}

int Teszt2(struct gen egyed) {
    // The boy wearing the Black shirt is somewhere to the left of the youngest boy.
    if(egyed.allel[4][3]==0 && egyed.allel[0][2]==0) return 0;
    else if(egyed.allel[4][2]==0 && egyed.allel[0][1]==0) return 0;
    else if(egyed.allel[4][1]==0 && egyed.allel[0][0]==0) return 0;
    else return 1;

}

int Teszt3(struct gen egyed) {
    //Joshua likes Horror movies.
    int sz;
    for(sz=0;sz<=3;sz++){
        if(egyed.allel[1][sz]==1 && egyed.allel[2][sz]==2) return 0;
    }
    return 1;
}

int Teszt4(struct gen egyed) {
    //The 14 years old boy is at third position.
    if(egyed.allel[4][2]==3) return 0;
    else return 1;
}

int Teszt5(struct gen egyed) {
    //The boy wearing the Red shirt is somewhere between the 13 years old boy and the one who likes Action movies, in that order.
    if(egyed.allel[4][0]==2 && egyed.allel[0][1]==3 && egyed.allel[2][3]==0) return 0;
    else if(egyed.allel[4][0]==2 && egyed.allel[0][2]==3 && egyed.allel[2][3]==0) return 0;
    else if(egyed.allel[4][0]==2 && egyed.allel[0][1]==3 && egyed.allel[2][2]==0) return 0;
    else if(egyed.allel[4][1]==2 && egyed.allel[0][2]==3 && egyed.allel[2][3]==0) return 0;
    else return 1;
}

int Teszt6(struct gen egyed) {
    //Daniel likes Thriller movies.
    int sz;
    for(sz=0;sz<=3;sz++){
        if(egyed.allel[1][sz]==0 && egyed.allel[2][sz]==3) return 0;
    }
    return 1;
}

int Teszt7(struct gen egyed) {
    //The boy who is going to eat Cookies is in one of the ends.
    if(egyed.allel[3][0]==1 || egyed.allel[3][3]==1) return 0;
    else return 1;

}

int Teszt8 (struct gen egyed) {
    //The boy wearing the Black shirt is exactly to the left of the one who likes Thriller movies.
    if(egyed.allel[2][3]==3 && egyed.allel[0][2]==0) return 0;
    else if(egyed.allel[2][2]==3 && egyed.allel[0][1]==0) return 0;
    else if(egyed.allel[2][1]==3 && egyed.allel[0][0]==0) return 0;
    else return 1;
}

int Teszt9 (struct gen egyed) {
    //The boy who is going to eat Crackers is exactly to the right of the boy who likes Comedy movies.
    if(egyed.allel[2][0]==1 && egyed.allel[3][1]==2) return 0;
    else if(egyed.allel[2][1]==1 && egyed.allel[3][2]==2) return 0;
    else if(egyed.allel[2][2]==1 && egyed.allel[3][3]==2) return 0;
    else return 1;
}

int Teszt10 (struct gen egyed) {
    //The boy wearing the Red shirt is somewhere between the boy who is going to eat Popcorn and Nicholas, in that order.
    if(egyed.allel[3][0]==3 && egyed.allel[0][1]==3 && egyed.allel[1][3]==2) return 0;
    else if(egyed.allel[3][0]==3 && egyed.allel[0][2]==3 && egyed.allel[1][3]==2) return 0;
    else if(egyed.allel[3][0]==3 && egyed.allel[0][1]==3 && egyed.allel[1][2]==2) return 0;
    else if(egyed.allel[3][1]==3 && egyed.allel[0][2]==3 && egyed.allel[1][3]==2) return 0;
    else return 1;
}

int Teszt11 (struct gen egyed) {
    //In one of the ends is the boy who likes Thriller movies.
    if(egyed.allel[2][0]==3 || egyed.allel[2][3]==3) return 0;
    else return 1;
}


int Teszt12 (struct gen egyed) {
    //Nicholas is somewhere between Joshua and Daniel, in that order.
    if(egyed.allel[1][0]==1 && egyed.allel[1][1]==2 && egyed.allel[1][3]==0) return 0;
    else if(egyed.allel[1][0]==1 && egyed.allel[1][2]==2 && egyed.allel[1][3]==0) return 0;
    else if(egyed.allel[1][0]==1 && egyed.allel[1][1]==2 && egyed.allel[1][2]==0) return 0;
    else if(egyed.allel[1][1]==1 && egyed.allel[1][2]==2 && egyed.allel[1][3]==0) return 0;
    else return 1;
}

int Teszt13 (struct gen egyed) {
    //At first position is the boy wearing the Green shirt.
    if(egyed.allel[0][0]==2) return 0;
    else return 1;
}

int hanyatSert(struct gen egyed){
    int sert=0;
    sert+=Teszt1(egyed);
    sert+=Teszt2(egyed);
    sert+=Teszt3(egyed);
    sert+=Teszt4(egyed);
    sert+=Teszt6(egyed);
    sert+=Teszt7(egyed);
    sert+=Teszt8(egyed);
    sert+=Teszt9(egyed);
    sert+=Teszt10(egyed);
    sert+=Teszt11(egyed);
    sert+=Teszt12(egyed);
    sert+=Teszt13(egyed);
    // ...
    return 0;
}

struct gen kezdetiRandom(){
    struct gen egyed;
    int sz,t;
    for(sz=0;sz<SZEK;sz++)
        for(t=0;t<TULAJDONSAG;t++)
            egyed.allel[sz][t]=t;
    egyed.megsert=hanyatSert(egyed); // TODO neghivni majd a kiertekelo fuggvenyt.
    /*
     * ITt valahogy random beallitgatni az ize-ben levo ertekeket
     */
     return egyed;
}

void egyedKiir(struct gen egyed){
    int sz,t;
    printf("|");
    for(sz=0;sz<SZEK;sz++){
        for(t=0;t<TULAJDONSAG;t++)
            printf("%d",egyed.allel[t][sz]);
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
    struct gen uj=egyed;
    int cseret=rand()%TULAJDONSAG;
    int csere1sz=rand()%SZEK;
    int csere2sz=rand()%SZEK;
    while (csere1sz==csere2sz) {
        csere2sz=rand()%SZEK;
    }
    uj.allel[cseret][csere1sz]=egyed.allel[cseret][csere2sz];
    uj.allel[cseret][csere2sz]=egyed.allel[cseret][csere1sz];
    uj.megsert=hanyatSert(uj);
    return uj;
}

struct gen Keresztez(struct gen egyed1, struct gen egyed2){
	int sz,t;
	struct gen egyed;
	for (t=0;t<TULAJDONSAG;t++){
		if (t<TULAJDONSAG/2){
            for (sz=0;sz<SZEK;sz++){
                egyed.allel[t][sz]=egyed1.allel[t][sz];
            }
        } else {
			for (sz=0;sz<SZEK;sz++){
               egyed.allel[t][sz]=egyed2.allel[t][sz];
			}
		}
	}
    egyed.megsert=hanyatSert(egyed);
    return egyed;
}

int main(){

    // Kezdeti populacio inicializalasa
    struct gen populacio[POPMERET];
    int i;
    for(i=0;i<POPMERET;i++) {
        populacio[i]=kezdetiRandom();
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
        k++;
        for (j=0;j<POPMERET-1;j++){
			temp[k]=Keresztez(populacio[j],populacio[j+1]);
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
        populacio[0]=temp[0];
        for (j=1;j<POPMERET;j++){
			k=rand()%((int) (POPMERET*1.2));
			if (k<POPMERET){
                populacio[j]=temp[j];
			} else {
                populacio[j]=temp[POPMERET+j];
			}
		}
    }
    return 0;
}
