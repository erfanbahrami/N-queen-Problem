#include <stdio.h>
#include <stdlib.h>
#include <math.h>    /* for pow(x, y) */
#include "type.h"

double decode(IPTR pj, int index, int size);
double binToDec(int *chrom, int l);

double eval(POPULATION *p, IPTR pj, int max_fitness) 
     /* Called from gen.c and init.c */
{
	double val;
	double square = 0.0;
	double counter = 0;
	int vertical_collisions = 0;
	for(int i = 0; i < p->lchrom; i++)
	{
		for(int j = 0; j < p->lchrom; j++)
		{
			if(pj->chrom[i] == pj->chrom[j] && (i != j))
			{
				vertical_collisions++;
			}
		}
	}
	vertical_collisions/=2;
	int n = p->lchrom;
	int *left_diagonal = (int *) calloc(n * 2, sizeof(int));
	int *right_diagonal = (int *) calloc(n * 2, sizeof(int));
	for(int i = 0 ; i < n ; i++)
	{
		left_diagonal[i + pj->chrom[i] - 1] += 1;
		right_diagonal[p->lchrom - i + pj->chrom[i] - 2] += 1;
	}
	double diagonal_collisions = 0;
	for(int i = 0 ; i < (2*n-1) ; i++)
	{
		counter = 0;
		if (left_diagonal[i] > 1)
		    counter += left_diagonal[i]-1;
		if (right_diagonal[i] > 1)
		    counter += right_diagonal[i]-1;
		diagonal_collisions += (counter / (n-abs(i-n+1)));
	}
	free(left_diagonal);
	free(right_diagonal);
	return (max_fitness - (vertical_collisions + diagonal_collisions));
}

double decode(IPTR pj, int index, int size)
{
  return ((double) binToDec(&(pj->chrom[0]), size));
}

double binToDec(int *chrom, int l)
{
  int i;
  double prod;

  prod = 0.0;

  for(i = 0; i < l; i++){
    prod += (chrom[i] == 0 ? 0.0 : pow((double)2.0, (double) i));
  }
  return prod;
}

void decToBin(int ad, int *barray, int size)
{
  int i, t;

  t = ad;
  for(i = 0; i < size; i++){
    barray[i] = t%2;
    t = t/2;
  }
}
