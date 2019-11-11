#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)

int main()
{
//	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village,baron,
//			great_hall};

	// Test with 2 cards in deck
	struct gameState A;
	//initializeGame(2, k, 30, &A);
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.deckCount[1] = 2;
	A.discardCount[1]=0;
	A.deck[1][0] = copper;
	A.deck[1][1] = smithy;
	A.coins = 0;
	A.numActions = 0;
	printf("Begin tribute card test\n");
	tributeCard(&A, 1,0);

	isTrue(A.coins == 2);
	isTrue(A.numActions == 2);
	printf("\n\n");

	//Test with one card in deck, one in discard deck.
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.deckCount[1] = 1;
	A.discardCount[1]=1;
	A.deck[1][0] = copper;
	A.discard[1][1] = smithy;
	A.coins = 0;
	A.numActions = 0;
	tributeCard(&A, 1,0);

	isTrue(A.coins == 2);
	isTrue(A.numActions == 2);	
	printf("\n\n");

	//Test with both cards  in discard deck.
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.discardCount[1]=2;
	A.deckCount[1]=0;
	A.discard[1][0] = copper;
	A.discard[1][1] = smithy;
	A.coins = 0;
	A.numActions = 0;
	tributeCard(&A, 1,0);

	isTrue(A.coins == 2);
	isTrue(A.numActions == 2);		
	printf("\n\n");

	//Test with no cards.
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.deckCount[1]=0;
	A.discardCount[1]=0;
	A.coins = 0;
	A.numActions = 0;
	tributeCard(&A, 1,0);

	isTrue(A.coins == 0);
	isTrue(A.numActions == 0);		
	printf("\n\n");

	//Test with two victory cards, one a gardens.
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.deckCount[1]=2;
	A.discardCount[1]=0;
	A.deck[1][0] = duchy;
	A.deck[1][1] = gardens;
	A.coins = 0;
	A.numActions = 0;
	tributeCard(&A, 1,0);

	isTrue(A.handCount[0] == 4);
	isTrue(A.coins == 0);
	isTrue(A.numActions == 0);		
	printf("\n\n");

	//Test with two identical cards.
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.deckCount[1]=2;
	A.discardCount[1]=0;
	A.deck[1][0] = copper;
	A.deck[1][1] = copper;
	A.coins = 0;
	A.numActions = 0;
	tributeCard(&A, 1,0);

	isTrue(A.coins == 2);
	isTrue(A.numActions == 0);		
	printf("\n\n");

	//Test with one card
	A.handCount[0] = 0;
	A.hand[0][0] = tribute;
	A.deckCount[1]=1;
	A.discardCount[1]=0;
	A.deck[1][0] = copper;
	A.coins = 0;
	A.numActions = 0;
	tributeCard(&A, 1,0);

	isTrue(A.coins == 2);
	isTrue(A.numActions == 0);		
	printf("\n\n");
	return 0;

}
