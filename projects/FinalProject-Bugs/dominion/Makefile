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
	gcc -o unittest1.exe -g unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2.exe -g unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3.exe -g unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4.exe -g unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest5.exe -g unittest5.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest6.exe -g unittest6.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest7.exe -g unittest7.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest8.exe -g unittest8.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest9.exe -g unittest9.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest10.exe -g unittest10.c dominion.o rngs.o $(CFLAGS)
	./unittest1.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest2.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest3.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest4.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest5.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest6.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.
	rm dominion.gcda
	./unittest7.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest8.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest9.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda
	./unittest10.exe >> unittestresults.out
	gcov -bf dominion.c >> unittestresults.out
	rm dominion.gcda

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o *.exe playdom player  *.gcov *.gcda *.gcno *.so *.out testDrawCard
