#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<stdbool.h>
#include<math.h>
void primetable(int n){
	bool primes[n+1];
	int p,i;
	memset(primes,true,sizeof(primes));
	for(p=2;p*p<=n;p++){
		if(primes[p]==true){
			for(i=p*p;i<=n;i+=p)
				primes[i]=false;
			}
	}
	for(p=2;p<=n;p++)
		if(primes[p]==true)
			printf("%d ",p);
	printf("\n");
	}

void  sinetable(int n){
	
	double * sines=(double *)malloc(sizeof(double)*n);
	int i,j;
	double pi=3.1421;
	for(i=0;i<n;i++)
	{
		sines[i]=sin(i*(pi/180));
		
	}

	printf("Sine table:\n");
	for(i=0;i<n;i++)
		printf("sin(%d)=%lf\n",i,sines[i]);
	}

void main(){
	int size;
	scanf("%d",&size);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
		primetable(size);
		}
		#pragma omp section
		{
		sinetable(size);
		}
	}
	}
