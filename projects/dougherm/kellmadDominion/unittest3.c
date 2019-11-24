#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)

int main()
{
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village,baron,
			great_hall};

	/* Test One: Player elects to gain coins*/
	struct gameState A;
	initializeGame(2, k,30,&A);
	A.coins = 0;
	printf("Test minionCard\n\n");
	minionCard(1,0,&A,0,0);
	isTrue(A.numActions == 2);
	isTrue(A.handCount[0] == 4);
	isTrue(A.coins == 2);
	printf("\n\n");
	
	/* Test Two: Player elects to discard, player 2 has 5 cards*/
	
	initializeGame(2, k,30,&A);
	A.coins = 0;
	A.hand[0][0] = minion;

	for(int i =0; i<5; i++)
	{
		drawCard(1,&A);
	}

	minionCard(0,1,&A,0,0);
	
	isTrue(A.numActions == 2);
	isTrue(A.handCount[0] == 4);
	isTrue(A.handCount[1] == 4);
	isTrue(A.coins == 0);
	printf("\n\n");

	/* Test Three: Player elects to discard, player 2 has 3 cards*/
	
	initializeGame(2, k,30,&A);
	A.coins = 0;
	A.hand[0][0] = minion;

	for(int i =0; i<3; i++)
	{
		drawCard(1,&A);
	}

	minionCard(0,1,&A,0,0);

	isTrue(A.numActions == 2);
	isTrue(A.handCount[0] == 4);
	isTrue(A.handCount[1] == 3);
	isTrue(A.coins == 0);
	printf("\n\n");

	/* Test Four: Player elects to discard, player 2 has 3 cards*/
	
	initializeGame(3, k,30,&A);
	A.coins = 0;
	A.hand[0][0] = minion;

	for(int i =0; i<3; i++)
	{
		drawCard(1,&A);
	}
	for(int i =0; i<5; i++)
	{
		drawCard(2, &A);
	}

	minionCard(0,1,&A,0,0);

	isTrue(A.numActions == 2);
	isTrue(A.handCount[0] == 4);
	isTrue(A.handCount[1] == 3);
	isTrue(A.handCount[2] == 4);
	isTrue(A.coins == 0);
	printf("\n\n");

	/*Test 5: Max number of players all with 5 cards*/
	initializeGame(4, k,30,&A);
	A.coins = 0;
	A.hand[0][0] = minion;
	
	for(int j=1; j<4; j++)
	{
		for(int i =0; i<5; i++)
		{
			drawCard(j,&A);
		}
	}
	minionCard(0,1,&A,0,0);

	isTrue(A.numActions == 2);
	isTrue(A.handCount[0] == 4);
	isTrue(A.handCount[1] == 4);
	isTrue(A.handCount[2] == 4);
	isTrue(A.handCount[3] == 4);
	isTrue(A.coins == 0);
	printf("\n\n");
	return 0;

}
