#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)
int main()
{
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
	initializeGame(2,k,30,&G);

	G.handCount[0] = 2;
	G.hand[0][0] = remodel;
	G.hand[0][1] = estate;
	int coinBonus = 0;
	G.supplyCount[great_hall] = 1;
	for(int i=2; i<5; i++)
	{
		G.hand[0][i] = -1;
	}

	int r = cardEffect(remodel,1, great_hall, -1, &G,0, &coinBonus);
	
	printf("Start Unit Test 3\n");
	isTrue(r==0);
	isTrue(G.handCount[0] == 0);
	isTrue(G.playedCardCount == 2);
	isTrue(G.discardCount[0] ==1);
	isTrue(G.discard[0][0] == great_hall);
	
	
	printf ("\n");
    return 0;
}
