#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

//************************
// Garrett and Aaron
// Last modified March 17, 2014, 4pm
// Notes: All work, If use keyword with spaces, you have to typewithoutthem
//	Add: remove spaces from input keywords
//************************
void createVigenereTable();
void save_file (string message);
void Shift_Encryp(string message);
void Shift_Decryp(string message);
void Affine_Encryp(string message);
void Affine_Decryp(string message);
void Substitution_Encryp(string message);
void Substitution_Decryp(string message);
void Vigenere_Encryp(string message);
void Vigenere_Decryp(string message);
void get_method();
void do_ciphering(string message);

bool repeat_letter(string New_key_word, int position, char letter);

string file_name;
int key = 0;
string key_word;
int Cipher_method;
int Action;
int b=0;

char vigenereTableLow[26][26];
char vigenereTableCap[26][26];

char ALPHCap[26]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char ALPHLow[26]= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

// 65-90 cap
// 97-122 lower
int main (int argc, char* argv[])
{	
	string message;
	char text_file_in[50];
	cout << "Please input the name of your input text file: " << endl;
	cin >> text_file_in;
	//cout << text_file_in << endl;
	char text_file_out[50];
	cout << "Please input the name of file you wish to save to: " << endl;
	cin >> text_file_out;
	file_name = text_file_out;
	ifstream text_file_read;
	text_file_read.open (text_file_in);
	if ( !text_file_read.is_open() )
		cout<<"***Could not open input file, you had one job...***\n";
	else {
		// save content of input file  to string 'content'
		string content( (istreambuf_iterator<char>(text_file_read) ),(istreambuf_iterator<char>()));
		cout << content << endl;
		message = content;
	}
	get_method();
	do_ciphering(message);	
	return 0;
}

void do_ciphering(string message){
	if(Cipher_method == 1){
		// function Shift
		cout << "Please input the key: " << endl;
		cin >> key;
		if(Action == 1){	// Decryption
			Shift_Encryp(message);
		}
		else if(Action == 2){	// Encryption
			Shift_Decryp(message);
		}
		else{
			cout << "still only had one job..." << endl;
		}
	}
	else if(Cipher_method == 2){
		// function Substitution
		cout << "Please input the key word: " << endl;
		cin >> key_word;
		if(Action == 1){	// Decryption
			Substitution_Encryp(message);
		}
		else if(Action == 2){	// Encryption
			Substitution_Decryp(message);
		}
		else{
			cout << "still only had one job..." << endl;
		}			
	}
	else if(Cipher_method == 3){
		// function Affine
		cout << "For the function y=(kx+b)%26 please input: " << endl;
		cout<< "k = ";
		cin >> key;
		cout << endl;
		cout << "b = ";
		cin >> b;
		cout << endl;
		if(Action == 1){	// Decryption
			Affine_Encryp(message);
		}
		else if(Action == 2){	// Encryption
			Affine_Decryp(message);
		}
		else{
			cout << "still only had one job..." << endl;
		}	
	}
	else if(Cipher_method == 4){
		// function Vigenere
		createVigenereTable();
		cout << "Please input the key word: " << endl;
		cin >> key_word;
		
		if(Action == 1){	// Decryption
			Vigenere_Encryp(message);
		}
		else if(Action == 2){	// Encryption
			Vigenere_Decryp(message);
		}
		else{
			cout << "still only had one job..." << endl;
		}		
	}
	else{
		cout << "You had one job..." << endl;
	}
}
	
void save_file (string message)
{
	ofstream out_stream;
	//char file[100];
	//for(int k=0; k< file_name.length(); k++)
	//	file[k]= file_name.at(k);
	out_stream.open(file_name.c_str()); // change back to file when done
	out_stream << message << endl;
	out_stream.close();
	cout << "File saved." << endl;
}

void get_method(){
	cout << "Which Cipher are you using:" << endl;
	cout<< "For Shift press 1."<<endl;
    cout<< "For Substitution press 2."<<endl;
	cout<< "For Affine press 3."<<endl;
    cout<< "For Vigenere press 4."<<endl;
	cin >> Cipher_method;
	cout << "Decrypt or Encrypt:" << endl;
	cout<< "For Encryption press 1."<<endl;
	cout<< "For Decryption press 2."<<endl;
	cin >> Action;
}

void Shift_Encryp (string message)
{
		string coded_message="";
		int encrypt = 0;
        for (int k=0; k<message.length(); k++)
        {
			//cout << message.at(k) << endl;
			if(message.at(k) >= 97 && message.at(k) <= 122){
				encrypt = message.at(k);
				coded_message += (((encrypt-97)+key)%26)+97;
				
			}
			else if(message.at(k) >= 65 && message.at(k) <= 90){
				encrypt = message.at(k);
				//cout << (((encrypt-65)+key)%26)+65 << endl;
				coded_message += (((encrypt-65)+key)%26)+65;
			}
			else{
				coded_message += message.at(k);
			}
			//cout << coded_message.at(k) << endl;
        }
        save_file(coded_message);
}
void Shift_Decryp(string message)
{
		string decoded_message;
		int decrypt = 0;
        for (int k=0; k<message.length(); k++)
        {
			if(message.at(k) >= 97 && message.at(k) <= 122){
				decrypt = message.at(k);
				decoded_message+= (((decrypt-97)+(26-key))%26)+97;
			}
			else if(message.at(k) >= 65 && message.at(k) <= 90){
				decrypt = message.at(k);
				decoded_message+= (((decrypt-65)+(26-key))%26)+65;
			}
			else{
				decoded_message+= message.at(k);
			}
        }
		cout << decoded_message << endl;
        save_file(decoded_message);
}
void Affine_Encryp(string message){
	string coded_message="";
	int encrypt = 0;
	for (int k=0; k<message.length(); k++)
    {	
	//cout << message.at(k) << endl;
		if(message.at(k) >= 97 && message.at(k) <= 122){
			encrypt = message.at(k);
			coded_message += ((((encrypt-97)*key)+b)%26)+97;
			
		}
		else if(message.at(k) >= 65 && message.at(k) <= 90){
			encrypt = message.at(k);
			//cout << (((encrypt-65)+key)%26)+65 << endl;
			coded_message += ((((encrypt-65)*key)+b)%26)+65;
		}
		else{
			coded_message += message.at(k);
		}
		//cout << coded_message.at(k) << end
	}
	
	save_file(coded_message);
}
void Affine_Decryp(string message){
	string decoded_message;
	int key_inverse = 0;
	int decrypt = 0;
	int key_inv[2][12] =
    {
        {1,3,5,7,9, 11, 15, 17, 19, 21, 23, 25},
        {1,9,21,15,3,19, 7, 23, 11, 5, 17, 25}
    };
	for(int i = 0; i<12; i++){
		if(key_inv[0][i] == key)
			key_inverse = key_inv[1][i];
	}
	//cout << "key_inverse: " << key_inverse << endl;
	for (int k=0; k<message.length(); k++)
    {
		if(message.at(k) >= 97 && message.at(k) <= 122){
			decrypt = message.at(k);
			decoded_message+= ((((decrypt-97)+26-b)*key_inverse)%26)+97;
		}
		else if(message.at(k) >= 65 && message.at(k) <= 90){
			decrypt = message.at(k);
			decoded_message+= ((((decrypt-65)+26-b)*key_inverse)%26)+65;
		}
		else{
			decoded_message+= message.at(k);
		}
	}
	save_file(decoded_message);
}
void Substitution_Encryp(string message){
	string coded_message="";
	string new_key_word="";
	for(int i =0; i< key_word.length(); i++){
		if(repeat_letter(new_key_word, i, key_word.at(i))!=true){
			new_key_word+= key_word.at(i);
		}
	}
	
	string key_word_Cap= "";
	for(int t = 0; t<new_key_word.length(); t++){
		key_word_Cap += toupper(new_key_word.at(t));
	}

	int alphabet_position = 0;
	double norm_rows = (26.0/new_key_word.length());
	int rows = ceil(norm_rows);
	//rows++;
	cout << rows << endl;
	cout << new_key_word << endl;
	char ** cipher_array = new char * [rows];
	for(int x=0; x<rows; x++){
		cipher_array[x] = new char[new_key_word.length()];
	}
	
	cout << key_word_Cap << endl;
	for(int i = 0; i<rows; i++){
		for(int k = 0; k<new_key_word.length(); k++){
			if(i==0){
				cipher_array[i][k]=key_word_Cap.at(k);
			}
			else{
				for(int j= alphabet_position; j<26; j++){
					if(repeat_letter(key_word_Cap, new_key_word.length(), ALPHCap[j])!=true){
						cipher_array[i][k]=ALPHCap[j];
						alphabet_position +=1;
						break;
					}else{
						alphabet_position +=1;
					}
				}
			}
		}
	}
	char Das_array_to_use_upper[26];
	char Das_array_to_use_lower[26];
	int count=0;
	for(int i = 0; i<rows; i++){
		for(int k = 0; k<new_key_word.length(); k++){
			Das_array_to_use_upper[count]=cipher_array[i][k];
			Das_array_to_use_lower[count]= tolower(cipher_array[i][k]);
			cout << Das_array_to_use_lower[count] << " ";
			count++;
		}
		cout << endl;
	}
	
	char cipher;
	for(int k =0; k<message.length(); k++){
		cipher = message.at(k);
		if(message.at(k) >= 97 && message.at(k) <= 122){
			cipher = message.at(k);
			coded_message += Das_array_to_use_lower[cipher-97];
		}
		else if(message.at(k) >= 65 && message.at(k) <= 90){
			cipher = message.at(k);
			coded_message += Das_array_to_use_upper[cipher-65];
		}
		else{
			coded_message+= message.at(k);
		}
		
	
	}
	cout << coded_message << endl;
	
	save_file(coded_message);
}
void Substitution_Decryp(string message){
	string decoded_message;
	string new_key_word="";
	for(int i =0; i< key_word.length(); i++){
		if(repeat_letter(new_key_word, i, key_word.at(i))!=true){
			new_key_word+= key_word.at(i);
		}
	}
	
	string key_word_Cap= "";
	for(int t = 0; t<new_key_word.length(); t++){
		key_word_Cap += toupper(new_key_word.at(t));
	}

	int alphabet_position = 0;
	double norm_rows = (26.0/new_key_word.length());
	int rows = ceil(norm_rows);
	
	cout << rows << endl;
	cout << new_key_word << endl;
	
	char ** cipher_array = new char * [rows];
	for(int x=0; x<rows; x++){
		cipher_array[x] = new char[new_key_word.length()];
	}
	
	cout << key_word_Cap << endl;
	for(int i = 0; i<rows; i++){
		for(int k = 0; k<new_key_word.length(); k++){
			if(i==0){
				cipher_array[i][k]=key_word_Cap.at(k);
			}
			else{
				for(int j= alphabet_position; j<26; j++){
					if(repeat_letter(key_word_Cap, new_key_word.length(), ALPHCap[j])!=true){
						cipher_array[i][k]=ALPHCap[j];
						alphabet_position +=1;
						break;
					}else{
						alphabet_position +=1;
					}
				}
			}
		}
	}
	
	char Das_array_to_use_upper[26];
	char Das_array_to_use_lower[26];
	
	int count=0;
	for(int i = 0; i<rows; i++){
		for(int k = 0; k<new_key_word.length(); k++){
			Das_array_to_use_upper[count]=cipher_array[i][k];
			Das_array_to_use_lower[count]= tolower(cipher_array[i][k]);
			cout << Das_array_to_use_lower[count] << " ";
			count++;
		}
		cout << endl;
	}
	
	char decipher;
	for(int k =0; k<message.length(); k++){
		decipher = message.at(k);
		if(message.at(k) >= 97 && message.at(k) <= 122){
			decipher = message.at(k);
			for(int i=0; i<26; i++){
				if(decipher == Das_array_to_use_lower[i]){
					decoded_message += 'a'+i;
				}
			}
		}
		else if(message.at(k) >= 65 && message.at(k) <= 90){
			decipher = message.at(k);
			for(int i=0; i<26; i++){
				if(decipher == Das_array_to_use_upper[i]){
					decoded_message += 'A'+i;
				}
			}
		}
		else{
			decoded_message+= message.at(k);
		}
		
	
	}
	cout << decoded_message << endl;
	
	save_file(decoded_message);
}
void Vigenere_Encryp(string message){
	string coded_message="";
	string key_word_Low= "";
	for(int t = 0; t<key_word.length(); t++){
		key_word_Low += tolower(key_word.at(t));
	}
	string key_word_Cap= "";
	for(int t = 0; t<key_word.length(); t++){
		key_word_Cap += toupper(key_word.at(t));
	}
	int key_word_count =0;
	int key_word_length = 0;
	for(int i=0; i<key_word.length(); i++){
		key_word_length++;
	}
	int key_word_letter = 0;
	for (int k=0; k<message.length(); k++){
		if((message.at(k) >= 97 && message.at(k) <= 122) || (message.at(k) >= 65 && message.at(k) <= 90)){
			for(int g=0; g<26;g++){
				for(int x=0;x<26;x++){
					if(message.at(k)== vigenereTableLow[0][g] && key_word_Low.at(key_word_letter) == vigenereTableLow[x][0]){
						coded_message += vigenereTableLow[x][g];
						break;
					}
					else if(message.at(k)== vigenereTableCap[0][g] && key_word_Cap.at(key_word_letter)== vigenereTableCap[x][0]){
						coded_message += vigenereTableCap[x][g];
						break;
					}
				}
			}
			key_word_count ++;
		}
		else{
			coded_message += message.at(k);
		}
		key_word_letter = key_word_count % key_word_length;
	}
	save_file(coded_message);
}
void Vigenere_Decryp(string message){
	string decoded_message;
	string key_word_Low= "";
	// lowercase the keyword in order to make the decrypting easier (to code)
	for(int t = 0; t<key_word.length(); t++){
		key_word_Low += tolower(key_word.at(t));
	}
	string key_word_Cap= "";
	// uppercase the keyword in order to make the decrypting easier (to code)
	for(int t = 0; t<key_word.length(); t++){
		key_word_Cap += toupper(key_word.at(t));
	}
	int key_word_count =0;
	int key_word_length = 0;
	for(int i=0; i<key_word.length(); i++){
		key_word_length++;
	}
	int key_word_letter = 0;
	for (int k=0; k<message.length(); k++){
		// If it is a letter
		if((message.at(k) >= 97 && message.at(k) <= 122) || (message.at(k) >= 65 && message.at(k) <= 90)){
			for(int g=0; g<26;g++){
				for(int x=0;x<26;x++){
					if(message.at(k)== vigenereTableLow[x][g] && key_word_Low.at(key_word_letter) == vigenereTableLow[x][0]){
						decoded_message += vigenereTableLow[0][g];
						break;
					}
					else if(message.at(k)== vigenereTableCap[x][g] && key_word_Cap.at(key_word_letter)== vigenereTableCap[x][0]){
						decoded_message += vigenereTableCap[0][g];
						break;
					}
				}
			}
			key_word_count ++;
		}
		// if it is not a letter, so: ' ' '.' '!' ',' ect
		else{
			decoded_message += message.at(k);
		}
		key_word_letter = key_word_count % key_word_length;
	}
	save_file(decoded_message);
}

// Check if there is a repeating letter in the key word
bool repeat_letter(string New_key_word, int position, char letter){
	bool repeat = false;
	for(int i = 0; i<position; i++){
		if(New_key_word.at(i)==letter){
			repeat=true;
			break;
		}
	}
	return repeat;
}

// Create a vigenere table to use for encoding and decoding
void createVigenereTable(){
	int i=0;int j=0;
    int k=0;
    for(i=0;i<26;i++){
        k=0;
        k=i+0;
        for(j=0;j<26;j++){
            if(k<26){
                vigenereTableCap[i][j]=ALPHCap[k];
				vigenereTableLow[i][j]=ALPHLow[k];
            }  
            else if(k>=26)
            {  
                vigenereTableCap[i][j]=ALPHCap[(k%26)];
				vigenereTableLow[i][j]=ALPHLow[(k%26)];
            }
            k++;
        }
    }
}


