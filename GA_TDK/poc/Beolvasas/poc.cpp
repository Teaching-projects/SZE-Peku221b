#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <new>

using namespace std;

struct Person {
    string property;
    string value;
};

struct OnePersonRule {
    struct Person first;
};

struct ZebraPuzzle {
    int chairNum;
    int propertyNum;
    string* properties;
    string** propertyvalues;
    int attheendRulesCount;
    struct OnePersonRule * attheendRules;
};

struct ZebraPuzzle Example;

bool readExample() {
    bool ok=true;
    ifstream file("egyed.txt");
    if(file.is_open()) {
        try{
            // Read example size
            file >> Example.chairNum;
            file >> Example.propertyNum;

            // Read properties and propertyvalues
            Example.properties = new string [Example.propertyNum];
            Example.propertyvalues = new string * [Example.propertyNum];
            for(int i = 0;i < Example.propertyNum;++i) {
                file >> Example.properties[i];
                Example.propertyvalues[i] = new string [Example.chairNum];
                for(int j = 0;j < Example.chairNum;++j) {
                    file >> Example.propertyvalues[i][j];
                }
            }

            // Read attheendconstraints
            file >> Example.attheendRulesCount;
            Example.attheendRules = new struct OnePersonRule [Example.attheendRulesCount];
            for (int r=0;r<Example.attheendRulesCount;r++) {
                file >> Example.attheendRules[r].first.property;
                file >> Example.attheendRules[r].first.value;
            }
        } catch (bad_alloc & ba) {
            cout << "Keves memoria " << ba.what();
            ok=false;
        }
    } else {
        ok=false;
        exit(EXIT_FAILURE);
    }
    return ok;
}

void printExample() {
    cout<<"Example:\n";
    for (int c=0;c<Example.chairNum; c++){
        cout << "\t" << c+1;
    }
    cout << "\n";
    for(int p=0;p<Example.propertyNum;p++){
        cout<<Example.properties[p];
        for (int c=0;c<Example.chairNum; c++){
            cout << "\t" << Example.propertyvalues[p][c];
        }
        cout<<"\n";
    }
    cout<<"The following people sit at one of the ends:\n";
    for(int r=0;r<Example.attheendRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.attheendRules[r].first.value
            <<" for "
            <<Example.attheendRules[r].first.property
            <<"\n";
}

void deleteExample() {
    // Torolni es felszabaditani a Example-t.
}

struct Solution {
    int violation_count;
    string** chromosome;
};

void Mutate(struct Solution * solution, int mutateCount = 50) {
    int i;
    string tmp;
    int switchProperty, switchChair1, switchChair2;
    for(i=0;i<mutateCount;i++){
        switchProperty=rand()%Example.propertyNum;
        switchChair1=rand()%Example.chairNum;
        do {
            switchChair2=rand()%Example.chairNum;
        } while (switchChair1==switchChair2);
        
        tmp=solution->chromosome[switchProperty][switchChair1];
        solution->chromosome[switchProperty][switchChair1]=solution->chromosome[switchProperty][switchChair2];
        solution->chromosome[switchProperty][switchChair2]=tmp;
    }
}


struct Solution * newRandomSolution(){
	struct Solution * newSolution = new struct Solution;
    newSolution->chromosome=new string * [Example.propertyNum];
    for(int i = 0;i < Example.propertyNum;++i) {
        newSolution->chromosome[i] = new string [Example.chairNum];
        for(int j = 0;j < Example.chairNum;++j) {
            newSolution->chromosome[i][j]=Example.propertyvalues[i][j];
        }
    }

    int switchCount=rand()%50+1;

    Mutate(newSolution,switchCount);

    newSolution->violation_count=0; // todo majd lecserelni a hanyatsert fv hivasra
    
    return newSolution;
}

void printSolution(struct Solution * solution) {
    cout<<"Solution:\n";
    for (int c=0;c<Example.chairNum; c++){
        cout << "\t" << c+1;
    }
    cout << "\n";
    for(int p=0;p<Example.propertyNum;p++){
        cout<<Example.properties[p];
        for (int c=0;c<Example.chairNum; c++){
            cout << "\t" << solution->chromosome[p][c];
        }
        cout<<"\n";
    }
}

void deleteSolution(struct Solution * solution) {
    for(int i = 0;i < Example.propertyNum;++i){
         delete[] solution->chromosome[i];
    }
    delete[] solution->chromosome;
    delete solution;
}

int main() {

    if(readExample()) {
        printExample();

        Solution * testSolution = newRandomSolution();
        printSolution(testSolution);
        deleteSolution(testSolution);
        
        
        deleteExample();
    }
}
