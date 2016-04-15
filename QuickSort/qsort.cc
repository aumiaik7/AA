#include <stdio.h>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
void srand( unsigned seed ); 

using namespace std;

#define N 700000

void quickSort(long int arr[], int left, int right);


int main ()
{ 
	long int number[N];
	int count;
	struct timeval  start, stop;
	srand( time(NULL) );
	
	/* generates input data randomly*/
	for (count=0 ; count<N ; count++ )
	{
		number[count] = rand() % 100 + 1;
	   // printf ("%d, ", number[count]);
	}
	/*sets number of cores to be used*/
	 __cilkrts_set_param("nworkers", "16");
		
	gettimeofday(&start,NULL);
	quickSort(number, 0, N-1);
	gettimeofday(&stop,NULL);
	
	printf("\n") ;
	
	for (count=0 ; count<N ; count++)
	{
		 printf ("%d, ", number[count]);
	}
	
	/* Total time of sorting  in seconds*/
	double time = (stop.tv_sec+(double)stop.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000)	;	
	//printf("time = %g\n", 
	cout<<endl<<"Sorting done in "<<time<< " seconds"<<endl;
	
}

void quickSort(long int arr[], int left, int right) {
      int i = left, j = right, l=right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j)

     {
           while (arr[i] < pivot)
                  i++;
             
	
            while (arr[j] > pivot)
                  j--;
                 
	   
            if(i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
	
      };
 
      /* recursion  */

      if (left < j)
          {cilk_spawn 
	quickSort(arr, left, j);
}
      if (i < right)
            quickSort(arr, i, right);
	cilk_sync;	
}
