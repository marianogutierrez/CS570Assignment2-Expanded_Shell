#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
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


/*Method to freeup the allocated array of parameters for execvp.*/
void freeLines(char** buff) {
  for(int i = 0; i < MAX_ARGS; i++) {
   free(buff[i]); // NOTE: one of these will be null for execvp, but that is safe
  }
  free(buff);
}

/*Checks to see if a delimiter i.e. ; or |. if | prints out error */
bool isDelimiter(string tok) {
    if(tok.compare(";") == 0 || tok.compare("|") == 0) { // delimiter, also handles pwd and cd multiple
        if (tok.compare("|") == 0) 
            cout << "Pipe not implemented" << endl; // warn the user.
         return true;
     }
     return false;
}

//Strips all <> and &
vector<string>* strip(vector<string> *cmds) {
    int currentSize = cmds -> size();
    vector<string>* cleanedUp = new vector<string>();
    bool detected = false; // to see if warning message will need to be printed.
    for(int i = 0; i < currentSize; i++) {
        if(cmds -> at(i).compare(">") == 0 || cmds -> at(i).compare("<") == 0){
            detected = true;
            if(i < cmds -> size()){   // as long as there is someting else to grab
                i++; // skip over it to ensure we don't add it on;
            }
        }
        else if(cmds -> at(i).compare("&") == 0) {
            detected = true;
        }
        else {
            cleanedUp -> push_back(cmds -> at(i));
        }
    }
    if(detected)  // dont want to print out multiple times
            cout << "IO redirection and background not implemented" << endl;
    return cleanedUp;
}


void execute_commands(LinkedList* list){
    while(list -> size != 0){ // while tokens are available
        vector<string> *command = new vector<string>();
        string token;
        while(list -> size != 0) { // delimit the command
            token = list -> removeFirst(); // decrements size hence need to be careful
            if(!isDelimiter(token)) 
                command -> push_back(token);
            else 
                break;
        }
        //big token 
        //if(!isDelimiter(token)) 
                //command -> push_back(token);
        // strip commands of < > or &
        command = strip(command);
        if(command -> size() == 0) break;

        if(command -> at(0).compare("cd") == 0){ // cd case:
            if(command -> size() == 2){ // one arg only
                string path = command -> at(1);
                if(chdir(path.c_str()) != 0){ // only works for char* | returns 0 on success
                    cout << "Directory does not exist or is not accessible." << endl;
                }
            }
            else {
                 cout << "Accepts exactly one argument" << endl;
            }
        }
        else if(command -> at(0).compare("pwd") == 0){ // single token pwd case
            if(command -> size() != 1 ){
                cout << "Error expected one single token" << endl;
            } 
            else {
                char* path = (char*) malloc(sizeof(char)*512);
                getcwd(path, 512);
                if(path == NULL)  // returns NULL on failure 
                    cout << "Unable to obtain current directory" << endl;
                string input(path); // convert back to c++ string
                cout << path << endl; // print out the cwd
            }
        } 
        else { // fork-exec case
            //construct argv to pass into execvp
            char** arrayOfParameters = (char**) malloc((sizeof(char*)) * MAX_ARGS);
            for(int i = 0; i < MAX_ARGS; i++) { // 2-d array
                arrayOfParameters[i] = (char*) malloc(sizeof(char) * 256); // max length of the string will be 256 bytes
            }
            strcpy(arrayOfParameters[0],command -> at(0).c_str()); // first arg ought to the name of the program

            int currentSize = command -> size();
            int i;
            for(i = 1; i < currentSize; i++) { // for filling array of params maybe change to list -> size dyanmic
                // check max arg amount...
                 if(i == 101) {
                    cout << "Max number of args reached!" << endl;
                    break;
                }
                strcpy(arrayOfParameters[i], command -> at(i).c_str());
            }
            arrayOfParameters[i] = NULL; // null terminate to use execvp
            
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
         delete command; // free up the commnd vector
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
            return 1; //EOF
        }
        string input(in);

        // Create LinkedList and call Tokenize method
        LinkedList* list = new LinkedList();
        Tokenizer::Tokenize(list, input);
        execute_commands(list);
        delete list;
    }
}