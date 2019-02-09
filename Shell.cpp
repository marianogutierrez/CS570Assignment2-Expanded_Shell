#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "LinkedList.hpp"
#include "Tokenizer.hpp"

using namespace std;

// Cameron Ozatalar
// Mariano Gutierrez

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

        // TODO: Execute Commands

        // Print Tokens
        if(list -> size != 0)
            cout << list -> toString() << endl;
        
        delete list;

    }
}