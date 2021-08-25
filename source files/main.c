#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "type.h"



int erfunc(char *s, int val);
void initialize(char *argv[], POPULATION *p, int n, int max, float, float);
void generation(POPULATION *p, int gen, int max);
void report(int gen, POPULATION *p, IPTR  pop);
void statistics(POPULATION *p, IPTR pop, int max);
double f_random();
void free_pop(POPULATION *p)
{
	IPTR pj, pi;
	for (int i = 0; i < p->popSize; i++){
	  pi = &(p->op[i]);
	  free(pi->chrom);
	  pj = &(p->np[i]);
	  free(pj->chrom);
    }
    free(p->op);
    free(p->np);
}
void print_pop(POPULATION *p, int n)
{
	for(int i = 0 ; i < p->popSize; i++)
	{
		printf("[");
		for(int j = 0 ; j < n ; j++)
		{
			printf("%d ", p->op[i].chrom[j]);
		}
		printf("] ");
		printf(" fitness: %lf\n", p->op[i].fitness);
	}
}
int main(int argc, char *argv[])
{
  srand(time(NULL));
  IPTR tmp, op, np;
  int n = 0;
  POPULATION *p = (POPULATION*) calloc(1, sizeof(POPULATION));
  int max_fitness = 0;
  
  printf("Enter the N for N*N queen: ");
  scanf("%d", &n);
  float p_cross = 0.01;
  float p_mut = 0.01;
  max_fitness = (n*(n-1))/2;
  for(;;)
  {
  
  p->gen = 0;
  printf("[----------------------------------]\n");
  initialize(argv, p, n, max_fitness, p_mut, p_cross);
  //print_pop(p, n);
  while(p->gen < p->maxGen){
    p->gen++;
	generation(p, p->gen, max_fitness);
	//print_pop(p, n);
	statistics(p, p->np, max_fitness);
	report(p->gen, p, p->np);
    tmp = p->op;
    p->op = p->np;
    p->np = tmp;
  }
  //free_pop(p);
  p->gen = 0;
  p_cross = f_random();
  p_cross = p_cross < 0.9 ? p_cross : 0.9;
  p_mut = f_random();
  p_mut = p_mut < 0.4 ? p_mut : 0.4;
  }
}
