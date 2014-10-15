//simulates the contact process on a 1D lattice with PBC
//written (in bad style) by Stefan Grosskinsky

# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <vector>
//#include <time.h>
#include "mtwist.h"


#define runs 100      //number of averages
#define steps 200     //number of outputs in the file
#define tmax 1000     //total (real) simulation time


FILE *output_ptr;
char *output_file;
char dataname[80];

int sum;        //array of individuals and sum
double t, pr, pi;     //time counter


void init(int iSystemSize, std::vector<int>& x);
void update(float fLambda, int iSystemSize, std::vector<int>& x);
void file(float fLambda, int iSystemSize);


int main(void)
{
	float fLambda = 0; //infection rate lambda
	int iSystemSize = 0; //system size
	int k, i, j, imax;
	time_t t1;
	for (fLambda = 1; fLambda <= 2; fLambda = fLambda + 0.1)
	{
		for (iSystemSize = 256; iSystemSize <= 256; iSystemSize++)
		  {
			  std::vector<int> x(iSystemSize);
			  mt_seed();  //random seed with system time t1
			  printf("This is a very good program for the contact process...\n");
			  pr = 1. / (2.*fLambda);     // recovery probability for l>=1
			  pi = 0.5;           // infection prob for l>=1
			  imax = tmax*iSystemSize * 2 * fLambda / steps;   // number of update steps between outputs
			  file(fLambda, iSystemSize);
			  output_ptr = fopen(output_file, "a");
			  for (j = 0; j < runs; j++)
			  {
				  init(iSystemSize, x);
				  for (k = 0; k < steps; k++)
				  {
					  for (i = 0; i < imax; i++) update(fLambda, iSystemSize, x);
					  //      printf("%i %g\n",sum,t);
					  fprintf(output_ptr, "%i %g\n", sum, t);
				  }
			  }
		  fclose(output_ptr);
		}
	}
  return 0;
}


void init(int iSystemSize, std::vector<int>& x)
{
  int i;
  for(i=0; i<iSystemSize; i++) x[i]=1;
  t=0;
  sum=iSystemSize;
}


void update(float fLambda,  int iSystemSize, std::vector<int>& x)
{
  int i, j;
  double p,r;
  i=mt_lrand()%iSystemSize;   //pick site
  p=x[i]*pr + (1-x[i])*pi*(x[(i+1)%iSystemSize]+x[(i-1+iSystemSize)%iSystemSize]);  //prob. for update
  r=mt_drand();
//  r=(double)gen_rand32()/(double)UINT32_MAX;
  if(r<p)
    {
      x[i]=1-x[i];
      sum+=2*x[i]-1;
    }
  t+=1./(iSystemSize*2*fLambda);
}


void file(float fLambda, int iSystemSize)
{
  sprintf(dataname,"contact_n%i_lambda%g.dat",iSystemSize,fLambda*10);
  output_file = dataname;
  output_ptr = fopen(output_file,"w");
  fclose(output_ptr);
}
