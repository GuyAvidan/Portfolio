#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include <string.h>
#include "vector.h"
#include "Player.h"
#include "Card.h"
#include "UI.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 684684
#define HAND_SIZE 13



Player *CreatePlayer (int _isReal )
{
    Player *dmnPlayer;
	Vector *temp;
	if((dmnPlayer =(Player*)malloc(sizeof(Player))) == NULL)
	{
		return NULL;
	}
    if((temp =(Vector*)malloc(sizeof(Vector))) == NULL)
	{
		return NULL;
	}
	temp=VectorCreate(HAND_SIZE,0);
	if( temp == NULL)
	{
		free(dmnPlayer);
		return NULL;
	}
	dmnPlayer->m_cards=temp;
    dmnPlayer->m_IsReal=_isReal;
	dmnPlayer->m_magicNumber=MAGIC_NUMBER;
	return dmnPlayer;
}

void DestroyPlayer ( Player *_player )
{
    if(_player!= NULL && _player->m_magicNumber == MAGIC_NUMBER)
	{
		_player->m_magicNumber =0;
		VectorDestroy(_player->m_cards);
		free(_player);
	}
}

Vector *ShowHand( Player *_player )
{
	if(_player == NULL)
	{
		return NULL;
	}
	return _player->m_cards;
}


ADTErr GetCard ( Player *_player, int _card)
{
	ADTErr stat;
	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	stat=VectorAdd(_player->m_cards, _card);
	return stat;
}

ADTErr ThrowCard ( Player *_player, void* _info, Strategy _strt ,Strategy _legalFunc  ,int  *_card)
{
	ADTErr stat;
	int loc=14, legal=0, contax;
	size_t roof;
	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_player->m_cards, &roof);
	if(_player->m_IsReal==1)
	{
		PrintHand(_player);
		while ( loc < 0  || loc >= roof || legal==0)
		{
			AskCard();
			scanf("%d", &loc );
			if (loc>=0 && loc < roof )
			{
				swap(_player->m_cards, loc, roof-1);
				stat=VectorGet(_player->m_cards,roof-1 ,_card);
				if( stat!= ERR_OK)
				{
					return stat;
				}
				contax=*_card;
				if(_legalFunc != NULL)
				{
					legal=_legalFunc(contax, _info, ShowHand(_player));
				} else 
				{
					legal=1;
				}
				
			}
		}
		VectorDelete(_player->m_cards,_card);
	}else
	{
		loc=_strt( 0 ,_info, ShowHand(_player));
		
		swap(_player->m_cards, loc, roof-1);
		stat=VectorDelete(_player->m_cards,_card);
		if( stat!= ERR_OK)
		{
			return stat;
		}		
	}
	return stat;
}

ADTErr SetName (Player *_player ,char _name[])
{
	if(_player == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	strcpy(_player->m_name,_name);
	return ERR_OK;
}

char *GetName(Player *_player)
{
	if(_player == NULL)
	{
		return;
	}
	return _player->m_name;
}

ADTErr FindCard (Player *_player ,int _card);