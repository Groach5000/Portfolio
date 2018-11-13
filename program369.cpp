#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <math.h>
#include <iomanip>
using namespace std;

// Program for CS 308, problem number 2390
// Garrett Roach
// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=305

long double factorial (long double number){
    long double result = 1;
    for (long double i = 2; i <= number; i++)
    {
        result = result*i;
    }
    return result;
}
int main (){
	ifstream myfile;
	myfile.open ("test369.txt");
	if (myfile.is_open()){
		long double m, n;
		while (myfile >> m >> n && m!=0 && n!=0)
		{
			long double r = (factorial(m))/(factorial(m-n)*factorial(n));
			cout << m << " things taken " << n << " at a time is " << fixed << setprecision(0) << r << " exactly." << endl;
		}
	}
	else
		cout << "could not open file";
	return 0;
}