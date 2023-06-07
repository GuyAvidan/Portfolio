#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "ADTDefs.h"
#include "vector.h"

typedef struct Player Player;
typedef int (*Strategy)(int _cotax, void* _info, Vector *_hand);

struct Player 
{
    Vector *m_cards;/*A vector of the cards in the player's hand*/
    char m_name[20];/*The player's name*/
    int m_IsReal;/*0-the player isn't real, 1-the player is real*/
    int m_magicNumber;
};


/*
Description: The function creates a dynamic player
Input: NA
Output:struct Dynamic player
Errors: NULL if can't create player
*/
Player *CreatePlayer (int _isReal );


/* 
Description: The function destroys a dynamic structure
Input:_player- struct to destroy
Output:NA
Errors: NA
*/
void DestroyPlayer ( Player *_player );


/* 
Description: The function showing the player hend as a vector
Input:_deck- struct to show
Output: vector of the dack
Errors: NULL if _deck is NULL
*/
Vector *ShowHand( Player *_player );


/* 
Description: The function add an input card to the player hend vector
Input:_player- the player, _card- the card to add
Output: ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_OVERFLOW, ERR_REALLOCATION_FAILED
*/
ADTErr GetCard ( Player *_player, int _card);


/* 
Description: The function throw card of the player
Input:_player- the player, _strt-strategy function for player, _legalFunc- check if the card is legal,_card- the card
Output: ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_UNDERFLOW
*/
ADTErr ThrowCard ( Player *_player ,void* _info, Strategy _strt ,Strategy _legalFunc, int  *_card);


/* 
Description: The function sets the player name
Input:_player- the player, _name[]- the name to set
Output: ERR_OK
Errors: ERR_NOT_INITIALIZED
*/
ADTErr SetName (Player *_player ,char _name[]);

/* 
Description: The function outputs the player name
Input:_player- the player
Output: player's name
Errors: NA
*/
char *GetName(Player *_player);

ADTErr FindCard (Player *_player ,int _card); /*Not in use*/

#endif /* #ifndef __PLAYER_H__ */
