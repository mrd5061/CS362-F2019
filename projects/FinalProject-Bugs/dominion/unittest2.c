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
	G.supplyCount[gold] = 1;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;
	int coinBonus = 0;
	for(int i=2; i<5; i++)
	{
		G.hand[0][i] = -1;
	}	

	int r = cardEffect(mine, 1, gold, -1, &G,0, &coinBonus);
	printf("Start Unit Test 2\n");
	isTrue(G.handCount[0] == 2);
	isTrue(G.hand[0][0] == mine);
	isTrue(G.hand[0][1] == copper);
	isTrue( r == -1);

	printf("\n");
	
	return 0;
}
