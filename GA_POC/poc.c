#include <stdio.h>
#include <stdlib.h>

#define SZEK 4
#define TULAJDONSAG 5
#define POPMERET 1000
#define MEGTART 100

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
        if(egyed.allel[NAME][sz]==JOSHUA && egyed.allel[MOVIE][sz]==HORROR) return 0;
    }
    return 1;
}

int Teszt4(struct gen egyed) {
    //The 14 years old boy is at third position.
    if(egyed.allel[AGE][2]==FOURTEEN) return 0;
    else return 1;
}

int Teszt5(struct gen egyed) {
    //The boy wearing the Red shirt is somewhere between the 13 years old boy and the one who likes Action movies, in that order.
    int piros=SZEK;
	int tizenharom=SZEK;
	int akcio=SZEK;
    int sz;
    for(sz=0;sz<SZEK; sz++){
        if(egyed.allel[AGE][sz]==THIRTEEN)  tizenharom=sz;
        if(egyed.allel[SHIRT][sz]==RED) piros=sz;
        if(egyed.allel[MOVIE][sz]==ACTION) akcio=sz;
    }
    if (akcio!=SZEK && piros!=SZEK && tizenharom!=SZEK) {
		if (piros>tizenharom && piros<akcio)return 0; else return 1;
    }else return 1;
}

int Teszt6(struct gen egyed) {
    //Daniel likes Thriller movies.
    int sz;
    for(sz=0;sz<=3;sz++){
        if(egyed.allel[NAME][sz]==DANIEL && egyed.allel[MOVIE][sz]==THRILLER) return 0;
    }
    return 1;
}

int Teszt7(struct gen egyed) {
    //The boy who is going to eat Cookies is in one of the ends.
    if(egyed.allel[SNACK][0]==COOKIES || egyed.allel[SNACK][3]==COOKIES) return 0;
    else return 1;

}

int Teszt8 (struct gen egyed) {
    //The boy wearing the Black shirt is exactly to the left of the one who likes Thriller movies.
    if(egyed.allel[MOVIE][3]==THRILLER && egyed.allel[SHIRT][2]==BLACK) return 0;
    else if(egyed.allel[MOVIE][2]==THRILLER && egyed.allel[SHIRT][1]==BLACK) return 0;
    else if(egyed.allel[MOVIE][1]==THRILLER && egyed.allel[SHIRT][0]==BLACK) return 0;
    else return 1;
}

int Teszt9 (struct gen egyed) {
    //The boy who is going to eat Crackers is exactly to the right of the boy who likes Comedy movies.
    if(egyed.allel[MOVIE][0]==COMEDY && egyed.allel[SNACK][1]==CRACKERS) return 0;
    else if(egyed.allel[MOVIE][1]==COMEDY && egyed.allel[SNACK][2]==CRACKERS) return 0;
    else if(egyed.allel[MOVIE][2]==COMEDY && egyed.allel[SNACK][3]==CRACKERS) return 0;
    else return 1;
}

int Teszt10 (struct gen egyed) {
    //The boy wearing the Red shirt is somewhere between the boy who is going to eat Popcorn and Nicholas, in that order.
    int piros=SZEK;
	int popc=SZEK;
	int nic=SZEK;
    int sz;
    for(sz=0;sz<SZEK; sz++){
        if(egyed.allel[SNACK][sz]==POPCORN)  popc=sz;
        if(egyed.allel[SHIRT][sz]==RED) piros=sz;
        if(egyed.allel[NAME][sz]==NICHOLAS) nic=sz;
    }
    if (popc!=SZEK && piros!=SZEK && nic!=SZEK) {
		if (piros>popc && piros<nic)return 0; else return 1;
    }else return 1;
}

int Teszt11 (struct gen egyed) {
    //In one of the ends is the boy who likes Thriller movies.
    if(egyed.allel[MOVIE][0]==THRILLER || egyed.allel[MOVIE][3]==THRILLER) return 0;
    else return 1;
}


int Teszt12 (struct gen egyed) {
    //Nicholas is somewhere between Joshua and Daniel, in that order.
	/*
    *if(egyed.allel[NAME][0]==JOSHUA && egyed.allel[NAME][1]==NICHOLAS && egyed.allel[NAME][3]==DANIEL) return 0;
    *else if(egyed.allel[NAME][0]==JOSHUA && egyed.allel[NAME][2]==NICHOLAS && egyed.allel[NAME][3]==DANIEL) return 0;
    *else if(egyed.allel[NAME][0]==JOSHUA && egyed.allel[NAME][1]==NICHOLAS && egyed.allel[NAME][2]==DANIEL) return 0;
    *else if(egyed.allel[NAME][1]==JOSHUA && egyed.allel[NAME][2]==NICHOLAS && egyed.allel[NAME][3]==DANIEL) return 0;
    *else return 1;
    */
    int jos=SZEK;
	int nic=SZEK;
	int dan=SZEK;
    int sz;
    for(sz=0;sz<SZEK; sz++){
        if(egyed.allel[NAME][sz]==JOSHUA)  jos=sz;
        if(egyed.allel[NAME][sz]==NICHOLAS) nic=sz;
        if(egyed.allel[NAME][sz]==DANIEL) dan=sz;
    }
    if (jos!=SZEK && nic!=SZEK && dan!=SZEK) {
		if (nic>jos && nic<dan)return 0; else return 1;
    }else return 1;
}

int Teszt13 (struct gen egyed) {
    //At first position is the boy wearing the Green shirt.
    if(egyed.allel[SHIRT][0]==GREEN) return 0;
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
    int sz,t,db,index;
    int van[SZEK];
    for (t=0;t<TULAJDONSAG;t++){
		for(sz=0;sz<SZEK;sz++){
			van[sz]=0;
		}
		for(sz=0;sz<SZEK;sz++){
			db=rand()%(SZEK-sz);
            index=0;
            while(van[index]==1) index++;
			for(;db!=0;index++){
				if (van[index]==0){
					db--; 
				}
			}
			van[index]=1;
			egyed.allel[t][sz]=t*10+index;
            
		}
	}
	egyed.megsert=hanyatSert(egyed);
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
    int hol=rand()%TULAJDONSAG;
	for (t=0;t<TULAJDONSAG;t++){
		if (t<hol){
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

int bennevanemar(struct gen egyedek[], int meddig, struct gen uj){
    return 0;
}

int main(){

    // Kezdeti populacio inicializalasa
    struct gen populacio[POPMERET];
    struct gen tmp;
    int i;
    for(i=0;i<POPMERET;i++) {
        do{
            tmp=kezdetiRandom();
        } while(bennevanemar(populacio,i,tmp);
        populacio[i]=tmp;
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
        /*temp[k]=Keresztez(populacio[POPMERET-1],populacio[0]);
        k++;
        for (j=0;j<POPMERET-1;j++){
			temp[k]=Keresztez(populacio[j],populacio[j+1]);
			k++;
		}*/

		// Crossover 2.0
        for (j=0;j<POPMERET;j++){
           int x=rand()%POPMERET;
           int y=rand()%POPMERET;
           temp[k]=Keresztez(populacio[x],populacio[y]);
           k++;
         }


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
