#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#define _XOPEN_SOURCE 600
#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)
int main()
{
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
  	 initializeGame(2,k,30,&G);

	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = silver;
	int coinBonus = 0;
	for(int i=2; i<5; i++)
	{
		G.hand[0][i] = -1;
	}

	cardEffect(mine,1, gold, -1, &G,0, &coinBonus);
	printf("Start Unit Test 1\n");
	isTrue(G.handCount[0] == 1);
	isTrue(G.hand[0][0] == gold);
	isTrue(G.playedCardCount == 1);
	isTrue(G.playedCards[1]!= silver);
	printf("\n");
	return 0;
}
