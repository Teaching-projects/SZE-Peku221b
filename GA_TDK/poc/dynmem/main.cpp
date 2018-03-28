#include <iostream>
#include <cstdlib>
using namespace std;

#define POPMERET 100
#define MEGTART 10


struct person {
        int property;
        int value;
};

struct gen{
    int** allel;
    int megsert;
};


struct onepersonrule {
    struct person first;
};

struct twopersonrule {
    struct person first;
    struct person second;
};

struct threepersonrule {
    struct person first;
    struct person second;
    struct person third;
};

struct positionrule {
    struct person first;
    int hely;
};

struct alltherules {
    int positionDB;
    struct onepersonrule * positionrules;
    // TODO toobbit is.
};


int hanyasSzek(struct gen egyed, struct person meh){
    int sz;
    for(sz=0;sz<SZEK;sz++)
        if (egyed.allel[meh.property][sz]==meh.value) return sz;
    return 0;
}

int testAtTheEnd(struct gen egyed, struct onepersonrule* attheend, int db){
    int i, position, megsert=0;
    for (i=0;i<db;i++){
        position=hanyasSzek(egyed, attheend[i].first);
        if (position>0 && position<SZEK-1) megsert++;
    }
    return megsert;
}

int testExactlyToTheLeft(struct gen egyed, struct twopersonrule * exactlyleft, int db){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(egyed, exactlyleft[i].first);
        position2=hanyasSzek(egyed, exactlyleft[i].second);
        if (position1!=position2-1) megsert++;
    }
    return megsert;
}

//TODO tobbire is mint az elozo kettonel

int testExactlyToTheRight(struct twopersonrule exactlyright[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(exactlyright[i].first.property, exactlyright[i].first.value);
        position2=hanyasSzek(exactlyright[i].second.property, exactlyright[i].second.value);
        if (position2!=position1-1) megsert++;
    }
    return megsert;
}

int testSomewhereToTheLeft(struct twopersonrule somewhereleft[1]){
    int i, position1, position2, megsert=0;
    for (i=0;i<1;i++){
        position1=hanyasSzek(somewhereleft[i].first.property, somewhereleft[i].first.value);
        position2=hanyasSzek(somewhereleft[i].second.property, somewhereleft[i].second.value);
        if (position1>=position2) megsert++;
    }
    return megsert;
}

int testSameperson (struct twopersonrule sameperson[2]){
    int i, position1, position2, megsert=0;
    for (i=0;i<2;i++){
        position1=hanyasSzek(sameperson[i].first.property, sameperson[i].first.value);
        position2=hanyasSzek(sameperson[i].second.property, sameperson[i].second.value);
        if (position1!=position2) megsert++;
    }
    return megsert;
}

int testPosition (struct positionrule position[2]){
    int i, megsert=0;
    for (i=0;i<2;i++){
        if (hely!=hanyasSzek(attheend[i].first.property, attheend[i].first.value)) megsert++;
    }
    return megsert;
}

int testSomewhereBetween (struct threepersonrule between[3]){
    int i, position1, position2, position3, megsert=0;
      for (i=0;i<3;i++){
        position1=hanyasSzek(between[i].first.property, between[i].first.value);
        position2=hanyasSzek(between[i].second.property, between[i].second.value);
        position3=hanyasSzek(between[i].third.property, between[i].third.value);
        if (!(position2<position1 && position1<position3)) megsert++;
      }
    return megsert;
}


int fitness(struct gen egyed, struct alltherules rules){
    megsert+=testSomewhereBetween(egyed,rules.kozott,rules.dbkozott); //tobbiere is ugynigy
    megsert+=testExactlyToTheLeft(*balpont);
    megsert+=testExactlyToTheRight(*jobbpont);
    megsert+=testPosition(*pozicio);
    megsert+=testSameperson(*ugyanaz);
    megsert+=testSomewhereToTheLeft(*balvhol);
    megsert+=testAtTheEnd(*vegen);
    return megsert;
}

struct gen kezdetiRandom(){
    struct gen egyed;
    int t,sz;
    egyed.allel = new int*[propertynum];
    for(int i=0;i<propertynum;i++)
        egyed.allel[i]=new int[szeknum];
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
    egyed.megsert=fitness();
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
	egyed.megsert=fitness();
	return egyed;
}

void egyedKiir(struct gen egyed){
    int sz,t;
    cout << ("\n");
    for(t=0;t<TULAJDONSAG;t++){
        cout<< ("|");
        for(sz=0;sz<SZEK;sz++){
            cout << (TULNEVEK[t][egyed.allel[t][sz]]);
        }
        cout << ("|\n");
    }
    cout << ("\n\n");
}

//Rendezés (növekvõ)
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
    uj.megsert=fitness();
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
    egyed.megsert=fitness();
    return egyed;
}

int main() {
    struct gen populacio[POPMERET];
    int i;
    for(i=0;i<POPMERET;i++) {
            populacio[i]=kezdetiRandom();
    }
    struct gen temp[POPMERET*4];
    int k;
    int j;

    for(i=0;populacio[0].megsert!=0;i++){
        printf("Generacio %2d: ",i);
        egyedKiir(populacio[0]);
        k=0;
        for (j=0;j<POPMERET; j++){
            temp[k]=populacio[j];
            k++;
        }
        for (j=0;j<POPMERET; j++){
            temp[k]=Mutal(populacio[j]);
            k++;
        }
        for (j=0;j<POPMERET;j++){
           int x=rand()%POPMERET;
           int y=rand()%POPMERET;
           temp[k]=Keresztez(populacio[x],populacio[y]);
           k++;
         }
        for (j=0;j<POPMERET;j++){
           int x=rand()%POPMERET;
           int y=rand()%POPMERET;
           temp[k]=Keresztez(temp[x+POPMERET],temp[y+POPMERET]);
           k++;
         }
    struct onepersonrule *vegen = new struct onepersonrule[3];
    struct onepersonrule attheend[3];
    attheend =
    {
        {NAME,JOSHUA},
        {SNACK,COOKIES},
        {MOVIE,THRILLER}
    };
    vegen = attheend;
    // meret meghatarozasa
    int meret = 1;
    struct twopersonrule *balpont = new struct twopersonrule[meret];
    struct twopersonrule  exactlyleft[1];
    for (int i=0; i<meret; ++i) {
        struct person szemely1, szemely2;
        // fajlbol beolvasni a parametereit
        int index = tulindex(beolvasott);
        szemely1.property = index;
        szemely1.value = JOSHUA;
//        balpont[i] = {szemely1, szemely2};
        balpont[i].first = szemely1;
        balpont[i].second = szemely2;
    }
    balpont = exactlyleft;
        {
        { int fajl[32];
        string line_;
        ifstream file_("fajl.txt");
        if(file_.is_open()){
            getline(file_,line_);
            file_.close();
        }
    else
    exit(EXIT_FAILURE);
        };
    };
    struct twopersonrule *jobbpont = new struct twopersonrule[1];
	struct twopersonrule exactlyright[1];
	exactlyright[0] = {MOVIE,COMEDY,SNACK,CRACKERS};
	exactlyright =
    {
        { MOVIE,COMEDY,SNACK,CRACKERS }
    };
	jobbpont = exactlyright;
    struct twopersonrule *balvhol = new struct twopersonrule[1];
	struct twopersonrule somewhereleft[1];
	somewhereleft[0] = { AGE,ELEVEN,SHIRT,BLACK };
	somewhereleft =
    {
        { AGE,ELEVEN,SHIRT,BLACK }
    };
	balvhol = somewhereleft;
    struct positionrule *pozicio = new struct positionrule[1];
	struct positionrule position[2];
	position=
    {
        { AGE,FOURTEEN,3 },
        { SHIRT,GREEN,1 }
    };
	pozicio = position;
    struct threepersonrule *kozott = new struct threepersonrule[3];
	struct threepersonrule between[3];
	between =
    {
        { AGE,THIRTEEN,SHIRT,RED,MOVIE,ACTION },
        { SNACK,POPCORN,SHIRT,RED,NAME,NICHOLAS },
        { NAME,JOSHUA,NAME,NICHOLAS,NAME,DANIEL }
    };
	kozott = between;
    struct twopersonrule *ugyanaz = new struct twopersonrule[2];
	struct twopersonrule sameperson[2];
	sameperson =
	{
        { NAME,JOSHUA,MOVIE,HORROR },
        { NAME,DANIEL,MOVIE,THRILLER }
    };
	ugyanaz = sameperson;
    fitness();
    delete[] ugyanaz,kozott,pozicio,balpont,vegen,balvhol,jobbpont;
    Rendezes(temp,4*POPMERET);
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

    cout << ("******************************\n");
    egyedKiir(populacio[0]);
    return 0;
}


