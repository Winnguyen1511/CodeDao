#include "defs.h"
report* walkthrough(knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
	report* pReturn = new report;
	int bFlag;
	//fighting for the existence of mankind here
	for(int i= 0; i < nCastle; i++)
	{
		//Run all castle here
		for(int j = 0; j < arrCastle[i].nEvent ; j++)
		{
			//Run each events in castle here.
			int update = event(theKnight, arrCastle[i].arrEvent[j], mode, i, j);
			int petalStatus = reducePetal(theKnight,update, nPetal, mode);
			update_report(pReturn, update, mode);
			if(petalStatus == PETAL_EXIT)
			{
				//The knight fail before defeating the Ultimecia.
				bFlag = 0;
				break;
			}
			else
			{
				//do another condition here.
				bFlag = 1;
			}
			
		}
	}

	// success or failure?	
	pReturn = (bFlag) ? pReturn : NULL;
	return pReturn;
}
int reducePetal(knight& theKnight,int update,int& nPetal,int mode)
{
	std::cout <<"> " << nPetal <<" left...\n";
	if(nPetal > 1)
	{
		nPetal--;
		return PETAL_MORE;
	}
	else
	{
		nPetal--;
		return PETAL_EXIT;
	}
	
}
int update_report(report* pReturn, int update, int mode)
{
	std::cout <<"> update report\n";
}
//called when knight falling in the battle field
int callPhoenix(knight& woundedKnight, int MaxHP)
{
	static int nTimes = 0;
	woundedKnight.HP = MaxHP / 2;
	woundedKnight.gil = woundedKnight.gil < 100 ? 0 : woundedKnight.gil - 100;
	return ++nTimes;
}

//for mode 1 only
int hash(int eventCode)
{
	return eventCode;
}