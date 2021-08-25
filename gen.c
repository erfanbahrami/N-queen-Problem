#include <stdio.h>

#include "type.h"

int roulette(IPTR pop, double sumFitness, int popsize);
void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2);
double eval(POPULATION *p, IPTR pj, int max);

int generation(POPULATION *p, int t, int max)
{

  int i, p1, p2, c;

  IPTR pi, piPlus1, om1, om2;

  for(i = 0; i < p->popSize; i += 2){

    p1 = roulette(p->op, p->sumFitness, p->popSize);
    p2 = roulette(p->op, p->sumFitness, p->popSize);

    pi = &(p->np[i]);			//future population
    piPlus1 = &(p->np[i+1]);	//future population
    om1 = &(p->op[p1]);			//current population
    om2 = &(p->op[p2]);			//current population

    crossover(p, om1, om2, pi, piPlus1);

    pi->fitness = eval(p, pi, max); 
    pi->parent1 = p1;
    pi->parent2 = p2;

    
    piPlus1->fitness = eval(p, piPlus1, max); 
    piPlus1->parent1 = p2;
    piPlus1->parent2 = p1;
  }

}

