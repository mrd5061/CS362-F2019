
/*
 * Include the following lines in your makefile:
 *
 * unittestBug9: unittestBug9.c dominion.c rngs.c
 *	 gcc -o unittestBug9 -g  unittestBug9.c dominion.c rngs.c $(CFLAGS)
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

//tests tribute case with next player revealing two of the same treasure card - Bug 9
void posCase(struct gameState *post, int currentPlayer, int nextPlayer) {

  int coin_bonus = 0;
  int handPos = 0;

//set initial player conditions
//------------------------------------------------------------------------------
    //current player
    post->hand[currentPlayer][0] = tribute;
    post->handCount[currentPlayer] = 1;

    post->deck[currentPlayer][0] = minion;
    post->deck[currentPlayer][1] = minion;
    post->deck[currentPlayer][2] = minion;
    post->deck[currentPlayer][3] = minion;
    post->deck[currentPlayer][4] = minion;
    post->deck[currentPlayer][5] = minion;
    post->deckCount[currentPlayer] = 6;

    //next player
    post->deck[nextPlayer][0] = copper;
    post->deck[nextPlayer][1] = copper;
    post->deck[nextPlayer][2] = copper;
    post->deck[nextPlayer][3] = copper;
    post->deck[nextPlayer][4] = copper;
    post->deck[nextPlayer][5] = copper;
    post->deckCount[nextPlayer] = 6;

    post->coins = 0;

    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int r;
    int tributeRevealedCardsPre[2] = {-1, -1};
//run test function
//----------------------------------------------------------------------------------
    //run tribute case of cardEffect()
    //r = playCard(handPos, 0, 0, 0, post);
    r = cardEffect(tribute, 0, 0, 0, post, handPos, &coin_bonus);

    //increase coins by 2
    pre.coins+=2;

    //reduce number of actions because played tributeRevealedCard
    //pre.numActions--;

    //add two cards to tribute revealed array and then discard from next player's deck
    for(int j = 0; j<2; j++)
    {
      //add to tributeRevealedCards
      tributeRevealedCardsPre[j] = pre.deck[nextPlayer][pre.deckCount[nextPlayer]-1];
      //add revealed card to discard
      pre.discard[nextPlayer][pre.discardCount[nextPlayer]] = pre.deck[nextPlayer][pre.deckCount[nextPlayer]-1];
      pre.discardCount[nextPlayer]++;
      //remove from deck
      pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1] = -1;
      pre.deckCount[nextPlayer]--;
    }

  //check asserts
  //-----------------------------------------------------------------
    //checks the number of actions
    myAssert ((post->numActions) == (pre.numActions), __LINE__, __FILE__);
    printf("\tExpected number of Actions = %d, Result = %d\n", (pre.numActions), (post->numActions));

    //checks the number of coins
    myAssert (post->coins== pre.coins, __LINE__, __FILE__);
    printf("\tExpected number of coins = %d, Result = %d\n", pre.coins, post->coins);

    //assert that the number of cards in the current player's hand remained the same
    //myAssert (post->handCount[currentPlayer] == pre.handCount[currentPlayer], __LINE__, __FILE__);
    //printf("\tExpected number of cards in current player's hand = %d, Results = %d\n", pre.handCount[currentPlayer], post->handCount[currentPlayer]);

    //assert that the number of cards in the current player's deck remained the same
    //myAssert (post->deckCount[currentPlayer] == pre.deckCount[currentPlayer], __LINE__, __FILE__);
    //printf("\tExpected number of cards in current player's deck = %d, Results = %d\n", pre.deckCount[currentPlayer], post->deckCount[currentPlayer]);

}

int main() {
  int numPlayers = 2;
  int seed = 1000;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, tribute
              };

  struct gameState G;

  printf ("Starting unittestBug9 for tribute case - Improper Handling of Duplicate Revealed Cards.\n");

  //initialize game states
  initializeGame(numPlayers, k, seed, &G);
  int currentPlayer = G.whoseTurn;
  int nextPlayer = currentPlayer+1;
  posCase(&G, currentPlayer, nextPlayer);

  printf("Ending unittestBug9.\n");

  exit(0);
}
