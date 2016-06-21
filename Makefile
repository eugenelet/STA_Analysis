CC=g++
CFLAGS=-c -Wall
DFLAGS=-g
OUT=EDA
SRC=main.cpp parser.cpp debug.cpp generateTree.cpp node.cpp
CASE=case_test


all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(DFLAGS) $(SRC) -o $@


run: $(OUT)
	./$(OUT) $(CASE) tmp.rpt 	


clean:
	rm  $(OUT)
