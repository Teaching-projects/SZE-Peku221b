#include <stdio.h>
#include <stdlib.h>

#define SZEK 5
#define TULAJDONSAG 6
#define POPMERET 1000
#define MEGTART 10

#define DRESS 0
    #define BLACK 00
    #define BLUE 01
    #define PURPLE 02
    #define RED 03
    #define WHITE 04

#define NAME 1
    #define CARMEN 10
    #define DIANA 11
    #define JANE 12
    #define LIDIA 13
    #define MELISSA 14

#define DONATION 2
    #define TIZK 20
    #define HUSZK 21
    #define HARMINCK 22
    #define NEGYVENK 23
    #define OTVENK 24

#define COCKTAIL 3
    #define COSMOPOLITAN 30
    #define DAIQUIRI 31
    #define MANHATTAN 32
    #define MARGARITA 33
    #define MARTINI 34

#define NECKLACE 4
    #define EMERALD 40
    #define MOONSTONE 41
    #define PEARL 42
    #define SAPPHIRE 43
    #define TURQUOISE 44
    
#define AGE 5
    #define NEGYVEN 50
    #define NEGYVENOT 51
    #define OTVEN 52
    #define OTVENOT 53
    #define HATVAN 54

const char *TULNEVEK[TULAJDONSAG][SZEK] = {
        {"black","blue","purple","red","white"},
        {"Carmen", "Diana", "Jane", "Lidia","Melissa"},
        {"10,000 $", "20,000 $", "30,000 $", "40,000 $","50,000 $"},
        {"cosmopolitan", "daiquiri", "manhattan", "margarita","martini"},
        {"emerald", "moonstone", "pearl", "sapphire","turquoise"},
        {"40","45","50","55","60"}
    };
int type(int value) {
     return value/10;
}

struct gen{
    int allel[TULAJDONSAG][SZEK];
    int megsert;
};

int Teszt11(struct gen egyed) {
    // Jane donated $ 20,000.
    int i=0;
    while (egyed.allel[NAME][i]==JANE){
		i++;
	}
	if (egyed.allel[DONATION][i]==HUSZK)	return 0;
	else return 1;
}

int Teszt12(struct gen egyed){
	//Melissa is exactly to the right of the guest drinking Cosmopolitan.
	int sz=0;
	while (egyed.allel[COCKTAIL][sz]==COSMOPOLITAN){
		sz++;
	}
	if (sz==(SZEK-1) || egyed.allel[NAME][sz+1]!=MELISSA) return 1;
	else return 0; 
}

int Teszt13(struct gen egyed){
	//The lady wearing the Blue dress is somewhere to the left of the lady drinking Margarita.
	int kek, margarita;
    int sz;
    for(sz=1;sz<SZEK; sz++){
        if(egyed.allel[DRESS][sz]==BLUE)  kek=sz;
        if(egyed.allel[COCKTAIL][sz]==MARGARITA) margarita=sz;
    }
    if (kek<margarita) return 0;
    else return 1;
}

int Teszt14(struct gen egyed){
	//The guest that donated $ 20,000 is immediately before the guest drinking Daiquiri.
	int sz=0;
	while (egyed.allel[DONATION][sz]==HUSZK){
		sz++;
	}
	if (sz==(SZEK-1) || egyed.allel[COCKTAIL][sz+1]!=DAIQUIRI) return 1;
	else return 0; 
}

int Teszt15(struct gen egyed){
	//The 50 years old woman is exactly to the right of the woman wearing the Pearl necklace.
	int sz=0;
	while (egyed.allel[AGE][sz]==OTVEN){
		sz++;
	}
	if (sz==0) 
		{ return 1;
			} else {
				if (egyed.allel[NECKLACE][sz-1]==PEARL) return 1;
				else return 0; 
			}
}

int Teszt16(struct gen egyed){
	//Lidia is next to the woman drinking Cosmopolitan.
	int sz=0;
	while (egyed.allel[NAME][sz]==LIDIA){
		sz++;
	}
	switch (sz)
	{
	case 0:
		if (egyed.allel[COCKTAIL][1]==COSMOPOLITAN) return 0; else return 1;
	break;
	
	case SZEK:
		if (egyed.allel[COCKTAIL][SZEK-1]==COSMOPOLITAN) return 0; else return 1;
	break;
	
	default:
		if (egyed.allel[COCKTAIL][sz-1]==COSMOPOLITAN || egyed.allel[COCKTAIL][sz+1]==COSMOPOLITAN) return 0; else return 1;
	}
}


int hanyatSert(struct gen egyed){
    int sert=0;
    /*sert+=Teszt1(egyed);
    sert+=Teszt2(egyed);
    sert+=Teszt3(egyed);
    sert+=Teszt4(egyed);
    sert+=Teszt5(egyed);
    sert+=Teszt6(egyed);
    sert+=Teszt7(egyed);
    sert+=Teszt8(egyed);
    sert+=Teszt9(egyed);
    sert+=Teszt10(egyed);
    */
    sert+=Teszt11(egyed);
    sert+=Teszt12(egyed);
    sert+=Teszt13(egyed);
    sert+=Teszt14(egyed);
    sert+=Teszt15(egyed);
    sert+=Teszt16(egyed);
    /*
    sert+=Teszt17(egyed);
    sert+=Teszt18(egyed);
    sert+=Teszt19(egyed);
    sert+=Teszt20(egyed);
    sert+=Teszt21(egyed);
    */
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
    /*
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
    */
    if(Teszt11(egyed)==1) printf ("(11)");
    if(Teszt12(egyed)==1) printf ("(12)");
    if(Teszt13(egyed)==1) printf ("(13)");
    if(Teszt14(egyed)==1) printf ("(14)");
    if(Teszt15(egyed)==1) printf ("(15)");
    if(Teszt16(egyed)==1) printf ("(16)");
	/*
    if(Teszt17(egyed)==1) printf ("(17)");
    if(Teszt18(egyed)==1) printf ("(18)");
    if(Teszt19(egyed)==1) printf ("(19)");
    if(Teszt20(egyed)==1) printf ("(20)");
    if(Teszt21(egyed)==1) printf ("(21)");
    */
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
        //temp[k]=Keresztez(populacio[POPMERET-1],populacio[0]);
        //k++;
        //for (j=0;j<POPMERET-1;j++){
		//	temp[k]=Keresztez(populacio[j],populacio[j+1]);
		//	k++;
		//}

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

