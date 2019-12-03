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
  printf("Testing with cards only in deck...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               duchy,
               province,
               mine,
               estate,
               smithy,
               village,
               curse,
               great_hall};
  int numPlayers = 2;
  int seed = 1000;
  int currentPlayer = 0;
  struct gameState G;

  // Reset game state & initialize new game
  int result = initializeGame(numPlayers, k, seed, &G);
  if (result != 0)
  {
    perror("Could not initialize test game state");
    exit(1);
  }

  // Set up test variables
  G.handCount[currentPlayer] = 0;
  G.discardCount[currentPlayer] = 0;

  G.deckCount[currentPlayer] = 5;
  int deckCards[5] = {curse, estate, duchy, province, great_hall};
  int i;
  for (i = 0; i < G.deckCount[currentPlayer]; i++)
  {
    G.deck[currentPlayer][i] = deckCards[i];
  }

  int score = scoreFor(currentPlayer, &G); // Call function
  assertEqual(score, 10);                  // Assert that score is 10 = curse+estate+duchy+province+great_hall = -1+1+3+6+1
}

void testcase2()
{
  printf("Testing with cards only in discard pile...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               duchy,
               province,
               mine,
               estate,
               smithy,
               village,
               curse,
               great_hall};
  int numPlayers = 2;
  int seed = 1000;
  int currentPlayer = 0;
  struct gameState G;

  // Reset game state & initialize new game
  int result = initializeGame(numPlayers, k, seed, &G);
  if (result != 0)
  {
    perror("Could not initialize test game state");
    exit(1);
  }

  // Set up test variables
  G.deckCount[currentPlayer] = 0;
  G.handCount[currentPlayer] = 0;

  G.discardCount[currentPlayer] = 5;
  int discardCards[5] = {curse, estate, duchy, province, great_hall};
  int i;
  for (i = 0; i < G.discardCount[currentPlayer]; i++)
  {
    G.discard[currentPlayer][i] = discardCards[i];
  }

  int score = scoreFor(currentPlayer, &G); // Call function
  assertEqual(score, 10);                  // Assert that score is 10 = curse+estate+duchy+province+great_hall = -1+1+3+6+1
}

void testcase3()
{
  printf("Testing with cards only in hand...\n");

  // Set up game variables
  int k[10] = {adventurer,
               council_room,
               duchy,
               province,
               mine,
               estate,
               smithy,
               village,
               curse,
               great_hall};
  int numPlayers = 2;
  int seed = 1000;
  int currentPlayer = 0;
  struct gameState G;

  // Reset game state & initialize new game
  int result = initializeGame(numPlayers, k, seed, &G);
  if (result != 0)
  {
    perror("Could not initialize test game state");
    exit(1);
  }

  // Set up test variables
  G.discardCount[currentPlayer] = 0;
  G.deckCount[currentPlayer] = 0;

  G.handCount[currentPlayer] = 5;
  int handCards[5] = {curse, estate, duchy, province, great_hall};
  int i;
  for (i = 0; i < G.handCount[currentPlayer]; i++)
  {
    G.hand[currentPlayer][i] = handCards[i];
  }

  int score = scoreFor(currentPlayer, &G); // Call function
  assertEqual(score, 10);                  // Assert that score is 10 = curse+estate+duchy+province+great_hall = -1+1+3+6+1
}

int main()
{
  printf("Testing bug fixes for Dominion Bug #5:\n");

  testcase1();
  testcase2();
  testcase3();

  printf("Tests for Dominion Bug #5 fixes completed!\n\n");
  return 0;
}