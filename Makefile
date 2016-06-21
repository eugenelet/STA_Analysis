CC=g++
CFLAGS=-c -Wall
DFLAGS=-g
OUT=EDA
SRC=main.cpp parser.cpp debug.cpp generateTree.cpp node.cpp
CASE=case3


all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(DFLAGS) $(SRC) -o $@


run: $(OUT)
	./$(OUT) $(CASE) tmp.rpt 	


clean:
	rm  $(OUT)
