#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

struct ZebraPuzzle {
    int chairNum;
    int propertyNum;
    string* properties;
    string** propertyvalues;
    
};

struct ZebraPuzzle Example;

bool readExample() {
    // TODO beolvasni a feladatot a Pelda-ba. true, ha minden oke volt, false, ha nem.
}

void printExample() {
    // TODO Valami egyszeru modon kiiratni a Pelda-t
}

void deleteExample() {
    // Torolni es felszabaditani a Pelda-t. 
}

struct Solution {
    int violation_count;
    string** chromosome;
};

struct Solution newRandomSolution(struct ZebraPuzzle Example,int chairN,int propertyN){
    // TODO lefoglalni, feltolteni random modon. (megsert egyelore 0-ra.)
	struct Solution newSolution = struct ZebraPuzzle Example.propertyvalues;
	
    int switchCount=rand()%50+1;
    int i;
    string tmp;
    for(i=0;i<switchCount;i++){
        int switchProperty=rand()%propertyN;
        int switchChair1=rand()%chairN;
        int switchChair2=rand()%chairN;
        while (switchChair1==switchChair2) {
            switchChair2=rand()%chairN;
        }
        tmp=newSolution.chromosome[switchProperty][switchChair1];
        newSolution.chromosome[switchProperty][switchChair1]=newSolution.chromosome[switchProperty][switchChair2];
        newSolution.chromosome[switchProperty][switchChair2]=tmp;
    }	
	newSolution.violation_count=0;
    return newSolution;
}
/*
 //Kezdeti Random, amikor már a newSolution.chromosome int lesz string helyett.
struct Solution newRandomSolution(int chairN,int propertyN){
    struct Solution newSolution;
    int t,sz;
    for (t=0;t<propertyN;t++){
		for(sz=0;sz<chairN;sz++){
			newSolution.chromosome[t][sz]=t*10+sz;
        }
    }
    int i;
    int j;
    int tmp;
    for (t=0;t<propertyN;t++){
		for(i=chairN-1;i>=1;i--){
            j=rand()%(i+1);
            tmp=newSolution.chromosome[t][i];
            newSolution.chromosome[t][i]=newSolution.chromosome[t][j];
            newSolution.chromosome[t][j]=tmp;
        }
    }
    newSolution.violation_count=0;
    return newSolution;
}
*/

void deleteSolution(struct Solution solution,int propertyNum) {
    // TODO felszabaditani a dinamikusan lefoglalt dolgokat, es mindent 0-ra, NULL-ra allitani.
        for(int i = 0;i < propertyNum;++i){
             delete[] solution.chromosome[i]; 
        }
        delete[] solution.violation_count;
        delete[] solution;
}

int main() {
    ifstream file("egyed.txt");
    if(file.is_open()) {
        
        //Beolvasás
        int tulsz,szekek;
        file >> szekek;
        file >> tulsz;
        string *tulajdonsagok = new string [tulsz];
        string **egyed = new string * [tulsz];
        for(int i = 0;i < tulsz;++i) {
            file >> tulajdonsagok[i];
            egyed[i] = new string [szekek];
            for(int j = 0;j < szekek;++j) {
                file >> egyed[i][j];
            }
        }
        
        //Kiiratás
        for(int i =0; i < tulsz; i++){
            for(int j = 0; j < szekek; ++j){
                cout << egyed[i][j] << "\t";
            }
            cout << "\n";
        }
        for(int j = 0; j < tulsz; ++j)
            cout << tulajdonsagok[j] << "\t";
        
        //Felszabadítás
        delete[] tulajdonsagok;
        for(int i = 0;i < tulsz;++i){
             delete[] egyed[i]; 
        }
        delete[] egyed;
    }

}
