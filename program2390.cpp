#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

// Program for CS 308, problem number 2390
// Garrett Roach
// http://poj.org/problem?id=2390

int main (int argc, char * argv[]) {
	int R = 0;
	int M = 0;
	int Y = 0;
	ifstream myfile;
	myfile.open ("test2390.txt");
	if (myfile.is_open()){
		myfile >> R;
		myfile >> M;
		myfile >> Y;
		double year_answer = 0.0;
		int answer = 0;
		double money = M;
		for(int i = 0; i<Y;i++){
			money = (((static_cast<double>(R)/100)+1)*money);
		}
		double f = money;
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(0);
		cout << floor(f) << endl;
		
	}
	else
		cout << "could not open file";
	return 0;
}