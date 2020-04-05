CC=g++
CFLAGS=-W -Wall -ansi -pedantic

all: systm.o utils.o factor.o eval.o bigRa.o listera.o transv.o Integer.o main.o opera clean

systm.o: systm.cpp
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

transv.o: transv.cpp 
	$(CC) -c $< $(CFLAGS)

Integer.o: Integer.cpp 
	$(CC) -c $< $(CFLAGS)

main.o: main.cpp 
	$(CC) -c $< $(CFLAGS)

opera:
	g++ -o opera systm.o utils.o factor.o eval.o bigRa.o listera.o transv.o Integer.o main.o -lgmp

clean:
	rm -rf *.o

