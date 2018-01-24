#include <stdio.h>
#include <stdlib.h>

#define SZEK 4
#define TULAJDONSAG 5
#define POPMERET 1000
#define MEGTART 10

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


const char *TULNEVEK[TULAJDONSAG][SZEK] = {
        {"black","blue","green","red"},
        {"Daniel", "Joshua", "Nicholas", "Ryan"},
        {"action", "comedy", "horror", "thriller"},
        {"chips", "cookies", "crackers", "popcorn"},
        {"11", "12", "13", "14"}
    };
int type(int value) {
     return value/10;
}


struct gen{
    int allel[TULAJDONSAG][SZEK];
    int megsert;
};

int Teszt1(struct gen egyed) {
    // Joshua is in one of the ends.
    if (egyed.allel[NAME][0]==JOSHUA || egyed.allel[NAME][SZEK-1]==JOSHUA) return 0;
    else return 1;

}

int Teszt2(struct gen egyed) {
    // The boy wearing the Black shirt is somewhere to the left of the youngest boy.
    int fekete, tizenegy;
    int sz;
    for(sz=1;sz<SZEK; sz++){
        if(egyed.allel[AGE][sz]==ELEVEN)  tizenegy=sz;
        if(egyed.allel[SHIRT][sz]==BLACK) fekete=sz;
    }
    if (fekete<tizenegy) return 0;
    else return 1;
}

int Teszt3(struct gen egyed) {
    //Joshua likes Horror movies.
    int sz;
    for(sz=0;sz<SZEK;sz++){
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
    sert+=Teszt5(egyed);
    sert+=Teszt6(egyed);
    sert+=Teszt7(egyed);
    sert+=Teszt8(egyed);
    sert+=Teszt9(egyed);
    sert+=Teszt10(egyed);
    sert+=Teszt11(egyed);
    sert+=Teszt12(egyed);
    sert+=Teszt13(egyed);
    // ...
    return sert;
}

struct gen kezdetiRandom(){
    struct gen egyed;
    int sz,t;
    for(t=0;t<TULAJDONSAG;t++){
        for(sz=0;sz<SZEK;sz++){
            egyed.allel[t][sz]=t*10+sz;
        }
    }
    egyed.megsert=hanyatSert(egyed); // TODO neghivni majd a kiertekelo fuggvenyt.
    /*
     * ITt valahogy random beallitgatni az ize-ben levo ertekeket
     */
     return egyed;
}

void egyedKiir(struct gen egyed){
    int sz,t;
    printf("\n");
    for(t=0;t<TULAJDONSAG;t++){
        printf("|");
        for(sz=0;sz<SZEK;sz++){
            printf("%15s",TULNEVEK[t][egyed.allel[t][sz]%10]);
        }
        printf("|\n");
    }
    printf("%2d ",egyed.megsert);
    if(Teszt1(egyed)==1) printf ("(1)");
    if(Teszt2(egyed)==1) printf ("(2)");
    if(Teszt3(egyed)==1) printf ("(3)");
    if(Teszt4(egyed)==1) printf ("(4)");
    if(Teszt5(egyed)==1) printf ("(5)");
    if(Teszt6(egyed)==1) printf ("(6)");
    if(Teszt7(egyed)==1) printf ("(7)");
    if(Teszt8(egyed)==1) printf ("(8)");
    if(Teszt9(egyed)==1) printf ("(9)");
    if(Teszt10(egyed)==1) printf ("(10)");
    if(Teszt11(egyed)==1) printf ("(11)");
    if(Teszt12(egyed)==1) printf ("(12)");
    if(Teszt13(egyed)==1) printf ("(13)");
    printf ("\n\n");
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

    struct gen temp[POPMERET*3];
    // Iteralasok
    int k;
    int j;

    //struct gen megoldas;
    //megoldas.allel[Name][0]=Joshua;
    //...
    // megoldas.allel={{Joshua,Dave, kdfjl,sdf},{black,red,...

    //megoldas.megsert=hanyatSert(megoldas);
    //egyedKiir(megoldas);


    for(i=0;populacio[0].megsert!=0;i++){
        printf("Generacio %2d: ",i);
        egyedKiir(populacio[0]);
        k=0;
        // Masoljunk at minden eddigit
        for (j=0;j<POPMERET; j++){
            temp[k]=populacio[j];
            k++;
        }


        // Mutaljunk meg nehany egyedet (100 db)
        for (j=0;j<POPMERET; j++){
            temp[k]=Mutal(populacio[j]);
            k++;
        }

        // Crossover 1.0
        temp[k]=Keresztez(populacio[POPMERET-1],populacio[0]);
        k++;
        for (j=0;j<POPMERET-1;j++){
			temp[k]=Keresztez(populacio[j],populacio[j+1]);
			k++;
		}

		// Crossover 2.0
        //   for (j=0;j<POPMERET;j++){
        //   int x=rand()%POPMERET;
        //   int y=rand()%POPMERET;
        //   temp[k]=Keresztez(populacio[x],populacio[y]);
        //   k++;
        // }


        // Valasszuk ki, kik maradnak
        Rendezes(temp);
        //Nagyobb esellyel maradnak a jok, de azert rosszak is bekerulhetnek.
        for (j=0; j<MEGTART;j++){
            populacio[j]=temp[j];
        }
        for (j=MEGTART;j<POPMERET;j++){
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
