#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CITIES 7
#define POPSIZE 10
#define ELITES 1
#define MUTRATE 0.25
#define MAXITER 30

typedef struct genotype {
  char order[CITIES];
  int fitness;
  int objective;
} GENOTYPE;

/* https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle */
void fisherYates(char* order) {
  int g1;
  for(g1=CITIES-1; g1>0; g1--) {
      int g2 = rand()%(g1+1);
      char tmp = order[g1];
      order[g1] = order[g2];
      order[g2] = tmp;
  }
}

void init(GENOTYPE* pop) {
  int ind, gene;
  for(ind=0; ind<POPSIZE; ind++) {
    for(gene=0; gene<CITIES; gene++) {
      pop[ind].order[gene] = gene;
    }
    fisherYates(pop[ind].order);
  }
}

void objective(GENOTYPE* pop) {
  static int distances[CITIES][CITIES] = {
    {   0, 121, 174, 231, 115,  83, 139 },
    { 121,   0, 287, 377,  82, 176, 285 },
    { 174, 287,   0, 218, 278, 161, 298 },
    { 231, 377, 218,   0, 368, 320, 131 },
    { 115,  82, 278, 368,   0, 103, 275 },
    {  83, 176, 161, 320, 103,   0, 228 },
    { 139, 285, 298, 131, 275, 228,   0 }
  };
  int ind, gene, obj, from, to;
  for(ind=0; ind<POPSIZE; ind++) {
    for(obj=gene=0, to=pop[ind].order[gene]; gene<CITIES-1; gene++) {
      from = to;
      to   = pop[ind].order[gene+1];
      obj += distances[from][to];
    }
    from = to;
    to   = pop[ind].order[0];
    obj += distances[from][to];
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
  int pos1 = rand()%CITIES;
  int pos2;
  char tmp;
  do {
    pos2 = rand()%CITIES;
  } while(pos1 == pos2); /* Different positions needed */
  tmp = ind->order[pos1];
  ind->order[pos1] = ind->order[pos2];
  ind->order[pos2] = tmp;
}

/* PMX https://www.slideshare.net/guest9938738/genetic-algorithms */
void crossover(const GENOTYPE* popOld, GENOTYPE* popNew) {
  int ind, par1, par2, pos1, pos2, gene;
  copyElites(popOld, popNew);
  for(ind=ELITES; ind<POPSIZE; ind++) {
    par1 = selection(popOld);
    do {
      par2 = selection(popOld);
    } while(par1 == par2);
    pos1 = rand()%CITIES;
    pos2 = rand()%(CITIES-pos1) + pos1;
    /* Step1: copy matching section elements of par1 into offspring to the same position */
    for(gene=0; gene<CITIES; gene++) {
      if(gene>=pos1 && gene<=pos2) {
        popNew[ind].order[gene] = popOld[par1].order[gene];
      } else {
        popNew[ind].order[gene] = -1;
      }
    }
    /* Step2: copy missing elements of par2's matching section into offspring */
    for(gene=pos1; gene<=pos2; gene++) {
      char* copyPos = memchr(popOld[par1].order+pos1, popOld[par2].order[gene], pos2-pos1+1);
      if(!copyPos) { /* Allele is missing */
        int where = gene;
        do {
          where = memchr(popOld[par2].order, popOld[par1].order[where], CITIES) - (void*)popOld[par2].order;
        } while(where>=pos1 && where<=pos2);
        popNew[ind].order[where] = popOld[par2].order[gene];
      }
    }
    /* Step3: fill all non-defined alleles of the offspring using par2 data */
    for(gene=0; gene<CITIES; gene++) {
      if(popNew[ind].order[gene] == -1) {
        popNew[ind].order[gene] = popOld[par2].order[gene];
      }
    }
    if(rand()/RAND_MAX < MUTRATE) mutation(popNew+ind);
  }
}

void rotate(char* order) {
  while(*order) {
    char tmp = *order;
    memmove(order, order+1, CITIES-1);
    *(order+CITIES-1) = tmp;
  }
}

void printBest(int iter, const GENOTYPE* pop) {
  static char* cityNames[CITIES] = {
    "Bp.",
    "Gyor",
    "Szeged",
    "Debrecen",
    "Veszprem",
    "Duv.",
    "Eger"
  };
  int city;
  char copy[CITIES];
  memmove(copy, pop->order, CITIES);
  rotate(copy);
  printf("%4d: %s", iter, cityNames[*copy]);
  for(city=1; city<CITIES; city++) {
    printf("->%s", cityNames[copy[city]]);
  }
  printf("->%s = %d km.\n", cityNames[*copy], pop->objective);
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
    crossover(ppa, ppb);
    swap(&ppa, &ppb);
  }

  return 0;
}
