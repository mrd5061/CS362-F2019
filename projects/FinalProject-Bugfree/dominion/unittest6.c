#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include "dominion.h"

void assertEqual(int a, int b)
{
  if (!(a == b))
    printf("Assertion failed: %d == %d\n", a, b);
  else
    printf("Assertion passed!\n");
}

void testcase1()
{
  printf("Testing feast card...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               feast,
               gardens,
               mine,
               remodel,
               smithy,
               village,
               baron,
               great_hall};
  int numPlayers = 2;
  int seed = 1000;
  int currentPlayer = 0;
  struct gameState G;

  // Reset game state & initialize new game
  int result = initializeGame(numPlayers, k, seed, &G); // also initializes hand with coppers
  if (result != 0)
  {
    perror("Could not initialize test game state");
    exit(1);
  }

  // Set up test variables
  int handPos = G.handCount[currentPlayer] - 1;
  int bonus = 0;
  int cardToGain = gold;

  result = cardEffect(feast, cardToGain, -1, -1, &G, handPos, &bonus); // Call function
  assertEqual(result, -1);                                             // Assert that player did not gain card
}

int main()
{
  printf("Testing bug fixes for Dominion Bug #6:\n");

  testcase1();

  printf("Tests for Dominion Bug #6 fixes completed!\n\n");
  return 0;
}