GPP = g++ -O3 -Wall

UTILS = ../../Utilities

A = Main.o
D = DoTheWork.o
R = Record.o
S = Scanner.o
SL = ScanLine.o
U = Utils.o

Aprog: $(A) $(D) $(R) $(S) $(SL) $(U)
	$(GPP) -o Aprog $(A) $(D) $(R) $(S) $(SL) $(U)

Main.o: Main.h Main.cpp
	$(GPP) -c Main.cpp

DoTheWork.o: DoTheWork.h DoTheWork.cpp
	$(GPP) -c DoTheWork.cpp

Record.o: Record.h Record.cpp
	$(GPP) -c Record.cpp

Scanner.o: $(UTILS)/Scanner.h $(UTILS)/Scanner.cpp
	$(GPP) -c $(UTILS)/Scanner.cpp

ScanLine.o: $(UTILS)/ScanLine.h $(UTILS)/ScanLine.cpp
	$(GPP) -c $(UTILS)/ScanLine.cpp

Utils.o: $(UTILS)/Utils.h $(UTILS)/Utils.cpp
	$(GPP) -c $(UTILS)/Utils.cpp

