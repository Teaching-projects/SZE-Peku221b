#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TARGET "Hello world!"
#define TSIZE sizeof(TARGET)
#define POPSIZE 2048
#define ELITES 10
#define MUTRATE 0.25
#define MAXITER 10000

typedef struct genotype {
  char str[TSIZE];
  int fitness;
  int objective;
} GENOTYPE;

void init(GENOTYPE* pop) {
  int ind, gene;
  for(ind=0; ind<POPSIZE; ind++) {
    for(gene=0; gene<TSIZE-1; gene++) {
      pop[ind].str[gene] = rand()%90 + 32;
    }
    pop[ind].str[gene] = '\0';
  }
}

void objective(GENOTYPE* pop) {
  int ind, gene, obj;
  for(ind=0; ind<POPSIZE; ind++) {
    for(obj=gene=0; gene<TSIZE-1; gene++) {
      obj += abs(pop[ind].str[gene] - TARGET[gene]);
    }
    pop[ind].objective = obj;
  }
}

int compare(const void* ind1, const void* ind2) {
  return ((GENOTYPE*)ind1)->objective - ((GENOTYPE*)ind2)->objective;
}

void fitness(GENOTYPE* pop) {
  int ind;
  qsort(pop, POPSIZE, sizeof(GENOTYPE), compare);
  for(ind=0; ind<POPSIZE; ind++) {
    pop[ind].fitness = (POPSIZE-ind)*(POPSIZE-ind);
  }
}

void copyElites(const GENOTYPE* popOld, GENOTYPE* popNew) {
  memmove(popNew, popOld, ELITES*sizeof(GENOTYPE));
}

int selection(const GENOTYPE* pop) {
  int sumFitness, partFitness, ind, rnd;
  for(sumFitness=ind=0; ind<POPSIZE; ind++) {
    sumFitness += pop[ind].fitness;
  }
  rnd = rand()%sumFitness + 1;
  for(partFitness=ind=0; partFitness<rnd; ind++) {
    partFitness += pop[ind].fitness;
  }
  return ind-1;
}

void mutation(GENOTYPE* ind) {
  ind->str[rand()%(TSIZE-1)] = rand()%90 + 32;
}

void crossover(const GENOTYPE* popOld, GENOTYPE* popNew) {
  int ind, par1, par2, pos;
  copyElites(popOld, popNew);
  for(ind=ELITES; ind<POPSIZE; ind++) {
    par1 = selection(popOld);
    par2 = selection(popOld);
    pos = rand()%TSIZE;
    memmove(popNew[ind].str, popOld[par1].str, pos);
    memmove(popNew[ind].str+pos, popOld[par2].str+pos, TSIZE-pos);
    if(rand()/RAND_MAX < MUTRATE) mutation(popNew+ind);
  }
}

void printBest(int iter, const GENOTYPE* pop) {
  printf("%4d: '%s' --> %d\n", iter, pop->str, pop->objective);
}

void swap(GENOTYPE** pop1, GENOTYPE** pop2) {
  GENOTYPE* tmp = *pop1;
  *pop1 = *pop2;
  *pop2 = tmp;
}

int main(void) {
  GENOTYPE popa[POPSIZE];
  GENOTYPE popb[POPSIZE];
  GENOTYPE* ppa = popa;
  GENOTYPE* ppb = popb;
  int iteration;

  srand((unsigned)time(NULL));
  init(ppa);
  for(iteration=0; iteration<MAXITER; iteration++) {
    objective(ppa);
    fitness(ppa);
    printBest(iteration, ppa);
    if(!ppa->objective) break;
    crossover(ppa, ppb);
    swap(&ppa, &ppb);
  }

  return 0;
}
