CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

MadieRefactoredDominionCode.o: dominion.h MadieRefactoredDominionCode.c rngs.o
	gcc -c MadieRefactoredDominionCode.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestresults: MadieRefactoredDominionCode.o rngs.o
	gcc -o test1 randomtestcard1.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	gcc -o test2 randomtestcard2.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	gcc -o test3 randomtestcard3.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	./test1>> randomtestresult.out
	./test2>> randomtestresult.out
	#./test3>> randomtestresult.out
	gcov -b -f MadieRefactoredDominionCode.c >> randomtestresult.out

unittestresults: MadieRefactoredDominionCode.o rngs.o
	gcc -o utest1 unittest1.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	gcc -o utest2 unittest2.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	gcc -o utest3 unittest3.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	gcc -o utest4 unittest4.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	gcc -o utest5 unittest5.c -g MadieRefactoredDominionCode.o rngs.o $(CFLAGS)
	./utest1>> unittestresult.out
	./utest2>> unittestresult.out
	./utest3>> unittestresult.out
	./utest4>> unittestresult.out
	./utest5>> unittestresult.out
	gcov -b -f MadieRefactoredDominionCode.c >> unittestresult.out

	
	
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe test1 test2 test3 utest1 utest2 utest3 utest4 utest5
