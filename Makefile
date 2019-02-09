#Cameron Ozatalar
#Mariano Gutierrez

shell: Shell.cpp Tokenizer.o LinkedList.o
	g++ Shell.cpp Tokenizer.o LinkedList.o -g -o shell -lreadline

#Create Tokenizer Object
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp
	g++ -c Tokenizer.cpp

#Create LinkedList Object
LinkedList.o: LinkedList.cpp LinkedList.hpp
	g++ -c LinkedList.cpp

#Clean up object and executable files
clean:
	rm -f core Tokenizer.o LinkedList.o shell
