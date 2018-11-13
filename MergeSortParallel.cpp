#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <math.h>
#include <strstream>
#include "mpi.h" // message passing interface
#include <stdlib.h>     /* qsort */

// Merge sort in parallel (really bad)
// Garrett and Aaron

using namespace std;

int my_rank;
int p;

void merge(unsigned long int*, unsigned long int*, int, int, int);

void pmerge(unsigned long int*, unsigned long int*, int, int, int);

void swap(unsigned long int &a, unsigned long int &b){
	unsigned long int temp = a;
	a=b;
	b=temp;
}
unsigned long int n;
unsigned long int * c = new unsigned long int[n];


//returns the index of an item in an array
unsigned long int binRank (unsigned long int *A, long int N, long int tarVal){
	long int Mid,Lbound=0,Ubound=N-1, index;
	
	while(Lbound<=Ubound)
	{
		Mid=(Lbound+Ubound)/2;
		if(tarVal==A[Mid]){
			index = Mid;
			return index;
		}else if(tarVal>A[Mid]){
			Lbound=Mid+1;
			index = Lbound;
		}else if(tarVal<A[Mid]){
			Ubound = Mid-1;
			index = Ubound+1;
		}
	
	}
	return index;
}

// Main merge sort
void mergesort(unsigned long int *a, unsigned long int*b, int start, int end) {
	int halfpoint;
	
	
	// 1 base case
	if ((end-start) == 0)
		return;
	
	// 2 base case
	if ((end-start) == 1){
		if(a[start] > a[end])
			swap(a[start], a[end]);
	}
	
	// 3 base case
	if((end-start) == 2){
		if(a[start]>a[start+1])
			swap(a[start], a[start+1]);
		if(a[start+1]>a[end])
			swap(a[start+1], a[end]);
		if(a[start]>a[start+1])
			swap(a[start], a[start+1]);
	}
	
	//4 base case
	if((end-start) == 3){
		if(a[start]>a[start+1])
			swap(a[start], a[start+1]);
		if(a[start+2]>a[end])
			swap(a[start+2], a[end]);
		if(a[start]>a[start+2])
			swap(a[start], a[start+2]);
		if(a[start+1]>a[end])
			swap(a[start+1], a[end]);
		if(a[start+1]>a[start+2])
			swap(a[start+1], a[start+2]);
	}
	
	// 5 base case
	
	if((end-start) == 4){
		if(a[start]>a[start+1])
			swap(a[start], a[start+1]);
		if(a[start+2]>a[start+3])
			swap(a[start+2], a[start+3]);
		if(a[start]>a[start+2]){
			swap(a[start], a[start+2]);
			swap(a[start+1], a[start+3]);
			}
		if(a[end]>a[start+2]){
			if(a[end]>a[start+3]){
				if(a[start+1]>a[start+3]){
					if(a[start+1]>a[end]){
						swap(a[start+1], a[start+2]);
						swap(a[start+2], a[start+3]);
						swap(a[start+3], a[end]);
						//return(a[start], a[start+2], a[start+3], a[end], a[start+1]);
					}
					else{
						swap(a[start+1], a[start+2]);
						swap(a[start+2], a[start+3]);
						//return(a[start], a[start+2], a[start+3], a[start+1], a[end]);
					}
				}
				else{
					if(a[start+1]<a[start+2]){
						return;
						//return(a[start], a[start+1], a[start+2], a[start+3], a[end]);
					}
					else{
						swap(a[start+1], a[start+2]);
						//return(a[start], a[start+2], a[start+1], a[start+3], a[end]);
					}
				}
			}
			else{
				if(a[start+1]>a[end]){
					if(a[start+1]>a[start+3]){
						swap(a[start+1], a[start+2]);
						swap(a[start+2], a[end]);
						//return(a[start], a[start+2], a[end], a[start+3], a[start+1]);
					}
					else{
						swap(a[start+1], a[start+2]);
						swap(a[start+2], a[end]);
						swap(a[end], a[start+3]);
						//return(a[start], a[start+2], a[end], a[start+1], a[start+3]);
					}
				}
				else{
					if(a[start+1]<a[start+2]){
						swap(a[start+3], a[end]);
						//return(a[start], a[start+1], a[start+2], a[end], a[start+3]);
					}
					else{
						swap(a[start+1], a[start+2]);
						//return(a[start], a[start+2], a[start+1], a[end], a[start+3]);
					}
				}
			}
		}
		else{
			if(a[end]<a[start]){
				if(a[start+1]>a[start+2]){
					if(a[start+1]>a[start+3]){
						swap(a[start], a[start+1]);
						swap(a[end], a[start]);
						//return(a[end], a[start], a[start+2], a[start+3], a[start+1]);
					}	
					else{
						swap(a[start], a[start+1]);
						swap(a[end], a[start]);
						swap(a[end], a[start+3]);
						//return(a[end], a[start], a[start+2], a[start+1], a[start+3];
					}	
				}
				else{
					swap(a[start], a[start+1]);
					swap(a[end], a[start]);
					swap(a[end], a[start+3]);
					swap(a[start+3], a[start+2]);
					//return(a[end], a[start], a[start+1], a[start+2], a[start+3]);
				}
			}
			else{
				if(a[start+1]>a[start+2]){
					if(a[start+1]>a[start+3]){
						swap(a[start+1], a[end]);
						//return(a[start], a[end], a[start+2], a[start+3], a[start+1]);
					}
					else{
						swap(a[start+1], a[end]);
						swap(a[start+3], a[end]);
						//return(a[start], a[end], a[start+2], a[start+1], a[start+3]);
					}
				}
				else{
					if(a[start+1]<a[end]){
						swap(a[start+3], a[end]);
						swap(a[start+2], a[start+3]);
						//return(a[start], a[start+1], a[end], a[start+2], a[start+3]);
					}
					else{
						swap(a[start+1], a[end]);
						swap(a[start+3], a[end]);
						swap(a[start+2], a[start+3]);
						//return(a[start], a[end], a[start+1], a[start+2], a[start+3]);
					}
				}
			}
		}		
	}
	
	//6 base case
	if((end-start) == 5){  // takes 12 comparisons 
	
		if(a[start]>a[start+1])
			swap(a[start], a[start+1]);
		if(a[start+2]>a[start+3])
			swap(a[start+2], a[start+3]);
		if(a[start+4]>a[end])
			swap(a[start+4], a[end]);
		// end of first 3 comparisons
	
		if(a[start]>a[start+2])
			swap(a[start], a[start+2]);
		if(a[start+2]>a[start+4])
			swap(a[start+2], a[start+4]);
		if(a[start]>a[start+2])
			swap(a[start], a[start+2]);
			
		if(a[start+1]>a[start+3])
			swap(a[start+1], a[start+3]);
		if(a[start+3]>a[end])
			swap(a[start+3], a[end]);
		if(a[start+1]>a[start+3])
			swap(a[start+1], a[start+3]); 
		// end of next 6 comparisons

		if(a[start+1]> a[start+2])
			swap(a[start+2], a[start+1]);
		if(a[start+3]> a[start+4])
			swap(a[start+3], a[start+4]);
		if(a[start+2]> a[start+3])
			swap(a[start+3], a[start+2]);
		// end of next 3 comparisons

	}
	
	
	if (start < end) {
		halfpoint = (start + end) / 2;
		mergesort(a, b, start, halfpoint);
		mergesort(a, b, halfpoint + 1, end);
		//merge(a, b, start, halfpoint, end); // change to pmerge(a, b, start, halfpoint, end);
		pmerge(a, b, start, halfpoint, end);
	}
	
}

//Merge Function
void merge(unsigned long int *a, unsigned long int *b, int start, int halfpoint, int end) {
	int h, i, j, k;
	h = start;
	i = start;
	j = halfpoint + 1;

	
	
	while ((h <= halfpoint) && (j <= end)) {
		if (a[h] <= a[j]) {
			b[i] = a[h];
			h++;
		} else {
			b[i] = a[j];
			j++;
		}
		i++;
	}// End While
	if (h > halfpoint) {
		for (k = j; k <= end; k++) {
		b[i] = a[k];
		i++;
    }// End for
	} else {
		for (k = h; k <= halfpoint; k++) {
			b[i] = a[k];
			i++;
		}
	}
  // Write the final sorted array to our original one
	for (k = start; k <= end; k++) 
		a[k] = b[k];

}
 void quickSort(unsigned long arr[], int left, int right)
 {
  int i = left, j = right;
  int tmp;
  int pivot = arr[(left + right) / 2];

  /* partition */
  while (i <= j) {
        while (arr[i] < pivot)
              i++;
        while (arr[j] > pivot)
              j--;
        if (i <= j) {
              tmp = arr[i];
              arr[i] = arr[j];
              arr[j] = tmp;
              i++;
              j--;
    }
}
/* recursion */
if (left < j)
    quickSort(arr, left, j);
if (i < right)
        quickSort(arr, i, right);
}

//pmerge function
void pmerge(unsigned long int *a, unsigned long int *b, int start, int halfpoint, int end) {


	
	/*cout << "______________________________" << endl;
	cout<< endl;
	cout<< "start = " <<start;
	cout<< "end = " <<end+1;
	cout<< endl;*/
	//cout << "______________________________" << endl;
	
	unsigned long int size = end-start+1;
	// cout<< endl;
	// cout<< "size = " <<size;  
	// cout<< endl;
	double halfsize = (size/2.0); 
	// cout<< endl;
	// cout<< "halfsize = " <<halfsize;
	// cout<< endl;
	unsigned long int fsize = floor(halfsize);
	unsigned long int csize = ceil(halfsize);
	// cout<< "fsize = " <<fsize;
	// cout<< "csize = " <<csize;
	// cout<< endl;
	unsigned long int * lhs = new unsigned long int[fsize];
	unsigned long int * rhs = new unsigned long int[csize];

	// for(int c=start; c<end+1; c++)
		// cout << "a = " << a[c] << " ";
	// cout<< endl;
	// cout<< "size = " <<size;
	// cout<< endl;
	// cout<< "halfpoint = " << a[halfpoint] << endl;
	if(size%2 != 0){
		if(a[halfpoint] <= a[halfpoint+1]){
			for(int c=0; c<fsize; c++)
				lhs[c] = a[start+c];
			for(int c = 0; c<csize; c++)
				rhs[c] = a[halfpoint+c];
			}
		else{
			for(int c = 0; c<csize; c++)
				rhs[c] = a[start+c];
			for(int c=0; c<fsize; c++)
				lhs[c] = a[halfpoint+1+c];
			
		}
	}
	else{
		for(int c=0; c<fsize; c++)
			lhs[c] = a[start+c];
		if(size%2 == 0){	
			for(int c = 0; c<csize; c++)
				rhs[c] = a[halfpoint+1+c];
		}
		else{
			for(int c = 0; c<csize; c++)
				rhs[c] = a[halfpoint+c];
		}
	}
	int n = end+1;
	int n2 = n/2;
	double LOGN=0;
	if(csize>=3){
		LOGN = (log (csize)) / (log(2.0));
	}else{
		LOGN = 1;
	}
	
	int sizearank;
	int sizebrank;
	if(fsize>2){
		sizearank = ceil(log(fsize)/log(2.0));
	}else{
		sizearank = 1;
	}
	if(csize>2){
		sizebrank = ceil(log(csize)/log(2.0));
	}else{
		sizebrank = 1;
	}
	// cout << " sizearank is : " << sizearank << endl;
	// cout << " sizearank is : " << sizebrank << endl;
	int NcsizeLOGN;
	int NfsizeLOGN;
	if(sizearank>1){
		NcsizeLOGN = ceil((double)csize/sizebrank);
	}else{
		NcsizeLOGN = 1;
	}
	if(sizebrank>1){
		NfsizeLOGN = ceil((double)fsize/sizebrank);
	}else{
		NfsizeLOGN = 1;
	}
	
	unsigned long * l_arank = new unsigned long[fsize];
	unsigned long * l_brank = new unsigned long[csize];
	
	for(int c=0; c<fsize; c++)
		l_arank[c]=0;
	for(int c=0; c<csize; c++)
		l_brank[c]=0;
		
	// cout << "lhs = ";
	// for (int i = 0; i < fsize ; i++){
		// cout << lhs[i] << " ";
	// }
	// cout << endl;
	// cout << "rhs = ";
	// for (int i = 0; i < csize; i++){
		// cout << rhs[i] << " ";
	// }
	// cout << endl;
	MPI_Barrier(MPI_COMM_WORLD);
	
	int lstart = my_rank*sizearank;
	//cout << "floor logn = " << floor(LOGN) << endl;
	//cout << "ceil logn = " << ceil(LOGN) << endl;
	for(int i=lstart; i < fsize; i += (p*sizearank)){
		l_arank[i] = binRank(rhs, csize, lhs[i]);
	}

	for(int i=lstart; i < csize; i += (p*sizebrank)){
		l_brank[i] = binRank(lhs, fsize, rhs[i]);
	}

	unsigned long * arank = new unsigned long[fsize];
	unsigned long * brank = new unsigned long[csize];
	
	for(int c=0; c<fsize; c++)
		arank[c]=0;
	for(int c=0; c<csize; c++)
		brank[c]=0;
	
	MPI_Allreduce(l_arank, arank, fsize, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(l_brank, brank, csize, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
	//MPI_Bcast(arank, fsize, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
	//MPI_Bcast(brank, csize, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
	
	// cout << "l_arank = ";
	// for (int i = 0; i < fsize; i++)
		// cout << l_arank[i] << " ";
	// cout << endl;
	// cout << "l_brank = ";
	// for (int i = 0; i < csize; i++)
		// cout << l_brank[i] << " ";
	// cout << endl;
	
	// cout << "arank = ";
	// for (int i = 0; i < fsize; i++)
		// cout << arank[i] << " ";
	// cout << endl;
	// cout << "brank = ";
	// for (int i = 0; i < csize; i++)
		// cout << brank[i] << " ";
	// cout << endl;
	
	unsigned long * Shortarank = new unsigned long[NfsizeLOGN];
	unsigned long * Shortbrank = new unsigned long[NcsizeLOGN];
	unsigned long * Itemsarank = new unsigned long[NfsizeLOGN];
	unsigned long * Itemsbrank = new unsigned long[NcsizeLOGN];
	
	//cout<< "Try"<< endl;

	
	
	int countshortA=0;
	// send a rank into a condenced array
	//cout << "shortarank = ";
		// for(int i=0; i < sizearank; i++){
			// Shortarank[i]=arank[i*sizearank];
			// cout << Shortarank[i] << " ";
		// }	
	// }

	for(int i=0; i < fsize; i += (sizearank)){
		Shortarank[countshortA]= arank[i];
		//cout<< Shortarank[countshortA] << " ";
		countshortA++;
	}
	// send b rank into a condenced array
	//cout << endl;
	int countshortB=0;
	//cout << "shortbrank = ";
	for(int i=0; i < csize; i += (sizebrank)){
		Shortbrank[countshortB]= brank[i];
		//cout<< Shortbrank[countshortB] << " ";
		countshortB++;
	}
	
	
	int countItemA=0;
	//cout << endl;
	// Get lhs items
	//cout << "Itemsarank = ";
	for(int i=0; i < fsize; i += (sizearank)){
		Itemsarank[countItemA]=i;
		//cout << Itemsarank[countItemA] << " ";
		countItemA++;
	}

	
	

	//cout << endl;
	// Get rhs items
	//cout << "Itemsbrank = ";
	int countItemB=0;
	for(int i=0; i < csize; i += (sizebrank)){
		Itemsbrank[countItemB]=i;
		//cout << Itemsbrank[countItemB] << " ";
		countItemB++;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	
	cout << endl;
	// Make a single array with Shortarank in front and Itemsbrank in back
	unsigned long * Adiv = new unsigned long[countItemA+countshortB];
	unsigned long * AdivSort = new unsigned long[countItemA+countshortB];
			for(int c=0; c<countItemA+countshortB; c++)
				AdivSort[c]=0;
	for(int i=0; i < countshortB; i++){
		Adiv[i]=Shortbrank[i];
	}	
	for(int i=0; i < countItemA; i++){
		Adiv[i+countshortB]=Itemsarank[i];
	}	
	// cout << "Adiv = ";
	// for(int y=0; y<(countItemA+countshortB); y++)
		// cout<< Adiv[y] << " ";
	// cout << endl;
	
	// Merge Sort
	if((countItemA+countshortB)%2 == 0)
		merge(Adiv, AdivSort, 0, floor((countItemA+countshortB)/2.0)-1, ((countItemA+countshortB))-1);
	else
		if(countItemA<countshortB)
			merge(Adiv, AdivSort, 0, countshortB-1, ((countItemA+countshortB))-1);
		else
			merge(Adiv, AdivSort, 0, ceil((countItemA+countshortB)/2.0)-1, ((countItemA+countshortB))-1);
	quickSort(Adiv, 0, ((countItemA+countshortB))-1);	
	// do not think I did the merge sort function correctly
	
	// cout << "Adiv Sorted = ";
	// for(int y=0; y<(countItemA+countshortB); y++){
		// cout<< Adiv[y] << " ";
		// }
	// cout << endl;
	// cout << "c()divide by 2 = " << ceil((countItemA+countshortB)/2.0) << endl;
	// cout << "cdivide by 2 = " << ceil(countItemA+countshortB)/2.0 << endl;
	// cout << " normal = " << countItemA+countshortB << endl;
	
	// Make a single array with Shortbrank in front and Itemsarank in back
	unsigned long * Bdiv = new unsigned long[countItemB+countshortA];
	unsigned long * BdivSort = new unsigned long[countItemB+countshortA];
		for(int c=0; c<countItemB+countshortA; c++)
			BdivSort[c]=0;
	for(int i=0; i < countItemB; i++){
		Bdiv[i+countshortA]=Itemsbrank[i];
	}
	for(int i=0; i < countshortA; i++){
		Bdiv[i]=Shortarank[i];
	}
	// cout << "Bdiv = ";
	// for(int y=0; y<(countItemB+countshortA); y++){
		// cout<< Bdiv[y] << " ";
		// }
	// cout << endl;
	
	// Merge Sort
	
	if((countItemB+countshortA)%2 == 0)
		merge(Bdiv, BdivSort, 0, floor((countItemB+countshortA)/2.0)-1, ((countItemB+countshortA))-1);
	else{
		merge(Bdiv, BdivSort, 0, ceil((countItemB+countshortA)/2.0)-1, ((countItemB+countshortA))-1);
	}	
	quickSort(Bdiv, 0, ((countItemB+countshortA))-1);	
	//for(int d=0; d<(countItemB+countshortA); d++)
	//	if(Bdiv[d]>Bdiv[d+1])
	//		swap(Bdiv[d],Bdiv[d+1]);
		
	// do not think I did the merge sort function correctly
	
	// cout << "Bdiv Sorted = ";
	// for(int y=0; y<(countItemB+countshortA); y++)
		// cout<< Bdiv[y] << " ";
	// cout << endl;
	
	unsigned long * c = new unsigned long[n];
	for (int x = 0; x < (end+1); x++)
		c[x] = 0;
	for (int x = 0; x < (end+1); x++)
		b[x] = 0;
		

	unsigned long int shapelengthB;
	unsigned long int shapelengthA;
	unsigned long int shapelengthTotal=ceil(sizearank+sizebrank);

	//cout << "shapelengthTotal is " << shapelengthTotal << endl;
	
	MPI_Barrier(MPI_COMM_WORLD);
	for (int i = my_rank; i < ceil((countItemA+countshortB+countItemB+countshortA)/2)-1; i += p) {

		if (i == ceil((countItemA+countshortB+countItemB+countshortA)/2)-2) {
				shapelengthA = fsize-Adiv[i];
				shapelengthB = csize- Bdiv[i];

			//cout << "shape " << Adiv[i] << endl;
			//cout << "shape " << Bdiv[i] << endl;
		} // end if
		else{
				shapelengthA = Adiv[i+1] - Adiv[i];
				shapelengthB = Bdiv[i+1] - Bdiv[i];
		}
		//cout << "P " << my_rank << ": shapelengthA " << shapelengthA << endl;
		//cout << "P " << my_rank << ": shapelengthB " << shapelengthB << endl;
		unsigned long * minimerge = new unsigned long[shapelengthA+shapelengthB];
		int j;
		for (j=0; j < shapelengthA; j++)
			minimerge[j] = lhs[Adiv[i]+j];
		for (j=0; j < shapelengthB; j++)
			minimerge[j+shapelengthA] = rhs[Bdiv[i]+j];
		//cout << "P " << my_rank << ": minimerge ";
		//for (int x = 0; x < shapelengthA+shapelengthB; x++)
			//cout << minimerge[x] << " ";
		//cout << endl;
		
		if((size)%2 == 0 )
			merge(minimerge, &c[Adiv[i]+Bdiv[i]], 0, shapelengthA-1, shapelengthA+shapelengthB-1);
		else
			merge(minimerge, &c[Adiv[i]+Bdiv[i]], 0, shapelengthA-1, shapelengthA+shapelengthB-1);
		
		delete [] minimerge;
		
	} // end for


	MPI_Allreduce(c, b, n, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);
	
	//cout << "P " << my_rank << ": b ";
	//for (int x = 0; x < (end+1); x++)
		//cout << b[x] << " ";
	//cout << endl;

	unsigned long g=0;
	for(int c=start; c<end+1; c++){
		a[c]=b[g];
		g++;
		//cout << "a = " << a[c] << " ";
	}
	
	//cout << my_rank << " Made it here!" << endl;
	delete [] Itemsarank;
	delete [] Itemsbrank;
	delete [] Shortarank;
	delete [] Shortbrank;
	delete [] arank;
	delete [] brank;
	delete [] l_arank;
	delete [] l_brank;
	delete [] lhs;
	delete [] rhs;
	delete [] Bdiv;
	delete [] Adiv;
	delete [] BdivSort;
	delete [] AdivSort;
	delete [] c;
	//delete [] AandBcombine;
}


int main (int argc, char * argv[]) {

	int source;				// rank of the sender
	int dest;				// rank of destination
	int tag = 0;			// message number
	MPI_Status status;		// return status for receive
	
	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// Find out the number of processes!
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	// THE REAL PROGRAM IS HERE
	
	// Know the problem parameters.
	unsigned long int * a;
	unsigned long int * g;
	unsigned long int * b;
	//srand(1251);

	//fill arrays
	// read from text file
	string line;
	ifstream myfile;
	myfile.open ("fileName1.txt");
	if (myfile.is_open()){
		myfile>>n;
		a = new unsigned long int[n];
		b = new unsigned long int[n];
		g = new unsigned long int[n];
		for (int x = 0; x < n; x++)
			myfile >> g[x];
		cout << " " << endl;
		//cout << "The position of x is : " << binSearch(a, n, 6) << endl;
		
	}
	else 
		cout <<"I hate this project" << endl;
	myfile.close();
	cout << "n = "<< n << endl;
	cout << endl;
		
		
	for(long int i =0; i <(n); i++){
		a[i] = g[i];
	}

		
	mergesort(a, b, 0, n-1);	
		
	// Print the sorted array
	if(my_rank==0){
		cout << endl;
		for (int i = 0; i < (n); i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	
	// Save sorted array into a new text file
	
	
	
	unsigned long int d =0;
	
	ofstream myfile2;
	myfile2.open ("PmergeResults.txt");
	if (myfile2.is_open()){
		myfile2 <<n << endl;
		for (int x = 0; x < (n); x++){
			d=a[x];
			myfile2 << d << endl;
			}
	}
	else 
		cout <<"I hate this project" << endl;
	myfile2.close();
	}
	// Shut down MPI
	delete [] a;
	delete [] b;
	delete [] g;
	MPI_Finalize();

	return 0;
}





