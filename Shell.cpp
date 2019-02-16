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

const int MAX_ARGS = 102; // so, really 99 args max since first arg is the program to run
// Cameron Ozatalar
// Mariano Gutierrez

/*
  Method to freeup the allocated array of parameters
 */
void freeLines(char** buff) {
  for(int i = 0; i < MAX_ARGS; i++) {
   free(buff[i]); // NOTE: one of these will be null but that is safe
  }
  free(buff);
}

bool isDelimiter(string* tok) {
    if(tok -> compare(";") == 0 || tok -> compare("|") == 0) { // delimiter, also handles pwd and cd multiple
        if (tok -> compare("|") == 0) {
            cout << "Pipe not implemented" << endl; // warn the user.
         }
         return true;
     }
     return false;
}


void execute_commands(LinkedList* list){
    while(list -> size != 0){ // while tokens are available
        string* token = list -> removeFirst();
        if(isDelimiter(token)){
            continue; // just go on executing commands.
        } 
        else if(token -> compare(">") == 0 || token -> compare("<") == 0) {
                if((list -> size - 1 >= 0))   // as long as there is someting else to grab
                    list -> removeFirst();  // strip the following token dunno if need
            cout << "IO redirection and background not implemented" << endl;
            }
        else if(token -> compare("&") == 0) {
            cout << "IO redirection and background not implemented" << endl;
        }
        else if(token -> compare("cd") == 0){ // STARTING WITH THE TOKEN CD
            if(list -> size >= 2){  // case in which multiple cmds's e.g. cd.. ; ls
                string* path = list -> removeFirst();
                if(isDelimiter(list -> removeFirst())) {
                    if(chdir(path -> c_str()) != 0) { // only works for char* | returns 0 on success
                        cout << "Directory does not exist or is not accessible." << endl;
                    }
                }
                else {
                    cout << "Accepts exactly one argument" << endl;
                }
            }else if(list -> size == 1){
                string* path = list -> removeFirst();
                if(chdir(path -> c_str()) != 0){ // only works for char* | returns 0 on success
                    cout << "Directory does not exist or is not accessible." << endl;
                }
            }
            else { // zero args
                cout << "Accepts exactly one argument" << endl;
            }
        }else if(token -> compare("pwd") == 0){ // single token
            char* path = (char*) malloc(sizeof(char)*512);
            getcwd(path, 512);
            if(path == NULL)  // returns NULL on failure 
                cout << "Unable to obtain current directory" << endl;
            string input(path); // convert back to c++ string
            cout << path << endl; // print out the cwd
        } 
        else {
            // fork-exec 
            //construct argv to pass into execvp
            char** arrayOfParameters = (char**) malloc((sizeof(char*)) * MAX_ARGS);
            for(int i = 0; i < MAX_ARGS; i++) { // 2-d array
                arrayOfParameters[i] = (char*) malloc(sizeof(char) * 256); // max length of the string will be 256 bytes
            }

            strcpy(arrayOfParameters[0],token -> c_str()); // first arg ought to the name of the program

            int currentSize = list -> size;
            int posToEnd = 1; // where to append the null pointer, by default 1 as in no args 
            for(int i = 1; i <= currentSize; i++) { // for filling array of params maybe change to list -> size dyanmic
                // check max arg amount...
                 if(i == 101) {
                    cout << "Max number of args reached!" << endl;
                    break;
                }
                string* token = list -> removeFirst();
                if(token -> compare(">") == 0 || token -> compare("<") == 0) {
                    if((list -> size - 1 >= 0))  { // as long as there is someting else to grab
                        list -> removeFirst();  // strip the following token dunno if need
                        i++; // ensure we dont read in the skipped one 
                    }
                    cout << "IO redirection and background not implemented" << endl;
                }
                else if(isDelimiter(token)) {
                    break; 
                }
                else {
                strcpy(arrayOfParameters[i], token -> c_str());
                posToEnd++;
                }
            } // end for loop
            arrayOfParameters[posToEnd] = NULL;
            
            pid_t pid = fork(); // spawn off the executioner 

            if(pid == -1) // Fork Failed
                cout << "unable to spawn program" << endl; // In practice this should not typically happen

            if(pid == 0) { // Child/Executioner 
                int execStatus = execvp(arrayOfParameters[0], arrayOfParameters); 
                if(execStatus == -1) // Execve failed 
                    cout << "Unable to execute " << token << endl;
            }
            else { // I am the parent
                pid_t returnStatus;
                wait(&returnStatus);
                if(returnStatus == -1)  { // wait returned retrunStatus as a fail
                    cout << "Process exited with error" << endl;
                }
                else {
                    cout << "Process exited successfully" << endl;
                }
                freeLines(arrayOfParameters); // either way, we need to free that array of pointers 
            }
        } 
    }
}

int main(int argc, char** argv){
    while(true){
        // Get input string
        char* in = readline("> ");

        //Exit case (Ctrl-d)
        if(in == NULL){
            cout << endl;
            return 1; //EOFl
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