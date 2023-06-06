#ifndef __UI_H__
#define __UI_H__
#include <string.h>
#include "ADTDefs.h"
#include "Player.h"
#include "Deck.h"
#include "Card.h"


/* 
Description: The function prints a card fron int
Input:_card- the card
Output: card
Errors: NA
*/
void PrintCard( int _card );


/* 
Description: The function prints a deck
Input:_deck- the deck
Output: deck
Errors: NA
*/
void PrintDeck( Deck *_deck );


/* 
Description: The function prints the player's hand
Input:_plyr- the player
Output: hand
Errors: NA
*/
void PrintHand( Player *_plyr);


/* 
Description: The function prints the player's card on the table
Input:_plyrs- the player, _card- the card
Output: _plyr"'s card is "card
Errors: NA
*/
void PrintTurn(Player *_plyrs,int _card);


/* 
Description: The function prints the player's name
Input:_plyrs- the player
Output: player's name
Errors: NA
*/
void PrintName( Player *_plyrs);


/* 
Description: The function prints the players' score
Input:_plyrs- the player, _arr- array of socres, _nunOfPleyers- the number of players
Output: the players' score
Errors: NA
*/
void PrintScore( Player *_plyrs, int *_arr, int _nunOfPleyers);


/* 
Description: The function prints the winner's name
Input:_plyrs- the player
Output: the winner's name
Errors: NA
*/
void WinnerIS( Player *_plyrs);


/* 
Description: The function prints the turn number
Input:_num- the turn number
Output: the turn number
Errors: NA
*/
void TurnNum(int _num);


/* 
Description: The function prints the turn loser
Input:_plyrs- the turn loser
Output: the turn loser
Errors: NA
*/
void PrintLose( Player *_plyrs);


/* 
Description: The function ask the name of the player
Input:NA
Output: NA
Errors: NA
*/
void AskName();


/* 
Description: The function ask the player for the card to pull index
Input:NA
Output: NA
Errors: NA
*/
void AskCard();

#endif /* #ifndef __UI_H__ */
