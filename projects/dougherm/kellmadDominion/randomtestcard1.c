#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)

int main()
{
	srand(time(NULL));
	/* Test One: Player elected to discard estate with estate in hand*/
	//generate random number of tests from 6 to 25.
	int numRandTests = rand() % 100+100;
	printf("Begin baronCard test\n");
	for(int i=0; i<numRandTests; i++)
	{
		//Declar the gamestate struct		
		struct gameState A;
	
		//initialize variables
		A.hand[0][0] = -1;
		A.numBuys=0;
		//randomly decide if the player will discard an estate card
		int choice = rand() % 2;

		A.handCount[0]=1;
		//randomly assign a card to the first slot in player's hand
		A.hand[0][0] = rand() % 26;	
		A.supplyCount[estate]=1;
		A.coins = 0;
		
		//call baron function
		baronEffect(choice,&A,0);
		if (choice==1 && A.hand[0][0] == estate)
		{	printf("Discard Positive\n");
			//discarded estate with estate in hand
			isTrue(A.numBuys==1);
			isTrue(A.coins == 4);
			isTrue(A.handCount[0] ==0);
			isTrue(A.hand[0][0] != estate);
			printf("\n");
		}
		else if (choice==1 && A.hand[0][0] != estate)
		{	
			printf("Discard Negative\n");
			isTrue(A.numBuys==1);
			//discarded estate without estate in hand
			isTrue(A.coins == 0);
			isTrue(A.handCount[0] == 2);
			isTrue(A.hand[0][1] == estate);
			isTrue(A.supplyCount[estate] == 0);
			printf("\n");

		}
		else if( choice==0)
		{	
			printf("Gain Estate\n");
			//chose to gain estate
			isTrue(A.numBuys==1);
			isTrue(A.coins == 0);
			isTrue(A.handCount[0] ==2);
			isTrue(A.hand[0][1] == estate);
			isTrue(A.supplyCount[estate]==0);
			printf("\n");
		}
		else
			printf("Something went wrong\n");

	}
	printf("Baron Test Complete ran %d tests \n\n", numRandTests);
	return 0;
}
