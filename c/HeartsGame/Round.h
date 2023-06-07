#ifndef __ROUND_H__
#define __ROUND_H__
#include "ADTDefs.h"
#include "Player.h"
#include "Deck.h"
#include "vector.h"
#define OK 1
#define NOT_OK 1


typedef struct Info
{
	int m_isHeartBrok;
	int m_leadSuit;
	int m_leadRank;
    int m_isFirst;
    int m_turnNum;
} Info;

typedef struct Round 
{
    int m_cards[4]; /*the cards on the table*/
    int m_shift[12]; /*the cards to shift*/
    Deck *m_deck; /*the deck*/
    Player *m_plyrs; /* the players*/
    int m_nunOfPleyers; /*the number of players*/
    int m_score[4]; /*the score*/
    int m_roundNum; /*the round number*/
    int m_first; /*Who starts the turn*/
    int m_magicNumber;
    Info *m_info;

} Round;


/*
Description: The function creates a dynamic round
Input: _numOfPleyers-the number of players, _plyrs-the players, _roundNum-the round number
Output:struct Dynamic player
Errors: NULL if can't create player
*/
Round *CreateRound(int _numOfPleyers , Player *_plyrs, int _roundNum);


/* 
Description: The function destroys a dynamic structure
Input:_round- struct to destroy
Output:NA
Errors: NA
*/
void DestroyRound( Round *_round);


/* 
Description: The function runs a full round
Input:_round- the round, _roundNum- the round number in the game
Output:ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_OVERFLOW, ERR_REALLOCATION_FAILED, ERR_UNDERFLOW
*/
ADTErr RunRound (Round *_rund, int _roundNum);


/* 
Description: The function calculates the score in the turn and adds it to the loser
Input:_round- the round
Output:ERR_OK or Error
Errors: ERR_NOT_INITIALIZED
*/
ADTErr ScoreNAddress(  Round *_rund);


/* 
Description: The function checks if someone has reached the threshold and returns the position of the winner
Input:_round- the round
Output: (-1) - no winner, index- the winner index
Errors: NA
*/
int IsEnd(Round *_rund );



#endif /* #ifndef __ROUND_H__ */
