P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm -f *.o P2.out *.gch *.x *.p1 *.p2 *.ss *.lst *.dbg *.exp

cleanProgram : 
	rm -f *.o P2.out 

cleanTestFiles : 
	rm -f *.p1 *.p2 *.ss *.lst *.dbg *.exp

submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamRP2
	mkdir TeamRP2
	cp Project2.cpp TeamRP2
	cp LexicalAnalyzer.h TeamRP2
	cp LexicalAnalyzer.cpp TeamRP2
	cp SyntacticalAnalyzer.h TeamRP2
	cp SyntacticalAnalyzer.cpp TeamRP2
	cp makefile TeamRP2
	cp README.txt TeamRP2
	tar cfvz TeamRP2.tgz TeamRP2
	cp TeamRP2.tgz ~tiawatts/cs460drop
