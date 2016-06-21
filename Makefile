CC=g++
CFLAGS=-c -Wall
DFLAGS=-g
OUT=EDA
SRC=main.cpp parser.cpp debug.cpp generateTree.cpp node.cpp print.cpp
CASE=case/test1.txt


all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(DFLAGS) $(SRC) -o $@


run: $(OUT)
	./$(OUT) $(CASE) tmp.rpt 	


clean:
	rm  $(OUT)
