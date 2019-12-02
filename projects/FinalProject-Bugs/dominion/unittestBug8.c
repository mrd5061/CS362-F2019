
/*
 * Include the following lines in your makefile:
 *
 * unittestBug8: unittestBug8.c dominion.c rngs.c
 *	 gcc -o unittestBug8 -g  unittestBug8.c dominion.c rngs.c $(CFLAGS)
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

//test coins updated properly using baron case of cardEffect() run by playcard - Bug 8
void posCase(int choice1, struct gameState *post, int currentPlayer, int nextPlayer) {
    int handPos = 0;
//set initial player conditions
//------------------------------------------------------------------------------
    post->hand[currentPlayer][0] = baron;
    post->hand[currentPlayer][1] = estate;
    post->hand[currentPlayer][2] = adventurer;
    post->hand[currentPlayer][3] = province;
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
    //run playcard with baron card - choosing to discard Estate
    r = playCard(handPos, 1, 0, 0, post);

    //increase buys by 1
    pre.numBuys++;
    //increase coins by 4
    pre.coins += 4;

    //add Estate to discard pile
    pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][1];
    pre.discardCount[currentPlayer]++;
    //remove Estate from hand
    //replace Estate card with card at end of hand
    pre.hand[currentPlayer][1] = pre.hand[currentPlayer][(pre.handCount[currentPlayer] - 1)];
    //set last card to -1
    pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1] = -1;
    //reduce number of cards in hand
    pre.handCount[currentPlayer]--;

//check asserts
//-----------------------------------------------------------------
    //assert that +4 coins was given for this round only
    myAssert(post->coins == pre.coins, __LINE__, __FILE__);
    printf("\tExpected number of coins = %d, Results = %d\n", pre.coins, post->coins);

    //checks that the number of buys was increased by 1
    //myAssert (post->numBuys == pre.numBuys, __LINE__, __FILE__);
    //printf("\tExpected number of buys = %d, Result = %d\n", pre.numBuys, post->numBuys);

    //assert that number of cards in hand reduced by 1
    //myAssert(post->handCount[currentPlayer] == pre.handCount[currentPlayer], __LINE__, __FILE__);
    //printf("\tExpected hand count = %d, Result = %d\n", pre.handCount[currentPlayer], post->handCount[currentPlayer]);

    //assert that the number of cards in the current player's discard pile was increased by 1
    //myAssert (post->discardCount[currentPlayer] == pre.discardCount[currentPlayer], __LINE__, __FILE__);
    //printf("\tExpected number of cards in discard = %d, Results = %d\n", pre.discardCount[currentPlayer], post->discardCount[currentPlayer]);
    }

int main() {
  int numPlayers = 2;
  int seed = 1000;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall
              };

  struct gameState G;

  printf ("Starting unittestBug8 - CardEffect() Does Not Update coin_bonus Properly.\n");

  //initialize game states
  initializeGame(numPlayers, k, seed, &G);
  int currentPlayer = G.whoseTurn;
  int nextPlayer = currentPlayer+1;
  posCase(1, &G, currentPlayer, nextPlayer);

  printf("Ending unittestBug8.\n");

  exit(0);
}
