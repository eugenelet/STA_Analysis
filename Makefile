CC=g++
CFLAGS=-c -Wall
DFLAGS=-g -O3
OUT=EDA
SRC=main.cpp parser.cpp debug.cpp generateTree.cpp node.cpp print.cpp node_judge.cpp SAT.cpp node_judge_for_every_cell.cpp
CASE=case/case_test


all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(DFLAGS) $(SRC) -o $@


run: $(OUT)
	./$(OUT) $(CASE) tmp.rpt 	


clean:
	rm  $(OUT)
