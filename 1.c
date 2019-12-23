#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
void merge(int a[],int l,int m,int r){
	int n1,n2,i,j,k;
	n1=m-l+1;
	n2=r-m;
	int L[n1],R[n2];
	for(i=0;i<n1;i++)
		L[i]=a[l+i];
	for(j=0;j<n2;j++)
		R[j]=a[m+j+1];
	i=0;
	k=l;
	j=0;
	while(i<n1 && j<n2){
		if(L[i]<=R[j]){
			a[k]=L[i];
			i++;
			}
		else{
			a[k]=R[j];
			j++;
			}
		k++;
		}
	while(i<n1){
		a[k]=L[i];
		i++;
		k++;
		}
	while(j<n2){
		a[k]=R[j];
		j++;
		k++;
		}
	}
void mergesort(int arr[],int l,int r){
	if(l<r)
	{
		int mid;
	#pragma omp parallel sections
	{
		mid=(l+r)/2;
		#pragma omp section
		{			printf("Thread id: %d \t mid:%d\n",omp_get_thread_num(),mid);
			mergesort(arr,l,mid);
		}
		#pragma omp section
		{	
			printf("Thread id:%d \t mid+1:%d\n",omp_get_thread_num(),mid+1);
			mergesort(arr,mid+1,r);
		}
	}
		merge(arr,l,mid,r);
		}
	}
void main(){
	omp_set_nested(1);
	int n,i;
	printf("Enter n:\n");
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++)
		arr[i]=rand()%100;
	printf("Unsorted ARRAY:\n");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
	
	double t1=omp_get_wtime();
	mergesort(arr,0,n-1);
	double t2=omp_get_wtime();
	printf("sorted ARRAY:\n");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("Time taken for sort:%lf s",t2-t1);
	}
