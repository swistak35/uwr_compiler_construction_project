
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11
CPP = g++


calculator : Makefile   calculator.o varstore.o parser.o tokenizer.o token.o tree.o 
	$(CPP) $(Flags) -o calculator   calculator.o varstore.o parser.o tokenizer.o token.o tree.o 

calculator.o : Makefile   calculator.cpp   tree.h parser.h token.h tokenizer.h reader.h varstore.h assert.h 
	$(CPP) -c $(Flags) calculator.cpp -o  calculator.o


varstore.o : Makefile   varstore.cpp   assert.h varstore.h 
	$(CPP) -c $(Flags) varstore.cpp -o  varstore.o


parser.o : Makefile   parser.cpp   parser.h token.h tokenizer.h reader.h assert.h varstore.h 
	$(CPP) -c $(Flags) parser.cpp -o  parser.o


tokenizer.o : Makefile   tokenizer.cpp   tokenizer.h reader.h token.h 
	$(CPP) -c $(Flags) tokenizer.cpp -o  tokenizer.o


token.o : Makefile   token.cpp   token.h 
	$(CPP) -c $(Flags) token.cpp -o  token.o


tree.o : Makefile   tree.cpp   tree.h 
	$(CPP) -c $(Flags) tree.cpp -o  tree.o

maphoon_parser: calculator.m
	../maphoon2008c/maphoon calculator.m > /dev/null

run: maphoon_parser calculator
	./calculator

tests: maphoon_parser calculator
	./test.sh "basic"


