#include <stdio.h>
#include <iostream>
#include <string>

#include <readline/readline.h>
#include <readline/history.h>

#include "LinkedList.hpp"

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

        // Create LinkedList and Special Character String
        LinkedList* list = new LinkedList();
        string spChar = "|;<>&";

        // Loop through input string
        string token = "";
        for(int i = 0; i < input.length(); i++){
            if(input.at(i) == '\\'){ // Escape Char
                if(++i < input.length()){
                    token.append(1, input.at(i));
                }
            }else if(spChar.find(input.at(i)) != string::npos){ // Special Char
                if(token.length() != 0)
                    list -> add(token);
                list -> add(string(1, input.at(i)));
                token = "";

            }else if(input.at(i) == '"'){ // Double Quote Char
                while(++i < input.length()){
                    if(input.at(i) == '\\'){ // Escape Char input Quotes
                        if(++i < input.length()){
                            token.append(1, input.at(i));
                        }
                    }else if(input.at(i) == '"'){ // End Quote char
                        break;

                    }else token.append(1, input.at(i)); // add char to token string
                }

            }else if(input.at(i) == '\''){ // Single Quote char
                while(++i < input.length()){
                    if(input.at(i) == '\''){ // End Quote char
                        break;

                    }else token.append(1, input.at(i)); // add char to token string
                }

            }else if(isspace(input.at(i))){ // Whitespace
                if(token.length() != 0)
                    list -> add(token);
                token = "";

            }else token.append(1, input.at(i)); // add char to token string
        }

        // Add last token and Print Tokens
        if(token.length() != 0)
            list -> add(token);

        if(list -> size != 0)
            cout << list -> toString() << endl;
        
        delete list;
    }
}