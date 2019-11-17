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
	int numRandTests = rand()%100+100;
	printf("Begin Tribute Test\n");

	for(int i=0; i<numRandTests; i++)
	{
		struct gameState A;
		int randCard=0;
		int treasureCount =0;
		int victoryCount=0;
		int otherCount =0; 
		A.coins = 0;
		A.numActions = 0;
		A.handCount[0] = 1;
		A.hand[0][0] = tribute;
	
		//randomize the cards in the player's discard and deck piles
		int discardCountNum = rand()%5;
		int deckCountNum = rand()%5;
	
		A.deckCount[1] = deckCountNum;
		A.deckCount[2] = deckCountNum;
		A.discardCount[1] = discardCountNum;
		A.discardCount[2] = discardCountNum;

		//randomize the cards in the player's discard and deck piles
	
		for(int i =0; i<discardCountNum; i++)
		{
			randCard= rand() %27;
			A.discard[1][i] = randCard;
			A.discard[2][i] = randCard;
		}
	
		for(int j =0; j<deckCountNum; j++)
		{
			randCard = rand()%27;
			A.deck[1][j] = randCard;
			A.deck[2][j] = randCard;
		}
	
		//If the deck is 0 and the discard has more than one card in it, move all discard cards to deck
		//and shuffle deck. This mimics what the tribute card function does to player 2 so that we can 
		//see what player 2 should have revealed and thus verify function output
		if(deckCountNum ==0 && discardCountNum>1)
		{
			for(int i=0; i< discardCountNum; i++)
			{
				A.deck[2][i] = A.discard[2][i];
				A.deckCount[2]++;
				A.discard[2][i] = -1;
				A.discardCount[2]--;
			}
			shuffle(2,&A);
		}
		tributeCard(&A, 1, 0);
	
	
		if(deckCountNum==0 && discardCountNum==0)
		{
			printf("No Cards\n");
			isTrue(A.coins == 0);
			isTrue(A.numActions == 0);
			isTrue(A.handCount[0]==1);
			printf("\n");
		}
	
		else if (discardCountNum==1 && deckCountNum == 0 )
		{
			printf("One card total from discard\n");
			printf ("Card: %d\n", A.discard[2][0]);	
			if(A.discard[2][0] == copper || A.discard[2][0] == silver || A.discard[2][0] == gold)
				treasureCount++;
			else if (A.discard[2][0] == estate ||A.discard[2][0] == duchy || A.discard[2][0] == province || A.discard[2][0] == gardens || A.discard[2][0] == great_hall)
				victoryCount++;
			else
				otherCount++;	
	
			//Assert that the player was awarded the correct bonuses.
			isTrue(A.coins == treasureCount * 2);
			isTrue(A.handCount[1] == victoryCount *2);
			isTrue(A.numActions== otherCount*2);
		}
		
		else
		{
	
			printf("%d cards in Deck originally\n",deckCountNum);
			printf("%d cards in Discard originally\n",discardCountNum);
			
			for(int k =0; k < 2; k++)
			{
				printf("Card: %d\n", A.deck[2][k]);
				if(A.deck[2][k] == copper || A.deck[2][k] == silver || A.deck[2][k] == gold)
					treasureCount++;
				else if (A.deck[2][k] == estate || A.deck[2][k] == duchy || A.deck[2][k] == province || A.deck[2][k] == gardens || A.deck[2][k] == great_hall)
					victoryCount++;
				else if(A.deck[2][k] != -1)
					otherCount++;	
			}
			//Assert that the player was awarded the correct bonuses.
			isTrue(A.coins == treasureCount * 2);
			isTrue(A.handCount[1] == victoryCount *2);
			isTrue(A.numActions== otherCount*2);
		}
		printf("Test Complete ran %d times", numRandTests);
		printf("\n\n");
	}
	return 0;

}
