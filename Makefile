#Cameron Ozatalar
#Mariano Gutierrez

#Create tokenizer executable
tokenizer: Tokenizer.cpp LinkedList.o
	g++ Tokenizer.cpp LinkedList.o -g -o tokenizer -lreadline

LinkedList.o: LinkedList.cpp LinkedList.hpp
	g++ -c LinkedList.cpp

#Clean up object and executable files
clean:
	rm -f core tokenizer LinkedList.o
