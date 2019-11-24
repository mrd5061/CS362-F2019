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

	/* Test One: Normal ambassador action where there are enough cards
	 * to go around in the supply count*/
	struct gameState A;
	int val = -2;
	//initialize the game
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 2;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	//clear out the rest of player one's hand
	for(int i =2; i< 5; i++)
	{
		A.hand[0][i] = -1;
	}
	A.handCount[0] = 2;
	printf("Begin ambassadorCard test \n\n");
	val = ambassadorCard(0,0,&A,1, 0);

	//assert that the function completed normally
	isTrue(val==0);
	//assert that player 1's hand has one card;
	isTrue(A.handCount[0] == 1);
	//Assert that player 2's hand has one card
	isTrue(A.handCount[1] == 1);
	//Assert that player 3's hand has one card
	isTrue(A.handCount[2] == 1);
	//Assert that the supply has one card in it (Started as 2, added card
	//from player 1 then subtracted 2 for the other players)
	isTrue(A.supplyCount[copper] == 1);
	printf("\n");

	/*Player tries to discard 2 copies of the copper card*/

	val = -2;
	//initialize the game
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 2;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = ambassador;
	//clear out the rest of player one's hand
	for(int i =1; i< 5; i++)
	{
		A.hand[0][i] = copper;
	}

	A.handCount[0] = 5;

	//call the function. Player 1 shows a copper card and discards 
	//2 copies.
	val = ambassadorCard(1,2,&A,0,0);

	//assert that the function completed normally
	isTrue(val==0);
	//assert that player 1's hand has two cards;
	isTrue(A.handCount[0] == 2);
	//Assert that player 2's hand has one card
	isTrue(A.handCount[1] == 1);
	//Assert that player 3's hand has one card
	isTrue(A.handCount[2] == 1);
	//Assert that the supply has three cards in it (Started as 2, added card
	//from player 1 then subtracted 2 for the other players)
	isTrue(A.supplyCount[copper] == 3);
	printf("\n");


	/*Test trying to discard more copies than in hand*/
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 2;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	//clear out the rest of player one's hand
	for(int i =2; i< 5; i++)
	{
		A.hand[0][i] = -1;
	}
	A.handCount[0] = 2;

	//call the function. Player 1 elects to only discard the 1 copper
	//card in their hand and no copies.
	val = ambassadorCard(0,1,&A,1, 0);

	//assert that the function completed normally
	isTrue(val==-1);
	//assert that player 1's hand has one card;
	isTrue(A.handCount[0] == 2);
	//Assert that player 2's hand has one card
	isTrue(A.handCount[1] == 0);
	//Assert that player 3's hand has one card
	isTrue(A.handCount[2] == 0);
	//Assert that the supply has one card in it (Started as 2, added card
	//from player 1 then subtracted 2 for the other players)
	isTrue(A.supplyCount[copper] == 2);
	printf("\n");
	
	/*Test that the supply count is incrementing correctly*/
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 1;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	A.hand[0][2] = copper;
	A.hand[0][3] = copper;
	//clear out the rest of player one's hand
	for(int i =4; i< 5; i++)
	{
		A.hand[0][i] = -1;
	}
	A.handCount[0] = 3;

	//call the function. Player 1 elects to only discard the 1 copper
	//card in their hand and no copies.
	val = ambassadorCard(0,1,&A,1,0);

	//assert that the function completed normally
	isTrue(val==0);
	//assert that player 1's hand has one cards;
	isTrue(A.handCount[0] == 1);
	//Assert that player 2's hand has one card
	isTrue(A.handCount[1] == 1);
	//Assert that player 3's hand has one card
	isTrue(A.handCount[2] == 1);
	//Assert that the supply has one card in it (Started as 2, added card
	//from player 1 then subtracted 2 for the other players)
	isTrue(A.supplyCount[copper] == 0);
	printf("\n");

	/*Test negative choice 2*/
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 1;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	A.hand[0][2] = copper;
	A.hand[0][3] = copper;
	//clear out the rest of player one's hand
	for(int i =4; i< 5; i++)
	{
		A.hand[0][i] = copper;
	}
	A.handCount[0] = 5;

	//call the function. Player 1 elects to only discard the 1 copper
	//card in their hand and no copies.
	val = ambassadorCard(0,-4,&A,1,0);

	//assert that the function completed normally
	isTrue(val==-1);
	printf("\n");

	/*Test choice 2 =3*/
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 1;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	A.hand[0][2] = copper;
	A.hand[0][3] = copper;
	//clear out the rest of player one's hand
	for(int i =4; i< 5; i++)
	{
		A.hand[0][i] = copper;
	}
	A.handCount[0] = 5;

	//call the function. Player 1 elects to only discard the 1 copper
	//card in their hand and no copies.
	val = ambassadorCard(0,3,&A,1,0);

	//assert that the function completed normally
	isTrue(val==-1);
	printf("\n");

	/*Test character choice 2*/
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 1;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	A.hand[0][2] = copper;
	A.hand[0][3] = copper;
	//clear out the rest of player one's hand
	for(int i =4; i< 5; i++)
	{
		A.hand[0][i] = copper;
	}
	A.handCount[0] = 5;

	//call the function. Player 1 elects to only discard the 1 copper
	//card in their hand and no copies.
	val = ambassadorCard(0,'{',&A,1,0);

	//assert that the function completed normally
	isTrue(val==-1);
	printf("\n");


	/*Test choice 1 == handPos*/
	initializeGame(3, k,30,&A);
	//Adjust the player supply count for the copper card to 3
	A.supplyCount[copper] = 1;
	//adjust player 1's hand to be an ambassador card and a copper card.
	A.hand[0][0] = copper;
	A.hand[0][1] = ambassador;
	A.hand[0][2] = copper;
	A.hand[0][3] = copper;
	//clear out the rest of player one's hand
	for(int i =4; i< 5; i++)
	{
		A.hand[0][i] = copper;
	}
	A.handCount[0] = 5;

	//call the function. Player 1 elects to only discard the 1 copper
	//card in their hand and no copies.
	val = ambassadorCard(0,0,&A,0,0);

	//assert that the function completed normally
	isTrue(val==-1);
	printf("\n");
	return 0;

}
