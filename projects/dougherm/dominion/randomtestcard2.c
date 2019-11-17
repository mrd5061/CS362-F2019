#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)

int main()
{
	//seed the random number function
	srand(time(NULL));

	//initialize variables
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village,baron,
			great_hall};
	//select number of random tests
	int numRandTests = rand()%51+50;
	int numPlayers, numCards, choice;

	//Testing loop
	for(int i=0; i<numRandTests; i++)
	{
		//initialize gameplay
		struct gameState A;
		//array to keep track of player card counts from before minion card call.
		int preCardCount[5];
		//select number of players, between 2 and 4 inclusive
		numPlayers = rand() % 3+2;
		initializeGame(numPlayers, k, 30, &A);
		A.coins =0;
		//randomly choose to discard or gain coins.
		choice = rand()%2;
		//make sure player 1 has a minion card.
		A.hand[0][0] = minion;
		preCardCount[0]=5;

		//loop through players and assign a random number of cards
		for (int j=1; j<numPlayers; j++)
		{
			numCards = rand()%5+1;
			preCardCount[j] = numCards;
			for(int k=0; k<numCards; k++)
			{
				drawCard(j,&A);
			}
		}
		//start the test. 
		printf("Start Minion Test\n");

		//function calls with appropriate flags based on random choice
		if(choice)
			minionCard(0,1,&A,0,0);
		else
			minionCard(1,0,&A,0,0);

		//Testing print out if coins were chosen
		if (!choice)
		{
			printf("Chose Coins\n");
			isTrue(A.coins==2);
			isTrue(A.handCount[0] == 4);
			isTrue(A.numActions==2);
		}
		//Testing print out if discard was chosen
		else
		{
			printf("Chose discard\n");
			isTrue(A.coins ==0);
			isTrue(A.numActions ==2);
			//make sure player 1's hand count is 4
			printf("Player one hand count 4? ");
			isTrue(A.handCount[0]==4);
			//verify that the function chose the players
			//to redraw hands correctly.
			for(int k=1; k<numPlayers; k++)
			{
				//if their starting card count was 5
				if(preCardCount[k]==5)
				{	//make sure their card count is now 4
					printf("Player %d discarded. Hand count is 4? ", k+1);
					isTrue(A.handCount[k]==4);
				}
				else
				{
					//otherwise, current card count
					//should equal starting card count
					printf("Player %d did not discard. Hand count same? ", k+1);
					isTrue(A.handCount[k]==preCardCount[k]);
				}
			}
	
		}
		printf("\n");
	}

	printf("Test complete. Ran %d times\n\n", numRandTests);
	return 0;

}
