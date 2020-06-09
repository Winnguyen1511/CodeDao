#ifndef EVENT_H
#define EVENT_H
#include "knight.h"

#define BIT(X)	(1<<X)

typedef enum event_enum{
    MAD_BEAR=1,
    MEET_MOON_BRINGER,
    MEET_ELF,
    MEET_SAXON,
    MEET_TROLL,
    MEET_TORNBERY,
    MEET_QUEEN_CARDS,
    MEET_NINA_DE_RINGS,
    LOST_DURIAN_GARDEN,
    PICK_ANTIDOTE,
    MEET_ODIN,
    MEET_MERLING,
    MEET_OMEGA,
    MEET_HADES,
    PICK_SH,
    MEET_LOCKED_DOOR,
    PICK_PALADIN_SHIELD=95,
    PICK_LANCELOT_SPEAR,
    PICK_GUINEVERE_HAIR,
    PICK_EXCALIBUR_SWORD,
    ENCOUTER_ULTIMECIA
}event_t;

//For event() return status.
//After this, use the status to update the report
typedef enum event_return_enum{
    EVENT_=0
}event_return_t;

typedef enum petal_event_enum{
    PETAL_EXIT=0,
    PETAL_MORE
}petal_event_t;

typedef enum gil_gained_enum{
    GIL_MAD_BEAR=100,
    GIL_MOON_BRINGER=150,
    GIL_ELF=450,
    GIL_SAXON=650,
    GIL_TROLL=850
}gil_gained_t;

#define    BD_MAD_BEAR      1
#define    BD_MOON_BRINGER  1.5
#define    BD_GIL_ELF       4.5
#define    BD_SAXON         6.5
#define    BD_TROLL         8.5


int event(knight& theKnight, int event_code, int mode, int& castleIndex, int& eventIndex);
//fight with normal the opponents:
// -> Defeat
// -> Lose
int fightNormalOpponent(knight& theKnight, int event_code, int mode);

//fight with special opponents:
// ->Defeat
// ->Lose

//fight with legend opponents:
// ->Defeat
// -> Lose

//Meet ally:
//

//Pick items:
//
#endif