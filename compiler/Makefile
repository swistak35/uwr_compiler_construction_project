
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -g -pedantic -pedantic-errors -Wundef -std=c++11 -O0
CPP = clang++

# LLVM_FLAGS = -I/usr/include -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong  -fPIC -fvisibility-inlines-hidden -Wall -W -Wno-unused-parameter -Wwrite-strings -Wcast-qual -Wno-missing-field-initializers -pedantic -Wno-long-long -Wno-maybe-uninitialized -Wnon-virtual-dtor -Wno-comment -std=c++11 -ffunction-sections -fdata-sections -O3 -DNDEBUG -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
LLVM_FLAGS = -I/usr/include -march=x86-64 -mtune=generic -pipe -fstack-protector-strong  -fPIC -fvisibility-inlines-hidden -Wall -W -Wno-unused-parameter -Wwrite-strings -Wcast-qual -Wno-missing-field-initializers -pedantic -Wno-long-long -Wnon-virtual-dtor -Wno-comment -std=c++11 -ffunction-sections -fdata-sections -DNDEBUG -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
LLVM_LINK_FLAGS = -L/usr/lib -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMCodeGen -lLLVMScalarOpts -lLLVMProfileData -lLLVMInstCombine -lLLVMInstrumentation -lLLVMTransformUtils -lLLVMipa -lLLVMX86Desc -lLLVMMCDisassembler -lLLVMX86Info -lLLVMX86AsmPrinter -lLLVMX86Utils -lLLVMMCJIT -lLLVMExecutionEngine -lLLVMTarget -lLLVMAnalysis -lLLVMRuntimeDyld -lLLVMObject -lLLVMMCParser -lLLVMBitReader -lLLVMMC -lLLVMCore -lLLVMSupport -lrt -ldl -lcurses -lpthread -lz -lm

compile: maphoon_parser calculator

calculator : Makefile   calculator.o varstore.o parser.o tokenizer.o token.o tree.o 
	$(CPP) $(Flags) -o calculator   calculator.o varstore.o parser.o tokenizer.o token.o tree.o -lSegFault $(LLVM_FLAGS) $(LLVM_LINK_FLAGS)

calculator.o : Makefile   calculator.cpp   tree.h parser.h token.h tokenizer.h reader.h varstore.h assert.h 
	# $(CPP) -c $(Flags) calculator.cpp -o calculator.o `llvm-config --cxxflags`
	$(CPP) -c $(Flags) calculator.cpp -o calculator.o $(LLVM_FLAGS)


varstore.o : Makefile   varstore.cpp   assert.h varstore.h 
	$(CPP) -c $(Flags) varstore.cpp -o varstore.o


parser.o : Makefile   parser.cpp   parser.h token.h tokenizer.h reader.h assert.h varstore.h 
	$(CPP) -c $(Flags) parser.cpp -o parser.o


tokenizer.o : Makefile   tokenizer.cpp   tokenizer.h reader.h token.h 
	$(CPP) -c $(Flags) tokenizer.cpp -o tokenizer.o


token.o : Makefile   token.cpp   token.h 
	$(CPP) -c $(Flags) token.cpp -o  token.o


tree.o : Makefile   tree.cpp   tree.h 
	$(CPP) -c $(Flags) tree.cpp -o  tree.o

maphoon_parser: calculator.m
	../maphoon2008c/maphoon calculator.m > /dev/null

run: maphoon_parser calculator
	./calculator

tests: maphoon_parser calculator
	./test.sh "main"


