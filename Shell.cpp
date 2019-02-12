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

        }else if(token -> compare("|") == 0){
            cout << "Pipe not implemented" << endl;

        }else if(token -> compare(";") == 0){

        }else if(token -> compare("cd") == 0){
            if(list -> size != 1){ // TODO: ASK e.g. cd /media/ | ; goto media then print fail 
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
            cout << path << endl; // bring out the pwd
        } 
        else {
            // fork-exec 
            int pid = fork();
            if(pid == 0) { // child 
                execve(token -> c_str(), NULL, NULL); // the token
            }
            //TODO: otherwise wait for exec to finish
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
            return 0;
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