#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    ifstream file("egyed.txt");
    if(file.is_open())
    {
        int tulsz,szeksz;
        file >> szeksz;
        file >> tulsz;

		string tulajdonsagok[tulsz];
		string egyed[tulsz][szeksz];
		for(int i =0; i < tulsz; i++){
			file >> tulajdonsagok[i];
			for(int j = 0; j < szeksz; ++j)
			{
				file >> egyed[i][j];
				cout << egyed[i][j] << "\t";
			}
		cout << "\n";
		}
		for(int j = 0; j < tulsz; ++j)
		cout << tulajdonsagok[j] << "\t";
    }
}
