#include <stdio.h>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
void srand( unsigned seed ); 



using namespace std;

#define N 700000

void merge(long int [], long int [], int, int,int);
void mergeSort(long int [], long int [], int, int );

int main ()
{ 
	long int a[N],b[N];
	int count;
	struct timeval  start, stop;
	srand( time(NULL) );
	
	/* generates random data*/

	for (count=0 ; count<N ; count++ )
	{
		a[count] = rand() % 100 + 1;
	   // printf ("%d, ", number[count]);
	}
	__cilkrts_set_param("nworkers", "16");
		
	gettimeofday(&start,NULL);
	mergeSort(a,b, 0, N-1);
	gettimeofday(&stop,NULL);
	
	printf("\n") ;
	
	for (count=0 ; count<N ; count++)
	{
		 printf ("%d, ", a[count]);
	}
	
	/* Total time of sorting in seconds*/
	double time = (stop.tv_sec+(double)stop.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000)	;	
	//printf("time = %g\n", 
	cout<<endl<<"Sorting done in "<<time<< " seconds"<<endl;
	
}


void mergeSort(long int a[],long int b[], int low, int high)
 {
     
      int pivot;
      if(low<high){
	pivot=(low + high) / 2; 
	cilk_spawn 
	mergeSort(a,b,low,pivot);
	mergeSort(a,b,pivot+1,high);
	cilk_sync;
	merge(a,b,low,pivot,high);
	
	}
}
 
      /* partition */
void merge(long int a[], long int b[],int low,int pivot,int high)
{
int h,i,j,k;
h=low;
i=low;
j=pivot+1;

while((h<=pivot) && (j<=high)){

	if(a[h]<=a[j])
	{
		b[i]=a[h];
		h++;
	}
	else
	{
		b[i]=a[j];
		j++;

	}
	i++;

}
if(h>pivot)
{
	for(k=j; k<=high; k++)
	{
		b[i]=a[k];
		i++;

	}
}
else
{
	for(k=h; k<=pivot; k++)
	{
		b[i]=a[k];
		i++;
	}
}
for(k=low; k<=high; k++)
	a[k]=b[k];
}
