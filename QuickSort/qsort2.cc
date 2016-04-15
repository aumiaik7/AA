#include <stdio.h>
#include <iostream>
//#include "gettimeofday.h"
#include <cstdlib>
#include <cilk/cilk.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>

using namespace std;
void srand( unsigned seed ); 
void swap (int&, int&);

#define N 60000

void quickSort(int arr[],int left,int right);

int main ()
{ 
	//vector<int> number(N,0);
	int number[N];
	//long int number[N];
	int count;
	struct timeval  start, stop;
	//srand( time(NULL) );
	
	//number.reserve(N);
	for (count=0 ; count<N ; count++ )
	{
		number[count] = rand() % 100 + 1;
	    //printf ("%d, ", number[count]);
	}
	//start = wcgettimeofday();	
	gettimeofday(&start,NULL);
//	cout<<"Start Time"<<start.tv_usec<<endl;

	quickSort(number, 0, N-1);
	//stop = wcgettimeofday();
	//gettimeofday(&stop,NULL);
	cout<<"Start Time"<<start.tv_usec<<endl;

	cout<<"End Time"<<stop.tv_usec<<endl;
	printf("\n") ;
	
	for (count=0 ; count<N ; count++)
	{
		 printf ("%d, ", number[count]);
	}
	gettimeofday(&stop,NULL);

	double time = (stop.tv_sec+(double)stop.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000)	;	
	//printf("time = %g\n", 
	cout<<endl<<"Sorting done in "<<time<< " seconds"<<endl;
	
}

void quickSort(int arr[],int left,int right) {
      //if(left>right)
    	//  return;
//		int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
      //vector<int> leftVec(N,0);
      //vector<int> rightVec(N,0);
      //vector<int> midVec(N,0);
      int leftVec[N];
      int midVec[N];
      int rightVec[N];	 	
cout<<"There is is Pivot   ="<<pivot<<"there it is"<<endl;
      //vector<int>().swap(leftVec);
      //vector<int>().swap(rightVec);
      //vector<int>().swap(midVec);
      int k=0,l=0,m=0;
/*				
for(int a = 0; a< N ;a++)
{
	leftVec[a] = midVec[a] = rightVec[a] = 0;
}
*/	  
//arr[(left + right) / 2];
 

      //i = left - 1;
      //j = right + 1;
	/* partition */

	cout<<"left = "<<left<<" right = "<<right<<endl;
	#pragma cilk grainsize = N 
	cilk_for (int i = left; i<= right; i++) {
	    	if(arr[i] < pivot)
		{
			//leftVec.push_back(1);
			leftVec[k] = arr[i];
			k++;
		
		}

    	
	//leftVec.push_back(arr.at(i));

    		else if(arr[i] > pivot)
		{
			rightVec[m] = arr[i]; 
			m++;   	
		}

		else //if(arr[i] == pivot)
		{
			midVec[l] = arr[i];
		//	cout<<"a = "<<arr.at(i)<<" m="<<midVec.at(l)<<endl;
			l++;	
		}
    		//midVec.push_back(arr.at(i));
      }
	
/*
cout<<"k = "<<k<<" l = "<<l<<" m = "<<m<<endl;
for(int count = 0; count < k ;count++)
cout<<leftVec[count]<<" ";
cout<<endl;
for(int count = 0; count < l ;count++)
cout<<midVec[count]<<" ";
cout<<endl;
for(int count = 0; count < m ;count++)
cout<<rightVec[count]<<" ";
*/
//#pragma cilk grainsize = N*2

for (long int leftPart = 0; leftPart < k ; leftPart ++)
	arr[left+leftPart] =  leftVec[leftPart];
//#pragma cilk grainsize = N*2
for (long int midPart = 0; midPart < l; midPart++)
	arr[left+k+midPart] = midVec[midPart];
//#pragma cilk grainsize = N*2
for (long int rightPart = 0; rightPart < m; rightPart++)
	arr[left+k+l+rightPart] = rightVec[rightPart];


//if(k>0)k-=1;if(l>0)l-=1;if(m>0)m-=1;
      //rightVec.push_back(pivot);
    //leftVec.push_back(pivot);
   //vector<int>().swap(set1); 
//   vector<int> set1(k+l);
//`if(k>0)k-=1;if(l>0)l-=1;if(m>0)m-=1;

    //set1.reserve(leftVec.size()+midVec.size());
    //set_union( leftVec.begin(), leftVec.begin()+k,midVec.begin(), midVec.begin()+l, set1.begin() );
    //set_union( set1.begin(), set1.end(),rightVec.begin(), rightVec.begin()+m, arr.begin()+left );
//	vector<int>().swap(set1);   
   /* recursion  */

  if (k > 1)
          {
	        //cilk_spawn
	       long int r = k+left;
		//if(k>0)
		//   r -= 1; 
//		cilk_spawn 
		quickSort(arr, left, r-1 );
	  }	
      //if ((right - rightVec.size()-1) <right)
	  //if (rightVec.size() > 1)
	  if(m>1)
	  {
		//int l = left+leftVec.size()+midVec.size();
		long int lf = left+k+l;
	//	if(leftVec.size()>0)
	//	   l-=1;
        //        if(midVec.size()>0)
	//	  l-=1;	
            quickSort(arr, lf , right);
		
	//	cilk_sync;
	}	//*/
	
}

void swap(int& a, int& b)
{
	
int temp;
	temp = a;
	a = b;
	b = temp;
}
