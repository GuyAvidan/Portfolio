#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include <time.h>
#include "vector.h"
#include "Game.h"
#include "Card.h"
#include "Deck.h"
#include "Round.h"
#include "Player.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 1561631
char names[6][10]= {"Aron", "Bob", "Calvin", "Daniel", "Eric"};


Game *CreateGame(  int _numOfPleyers, int _real)
{
    Game *dmnGame;
    int size, i;
    Player *plyr;
    Round *tempRound;
    Vector *temp;
    char buff[20];
    srand(time(NULL));
    if( _real > _numOfPleyers)
    {
        return NULL;
    }
	if((dmnGame =(Game*)malloc(sizeof(Game))) == NULL)
	{
		return NULL;
	}
    if((plyr =(Player*)malloc(_numOfPleyers*sizeof(Player))) == NULL)
	{
		free(dmnGame);
		return NULL;
	}
    dmnGame->m_plyr=plyr;
    for (i=0; i< _numOfPleyers-_real; i++)
    {
        plyr=(Player*)malloc(_numOfPleyers*sizeof(Player));
        plyr=CreatePlayer(0);
        dmnGame->m_plyr[i]=*plyr;
        if (&dmnGame->m_plyr[i] == NULL)
        {
            free(dmnGame);
            return NULL;
        }
        SetName (&dmnGame->m_plyr[i], names[i]);
    }
    for (i; i< _numOfPleyers; i++)
    {
        plyr=(Player*)malloc(_numOfPleyers*sizeof(Player));
        plyr=CreatePlayer(1);
        dmnGame->m_plyr[i]=*plyr;
        if (&dmnGame->m_plyr[i] == NULL)
        {
            free(dmnGame);
            return NULL;
        }
        AskName();
        scanf("%s",buff);
        SetName (&dmnGame->m_plyr[i], buff);
    }
    if((tempRound =(Round*)malloc(sizeof(Round))) == NULL)
	{
		free(dmnGame);
		return NULL;
	}
    tempRound=CreateRound(_numOfPleyers, dmnGame->m_plyr ,0);
	for (i=0; i< _numOfPleyers; i++)
    {
        dmnGame->m_score[i]=0;
    }
    dmnGame-> m_gameRound=tempRound;
    dmnGame->m_roundNum=0;
    dmnGame->m_nunOfPleyers=_numOfPleyers;
	dmnGame->m_magicNumber=MAGIC_NUMBER;
	return dmnGame;
}


void DestroyGame( Game *_game)
{
    int i;
    if(_game != NULL && _game->m_magicNumber == MAGIC_NUMBER)
	{
        DestroyPlayer (_game->m_plyr);
        DestroyRound( _game-> m_gameRound);
        _game->m_magicNumber =0;
		free(_game);
	}
}

ADTErr RunGame( Game *_game)
{
    int round_num, win=-1;
    Round *roundGame;
    ADTErr stat;
    if(_game==NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    _game->m_gameRound =CreateRound(_game->m_nunOfPleyers , _game->m_plyr, _game->m_roundNum);
    if(_game->m_gameRound==NULL)
    {
        return ERR_ALLOCATION_FAILED;
    }
    while (win == -1)
    {
        RoundNumber(_game->m_roundNum);
        stat=RunRound(_game->m_gameRound,_game->m_roundNum);
        win=IsEnd(_game->m_gameRound);
        _game->m_roundNum++;
    }
    WinnerIS(&_game->m_plyr[win]);
    return stat;
}

