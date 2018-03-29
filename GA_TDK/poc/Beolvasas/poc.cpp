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

struct Solution newRandomSolution(){
    struct Solution newSolution;
    
    // TODO lefoglalni, feltolteni random modon. (megsert egyelore 0-ra.)
    
    return newSolution;
}

void deleteSolution(struct Solution solution) {
    // TODO felszabaditani a dinamikusan lefoglalt dolgokat, es mindent 0-ra, NULL-ra allitani.
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
