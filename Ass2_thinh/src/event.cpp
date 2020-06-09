#include "event.h"

int event(knight& theKnight, int event_code, int mode, int& castleIndex, int& eventIndex)
{
    int ret = 0;
    if(event_code == MAD_BEAR)
    {
        ret = fightNormalOpponent(theKnight, event_code, mode);
    }
    else if(event_code == MEET_MOON_BRINGER)
    {
        ret = fightNormalOpponent(theKnight, event_code, mode);
    }
    else if(event_code == MEET_ELF)
    {
        ret = fightNormalOpponent(theKnight, event_code, mode);
    }
    else if(event_code == MEET_SAXON)
    {
        ret = fightNormalOpponent(theKnight, event_code, mode);
    }
    else if(event_code == MEET_TROLL)
    {
         ret = fightNormalOpponent(theKnight, event_code, mode);
    }
    else if(event_code == MEET_TORNBERY)
    {
        
    }
    else if(event_code == MEET_QUEEN_CARDS)
    {

    }
    else if(event_code == MEET_NINA_DE_RINGS)
    {
        
    }
    else if(event_code == LOST_DURIAN_GARDEN)
    {
        
    }
    else if(event_code == PICK_ANTIDOTE)
    {
        
    }
    else if(event_code == MEET_ODIN)
    {
        
    }
    else if(event_code == MEET_MERLING)
    {
        
    }
    else if(event_code == MEET_OMEGA)
    {
        
    }
    else if(event_code == MEET_HADES)
    {
        
    }
    else if(event_code == PICK_SH)
    {
        
    }
    else if(event_code == MEET_LOCKED_DOOR)
    {
        
    }
    else if(event_code == PICK_PALADIN_SHIELD)
    {
        
    }
    else if(event_code == PICK_LANCELOT_SPEAR)
    {
        
    }
    else if(event_code == PICK_GUINEVERE_HAIR)
    {
        
    }
    else if(event_code == PICK_EXCALIBUR_SWORD)
    {
        
    }
    else if(event_code == ENCOUTER_ULTIMECIA)
    {
        
    }
    else{
        //do nothing.
    }
    return ret;
}

int fightNormalOpponent(knight& theKnight, int event_code, int mode)
{
    
}