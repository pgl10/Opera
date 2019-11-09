CC=g++
CFLAGS=-W -Wall -ansi -pedantic

all: aout.o utils.o factor.o eval.o bigRa.o listera.o Integer.o main.o opera clean

aout.o: aout.cpp
	$(CC) -c $< $(CFLAGS)

utils.o: utils.cpp 
	$(CC) -c $< $(CFLAGS)

factor.o: factor.cpp 
	$(CC) -c $< $(CFLAGS)

eval.o: eval.cpp 
	$(CC) -c $< $(CFLAGS)

bigRa.o: bigRa.cpp 
	$(CC) -c $< $(CFLAGS)

listera.o: listera.cpp 
	$(CC) -c $< $(CFLAGS)

Integer.o: Integer.cpp 
	$(CC) -c $< $(CFLAGS)

main.o: main.cpp 
	$(CC) -c $< $(CFLAGS)

opera:
	g++ -o opera aout.o utils.o factor.o eval.o bigRa.o listera.o Integer.o main.o -lgmp

clean:
	rm -rf *.o

