#include <sys/param.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

// Garrett Roach

// *******************************************************
// All works but TODO:
// make work by reading in a file
// *******************************************************
using namespace std;

void Parse(char* command, char* cmd[], char input[])
{
        // Parse
        command = strtok(input, " ");
		//cout<< command << "In parse" << endl;
        int i = 0;
        while(command != NULL){
            cmd[i] = command;
            i++;
            command = strtok(NULL, " ");
        }
}
void Clear(char* cmd[])
{
    for(int x=0; x < 1024; x++)
    {
                cmd[x] = NULL;
    }
}
void Clear2(char cmd[])
{
    for(int x=0; x < 1024; x++)
    {
                cmd[x] = NULL;
    }
}
void Exec(char* cmd[])
{
        // create another process and load another program in the process
        //fork
        int status = 0;
        pid_t pid;
        /* fork a child process */
        pid = fork();

        if(pid < 0) { /* error scenario */
                cerr << "fork() failed\n" << endl;
                exit(-1);
        }
        else if (pid == 0) { /* child process */
                execvp(cmd[0], cmd);
        }
        else { /* parent process */
                /* parent will wait for child to complete */
                wait(&status);
        }
}

int main(int argc, char* argv[]){ //argc contains number of arguments received, arguments are in the array argv, 
      
		char* command;
        char* command2;
        char* cmd[1024];
        char* cmd2[1024];
        char input[1024];
		char input2[1024];
		char* inputfile[1024];
        int r = 0;
        string myPrompt = "Prompt";
	//____________________________________
	// Messing with argc test
	if ( argc == 1 ){ // argc should be 2 for correct execution
		// We print argv[0] assuming it is the program name
		//cout<<"usage: "<< argv[0] <<" <filename>\n";	
		
		while(true){
                // Clear cmd array
                Clear(cmd);
                //Print Prompt
                cout << myPrompt << ">> "<< flush;
                // Get Input
				cin.getline(input,1024);

				command = strtok(input, ";");
				int j=0;
				int i = 0;
				while(command != NULL){
					cmd2[i] = command;
					i++;
					command = strtok(NULL, ";");
				}
				for(j=0; j<i; j++){
					//cout << cmd2[j] << "Cmd2: " << j << endl;
					command2 = cmd2[j];
					
					strcpy(input2, command2);
					//cout << command2 << " Command" << endl;
					//cout << input2 << " INput2" << endl;

                    Parse(command2, cmd, input2);
                    if(strcmp(cmd[0], "exit") == 0){        //user typed exit
						exit(0);
                    }
                    else if(strcmp(cmd[0], "pwd")== 0){
                        char buffer[MAXPATHLEN];
                        cout << getcwd(buffer, MAXPATHLEN) << endl;
                    }
                    else if(strcmp(cmd[0], "cd") == 0){     // cd
                        char buffer[MAXPATHLEN];
                        //cout << getcwd(buffer, MAXPATHLEN) << endl;
                        if (cmd[1]== NULL){
                            chdir ("/");
                            }
                        else{
                            if(chdir(cmd[1]) < 0)
                                cout << "Directory does not exist" << endl;
                            else{
                                int rc = chdir(cmd[1]);
                                if (rc < 0) {
                                    //cout << "ERROR" << endl; TODO: Handle error
                                }
                                cout << rc << endl;
                                myPrompt = getcwd(buffer, MAXPATHLEN);
                            }
                        }
                    }
                    else if(strcmp(cmd[0], "echo") == 0){   // echo
						//if(strcmp(cmd, '"'){
					//
						//}
						//else{
							r = 1;
							while(cmd[r] != NULL){
								cout << cmd[r] << " "; // need more than that
								r++;
								}
							cout << endl;
						//}
                    }
                    else if(strcmp(cmd[0], "set") == 0){    // set
                        if (strcmp(cmd[1], "PROMPT") == 0){
                            myPrompt = cmd[2];
                            //cout << "IF statement for PROMPT read" << endl;
                        }
                        else{
                            printf (cmd[0], " Error, have to set PROMPT");
                        }
                        //cout << "IF statement for set read" << endl;
                    }
                    else if(strcmp(cmd[0], "help") == 0){   // help
                        cout << " " << endl;
                        cout << "List of Commands: "<< endl;
						cout << "help\n" << "pwd\n" << "set\n" << "echo\n" << "cd\n" << "exit\n";
                        cout << " " << endl;
                        cout << "Made by: Garrett Roach" << endl;
                        cout << "Last Modified: October 21, 2013\n\n";
                        }
                    else{   //
                        Exec(cmd);
                    }
				Clear(cmd);
				Clear2(input2);
                }
                // End of For Loop
		Clear(cmd2);
        }
		
	}
	else {
		int c=0;
		//Exec2(argv);
		// We assume argv[1] is a filename to open
		ifstream the_file ( argv[1] );
		// Always check to see if file opening succeeded
		if ( !the_file.is_open() )
			cout<<"Could not open file\n";
		else {
			char x;  
			int place=0;
			
			int k = 0;
			int count =0;
			while (the_file != NULL)
			{
				the_file.getline(input,100);// delimeter is the newline char by default
				inputfile[k]=input;
				//cout << "inputfile[" << k<< "] = " << inputfile[k]<< endl;
				
				command2=inputfile[k];
				//cout<< "command2: "<< command2 << endl;
				strcpy(input, command2);
				command = strtok(input, ";");
						//cout<< "input: "<< input << endl;
						int j=0;
						int i = 0;
						while(command != NULL){
							cmd2[i] = command;
							i++;
							command = strtok(NULL, ";");
						}
						
						for(j=0; j<i; j++){
							//cout << cmd2[j] << "Cmd2: " << j << endl;
							command2 = cmd2[j];
							
							strcpy(input2, command2);
							//cout << command2 << " Command" << endl;
							//cout << input2 << " INput2" << endl;

							Parse(command2, cmd, input2);
							if(strcmp(cmd[0], "exit") == 0){        //user typed exit
								exit(0);
							}
							else if(strcmp(cmd[0], "pwd")== 0){
								char buffer[MAXPATHLEN];
								cout << getcwd(buffer, MAXPATHLEN) << endl;
							}
							else if(strcmp(cmd[0], "cd") == 0){     // cd
								char buffer[MAXPATHLEN];
								//cout << getcwd(buffer, MAXPATHLEN) << endl;
								if (cmd[1]== NULL){
									chdir ("/");
									}
								else{
									if(chdir(cmd[1]) < 0)
										cout << "Directory does not exist" << endl;
									else{
										int rc = chdir(cmd[1]);
										if (rc < 0) {
											//cout << "ERROR" << endl; TODO: Handle error
										}
										cout << rc << endl;
										myPrompt = getcwd(buffer, MAXPATHLEN);
									}
								}
							}
							else if(strcmp(cmd[0], "echo") == 0){   // echo
								r = 1;
								while(cmd[r] != NULL){
									cout << cmd[r] << " "; // need more than that
									r++;
									}
								cout << endl;
							}
							else if(strcmp(cmd[0], "set") == 0){    // set
								if (strcmp(cmd[1], "PROMPT") == 0){
									myPrompt = cmd[2];
									//cout << "IF statement for PROMPT read" << endl;
								}
								else{
									printf (cmd[0], " Error, have to set PROMPT");
								}
								//cout << "IF statement for set read" << endl;
							}
							else if(strcmp(cmd[0], "help") == 0){   // help
								cout << " " << endl;
								cout << "List of Commands: "<< endl;
								cout << "help\n" << "pwd\n" << "set\n" << "echo\n" << "cd\n" << "exit\n";
								cout << " " << endl;
								cout << "Made by: Garrett Roach" << endl;
								cout << "Last Modified: October 21, 2013\n\n";
								}
							else{   //
								Exec(cmd);
							}
							//cout << "J: " << j << endl;
							Clear(cmd);
							Clear2(input2);
							//if(j== (i-1) )
							//	cout<< myPrompt << ">> " << flush;
							//else 
							//	cout << "i: " << i << endl;
						}					
					c=1;
				//cout << "____________"<< endl;
				k++;
			}
	
//_____________________________________________________________________			
			while(true){      
				if(c!=0){
					// Clear cmd array
					Clear(cmd);
					//Print Prompt
					cout << myPrompt << ">> "<< flush;
					// Get Input
					cin.getline(input,1024);
						command = strtok(input, ";");
						int j=0;
						int i = 0;
						while(command != NULL){
							cmd2[i] = command;
							i++;
							command = strtok(NULL, ";");
						}
						
						for(j=0; j<i; j++){
							//cout << cmd2[j] << "Cmd2: " << j << endl;
							command2 = cmd2[j];
							
							strcpy(input2, command2);
							//cout << command2 << " Command" << endl;
							//cout << input2 << " INput2" << endl;

							Parse(command2, cmd, input2);
							if(strcmp(cmd[0], "exit") == 0){        //user typed exit
								exit(0);
							}
							else if(strcmp(cmd[0], "pwd")== 0){
								char buffer[MAXPATHLEN];
								cout << getcwd(buffer, MAXPATHLEN) << endl;
							}
							else if(strcmp(cmd[0], "cd") == 0){     // cd
								char buffer[MAXPATHLEN];
								//cout << getcwd(buffer, MAXPATHLEN) << endl;
								if (cmd[1]== NULL){
									chdir ("/");
									}
								else{
									if(chdir(cmd[1]) < 0)
										cout << "Directory does not exist" << endl;
									else{
										int rc = chdir(cmd[1]);
										if (rc < 0) {
											//cout << "ERROR" << endl; TODO: Handle error
										}
										cout << rc << endl;
										myPrompt = getcwd(buffer, MAXPATHLEN);
									}
								}
							}
							else if(strcmp(cmd[0], "echo") == 0){   // echo
								r = 1;
								while(cmd[r] != NULL){
									cout << cmd[r] << " "; // need more than that
									r++;
									}
								cout << endl;
							}
							else if(strcmp(cmd[0], "set") == 0){    // set
								if (strcmp(cmd[1], "PROMPT") == 0){
									myPrompt = cmd[2];
									//cout << "IF statement for PROMPT read" << endl;
								}
								else{
									printf (cmd[0], " Error, have to set PROMPT");
								}
								//cout << "IF statement for set read" << endl;
							}
							else if(strcmp(cmd[0], "help") == 0){   // help
								cout << " " << endl;
								cout << "List of Commands: "<< endl;
								cout << "help\n" << "pwd\n" << "set\n" << "echo\n" << "cd\n" << "exit\n";
								cout << " " << endl;
								cout << "Made by: Garrett Roach" << endl;
								cout << "Last Modified: October 21, 2013\n\n";
								}
							else{   //
								Exec(cmd);
							}
							//cout << "J: " << j << endl;
							Clear(cmd);
							Clear2(input2);
							//if(j== (i-1) )
							//	cout<< myPrompt << ">> " << flush;
							//else 
							//	cout << "i: " << i << endl;
						}
					}
				//cout<< "C: " << c;
				c=1;
					// End of For Loop
			Clear(cmd2);
			}
		}
// Here
//___________________________________________________________________		
    // the_file is closed implicitly here
	}
	
	//____________________________________
        
        return 1;
}


