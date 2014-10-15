//simulates the contact process on a 1D lattice with PBC
//written (in bad style) by Stefan Grosskinsky

# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
//#include <time.h>
#include "mtwist.h"


#define n 100         //system size
#define runs 100      //number of averages
#define steps 200     //number of outputs in the file
#define tmax 1000     //total (real) simulation time
#define l 1.7         //infection rate lambda

FILE *output_ptr;
char *output_file;
char dataname[80];

int x[n], sum;        //array of individuals and sum
double t, pr, pi;     //time counter


void init();
void update();
void file();


int main(void)
{
  int k,i, j,imax;
  time_t t1;
  mt_seed();  //random seed with system time t1
  printf("This is a very good program for the contact process...\n");
  pr=1./(2.*l);     // recovery probability for l>=1
  pi=0.5;           // infection prob for l>=1
  imax=tmax*n*2*l/steps;   // number of update steps between outputs
  file();
  output_ptr = fopen(output_file,"a");
  for(j=0; j<runs; j++)
  {
    init();
    for(k=0; k<steps; k++)
    {
      for(i=0; i<imax; i++) update();
      //      printf("%i %g\n",sum,t);
      fprintf(output_ptr,"%i %g\n",sum,t);
    }
  }
  fclose(output_ptr);    
  return 0;
}


void init()
{
  int i;
  for(i=0; i<n; i++) x[i]=1;
  t=0;
  sum=n;
}


void update()
{
  int i, j;
  double p,r;
  i=mt_lrand()%n;   //pick site
  p=x[i]*pr + (1-x[i])*pi*(x[(i+1)%n]+x[(i-1+n)%n]);  //prob. for update
  r=mt_drand();
//  r=(double)gen_rand32()/(double)UINT32_MAX;
  if(r<p)
    {
      x[i]=1-x[i];
      sum+=2*x[i]-1;
    }
  t+=1./(n*2*l);
}


void file()
{
  sprintf(dataname,"contact_n%i_l%g.dat",n,l*10);
  output_file = dataname;
  output_ptr = fopen(output_file,"w");
  fclose(output_ptr);
}
