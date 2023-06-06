#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include "vector.h"
#include "Round.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 4764964
#define QUEEN_SPADE 23
#define HAND_SIZE 13
#define END_GAME 100


static ADTErr DealCard( Round *_rund);
static ADTErr ShiftCards ( Round *_rund) ;
static ADTErr Shifting ( Round *_rund, int _mod);
static ADTErr TableCards ( Round *_rund);
static int GettingPoints (Round *_rund);
static Info *InfoCreate();
static int MidGame(int _num, void* _info, Vector *_hand);
static int MaxHand(int _num,void* _info, Vector *_hand);


Round *CreateRound(int _numOfPleyers, Player *_plyrs ,int _roundNum )
{
    int i;
	Round *dmnRound;
    Deck *tempDeck;
    Player *tempPlyrs;
	Info *tempInfo;
    if((dmnRound =(Round*)malloc(sizeof(Round))) == NULL)
	{
		return NULL;
	}
    if((tempDeck =(Deck*)malloc(sizeof(Deck))) == NULL)
	{
		return NULL;
	}
    tempDeck=CreateDeck();
    if( tempDeck == NULL)
	{
		free(dmnRound);
		return NULL;
	}
    dmnRound->m_deck=tempDeck;
	if((tempInfo =(Info*)malloc(sizeof(Info))) == NULL)
	{
		return NULL;
	}
    tempInfo=InfoCreate();
    if( tempInfo == NULL)
	{
		free(dmnRound);
		return NULL;
	}
    dmnRound->m_info=tempInfo;
    if((tempPlyrs =(Player*)malloc(_numOfPleyers*sizeof(Player))) == NULL)
	{
		return NULL;
	}
	dmnRound->m_plyrs=tempPlyrs;
    for (i=0; i< _numOfPleyers; i++)
    {
        tempPlyrs=(Player*)malloc(_numOfPleyers*sizeof(Player));
        *tempPlyrs=_plyrs[i];
        dmnRound->m_plyrs[i]=*tempPlyrs;
        if (&dmnRound->m_plyrs[i] == NULL)
        {
			free(tempPlyrs);
            return NULL;
        }
    }
	tempPlyrs=_plyrs;
    if( tempPlyrs == NULL)
	{
		free(dmnRound);
		return NULL;
	}

	for (i=0; i< _numOfPleyers; i++)
    {
        dmnRound->m_score[i]=0;
    }
    
    dmnRound->m_nunOfPleyers=_numOfPleyers;
    dmnRound->m_roundNum=_roundNum;
}


void DestroyRound( Round *_round)
{
    if(_round != NULL && _round->m_magicNumber == MAGIC_NUMBER)
	{
        DestroyDeck( _round-> m_deck);
        free(_round->m_plyrs);
		free(_round->m_info);
        _round->m_magicNumber =0;
		free(_round);
	}
}

ADTErr RunRound (Round *_rund, int _roundNum)
{
	int i;
	Deck *tempDeck;
	ADTErr stat;
	if(_rund== NULL )
	{
		return ERR_NOT_INITIALIZED;
	}
	tempDeck=CreateDeck();
    if( tempDeck == NULL)
	{
		free(_rund);
		return ERR_ALLOCATION_FAILED;
	}
    _rund->m_deck=tempDeck;
	
	stat=ShuffleDeck(_rund->m_deck);
	if( stat!= ERR_OK)
	{
		return stat;
	}
	stat=DealCard(_rund);
	if( stat!= ERR_OK)
	{
		
		return stat;
	}
	_rund->m_roundNum=_roundNum;
	if(_rund->m_roundNum%4 != 3)
	{
		stat=ShiftCards (_rund);
		if( stat!= ERR_OK)
		{
			return stat;
		}
	}
	for (i=0 ; i<HAND_SIZE; i++)
	{
		TurnNum(i);
		_rund->m_info->m_turnNum=i;
		stat=TableCards(_rund);
		if( stat!= ERR_OK)
		{
			return stat;
		}
		stat=ScoreNAddress(_rund);
		if( stat!= ERR_OK)
		{
			return stat;
		}
		_rund->m_info->m_leadRank=-1;
		_rund->m_info->m_leadSuit=-1;
	}
	PrintScore(_rund->m_plyrs, _rund->m_score, _rund->m_nunOfPleyers);
	DestroyDeck(_rund->m_deck);
	free(_rund->m_info);
	return stat;
}

ADTErr ScoreNAddress(  Round *_rund)
{
	int i, turnScore=0, card, getsPoint;
	if(_rund== NULL )
	{
		return ERR_NOT_INITIALIZED;
	}
	for (i=0; i< _rund->m_nunOfPleyers; i++)
	{
		card= _rund->m_cards[i];
		PrintTurn(&_rund->m_plyrs[i], card);
		if(SUIT(card) == HEART)
		{
			turnScore++;
		} 
		if (card == QUEEN_SPADE)
		{
			turnScore=turnScore+13;
		}
	}
	getsPoint=GettingPoints(_rund);
	_rund->m_first=getsPoint;
	_rund->m_score[getsPoint]+=turnScore;
	return ERR_OK;
}

int IsEnd(Round *_rund )
{
	int i, win = 0,minimum, flag=0;
	minimum=_rund->m_score[0];
	for ( i=0; i<_rund->m_nunOfPleyers; i++)
	{
		if (minimum > _rund->m_score[i])
		{
			minimum= _rund->m_score[i];
			win = i;
		}
		if (_rund->m_score[i]>=END_GAME)
		{
			flag=1;
		}

	}
	if (flag)
	{
		return win;
	}
	return -1;
}


int IsLegal(int _card, void *_info, Vector *_hand)
{
	size_t i, n;
	Info *tempInfo;
	int tempCard, rankDuty=0, firstDuty=0;
	tempInfo= (Info*)_info;
	VectorItemsNum( _hand, &n);
	if(n==1)
	{
		return OK;
	}
	if( tempInfo->m_isFirst == 1  && tempInfo->m_turnNum != 0)
	{
		if(SUIT(_card) != HEART)
		{
			return OK;
		} else if ( tempInfo->m_isHeartBrok==1)
		{
			return OK;
		} else
		{
			return NOT_OK;
		}
	}
	for( i=0; i< n-1; i++)
	{
		VectorGet(_hand, i, &tempCard);
		if(SUIT(tempCard) ==  tempInfo->m_leadSuit)
		{
			rankDuty=1;
		}
		if(tempCard==39)
		{
			firstDuty=1;
		}
	}
	if(firstDuty==1 && _card != 39)
	{
		return NOT_OK;
	}
	if(SUIT(_card) == tempInfo->m_leadSuit || (rankDuty==0 && SUIT(_card) != tempInfo->m_leadSuit))
	{
		return OK;
	}
	return OK;
}

static Info *InfoCreate()
{
	Info *dnmInfo;
	if((dnmInfo =(Info*)malloc(sizeof(Info))) == NULL)
	{
		return NULL;
	}
	dnmInfo->m_isHeartBrok=0;
	dnmInfo->m_leadRank=0;
	dnmInfo->m_leadSuit=0;
	return dnmInfo;
}
static ADTErr DealCard( Round *_rund)
{
	int card, j, i;
	ADTErr stat;
	if(_rund== NULL )
	{
		
		return ERR_NOT_INITIALIZED;
	}
	for (j=0; j< _rund->m_nunOfPleyers; j++)
	{
		
		for(i=0; i< HAND_SIZE ; i++)
		{
			stat=PopCard(_rund->m_deck, &card);
			if( stat!= ERR_OK)
			{
				
				return stat;
			}
			if ( card == 39)
			{
				_rund->m_first=j;
			}
			stat=GetCard (&_rund->m_plyrs[j], card);
			if( stat!= ERR_OK)
			{
				return stat;
			}
		}
	}
	return stat;
}

static ADTErr ShiftCards ( Round *_rund) 
{
	int card, j, i=0;
	ADTErr stat;
	if(_rund== NULL )
	{
		
		return ERR_NOT_INITIALIZED;
	}

	for (j=0; j< _rund->m_nunOfPleyers*3; j++)
	{
		stat=ThrowCard (&_rund->m_plyrs[i] ,_rund->m_info, MaxHand, NULL, &card);
		if( stat!= ERR_OK)
		{
			return stat;
		}
		_rund->m_shift[j]=card;
		if(j%3==2)
		{
			i++;
		}
	}
	
	stat=Shifting ( _rund, _rund->m_roundNum%4);
	return stat;
}


static ADTErr Shifting ( Round *_rund, int _mod)
{
	int card, j, i;
	ADTErr stat= ERR_OK;
	if(_rund== NULL )
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_mod==0)
	{
		i=_rund->m_nunOfPleyers-1;
		for (j=0; j< _rund->m_nunOfPleyers*3; j++)
		{
			stat=GetCard ( &_rund->m_plyrs[i] , _rund->m_shift[j]);
			if( stat!= ERR_OK)
			{
				return stat;
			}
			if(j%3==2)
			{
				i=(i+1)%_rund->m_nunOfPleyers;
			}
		}
	}
	if(_mod==1  || _mod==2)
	{
		i=_mod;
		for (j=0; j< _rund->m_nunOfPleyers*3; j++)
		{
			stat=GetCard ( &_rund->m_plyrs[i] , _rund->m_shift[j]);
			if( stat!= ERR_OK)
			{
				return stat;
			}
			if(j%3==2)
			{
				i=(i+1)%_rund->m_nunOfPleyers;
			}
		}
	}
	return stat;
}

static ADTErr TableCards ( Round *_rund)
{
	int card, j, i;
	ADTErr stat;
	if(_rund== NULL )
	{
		return ERR_NOT_INITIALIZED;
	}
	i=_rund->m_first;
	for (j=0; j< _rund->m_nunOfPleyers; j++)
	{
		stat=ThrowCard ( &_rund->m_plyrs[i] ,_rund->m_info, MidGame, IsLegal, &card);
		if( stat!= ERR_OK)
		{
			return stat;
		}
		if(SUIT(card)==HEART)
		{
			_rund->m_info->m_isHeartBrok=1;
		}
		if(j==0)
		{
			_rund->m_info->m_leadRank= RANK(card);
			_rund->m_info->m_leadSuit= SUIT(card);
		}
		
		_rund->m_cards[i]=card;
		i=(i+1)%_rund->m_nunOfPleyers;
	}

	return stat;
}



static int GettingPoints (Round *_rund)
{
	int i, leadSuit, card, worst, lose;
	worst=_rund->m_cards[_rund->m_first];
	leadSuit=SUIT(worst);
	lose=_rund->m_first;
	for (i=0; i< _rund->m_nunOfPleyers; i++)
	{
		card=_rund->m_cards[i];
		if((SUIT(card) == leadSuit)  &&  (RANK(card) >= RANK(worst)))
		{
			worst=card;
			lose=i;		
		}
	}
	PrintLose( &_rund->m_plyrs[lose]);
	return lose;
}

static int MidGame(int _num, void* _info, Vector *_hand)
{
	Info *turnInfo;
	size_t i, n, index=0;
	int legal,place, choose, isSuit, high, tempCard;
	int option[HAND_SIZE][2];
	place=0;
	choose=-1;
	isSuit=-1;
	high=-1;
	turnInfo= (Info*)_info;
	VectorItemsNum( _hand, &n);
	if(n==1)
	{
		return 0;
	}
	for( i=0; i< n-1; i++)
	{
		VectorGet(_hand, i, &tempCard);
		legal=IsLegal(tempCard, turnInfo, _hand);
		if(legal==OK)
		{
			option[place][0]=tempCard;
			option[place][1]=i;
			place++;
		}
	}
	if(place==1)
	{
		return option[place][1];
	}
	for( i=0; i< place-1; i++)
	{
		if(SUIT(option[i][0])==turnInfo->m_leadSuit)
		{
			isSuit=1;
		}
		if((RANK(option[i][0]) <= turnInfo->m_leadRank )|| isSuit==1)
		{
			if(choose<option[i][0])
			{
				choose=option[i][0];
				index=option[i][1];
			}
		}
		if(SUIT(option[i][0]) !=turnInfo->m_leadSuit)
		{
			if(high < option[i][0])
			{
				high=option[i][0];
				index=option[i][1];
			}
		}
	}

	return index;
}

static int MaxHand(int _num,void* _info, Vector *_hand)
{
	size_t i, n, index=0;
	int tempCard, maxCard=-1;
	VectorItemsNum( _hand, &n);
	for( i=0; i< n-1; i++)
	{
		VectorGet(_hand, i, &tempCard);
		if (RANK(tempCard) > RANK(maxCard) )
		{
			index=i;
			maxCard=tempCard;
		}
	}
	return index;
}