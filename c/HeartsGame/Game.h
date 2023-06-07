#ifndef __GAME_H__
#define __GAME_H__
#include "ADTDefs.h"
#include "Player.h"
#include "Round.h"

typedef struct Game Game;

struct Game 
{
    Player *m_plyr;/* the players*/
    int m_nunOfPleyers;/*the number of players*/
    int m_roundNum;/*the round number*/
    Round *m_gameRound;/*the round struct*/
    int *m_score[4];/*the score*/
    int m_magicNumber;
};


/*
Description: The function creates a dynamic game
Input: _numOfPleyers-the number of players, _real- How many real players
Output:struct Dynamic gmae
Errors: NULL if can't create game
*/
Game *CreateGame( int _numOfPleyers, int _real);


/* 
Description: The function runs a full game
Input:_game- the gmae
Output:ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_OVERFLOW, ERR_REALLOCATION_FAILED, ERR_UNDERFLOW
*/
ADTErr RunGame( Game *_game);


/* 
Description: The function destroys a dynamic structure
Input:_game - struct to destroy
Output:NA
Errors: NA
*/
void DestroyGame( Game *_game);


#endif /* #ifndef __GAME_H__ */
