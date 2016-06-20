CC=g++
CFLAGS=-c -Wall
DFLAGS=-g
OUT=EDA
SRC=main.cpp parser.cpp debug.cpp

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(DFLAGS) $(SRC) -o $@


run: $(OUT)
	./$(OUT) case1 tmp.rpt 	


clean:
	rm  $(OUT)
