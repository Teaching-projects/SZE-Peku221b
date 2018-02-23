#include <stdio.h>
#define SZEK 4
#define TULAJDONSAG 5




struct gen{
    int allel[TULAJDONSAG][SZEK];
    int megsert;
}


struct gen kezdetiRandom(){
    struct gen egyed;
    int t,sz;
    for (t=0;t<TULAJDONSAG;t++){
		for(sz=0;sz<SZEK;sz++){
			egyed.allel[t][sz]=t*10+sz;
        }
    }
    int i;
    int j;
    int tmp;
    for (t=0;t<TULAJDONSAG;t++){
		for(i=SZEK-1;i>=1;i--){
            j=rand()%(i+1);
            tmp=egyed.allel[t][i];
            egyed.allel[t][i]=egyed.allel[t][j];
            egyed.allel[t][j]=tmp;
        }
    }
    egyed.megsert=hanyatSert(egyed);
    return egyed;
}

struct gen kezdetiRandom2(){
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

void Rendezes(struct gen populacio[], int meret){
	struct gen X;
    int i,j;
	for (i=1;i<meret;i++){
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
    int hanyatmutal=rand()%5+1;
    int i;
    int tmp;
    for(i=0;i<hanyatmutal;i++){
        int cseret=rand()%TULAJDONSAG;
        int csere1sz=rand()%SZEK;
        int csere2sz=rand()%SZEK;
        while (csere1sz==csere2sz) {
            csere2sz=rand()%SZEK;
        }
        tmp=uj.allel[cseret][csere1sz];
        uj.allel[cseret][csere1sz]=uj.allel[cseret][csere2sz];
        uj.allel[cseret][csere2sz]=tmp;
    }
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
void Megold(){
        // Kezdeti populacio inicializalasa
    struct gen populacio[POPMERET];
    int i;
    for(i=0;i<POPMERET;i++) {
            populacio[i]=kezdetiRandom();
    }

    struct gen temp[POPMERET*4];
    // Iteralasok
    int k;
    int j;

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

         // Crossover 2.0 a mutalt egyedeken
        for (j=0;j<POPMERET;j++){
           int x=rand()%POPMERET;
           int y=rand()%POPMERET;
           temp[k]=Keresztez(temp[x+POPMERET],temp[y+POPMERET]);
           k++;
         }


        // Valasszuk ki, kik maradnak
        Rendezes(temp,4*POPMERET);
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

    printf("******************************\n");
    egyedKiir(populacio[0]);
}
