#ifndef __DECK_H__
#define __DECK_H__
#include "ADTDefs.h"
#include "Card.h"
#include "vector.h"

typedef struct Deck Deck;

struct Deck
{
	Vector *m_cards; /*A vector of the cards in the deck*/
	int m_magicNumber;
};


/*
Description: The function creates a dynamic Deck
Input: NA
Output:struct DynamicArray
Errors: NULL if can't create deck
*/
Deck *CreateDeck(  );


/* 
Description: The function destroys a dynamic structure
Input:_deck- struct to destroy
Output:NA
Errors: NA
*/
void DestroyDeck( Deck *_deck );


/* 
Description: The function showing the deck as a vector
Input:_deck- struct to show
Output: vector of the dack
Errors: NULL if _deck is NULL
*/
Vector *ShowDeck( Deck *_deck );


/* 
Description: The function popping card from the deck
Input:_deck- struct to show, _card-popped card
Output: ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_UNDERFLOW
*/
ADTErr PopCard( Deck *_deck , int *_card);


/* 
Description: The function shuffles the deck
Input:_deck- struct to shuffle
Output: ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_WRONG_INDEX
*/
ADTErr ShuffleDeck( Deck *_deck );

#endif /* #ifndef __DECK_H__ */
