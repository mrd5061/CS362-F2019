#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include "dominion.h"

int assertEqual(int a, int b)
{
  if (!(a == b))
  {
    printf("Assertion failed: %d == %d\n", a, b);
    return 1;
  }
  return 0;
}

void shuffleArray(int *array, size_t n)
{
  if (n > 1)
  {
    size_t i;
    for (i = 0; i < n - 1; i++)
    {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void testcase1()
{
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
  struct gameState G;

  // Reset game state & initialize new game
  int result = initializeGame(numPlayers, k, seed, &G);
  if (result != 0)
  {
    perror("Could not initialize test game state");
    exit(1);
  }

  // Set up test variables
  if (rand() % 10)
  {
    G.supplyCount[NUM_CARD_TYPES - 1] = 0;
    G.supplyCount[NUM_CARD_TYPES - 2] = 0;
    G.supplyCount[NUM_CARD_TYPES - 3] = 0;
  }
  else
  {
    int choices[NUM_CARD_TYPES] = {0};
    choices[0] = 1;
    choices[1] = 1;
    choices[2] = 1;
    shuffleArray(choices, NUM_CARD_TYPES);

    int i;
    for (i = 0; i < NUM_CARD_TYPES; i++)
    {
      if (choices[i])
        G.supplyCount[i] = 0;
    }
  }

  result = isGameOver(&G);                   // Call function
  int assertFailed = assertEqual(result, 1); // Assert that the game is over
  if (assertFailed)
  {
    printf("\t{");
    int i;
    for (i = 0; i < NUM_CARD_TYPES; i++)
    {
      printf("%c", (G.supplyCount[i] == 0) ? '0' : ',');
    }
    printf("}\n");
  }
}

int main()
{
  printf("Testing bug fixes for Dominion Bug #4:\n");

  int i;
  for (i = 0; i < 100; i++)
    testcase1();

  printf("Tests for Dominion Bug #4 fixes completed!\n\n");
  return 0;
}