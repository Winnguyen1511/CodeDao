#ifndef KNIGHT_H
#define KNIGHT_H
#define	NUM_TREASURE	6

typedef enum knight_cate_enum{
    KNIGHT_NORMAL=0,
    KNIGHT_PALADIN,
    KNIGHT_GUINEVERE,
    KNIGHT_LANCELOT,
    KNIGHT_KING_ARTHUR,
    KNIGHT_DRAGON_NIGHT
}knight_cate_t;


typedef enum knight_treasure_enum{
	TREASURE_PALADIN_SHIELD=0,
	TREASURE_LANCELOT_SPEAR,
	TREASURE_GUINEVERE_HAIR,
	TREASURE_LIONHEART_SWORD,
	TREASURE_MYTHRIL,
	TREASURE_EXCALIBUR_SWORD
}knight_treasure_t;

typedef enum opponent_cate_enum{
    OPPONENT_NORMAL=0,
    OPPONENT_SPECIAL,//Tornbery, QueenCard,... 
    OPPONENT_LEGEND//Dragon Night, Omega Dragon,...
}opponent_cate_t;

struct knight
{
	bool poisoned;//Poison if lose Tornbery.
	int Odin;//Odin ally counter.
	knight_cate_t knight_category;// 4 category and normal mode
	int treasure[NUM_TREASURE];//for Round Table Knight Treasure	
	int HPfactor;//for different HP calculation modes.
	int maxHP;
	int HP;
	int level;
	int antidote;
	int gil;
};

struct opponent
{
	int levelO;
	opponent_cate_t opponent_category;
};

struct castle
{
	int arrEvent[20];
	int nEvent;
};
int knightInit(knight& theKnight, int mode);
#endif