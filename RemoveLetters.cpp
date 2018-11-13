#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

// Garrett Roach
// Remove letters from a string and save text
// last modified: April 2, 2014 @ 4:00 pm

int main (){
	ifstream text_file_read;
	text_file_read.open ("Letter.txt");
	if ( !text_file_read.is_open() )
		cout<<"***Could not open input file, you had one job...***\n";
	else {
		string message;
		string content( (istreambuf_iterator<char>(text_file_read) ),(istreambuf_iterator<char>()));
		cout << content << endl;
		message = content;
	
		string New_Message;
		cout << endl;
		int Times;
		cout << "how many splits? " << endl;
		cin >> Times;
		int x = 0;
		while( x<Times){
			int start = x;
			int stop = message.length();
			cout << stop << endl;
			while (start < stop){
					New_Message += message.at(start);
				start = start+Times;
			}
			cout << "message (" << x <<"):  " << New_Message << endl;
			cout << endl;
			New_Message = "";
			x++;
		}
	}
	return 0;
}
