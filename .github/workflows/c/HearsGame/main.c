#include <stdio.h>
#include "ADTDefs.h"
#include "Game.h"

#define NUM_OF_PLAYERS 4
#define NUM_OF_REAL 1

int main(void)
{
    Game *dnmGame;
    dnmGame=CreateGame(NUM_OF_PLAYERS , NUM_OF_REAL );
    RunGame( dnmGame);
    DestroyGame( dnmGame);
}
