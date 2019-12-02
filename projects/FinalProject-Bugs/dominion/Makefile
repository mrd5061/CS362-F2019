CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
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

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c unittest6.c unittest7.c unittest8.c unittest9.c unittest10.c dominion.o rngs.o
	gcc -o unittest1.out -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2.out -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3.out -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4.out -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest5.out -g unittest5.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest6.out -g unittest6.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest7.out -g unittest7.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest8.out -g unittest8.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest9.out -g unittest9.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest10.out -g unittest10.c dominion.o rngs.o $(CFLAGS)
	./unittest1.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest2.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest3.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest4.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest5.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest6.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.
	rm dominion.gcda
	./unittest7.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest8.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest9.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest10.out >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
