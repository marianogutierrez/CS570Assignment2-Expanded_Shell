#include <stdio.h>
#include <iostream>
#include <string>

#include "LinkedList.hpp"
#include "Tokenizer.hpp"

using namespace std;

// Cameron Ozatalar
// Mariano Gutierrez

void Tokenizer::Tokenize(LinkedList* list, string input){
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

    // Add last token
    if(token.length() != 0)
        list -> add(token);
}