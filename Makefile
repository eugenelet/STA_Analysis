CC=g++
CFLAGS=-c -Wall
DFLAGS=-g
OUT=EDA
<<<<<<< HEAD
SRC=main.cpp parser.cpp debug.cpp generateTree.cpp node.cpp print.cpp
CASE=test1.txt
=======
SRC=main.cpp parser.cpp debug.cpp generateTree.cpp node.cpp
CASE=case_test
>>>>>>> 974d8a7ea2febb293d07cf323a170608fe3d7304


all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(DFLAGS) $(SRC) -o $@


run: $(OUT)
	./$(OUT) $(CASE) tmp.rpt 	


clean:
	rm  $(OUT)
