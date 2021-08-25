#include "type.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "type.h"

int rnd(int low, int high);
int flip(double);
void mutation(POPULATION *p, int*a, int size);
void printt(int *a, int size)
{
	printf("\n[");
	for(int i = 0 ; i < size ; i++)
	{
		printf("%d ",a[i]);
	}
	printf("]\n");
}
void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2)
{
/* p1,p2,c1,c2,m1,m2,mc1,mc2 */
  int *pi1,*pi2,*ci1,*ci2;
  int xp1, xp2, i, j;
  pi1 = p1->chrom;
  pi2 = p2->chrom;
  ci1 = c1->chrom;
  ci2 = c2->chrom;
  
  if(flip(p->pCross)){
    xp1 = rnd(0, p->lchrom - 1);
    xp2 = rnd(xp1, p->lchrom - 1);
    for(i = 0; i < xp1; i++){
      ci1[i] = pi1[i];
      ci2[i] = pi2[i];
    }
    for(i = xp1; i < xp2; i++){
      ci1[i] = pi2[i];
      ci2[i] = pi1[i];
    }
    for(i = xp2; i < p->lchrom; i++){
      ci1[i] = pi1[i];
      ci2[i] = pi2[i];
    }
    for(i = 0; i <xp1; i++ )
    {
    	for(j = xp1; j <xp2; j++ )
	    {
	    	if(j != i && ci1[i] == ci1[j])
	    	{
	    		ci1[i] = pi1[j];
			}
		}
	}
	for(i = xp1; i < xp2; i++ )
    {
    	for(j = xp2; j <p->lchrom; j++ )
	    {
	    	if(j != i && ci1[i] == ci1[j])
	    	{
	    		ci1[j] = pi1[i];
			}
		}
	}
	for(i = 0; i <xp1; i++ )
    {
    	for(j = xp1; j <xp2; j++ )
	    {
	    	if(j != i && ci2[i] == ci2[j])
	    	{
	    		ci2[i] = pi2[j];
			}
		}
	}
	for(i = xp1; i < xp2; i++ )
    {
    	for(j = xp2; j <p->lchrom; j++ )
	    {
	    	if(j != i && ci2[i] == ci2[j])
	    	{
	    		ci2[j] = pi2[i];
			}
		}
	}
  } else {
    for(i = 0; i < p->lchrom; i++){
      ci1[i] = pi1[i];
      ci2[i] = pi2[i];
    }
  }
  for(int i = 0 ; i < p->lchrom; i++)
  {
  	mutation(p, ci1, p->lchrom);
  	mutation(p, ci2, p->lchrom);
  }
}

void mutation(POPULATION *p, int*a, int size)
{
	int pos = 0;
	if(flip(p->pMut))
	{
		pos = rand() % size;
		swap(&a[pos], &a[size - pos - 1]);
	}
}



