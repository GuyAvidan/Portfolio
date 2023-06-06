#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include "vector.h"
#include "ADTDefs.h"
#include "Player.h"
#include "Deck.h"
#include "UI.h"
#include "Card.h"
#define BLACK "\x1b[30m"
#define WHITE "\x1B[37m"
#define RED "\x1B[31m"
#define HEARTS "\xE2\x99\xA5"
#define SPADES "\xE2\x99\xA0"
#define DIAMONDS "\xE2\x99\xA6"
#define CLUBS "\xE2\x99\xA3"
#define BOLD_ON "\x1b[1m"
#define UNDER_ON "\x1b[4m"
#define RESET_ALL "\x1b[0m"

char Ranks[13][3]={"2" ,"3", "4", "5",  "6" ,"7" ,"8" ,"9" , "10" ,"J", "Q" ,"K", "A"};

void PrintCard( int _card )
{
    RRank rank;
    SSuit suit;
    rank=RANK( _card);
    suit=SUIT(_card);
    if(suit==0)
    {
        printf(RED);
        printf("%s" HEARTS " ",Ranks[rank]);
    }
    if(suit==1)
    {
        printf(WHITE);
        printf("%s" SPADES " ",Ranks[rank]);
    }
    if(suit==2)
    {
        printf(RED );
        printf("%s" DIAMONDS " ",Ranks[rank]);
    }
    if(suit==3)
    {
        printf(WHITE);
        printf("%s" CLUBS " " ,Ranks[rank]);
    }
    printf(RESET_ALL);
}

void PrintDeck( Deck *_deck )
{
    int i, toPrint;
    size_t n;
    Vector *vec;
    if(_deck == NULL)
    {
        return;
    }
    vec=ShowDeck( _deck );
    VectorItemsNum(vec, &n);
    for (i=0; i<n; i++)
    {
        VectorGet(vec, i, &toPrint);
        PrintCard(toPrint);
    }

}

void PrintHand( Player *_plyr)
{
    int i, toPrint=0;
    size_t n=0;
    Vector *vec;
    if(_plyr == NULL)
    {
        return;
    }
    vec=ShowHand( _plyr );
    VectorItemsNum(vec, &n);
    PrintName(_plyr);
    printf("'s hand:\n");
    for (i=0; i<n; i++)
    {
        printf("  %d:",i);
        VectorGet(vec, i, &toPrint);
        PrintCard(toPrint);
    }
    printf("\n");
}

void PrintTurn(Player *_plyrs,int _card)
{
    if(_plyrs == NULL)
    {
        return;
    }
    PrintName(_plyrs);
    printf(" card is ");
    PrintCard(_card);
    printf("\n");

}

void PrintName( Player *_plyrs)
{
    char buff[20];
    if(_plyrs == NULL)
    {
        return;
    }
    strcpy(buff,GetName(_plyrs));
    printf("%s",buff);
}

void TurnNum(int _num)
{
    printf(BOLD_ON "Trick number %d\n" RESET_ALL,_num);
}

void RoundNumber(int _num)
{
    printf(UNDER_ON BOLD_ON "Round number %d\n" RESET_ALL,_num);
}

void PrintLose( Player *_plyrs)
{
    if(_plyrs == NULL)
    {
        return;
    }
    printf("loser of this trick is ");
	PrintName( _plyrs);
	printf("\n");
}

void PrintScore( Player *_plyrs, int *_arr, int _nunOfPleyers)
{
    int i;
    if(_plyrs == NULL || _arr==NULL)
    {
        return;
    }
    for(i=0 ; i< _nunOfPleyers; i++)
    {
        PrintName( &_plyrs[i]);
        printf("'s score %d\n",_arr[i]);
    }
}

void WinnerIS( Player *_plyrs)
{
    if(_plyrs == NULL)
    {
        return;
    }
    printf(UNDER_ON BOLD_ON "\nThe winner is ");
    PrintName(_plyrs);
    printf("\n    END\n" RESET_ALL);
}

void AskName()
{
    printf("Please enter your name:");
}

void AskCard()
{
    printf("Please enter card index:");
}
