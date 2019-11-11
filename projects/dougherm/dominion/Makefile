CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
test1: dominion.o rngs.o unittest1.c
	gcc -o test1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

test2: dominion.o rngs.o unittest2.c
	gcc -o test2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
test3: dominion.o rngs.o unittest3.c
	gcc -o test3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
test4: dominion.o rngs.o unittest4.c
	gcc -o test4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

test5: dominion.o rngs.o unittest5.c
	gcc -o test5 unittest5.c -g dominion.o rngs.o $(CFLAGS)
playdom: dominion.o playdom.c

unittestresults: dominion.o rngs.o 
	gcc -o test1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o test2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o test3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o test4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o test5 unittest5.c -g dominion.o rngs.o $(CFLAGS)
	./test1 >> unittestresult.out
	./test2 >> unittestresult.out
	./test3 >> unittestresult.out
	./test4 >> unittestresult.out
	./test5 >> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out
	
ests:
	
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
