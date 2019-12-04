
/*
 * Include the following lines in your makefile:
 *
 * unittestBug10: unittestBug10.c dominion.c rngs.c
 *	 gcc -o unittestBug10 -g  unittestBug10.c dominion.c rngs.c $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"
#include <stdlib.h>

//#define TESTCARD "steward"
#define DEBUG 0
#define NOISY_TEST 1

int myAssert(int expression, int line, const char *file){
  if(expression==0){
    printf("Error found on line %d while running %s:\n", line, file);
    return -1;
  }
  else{
    printf("PASS!\n");
    return 0;
  }
}

//tests ambassador case of cardEffect() - Bug 10
void posCase(struct gameState *post, int currentPlayer, int nextPlayer) {

  int coin_bonus = 0;
  int handPos = 0;

//set initial player conditions
//------------------------------------------------------------------------------
    //current player
    post->hand[currentPlayer][0] = ambassador;
    post->hand[currentPlayer][1] = village;
    post->hand[currentPlayer][2] = village;
    post->hand[currentPlayer][3] = village;
    post->hand[currentPlayer][4] = village;
    post->handCount[currentPlayer] = 5;

    post->hand[nextPlayer][0] = gold;
    post->hand[nextPlayer][1] = gold;
    post->handCount[nextPlayer] = 2;

    post->coins = 0;

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int r;

//run test function
//----------------------------------------------------------------------------------
    //run ambassador case of cardEffect() with choice to return 2 villages to supply
    r = cardEffect(ambassador, 1, 2, 0, post, handPos, &coin_bonus);

    pre.hand[currentPlayer][0] = village;
    pre.hand[currentPlayer][1] = village;
    pre.handCount[currentPlayer] = 2;

    pre.supplyCount[village] += 1;

    pre.discardCount[nextPlayer] = 1;
    pre.discard[nextPlayer][0] = village;

//check asserts
//-----------------------------------------------------------------
  //make sure the function thinks it executed correctly
  myAssert(r==0, __LINE__, __FILE__);
  printf("\tExpected return of cardEffect() = 0, Result = %d\n", r);

  //asserts that hand count of current player reduced appropriately
  myAssert(pre.handCount[currentPlayer]==post->handCount[currentPlayer], __LINE__, __FILE__);
  printf("\tExpected hand count of current player = %d, Result = %d\n", pre.handCount[currentPlayer], post->handCount[currentPlayer]);

  //asserts that discard count of current player increased appropriately
  myAssert(pre.discardCount[nextPlayer]==post->discardCount[nextPlayer], __LINE__, __FILE__);
  printf("\tExpected discard count of second player = %d, Result = %d\n", pre.discardCount[nextPlayer], post->discardCount[nextPlayer]);

  //asserts that supply count of village pile increased appropriately
  myAssert(pre.supplyCount[village]==post->supplyCount[village], __LINE__, __FILE__);
  printf("\tExpected supply count of village supply = %d, Result = %d\n", pre.supplyCount[village], post->supplyCount[village]);
}

int main() {
  int numPlayers = 2;
  int seed = 1000;

  int k[10] = {ambassador, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, tribute
              };

  struct gameState G;

  printf ("Starting unittestBug10 for ambassador case - Improperly searches for Cards to Return to Supply.\n");

  //initialize game states
  initializeGame(numPlayers, k, seed, &G);
  int currentPlayer = G.whoseTurn;
  int nextPlayer = currentPlayer+1;
  posCase(&G, currentPlayer, nextPlayer);

  printf("Ending unittestBug10.\n");

  exit(0);
}
