#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <new>
#include <ctime>

#define POPSIZE 100
#define ELITES 10

using namespace std;

string itoa(int a){
    if (a==0) return "0";
    string s;
    for (s="";a != 0;a/=10) 
        s = char('0'+(a%10)) + s;
    return s;
        
}

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

int getPropertyID(string property){
    for(int c=0; c<Example.propertyNum; c++)
        if (Example.properties[c]==property) return c;
    return -1;
}

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
    for(int i = 0;i < Example.propertyNum;++i) {
            delete[] Example.propertyvalues[i];
    }
    delete [] Example.propertyvalues;
    delete Example.properties;
    delete Example.attheendRules;
    delete Example.exactlyleftRules;
    delete Example.exactlyrightRules;
    delete Example.somewhereleftRules;
    delete Example.somewhererightRules;
    delete Example.betweenRules;
    delete Example.positionRules;
    delete Example.likesRules;
}

struct Solution {
    int violation_count;
    string** chromosome;
};

struct Solution * newEmptySolution() {
    struct Solution * newSolution = new struct Solution;
    newSolution->chromosome=new string * [Example.propertyNum];
    for(int i = 0;i < Example.propertyNum;++i) {
        newSolution->chromosome[i] = new string [Example.chairNum];
    }
    return newSolution;
}

struct Solution * copySolution(struct Solution * other) {
    struct Solution * copy = newEmptySolution();
    for(int i = 0;i < Example.propertyNum;++i) {
        for(int j = 0;j < Example.chairNum;++j) {
            copy->chromosome[i][j]=other->chromosome[i][j];
        }
    }
    copy->violation_count = other->violation_count;
    return copy;
}

void deleteSolution(struct Solution * solution) {
    for(int i = 0;i < Example.propertyNum;++i){
         delete[] solution->chromosome[i];
    }
    delete[] solution->chromosome;
    delete solution;
}

int findPosition(struct Solution* solution, Person p){
    int c;
    for(c=0;c<Example.chairNum;c++)
        if (solution->chromosome[getPropertyID(p.property)][c]==p.value) return c;
    return 0;
}


string updateFitness (struct Solution *solution){
    solution->violation_count=0;
    int position;
    string violated="";

    //AtTheEndTests
    for (int r=0;r<Example.attheendRulesCount;r++){
        position=findPosition(solution, Example.attheendRules[r].first);
        if (position>0 && position<Example.chairNum-1) {
			solution->violation_count++;
            violated += " ate(";
            violated += itoa(r);
            violated +=") ";
		}
    }
   
    //ExactlyLeftTests
    int position1, position2;
    for (int r=0;r<Example.exactlyleftRulesCount;r++){
        position1=findPosition(solution, Example.exactlyleftRules[r].first);
        position2=findPosition(solution, Example.exactlyleftRules[r].second);
        if (position1!=position2-1) {
			solution->violation_count++;
            violated += " eleft(";
            violated += itoa(r);
            violated +=") ";
		}
    } 
    //ExactlyRightTests
    for (int r=0;r<Example.exactlyrightRulesCount;r++){
        position1=findPosition(solution, Example.exactlyrightRules[r].first);
        position2=findPosition(solution, Example.exactlyrightRules[r].second);
        if (position2!=position1-1) {
			solution->violation_count++;
            violated += " eright(";
            violated += itoa(r);
            violated +=") ";
		}
	}
	//SomewhereLeftTests
    for (int r=0;r<Example.somewhereleftRulesCount;r++){
        position1=findPosition(solution, Example.somewhereleftRules[r].first);
        position2=findPosition(solution, Example.somewhereleftRules[r].second);
        if (position1>=position2) {
			solution->violation_count++;
            violated += " sleft(";
            violated += itoa(r);
            violated +=") ";
		}
    }
	//SomewhereRightTests
    for (int r=0;r<Example.somewhererightRulesCount;r++){
        position1=findPosition(solution, Example.somewhererightRules[r].first);
        position2=findPosition(solution, Example.somewhererightRules[r].second);
        if (position1<=position2) {
			solution->violation_count++;
            violated += " sright(";
            violated += itoa(r);
            violated +=") ";
		}
    }
    //PositonTest
    for (int r=0;r<Example.positionRulesCount;r++){
        if (Example.positionRules[r].chair!=findPosition(solution, Example.positionRules[r].first)) {
			solution->violation_count++;
            violated += " sright(";
            violated += itoa(r);
            violated +=") ";
		}
    }
    //BetweenTests
    int position3;
      for (int r=0;r<Example.betweenRulesCount;r++){
		position1=findPosition(solution, Example.betweenRules[r].first);
        position2=findPosition(solution, Example.betweenRules[r].second);
        position3=findPosition(solution, Example.betweenRules[r].third);
        if (!(position2<position1 && position1<position3)) {
			solution->violation_count++;
            violated += " sright(";
            violated += itoa(r);
            violated +=") ";
		}
      }
    //LikesTests
    for (int r=0;r<Example.likesRulesCount;r++){
		position1=findPosition(solution, Example.likesRules[r].first);
		position2=findPosition(solution, Example.likesRules[r].second);
		if (position1!=position2) {
			solution->violation_count++;
            violated += " sright(";
            violated += itoa(r);
            violated +=") ";
		}
    }

    return violated;
}

struct Solution * Mutate(struct Solution * msolution, int mutateCount = 50) {
    int i;
    string tmp;

    struct Solution * solution = copySolution(msolution);
    

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
    updateFitness(solution);
    return solution;
}

struct Solution * newRandomSolution(){
	struct Solution * newSolution = newEmptySolution();
    for(int i = 0;i < Example.propertyNum;++i) {
        for(int j = 0;j < Example.chairNum;++j) {
            newSolution->chromosome[i][j]=Example.propertyvalues[i][j];
        }
    }
	int switchCount;
	srand( time(0));
	switchCount=rand()%50+1;

    Mutate(newSolution,switchCount);

    updateFitness(newSolution); 

    return newSolution;
}

void Orderby(struct Solution ** solutions, int size){
	struct Solution * X;
	int i,j;
	for (i=1;i<size;i++){
 		X=copySolution(solutions[i]);
  		j=i-1;
  		while((j>=0) && (solutions[j]->violation_count>X->violation_count)){
  			solutions[j+1]=copySolution(solutions[j]);
  			j=j-1;
  		}
        solutions[j+1]=copySolution(X);
	}
}

struct Solution * Crossover(struct Solution * solution1, struct Solution * solution2){
	int c,p;
	struct Solution * solution = newEmptySolution();

	int cut;
	srand( time(0));
	cut=rand()%Example.propertyNum;
	for (p=0;p<Example.propertyNum;p++){
		if (p<cut){
            for (c=0;c<Example.chairNum;c++){
                solution->chromosome[p][c]=solution1->chromosome[p][c];
            }
        } else {
			for (c=0;c<Example.chairNum;c++){
               solution->chromosome[p][c]=solution2->chromosome[p][c];
			}
		}
	}
    updateFitness(solution);
    return solution;
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
    string violate=updateFitness(solution);
    cout<<"Violate: "<<violate<<endl;
}





void Execute(){
	int i;
	struct Solution ** population = new struct Solution * [POPSIZE];

	for(i=0;i<POPSIZE;i++) {
		population[i]=newRandomSolution();
	}
	struct Solution ** temp = new struct Solution * [POPSIZE*4];
    // Iteralasok
    int k;
    int j;

    for(i=0;population[0]->violation_count!=0;i++){
        cout <<"Generation "<< i <<": \n";
        printSolution(population[0]);
        k=0;
        // Copy from previously population
        for (j=0;j<POPSIZE; j++){
            temp[k]=copySolution(population[j]);
            k++;
        }
        // Mutations (x100)
        for (j=0;j<POPSIZE; j++){
            temp[k]=Mutate(population[j]);
            k++;
        }
        // Crossover (x100)
        for (j=0;j<POPSIZE;j++){
			srand( time(0));
			int x;
			x=rand()%POPSIZE;
			int y;
			y=rand()%POPSIZE;
			temp[k]=Crossover(population[x],population[y]);
			k++;
         }
        // Crossover after Mutation (x100)
        for (j=0;j<POPSIZE;j++){
			srand( time(0));
			int x;
			x=rand()%POPSIZE;
			int y;
			y=rand()%POPSIZE;
			temp[k]=Crossover(temp[x+POPSIZE],temp[y+POPSIZE]);
			k++;
         }
        // Delete old population
        for(int i=0; i<POPSIZE; i++){
            deleteSolution(population[i]);
        }
        // Select the new generation
        // Order them based on fitness
        Orderby(temp,4*POPSIZE);
        //The good solutions have better chance.
        for (j=0; j<ELITES;j++){
            population[j]=copySolution(temp[j]);
        }
        for (j=ELITES;j<POPSIZE;j++){
			int k;
			srand(time(0));
			k=rand()%((int) (POPSIZE*1.2));
			if (k<POPSIZE){
                population[j]=copySolution(temp[j]);
			} else {
                population[j]=copySolution(temp[POPSIZE+j]);
			}
		}
        // Delete temporary population array
        for(int i=0; i<POPSIZE*4; i++){
            deleteSolution(temp[i]);
        }
    }

    cout << "******************************\n";
    
    printSolution(population[0]);

    for (j=0; j<ELITES;j++){
            population[j]=copySolution(temp[j]);
    }
    delete [] population;
    delete [] temp;
}

int main() {

    if(readExample()) {
        printExample();

        // Test stingle solution
        /*Solution * testSolution = newRandomSolution();
        updateFitness(testSolution);
        printSolution(testSolution);
        deleteSolution(testSolution);*/

        // Execute GA
        Execute();
        deleteExample();
    }
}
