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

struct TwoPersonRule {
    struct Person first;
    struct Person second;
};

struct ThreePersonRule {
    struct Person first;
    struct Person second;
    struct Person third;
};

struct PositionRule {
    struct Person first;
    int chair;
};

struct ZebraPuzzle {
    int chairNum;
    int propertyNum;
    string* properties;
    string** propertyvalues;
    int attheendRulesCount;
    struct OnePersonRule * attheendRules;
    int exactlyleftRulesCount;
    struct TwoPersonRule * exactlyleftRules;
    int exactlyrightRulesCount;
    struct TwoPersonRule * exactlyrightRules;
    int somewhereleftRulesCount;
    struct TwoPersonRule * somewhereleftRules;
    int somewhererightRulesCount;
    struct TwoPersonRule * somewhererightRules;
    int positionRulesCount;
    struct PositionRule * positionRules;
    int betweenRulesCount;
    struct ThreePersonRule * betweenRules;
    int likesRulesCount;
    struct TwoPersonRule * likesRules;

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
            // Read exactlyleftconstraints
            file >> Example.exactlyleftRulesCount;
            Example.exactlyleftRules = new struct TwoPersonRule [Example.exactlyleftRulesCount];
            for (int r=0;r<Example.exactlyleftRulesCount;r++) {
                file >> Example.exactlyleftRules[r].first.property;
                file >> Example.exactlyleftRules[r].first.value;
                file >> Example.exactlyleftRules[r].second.property;
                file >> Example.exactlyleftRules[r].second.value;  
            }  
            // Read exactlyrightconstraints
            file >> Example.exactlyrightRulesCount;
            Example.exactlyrightRules = new struct TwoPersonRule [Example.exactlyrightRulesCount];
            for (int r=0;r<Example.exactlyrightRulesCount;r++) {
                file >> Example.exactlyrightRules[r].first.property;
                file >> Example.exactlyrightRules[r].first.value;
                file >> Example.exactlyrightRules[r].second.property;
                file >> Example.exactlyrightRules[r].second.value;              
            }
            // Read somewhereleftconstraints
            file >> Example.somewhereleftRulesCount;
            Example.somewhereleftRules = new struct TwoPersonRule [Example.somewhereleftRulesCount];
            for (int r=0;r<Example.somewhereleftRulesCount;r++) {
                file >> Example.somewhereleftRules[r].first.property;
                file >> Example.somewhereleftRules[r].first.value;
                file >> Example.somewhereleftRules[r].second.property;
                file >> Example.somewhereleftRules[r].second.value;  
            }  
            // Read somewhererightconstraints
            file >> Example.somewhererightRulesCount;
            Example.somewhererightRules = new struct TwoPersonRule [Example.somewhererightRulesCount];
            for (int r=0;r<Example.somewhererightRulesCount;r++) {
                file >> Example.somewhererightRules[r].first.property;
                file >> Example.somewhererightRules[r].first.value;
                file >> Example.somewhererightRules[r].second.property;
                file >> Example.somewhererightRules[r].second.value;              
            }
            // Read positionconstraints
            file >> Example.positionRulesCount;
            Example.positionRules = new struct PositionRule [Example.positionRulesCount];
            for (int r=0;r<Example.positionRulesCount;r++) {
                file >> Example.positionRules[r].first.property;
                file >> Example.positionRules[r].first.value;
                file >> Example.positionRules[r].chair;             
            }       
            // Read betweenconstraints
            file >> Example.betweenRulesCount;
            Example.betweenRules = new struct ThreePersonRule [Example.betweenRulesCount];
            for (int r=0;r<Example.betweenRulesCount;r++) {
                file >> Example.betweenRules[r].first.property;
                file >> Example.betweenRules[r].first.value;
                file >> Example.betweenRules[r].second.property;
                file >> Example.betweenRules[r].second.value;  
                file >> Example.betweenRules[r].third.property;
                file >> Example.betweenRules[r].third.value;              
            }
            // Read likesconstraints
            file >> Example.likesRulesCount;
            Example.likesRules = new struct TwoPersonRule [Example.likesRulesCount];
            for (int r=0;r<Example.likesRulesCount;r++) {
                file >> Example.likesRules[r].first.property;
                file >> Example.likesRules[r].first.value;
                file >> Example.likesRules[r].second.property;
                file >> Example.likesRules[r].second.value;  
            }                 
        } catch (bad_alloc & ba) {
            cout << "Run out of memory" << ba.what();
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
            
    cout<<"The following people sit exactly left from another people:\n";
    for(int r=0;r<Example.exactlyleftRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.exactlyleftRules[r].first.value
            <<" for "
            <<Example.exactlyleftRules[r].first.property
            <<" and "
            <<Example.exactlyleftRules[r].second.value
            <<" for "
            <<Example.exactlyleftRules[r].second.property
            <<"\n";
            
    cout<<"The following people sit exactly right from another people:\n";
    for(int r=0;r<Example.exactlyrightRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.exactlyrightRules[r].first.value
            <<" for "
            <<Example.exactlyrightRules[r].first.property
            <<" and "
            <<Example.exactlyrightRules[r].second.value
            <<" for "
            <<Example.exactlyrightRules[r].second.property
            <<"\n";
            
    cout<<"The following people sit somewhere left from another people:\n";
    for(int r=0;r<Example.somewhereleftRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.somewhereleftRules[r].first.value
            <<" for "
            <<Example.somewhereleftRules[r].first.property
            <<" and "
            <<Example.somewhereleftRules[r].second.value
            <<" for "
            <<Example.somewhereleftRules[r].second.property
            <<"\n";
            
    cout<<"The following people sit somewhere right from another people:\n";
    for(int r=0;r<Example.somewhererightRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.somewhererightRules[r].first.value
            <<" for "
            <<Example.somewhererightRules[r].first.property
            <<" and "
            <<Example.somewhererightRules[r].second.value
            <<" for "
            <<Example.somewhererightRules[r].second.property
            <<"\n";

    cout<<"The following people sit at the position:\n";
    for(int r=0;r<Example.positionRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.positionRules[r].first.value
            <<" for "
            <<Example.positionRules[r].first.property
            <<" sit at the "
            <<Example.positionRules[r].chair
            <<". position\n";     
            
    cout<<"The following people sit between the following two people:\n";
    for(int r=0;r<Example.betweenRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.betweenRules[r].first.value
            <<" for "
            <<Example.betweenRules[r].first.property
            <<" sits between "
            <<Example.betweenRules[r].second.value
            <<" for "
            <<Example.betweenRules[r].second.property
            <<" and "
            <<Example.betweenRules[r].third.value
            <<" for "
            <<Example.betweenRules[r].third.property
            <<"\n"; 
            
    cout<<"The following people likes something:\n";
    for(int r=0;r<Example.likesRulesCount;r++)
        cout<<"\t The person who has "
            <<Example.likesRules[r].first.value
            <<" for "
            <<Example.likesRules[r].first.property
            <<" likes "
            <<Example.likesRules[r].second.value
            <<" for "
            <<Example.likesRules[r].second.property
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

    newSolution->violation_count=0; // todo majd lecserelni a fitness(newSolution,Example) fgv hivasra
    
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

int fitness(struct Solution *solution, struct ZebraPuzzle *zebra){
    solution->violation_count=0;
    
    //AtTheEndTests
    int count = zebra->attheendRulesCount;
    int position;
    for (int c=0;c<count;c++){
        position=findPosition(solution->chromosome, zebra->attheendRules[c].first);
        if (position>0 && position<zebra->chairNum-1) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
    }  
    //ExactlyLeftTests
    count = zebra->exactlyleftRulesCount;
    int position1, position2;
    for (int c=0;c<count;c++){
        position1=findPosition(solution->chromosome, zebra->exactlyleftRules[c].first);
        position2=findPosition(solution->chromosome, zebra->exactlyleftRules[c].second);
        if (position1!=position2-1) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
    }   
    //ExactlyRightTests
    count = zebra->exactlyrightRulesCount;
    for (int c=0;c<count;c++){
        position1=findPosition(solution->chromosome, zebra->exactlyrightRules[c].first);
        position2=findPosition(solution->chromosome, zebra->exactlyrightRules[c].second);
        if (position2!=position1-1) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
	}
	//SomewhereLeftTests	
	count = zebra->somewhereleftRulesCount;
    for (int c=0;c<count;c++){
        position1=findPosition(solution->chromosome, zebra->somewhereleftRules[c].first);
        position2=findPosition(solution->chromosome, zebra->somewhereleftRules[c].second);
        if (position1>=position2) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
    }
	//SomewhereRightTests	
	count = zebra->somewhererightRulesCount;
    for (int c=0;c<count;c++){
        position1=findPosition(solution->chromosome, zebra->somewhererightRules[c].first);
        position2=findPosition(solution->chromosome, zebra->somewhererightRules[c].second);
        if (position1<=position2) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
    }  
    //PositonTest
	count = zebra->positionRulesCount;    
    for (int c=0;c<count;c++){
        if (zebra->positionRules[c].chair!=findPosition(solution->chromosome, zebra->positionRules[c].first)) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
    }
    //BetweenTests
    count = zebra->betweenRulesCount; 
    int position3;
      for (c=0;c<count;c++){
		position1=findPosition(solution->chromosome, zebra->betweenRules[c].first);
        position2=findPosition(solution->chromosome, zebra->betweenRules[c].second);
        position3=findPosition(solution->chromosome, zebra->betweenRules[c].third);
        if (!(position2<position1 && position1<position3)) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
      }
    //LikesTests
    count = zebra->likesRulesCount;
    for (c=0;c<count;c++){
		position1=findPosition(solution->chromosome, zebra->likesRules[c].first);
		position2=findPosition(solution->chromosome, zebra->likesRules[c].second);
		if (position1!=position2) {
			solution->violation_count++;
			cout << "(" << c << ") "; 
		}
    }  
    //Result
    return solution->violation_count;
}

int main() {

    if(readExample()) {
        printExample();

	Solution * testSolution = newRandomSolution();
	fitness(testSolution,Example);
	printSolution(testSolution);
	deleteSolution(testSolution);
        
        
	deleteExample();
    }
}
