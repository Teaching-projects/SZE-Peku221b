#include <stdio.h>
#include "fundraiser.h"

#define SZEK 5
#define TULAJDONSAG 6

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


//fuggveny a tesztekhez
int HanyadikSzek(struct gen egyed,int property, int value){
    int sz;
    for(sz=0;sz<SZEK;sz++)
        if (egyed.allel[property][sz]==value) return sz;
    return 0;
}

int Teszt1(struct gen egyed){
    //The woman who donated $ 30,000 is immediately before the youngest woman.
    int egyed1=HanyadikSzek(egyed,DONATION,HARMINCK);
    int egyed2=HanyadikSzek(egyed,AGE,NEGYVEN);

	return !(egyed1==egyed2-1);
}

int Teszt2(struct gen egyed){
   //Diana is exactly to the left of the 50 years old woman.
   int egyed1=HanyadikSzek(egyed,NAME,DIANA);
   int egyed2=HanyadikSzek(egyed,AGE,OTVEN);

   return !(egyed1==egyed2-1);

}

int Teszt3(struct gen egyed){
   //The donator wearing the Emerald necklace is exactly to the left of the donator wearing the Purple dress.
   int egyed1=HanyadikSzek(egyed,NECKLACE,EMERALD);
   int egyed2=HanyadikSzek(egyed,DRESS,PURPLE);

   return !(egyed1==egyed2-1);

}

int Teszt4(struct gen egyed){
   //The lady wearing the Pearl necklace donated the smallest amount.
   int egyed1=HanyadikSzek(egyed,NECKLACE,PEARL);
   int egyed2=HanyadikSzek(egyed,DONATION,TIZK);

   return !(egyed1==egyed2);
}

int Teszt5(struct gen egyed){
   //The guest drinking Martini is next to the guest who donated $ 10,000.
   int egyed1=HanyadikSzek(egyed,COCKTAIL,MARTINI);
   int egyed2=HanyadikSzek(egyed,DONATION,TIZK);

   return !(egyed1==egyed2-1 || egyed1-1==egyed2);

}


int Teszt6(struct gen egyed){
    //The woman wearing the Turquoise necklace donated $ 30,000.
    int egyed1=HanyadikSzek(egyed,NECKLACE,TURQUOISE);
    int egyed2=HanyadikSzek(egyed,DONATION,HARMINCK);

    return !(egyed1==egyed2);
}

int Teszt7(struct gen egyed){
    //The oldest woman is exactly to the right of the lady drinking Cosmopolitan
    int egyed1=HanyadikSzek(egyed,AGE,HATVAN);
    int egyed2=HanyadikSzek(egyed,COCKTAIL,COSMOPOLITAN);

    return !(egyed1==egyed2+1);
}

int Teszt8 (struct gen egyed) {
    //The donator wearing the White dress is next to the woman who gave the biggest donation.
    int egyed1=HanyadikSzek(egyed,DRESS,WHITE);
    int egyed2=HanyadikSzek(egyed,DONATION,OTVENK);

    return !(egyed1==egyed2-1 || egyed1-1==egyed2);

}

int Teszt9 (struct gen egyed) {
    //The woman wearing the Red dress is somewhere between the woman that donated $ 20,000 and the woman that gave $ 40,000, in that order.
    int egyed1=HanyadikSzek(egyed,DRESS,RED);
    int egyed2=HanyadikSzek(egyed,DONATION,HUSZK);
    int egyed3=HanyadikSzek(egyed,DONATION,NEGYVENK);

    return !(egyed2<egyed1 && egyed1<egyed3);
}

int Teszt10(struct gen egyed){
    //Lidia is next to the guest wearing the Black dress.
    int egyed1=HanyadikSzek(egyed,NAME,LIDIA);
    int egyed2=HanyadikSzek(egyed,DRESS,BLACK);

    return !(egyed1==egyed2-1 || egyed1-1==egyed2);

}

int Teszt11(struct gen egyed) {
    // Jane donated $ 20,000.
    int egyed1=HanyadikSzek(egyed,NAME,JANE);
    int egyed2=HanyadikSzek(egyed,DONATION,HUSZK);

    return !(egyed1==egyed2);
}

int Teszt12(struct gen egyed){
	//Melissa is exactly to the right of the guest drinking Cosmopolitan.
	int egyed1=HanyadikSzek(egyed,COCKTAIL,COSMOPOLITAN);
    int egyed2=HanyadikSzek(egyed,NAME,MELISSA);

	return !(egyed1==egyed2-1);
}

int Teszt13(struct gen egyed){
	//The lady wearing the Blue dress is somewhere to the left of the lady drinking Margarita.
	int egyed1=HanyadikSzek(egyed,DRESS,BLUE);
    int egyed2=HanyadikSzek(egyed,COCKTAIL,MARGARITA);

	return !(egyed1<egyed2);
}

int Teszt14(struct gen egyed){
	//The guest that donated $ 20,000 is immediately before the guest drinking Daiquiri.
	int egyed1=HanyadikSzek(egyed,DONATION,HUSZK);
	int egyed2=HanyadikSzek(egyed,COCKTAIL,DAIQUIRI);

	return !(egyed1==egyed2-1);

}

int Teszt15(struct gen egyed){
	//The 50 years old woman is exactly to the right of the woman wearing the Pearl necklace.
	int egyed1=HanyadikSzek(egyed,AGE,OTVEN);
    int egyed2=HanyadikSzek(egyed,NECKLACE,PEARL);

	return !(egyed1==egyed2+1);

}

int Teszt16(struct gen egyed){
	//Lidia is next to the woman drinking Cosmopolitan.
	int egyed1=HanyadikSzek(egyed,NAME,LIDIA);
    int egyed2=HanyadikSzek(egyed,COCKTAIL,COSMOPOLITAN);

	return !(egyed1==egyed2-1 || egyed1-1==egyed2);
}

int Teszt17(struct gen egyed){
    //The lady wearing the Black dress is somewhere to the left of the lady who donated $ 40,000.
    int egyed1=HanyadikSzek(egyed,DRESS,BLACK);
    int egyed2=HanyadikSzek(egyed,DONATION,NEGYVENK);

	return !(egyed1<egyed2);
}

int Teszt18 (struct gen egyed){
    //The 55 years old woman is wearing the Sapphire necklace.
    int egyed1=HanyadikSzek(egyed,AGE,OTVENOT);
    int egyed2=HanyadikSzek(egyed,NECKLACE,SAPPHIRE);

	return !(egyed1==egyed2);
}

int Teszt19 (struct gen egyed){
    //The 60 years old woman is somewhere to the right of the woman wearing the Black dress.
    int egyed1=HanyadikSzek(egyed,AGE,HATVAN);
    int egyed2=HanyadikSzek(egyed,DRESS,BLACK);

	return !(egyed1>egyed2);
}

int Teszt20(struct gen egyed){
    //The lady drinking Manhattan is exactly to the right of the lady wearing the Red dress.
    int egyed1=HanyadikSzek(egyed,COCKTAIL,MANHATTAN);
    int egyed2=HanyadikSzek(egyed,DRESS,RED);

	return !(egyed1==egyed2+1);
}

int Teszt21(struct gen egyed){
    //The guest wearing the White dress is somewhere to the left of the guest wearing the Black dress.
    int egyed1=HanyadikSzek(egyed,DRESS,WHITE);
    int egyed2=HanyadikSzek(egyed,DRESS,BLACK);

	return !(egyed1<egyed2);
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
    sert+=Teszt14(egyed);
    sert+=Teszt15(egyed);
    sert+=Teszt16(egyed);
    sert+=Teszt17(egyed);
    sert+=Teszt18(egyed);
    sert+=Teszt19(egyed);
    sert+=Teszt20(egyed);
    sert+=Teszt21(egyed);
    return sert;

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
    if(Teszt14(egyed)==1) printf ("(14)");
    if(Teszt15(egyed)==1) printf ("(15)");
    if(Teszt16(egyed)==1) printf ("(16)");
    if(Teszt17(egyed)==1) printf ("(17)");
    if(Teszt18(egyed)==1) printf ("(18)");
    if(Teszt19(egyed)==1) printf ("(19)");
    if(Teszt20(egyed)==1) printf ("(20)");
    if(Teszt21(egyed)==1) printf ("(21)");
    printf ("\n\n");
}
void joMegoldasTeszt(){
    //Jo megoldas tesztelese:
    struct gen jomegoldas={
        .allel = {
            {BLUE, RED, WHITE, BLACK, PURPLE},
            {JANE, DIANA, LIDIA, CARMEN, MELISSA},
            {HUSZK, TIZK, HARMINCK, OTVENK, NEGYVENK},
            {MARTINI, DAIQUIRI, MANHATTAN, COSMOPOLITAN, MARGARITA},
            {SAPPHIRE, PEARL, TURQUOISE, EMERALD, MOONSTONE},
            {OTVENOT, NEGYVENOT, OTVEN, NEGYVEN, HATVAN}
        }
    };
    jomegoldas.megsert=hanyatSert(jomegoldas);
    egyedKiir(jomegoldas);
}
