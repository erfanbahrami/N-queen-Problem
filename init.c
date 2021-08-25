#include <stdio.h>
#include <stdlib.h>  /* for calloc */
#include <string.h>
#include "type.h"
int flip(double p);
void randomize(POPULATION *p);

void statistics(POPULATION *p, IPTR pop, int max);

void rawStat(FILE *fp, POPULATION *p, IPTR pop);
double f_random();
double eval(POPULATION *p, IPTR pi, int max);
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int arr[], int n) {
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

void initData(char *inputFile, POPULATION *p);
void initPop(POPULATION *p, int max);
void initReport(POPULATION *p);
void initialize(char *argv[], POPULATION *p, int n, int max, float pmut, float pcross)
{ /* initialize everything */
/*
5
10
50
0.66
0.001
*/
	IPTR pj, pi;
	p->maxGen = 500;
	p->lchrom = n;
	p->popSize=100;
	p->pCross = pcross;//0.66
	p->pMut = pmut; //0.03
	p->op = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));
  	p->np = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));
  	for (int i = 0; i < p->popSize; i++){
	 pi = &(p->op[i]);
	 pi->chrom = (int *) calloc (p->lchrom, sizeof(int));

	 pj = &(p->np[i]);
	 pj->chrom = (int *) calloc (p->lchrom, sizeof(int));

	 for (int j = 0; j < p->lchrom; j++){
		pi->chrom[j] = j + 1;
	 }
	 shuffle(pi->chrom, p->lchrom);
	 
	 pi->fitness  = eval(p, pi, max);

  }
  randomize(p);
  p->highestEverFitness = 0.0;
  p->highestEverGen = 0;
  p->highestEverIndex = 0;
  
}

void initData(char *Ifile, POPULATION *p)
{ /* inittialize global params,

	  popsize:   population size
	  lchrom :   chromosome lenght
	  maxgen :   maximum no. of generations.
	  pcross :   crossover probability
	  pmut   :   mutation probability           */
  int i;
  FILE *inpfl;
  char tmp[1024];

  if( (inpfl = fopen(Ifile,"r")) == NULL){
	 printf("error in opening file %s \n", Ifile);
	 exit(1);
  }

  printf(" Enter population size - popSize-> ");
  fscanf(inpfl,"%d",&p->popSize);
  if(p->popSize % 2 != 0) {
	 p->popSize++;
  }
  printf("\nNote population size must be even: %i", p->popSize);

  printf(" Enter chromosome length - lChrom-> ");
  fscanf(inpfl,"%d",&p->lchrom);
  printf("\n");

  printf(" Enter max. generations - maxGen-> ");
  fscanf(inpfl,"%d",&p->maxGen);
  printf("\n");

  printf(" Enter crossover prob - pCross-> ");
  fscanf(inpfl,"%lf",&p->pCross);
  printf("\n");

  printf(" Enter mutation prob - pMut-> ");
  fscanf(inpfl,"%lf",&p->pMut);
  printf("\n");

  printf(" Enter file name for graph output -fname-> ");

  fscanf(inpfl,"%s", tmp);
  p->ofile = (char *) calloc (strlen(tmp)+1, sizeof(char));
  strcpy(p->ofile, tmp);
  printf("Save file is %s\n", p->ofile);


  fclose(inpfl);
  printf("\n");

  randomize(p); /* initialize random number generator */

  /* set progress indicators to zero */
  p->highestEverFitness = 0.0;
  p->highestEverGen = 0;
  p->highestEverIndex = 0;

}


void initPop(POPULATION *p, int max)
{ /* initialize a random population */
  IPTR pi, pj;
  int i, j;
  FILE *fp;
  double f1;

  p->op = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));
  p->np = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));


  for (i = 0; i < p->popSize; i++){
	 pi = &(p->op[i]);
	 pi->chrom = (int *) calloc (p->lchrom, sizeof(int));

	 pj = &(p->np[i]);
	 pj->chrom = (int *) calloc (p->lchrom, sizeof(int));

	 for (j = 0; j < p->lchrom; j++){
		pi->chrom[j] = rand()%6 + 1;
	 }
	 pi->fitness  = eval(p, pi, max);

  }
}


void initReport(POPULATION *p)
{
  FILE *fp;
  int i, k;

  printf("\n\nPopulation Size(popsize)  %d\n", p->popSize);
  printf("Chromosome length (lchrom)  %d\n", p->lchrom);
  printf("Maximum num of generations(maxgen)  %d\n", p->maxGen);
  printf("Crossover Probability (pcross)  %lf\n", p->pCross);
  printf("Mutation Probability (pmut)  %lf\n", p->pMut);
  printf("\n\t\tFirst Generation Stats  \n\n");
  printf("Maximum Fitness  %lf\n", p->max);
  printf("Average Fitness  %lf\n", p->avg);
  printf("Minimum Fitness  %lf\n", p->min);

  if( (fp = fopen(p->ofile, "a")) == NULL){
	 printf("error in opening file %s \n", p->ofile);
	 exit(1);
  }else{
	 rawStat(fp, p,  p->op);
	 fclose(fp);
  }
  rawStat(stdout, p, p->op);
}

