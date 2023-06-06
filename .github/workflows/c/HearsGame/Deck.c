#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include "vector.h"
#include "Deck.h"
#include "Card.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 888853
#define DECK_SIZE 52




Deck *CreateDeck( )
{
	Deck *dmnDeck;
    int size, i;
	Vector *temp;
	if((dmnDeck =(Deck*)malloc(sizeof(Deck))) == NULL)
	{
		return NULL;
	}
    if((temp =(Vector*)malloc(sizeof(Vector))) == NULL)
	{
		return NULL;
	}
	temp=VectorCreate(DECK_SIZE,0);
	if( temp == NULL)
	{
		free(dmnDeck);
		return NULL;
	}
	dmnDeck->m_cards=temp;
    for ( i = 0; i < DECK_SIZE ; i++)
    {
       VectorAdd(dmnDeck->m_cards, i);
    }
	dmnDeck->m_magicNumber=MAGIC_NUMBER;
	return dmnDeck;
}


void DestroyDeck( Deck *_deck )
{
    if(_deck != NULL && _deck->m_magicNumber == MAGIC_NUMBER)
	{
		_deck->m_magicNumber =0;
		VectorDestroy(_deck->m_cards);
		free(_deck);
	}
}


ADTErr PopCard( Deck *_deck , int *_card)
{
    if(_deck==NULL || _card== NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDelete (_deck->m_cards , _card);
}


ADTErr ShuffleDeck( Deck *_deck )
{
    int newIndx,i;
	if(_deck==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
    for ( i = 0; i < DECK_SIZE ; i++)
    {
       newIndx=rand()%DECK_SIZE;
       swap(_deck->m_cards, i , newIndx);
    }
}

Vector *ShowDeck( Deck *_deck )
{
	if(_deck==NULL)
	{
		return NULL;
	}
	return _deck->m_cards;
}