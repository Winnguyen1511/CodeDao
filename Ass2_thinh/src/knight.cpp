#include "knight.h"

#define BIT(X)	(1<<X)

int knightInit(knight& theKnight, int mode)
{
    theKnight.maxHP = theKnight.HP;
    theKnight.knight_category = KNIGHT_NORMAL;
    theKnight.Odin = 0;
    theKnight.poisoned = false;
    return 0;
}