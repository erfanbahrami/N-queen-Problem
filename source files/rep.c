#include <stdio.h>
#include <stdlib.h>

#include "type.h"

void rawStat(FILE *fp, POPULATION *p, IPTR pop);
//void rawStat();

void report(int gen, POPULATION *p, IPTR  pop, int max)
{ /* report generations stats */
  IPTR om;
  printf("fitness is : %lf\n\n", p->highestEverFitness);
  printf("p_cross: %lf, p_mut:%lf\n\n", p->pCross, p->pMut);
  for(int i = 0 ; i < p->popSize; i++)
  {
  	om = &(p->op[i]);
  	if(om->fitness >= max)
  	{
  		printf("[+] Solution founded!\n");
		printf("(one of them is: )\n[");
		for(int i = 0 ; i < p->lchrom ; i++)
		{
			printf("%d ",om->chrom[i]);
		}
		printf("]\n");
  		exit(0);
	}
  }

}

void rawStat(FILE *fp, POPULATION *p, IPTR pop)
{
  fprintf(fp," %3d %10.2lf %10.2lf %10.2lf ", p->gen, p->max,
	  p->avg, p->min);
  fprintf(fp," %3d %10.2lf %3d", p->highestEverGen,  p->highestEverFitness,
	  p->highestEverIndex);
  fprintf(fp," %10.2lf\n", pop[p->maxi].fitness);
}

