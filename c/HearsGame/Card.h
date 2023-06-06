#ifndef __CARD_H__
#define __CARD_H__
#define RANK(X) (X%13)
#define SUIT(X) (X/13)


/*All the possible ranks*/
typedef enum
{
	TWO=0,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	PRINCE,
	QUEEN,
	KING,
	ACE
} RRank;


/*All the possible suits*/
typedef enum
{
	HEART=0,
	SPADE,
	DIAMOND,
	CLUB
} SSuit;
	
#endif /* #ifndef __CARD_H__ */
