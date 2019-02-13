#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#include <readline/readline.h>
#include <readline/history.h>

#include "LinkedList.hpp"
#include "Tokenizer.hpp"

using namespace std;

const int MAX_ARGS = 100; // so, really 99 args max since first arg is the program to run
// Cameron Ozatalar
// Mariano Gutierrez

void execute_commands(LinkedList* list){
    while(list -> size != 0){
        string* token = list -> removeFirst();
        if(token -> compare(">") == 0 || token -> compare("<") == 0){ // if we find it... report the error
            if(!list -> size - 1 == 0) // reached the end and nothing to grab
                list -> removeFirst();  // strip the following token
            cout << "IO redirection and background not implemented" << endl;

        }else if(token -> compare("&") == 0){          
            cout << "IO redirection and background not implemented" << endl;

        }else if(token -> compare("|") == 0){ // might not need this 
            cout << "Pipe not implemented" << endl; // should pretend it is a ";" refer to bottom of pg.3

       // }else if(token -> compare(";") == 0){ // what do we need to do for this again?
            // should indicate to just continue processing the commands 

         } else if(token -> compare("cd") == 0){
            // TODO: ASK e.g. cd /media/ | ; goto media then print fail  NOTE BOTTOM OF PG 3 says this is required 
            if(list -> size != 1){  // maybe change to if the next one is not | or ;? 
                cout << "Accepts exactly one argument" << endl;
            }else{
                string* path = list -> removeFirst();
                if(chdir(path -> c_str()) != 0){ // only works for char* | returns 0 on success
                    cout << "Directory does not exist or is not accessible." << endl;
                }
            }
        }else if(token -> compare("pwd") == 0){
            char* path = (char*) malloc(sizeof(char)*512);
            getcwd(path, 512);
            if(path == NULL)  // returns NULL on failure 
                cout << "unable to obtain current directory" << endl;
            string input(path); // convert back to c++ string
            cout << path << endl; // print out the cwd
        } 
        else {
            // fork-exec 
            char** arrayOfParameters = (char**) malloc((sizeof(char*) * MAX_ARGS));
            for(int i = 0; i < 256; i++) { // 2-d array
                arrayOfParameters[i] = (char*) malloc(sizeof(char) * 256); // max length of the string will be 256 bytes
            }
            strcpy(arrayOfParameters[0],token -> c_str()); // first arg ought to the name of the program
            arrayOfParameters[MAX_ARGS-1] = '\0'; // Last arguement must be null as requested to function with execvp

            //TODO Produce error message if arg length exceeded!
            // will probably neeed to consume tokens until empty or hit "; or |"
            // check is greater than max length then and check for errors 
            int currentSize = list -> size;
            for(int i = 1; i < currentSize; i++) {
                // check max arg amount...
                strcpy(arrayOfParameters[i], list -> removeFirst() -> c_str());
            }
                
            
            
            pid_t pid = fork(); // spawn off the executioner 

            if(pid == -1) // Fork Failed
                cout << "unable to spawn program" << endl; // In practice this should not typically happen

            if(pid == 0) { // Child/Executioner 
                int execStatus;
                // Pass in the command, and the arguements, no need for environment pointer, hence set to NULL
                execStatus = execvp(token -> c_str(), arrayOfParameters); 
                if(execStatus == -1) // Execve failed 
                    cout << "Unable to execute " << token << endl;
            }
            //TODO: otherwise wait for exec to finish
            pid_t returnStatus;
            wait(&returnStatus);
            if(returnStatus == -1)  {
                cout << "Process exited with error" << endl;
            }
            else {
            cout << "Process exited successfully" << endl;
            }
            freeLines(arrayOfParameters); // either way, we need to free that array of pointers 
        } 
    }
}

// free things in order reverse stack-wise LIFO
void freeLines(char** buff) {
  for(int i = 0; i < 256; i++) {
   free(buff[i]);
  }
  free(buff);
}

int main(int argc, char** argv){
    while(true){
        // Get input string
        char* in = readline("> ");

        //Exit case (Ctrl-d)
        if(in == NULL){
            cout << endl;
            return 1; //EOF
        }
        string input(in);

        // Create LinkedList and call Tokenize method
        LinkedList* list = new LinkedList();
        Tokenizer::Tokenize(list, input);

        // Print Tokens
        if(list -> size != 0)
            cout << list -> toString() << endl;
        
        execute_commands(list);
        delete list;
    }
}