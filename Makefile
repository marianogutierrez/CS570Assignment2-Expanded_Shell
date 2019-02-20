#Cameron Ozatalar
#Mariano Gutierrez

# : indicates dependencies 
MUSH: shell.cpp Tokenizer.o LinkedList.o
	g++ shell.cpp Tokenizer.o LinkedList.o -g -o MUSH -lreadline

#Create Tokenizer Object
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp
	g++ -c Tokenizer.cpp

#Create LinkedList Object
LinkedList.o: LinkedList.cpp LinkedList.hpp
	g++ -c LinkedList.cpp

#Clean up object and executable files; Note that core is for the core dump file if one is produced
clean:
	rm -f core Tokenizer.o LinkedList.o shell 