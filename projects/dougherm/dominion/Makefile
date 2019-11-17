CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
test1: dominion.o rngs.o randomtestcard1.c
	gcc -o test1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

test2: dominion.o rngs.o randomtestcard2.c
	gcc -o test2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
test3: dominion.o rngs.o randomtestcard3.c
	gcc -o test3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS)

randomtestresults: dominion.o rngs.o 
	gcc -o test1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o test2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o test3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS)
	./test1 >> randomtestresult.out
	./test2 >> randomtestresult.out
	./test3 >> randomtestresult.out
	gcov -b -f dominion.c >> randomtestresult.out

tests:	
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player test1 player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe 
