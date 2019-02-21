#Cameron Ozatalar
#Mariano Gutierrez

# : indicates dependencies 
MUSH: Shell.cpp Tokenizer.o LinkedList.o
	g++ Shell.cpp Tokenizer.o LinkedList.o -g -o MUSH -lreadline

#Create Tokenizer Object
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp
	g++ -c Tokenizer.cpp

#Create LinkedList Object
LinkedList.o: LinkedList.cpp LinkedList.hpp
	g++ -c LinkedList.cpp

#Clean up object and executable files; Note that core is for the core dump file if one is produced
clean:
<<<<<<< HEAD
	rm -f core Tokenizer.o LinkedList.o MUSH 
=======
	rm -f core Tokenizer.o LinkedList.o MUSH 
>>>>>>> c114d0796d31fe21f73e0e644ae82beed4ccabb1
