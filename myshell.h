#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

main(){
	while(true){
		//Print Prompt 
		cout << getcwd(NULL, 0) << ">> " << flush;
		
		//User Input	
		char command[1024];
		cin.getline( command, 1024 );
		//Parse Input

		if(){	//user typed exit
			exit(0);
		}
		else if(command == "cd"){	// cd, command == "cd"
			chdir();
		}
		else if(command == "echo"){	// echo
		
		}
		else if(command == "set"){	// set
		
		}
		else if(command == "help"){	// help
		
		}
		else{	//
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
				exec();
			}			
			else { /* parent process */
				/* parent will wait for child to complete */
				wait(&status);
				cout << "\nChild complete\n" << endl;
			}

			
		}
	}
}