#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#define isTrue(x) do {if(!(x)) {printf("test failed\n");} else{printf("test passed\n");}}while(0)

int main()
{

	/* Test One: Player elected to discard estate with estate in hand*/
	//set variables
	struct gameState A;

	A.handCount[0] = 1;
	A.hand[0][0] = estate;
	A.supplyCount[estate]=2;
	A.coins = 0;
	//add estate card to player's hand
	gainCard(estate,&A,2,0);

	printf("Begin baronCard test\n");
	baronCard(1,&A,0);
	//assert +4 coins
	isTrue(A.coins == 4);
	//assert player has -1 cards in hand
	isTrue(A.handCount[0] == 0);
	//assert player has one less estate card
	isTrue(A.hand[0][0]!= estate);
	//assert that estate supply count is still 2
	isTrue(A.supplyCount[estate] == 2);
	printf("\n");

	//elected to discard estate without estate in hand
	A.handCount[0] = 0;
	A.hand[0][0] = -1;
	A.coins =0;
	A.supplyCount[estate] = 2;

	
	baronCard(1, &A,0);

	//Coins should be
	isTrue(A.coins == 0);
	//hand count should be 1
	isTrue(A.handCount[0] == 1);
	//Player card should be estate
	isTrue(A.hand[0][0] == estate);
	//State Supply count should be 1	
	isTrue(A.supplyCount[estate] == 1);

	//elected to gain estate
	A.handCount[0] = 0;
	A.hand[0][0] = -1;
	A.coins =0;
	A.supplyCount[estate] = 2;

	baronCard(0, &A,0);

	//Coins should be 0
	isTrue(A.coins == 0);
	//hand count should be 1\n
	isTrue(A.handCount[0] == 1);
	//Player card should be estate
	isTrue(A.hand[0][0] == estate);
	//State Supply count should be 1
	isTrue(A.supplyCount[estate] == 1);

	return 0;

}
