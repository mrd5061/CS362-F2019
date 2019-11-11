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

	/* Test One: Player trades a silver card for a gold card*/
	struct gameState A;
	A.hand[0][0] = silver;
	A.handCount[0] = 1;
	A.supplyCount[gold] = 1;
	printf("Start mineCard test\n");
	mineCard(0, gold, &A, 0, 0);
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == gold);
	isTrue(A.supplyCount[gold] == 0);
	printf("\n\n");

	/* Test Two: Player trades a copper for a silver*/

	A.hand[0][0] = copper;
	A.handCount[0] = 1;
	A.supplyCount[silver] = 1;
	mineCard(0, silver, &A, 0, 0);
	
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == silver);
	isTrue(A.supplyCount[silver] == 0);
	printf("\n\n");

	/* Test three: Player trades a copper card for a gold card*/
	A.hand[0][0] = copper;
	A.handCount[0] = 1;
	A.supplyCount[gold] = 1;
	int result = mineCard(0, gold, &A, 0, 0);
	
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == copper);
	isTrue(A.hand[0][0] != gold);
	isTrue(A.supplyCount[gold] == 1);
	isTrue(result==-1);
	printf("\n\n");
	
	/* Test four Player trades a silver card for a smithy card*/

	A.hand[0][0] = silver;
	A.handCount[0] = 1;
	A.supplyCount[adventurer] = 1;
	
	result = mineCard(0, adventurer, &A, 0, 0);
	
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == silver);
	isTrue(A.hand[0][0] != adventurer);

	isTrue(A.supplyCount[adventurer] == 1);
	isTrue(result==-1);
	printf("\n\n");

	/* Test five: Player trades an estate card for a baron card*/

	A.hand[0][0] = estate;
	A.handCount[0] = 1;
	A.supplyCount[baron] = 1;
	result = mineCard(0, baron, &A, 0, 0);
	
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == estate);
	isTrue(A.supplyCount[baron] == 1);
	isTrue(result == -1);
	
	A.hand[0][0] = silver;
	A.handCount[0] = 1;
	A.supplyCount[estate] = 1;
	printf("\n\n");

	
	result = mineCard(0, estate, &A, 0, 0);
	
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == silver);
	isTrue(A.supplyCount[estate]==1);
	isTrue(result == -1);

	A.hand[0][0] = silver;
	A.handCount[0] = 1;
	A.supplyCount[duchy] = 1;
	printf("\n\n");
	
	result = mineCard(0, duchy, &A, 0, 0);
	
	isTrue(A.handCount[0] == 1);
	isTrue(A.hand[0][0] == silver);
	isTrue(A.supplyCount[duchy]==1);
	isTrue(result == -1);
	printf("\n\n");
	return 0;

}
