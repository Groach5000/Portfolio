#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <bitset>

// **********************************************************
// NOTES:

// Garrett Roach
// Last Modified: Dec 11, 2013 12:22
// saved on thomas as: VirtMemSim.cpp
// loads file gcc.trace see line 52 if you want to change it

//***********************************************************

using namespace std;

int main(int argc, char* argv[]){
	
	int tdr = 0;
	int tdw = 0;
	int eit = 0;
	
	srand (time(NULL));
	
	string nframes = argv[1]; // number like 12 or 4
	string arg2 = argv[2];
	string tracefile = argv[3];
	int n = atoi(nframes.c_str());
	
	int LRUarray [3][n];
	int RANDarray [2][n];
	int FIFOarray [3][n];	
	
	int page_size = 4096;
	
	// Clear the arrays (this is extreamely important)
	// if you don't do this you might get different results each time.
	for(int a = 0; a<3; a++)
		for(int b=0; b<n; b++)
			LRUarray[a][b]=-1;
	for(int a = 0; a<3; a++)
		for(int b=0; b<n; b++)
			FIFOarray[a][b]=-1;
	for(int a = 0; a<2; a++)
		for(int b = 0; b<n; b++)
			RANDarray[a][b]=-1;
	
	// did not like setting file name to a variable 
	static const char filename[20] = {"gcc.trace"}; 
	int address; 
	int address_shifted;
	char mode; 
	
	FILE *file = fopen(filename, "r"); 
	if ( file != NULL ) { 
		while( fscanf(file, "%x %c", &address, &mode) != EOF) { 
			bitset<32> binary_address (address); // convert integer to binary number
			//cout << address << "   " << binary_address << "   "<< mode << endl;
			eit++;
			
			// print out with integer			
				//printf("data[%x] : %d\n", address, address);
			// print out with binary
				//cout << "data[" << address << hex << "]: " << binary_address << endl;
				address_shifted = address >> 12;
				//cout << "data[" << address << hex << "]: " << address_shifted << endl;
			
			if(arg2 == "rand"){ // do random replacement
				int found = 0;
				int location = 0;
				for(int i=0; i<n; i++){
					if(RANDarray[0][i] == address_shifted){
						found = 1;
						location = i;
						break;
					}
					else
						continue;	
				}
				if(found == 1){
					if (mode == 'w' || mode == 'W'){
						RANDarray[1][location]=1;
					}
				}
				else{
					location = rand() % n;
					if(RANDarray[1][location]==1)
						tdw++;
					tdr++;
					RANDarray[0][location] =address_shifted;
					if (mode == 'w' || mode == 'W'){
						RANDarray[1][location]=1;
					}
					else 
						RANDarray[1][location]=0;
				}
			}

			else if(arg2 == "lru"){ // do least recently used replacement
				int found = 0;
				int location = 0;
				for(int i=0; i<n; i++){
					if(LRUarray[0][i] == address_shifted){
						found = 1;
						location = i;
						break;
					}
				}
				if(found == 1){		
					if (mode == 'W' || mode == 'w'){	
						LRUarray[2][location]=1;
					}
					LRUarray[1][location] = eit;
					//cout<< "  " << LRUarray[0][location] << " " << LRUarray[1][location] << " " << LRUarray[2][location]<< endl;
				}
				else{
					
					// replace the one with lowest value of now-start
					int replace = 0;
					for(int j=0; j<n; j++){
						if(LRUarray[1][j] < LRUarray[1][replace])
							replace = j;
					}
					location = replace;
					if(LRUarray[2][location]==1){
						tdw++;
					}
					tdr++;					
					LRUarray[0][location] = address_shifted;
					LRUarray[1][location] = eit;
					if (mode == 'w' || mode == 'W'){
						LRUarray[2][location]=1;
					}
					else 
						LRUarray[2][location]=0;
						//cout<< "    " << LRUarray[0][location] << " " << LRUarray[1][location] << " " << LRUarray[2][location]<< endl;
				}
			}
			
			else if(arg2 == "fifo"){ // do First Come First Serve replacement
				int found = 0;
				int location = 0;
				for(int i=0; i<n; i++){
					if(FIFOarray[0][i] == address_shifted){
						found = 1;
						location = i;
						break;
					}
				}
				//cout << found << endl;
				if(found == 1){
					if (mode == 'W' || mode == 'w'){	
						FIFOarray[2][location]=1;
					}
					//cout<< "  " << FIFOarray[0][location] << " " << FIFOarray[1][location] << " " << FIFOarray[2][location]<< endl;
				}
				else{
					tdr++;
					// replace the one with lowest value of now-start
					int replace = 0;
					for(int j=0; j<n; j++){
						if(FIFOarray[1][j] < FIFOarray[1][replace])
							replace = j;
					}
					location = replace;
					if(FIFOarray[2][location]==1){
						tdw++;
					}
					FIFOarray[0][location] = address_shifted;
					FIFOarray[1][location] = eit;
					if (mode == 'w' || mode == 'W'){
						FIFOarray[2][location]=1;
					}
					else 
						FIFOarray[2][location]=0;
					//cout<< "     " << FIFOarray[0][location] << " " << FIFOarray[1][location] << " " << FIFOarray[2][location]<< endl;
				}
			}
			
			else{
				printf("Please use either rand, fifo, or lru for argument 2.\n");
				return 0;
			}
		} 
	} 
	cout << "total memory frames: " << n << endl;
	cout << "events in trace: " << eit << endl;
	cout << "total disk reads: " << tdr << endl;
	cout << "total disk writes: " << tdw << endl;

	return 0;
}

