#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

// Program for CS 308, problem number 2350
// Garrett Roach
// http://poj.org/problem?id=2350

int main (int argc, char * argv[]) {
	int n = 0;
	int number_of_scores = 0;
	double average = 0.000;
	ifstream myfile;
	myfile.open ("test2350.txt");
	if (myfile.is_open()){
		myfile >> n;
		for (int i = 0; i<n; i++){
			//cout << "hi";
			myfile >> number_of_scores;
			int score[number_of_scores];
			double total = 0;
			for(int j = 0; j<number_of_scores; j++){
				//cout << "here";
				int a_score = 0;
				myfile >> a_score;
				score[j]= a_score;
				total = total+a_score;
			}
			average = total/number_of_scores;
			//cout << average;	
			//cout << endl;
			int count_larger_than_average = 0;
			for(int j = 0; j<number_of_scores; j++){
				if(score[j]>average)
					count_larger_than_average++;
			}
			//cout << number_of_scores;
			//cout << count_larger_than_average;
			 double f = (static_cast<double>(count_larger_than_average)/static_cast<double>(number_of_scores))*100;
			cout.setf(ios::fixed,ios::floatfield);
			cout.precision(3);
			cout << f  << endl;
		}
	}
	else
		cout << "could not open file";
	return 0;
}