#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    ifstream file("egyed.txt");
    if(file.is_open())
    {
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
			for(int j = 0; j < szekek; ++j)
			{
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
