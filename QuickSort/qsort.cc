/*
*
*Ahamad Imtiaz Khan (001188188)
*Grad Student (MSc) 
*Quicksort with partitioning done sequntially
*how to run this program is mentioned inside howToRun.txt
*
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

void srand( unsigned seed ); 

using namespace std;

#define N 700000

void quickSort(long int arr[], int left, int right);


int main (int argc, char *argv[])
{
	//array that holds all the numbers 
	long int array[N];
	
	//this counter is used for displaying the data only
	int count;
	
	//start time and end time is used to get the time for quicksort operation
	struct timeval  start, end;
	
	//Srand will seed the random number generator to prevent random numbers 
	//from being the same every time the program is executed and to allow more pseudorandomness
	srand( time(NULL) );
	
	//generate numbers randomly
	for (count=0 ; count<N ; count++ )
	{
		array[count] = rand() % 100 + 1;
	}

	//default number of cores
	const char* numOfCores = "16";
	//get number of cores from command line argument
	if(argc == 2)
	{
		numOfCores = argv[1];
	}
	 __cilkrts_set_param("nworkers", numOfCores);
	
	cout<<"There are "<<numOfCores<<" workers working"<<endl;
		
	//start time	
	gettimeofday(&start,NULL);
	//start main operation
	quickSort(array, 0, N-1);
	//end time	
	gettimeofday(&end,NULL);
	
	//display output
	for (count=0 ; count<N ; count++)
	{
		 cout<<array[count]<<" ";
	}
	
	//calculate the time needed for sorting in seconds
	double time = (end.tv_sec+(double)end.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000)	;	

	cout<<endl<<"Sorting done in "<<time<< " seconds"<<endl;
	
}

void quickSort(long int arr[], int left, int right) {
      
	int i = left, j = right, l=right;
	int tmp;
	//select pivot (middle element)	 
	int pivot = arr[(left + right) / 2];
 
	//sequential partitioning
	while (i <= j)
	{
		//find number greater than pivot in left side	
		while (arr[i] < pivot)
			i++;
		//find nubmer less than pivot in right side
      		while (arr[j] > pivot)
			j--;
	        //swap the numbers
		if(i <= j) 
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	
	};
	//recursion done in parallel
	if(left < j)
	{
		cilk_spawn //call the method asynchronously
		quickSort(arr, left, j);
	}
	if (i < right)
            quickSort(arr, i, right);
		
	//Synchronize the processes
	cilk_sync;	
}
