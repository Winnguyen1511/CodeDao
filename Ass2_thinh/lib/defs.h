#ifndef DEFS_H
#define DEFS_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "knight.h"
#include "event.h"


#define BIT(X)	(1<<X)
struct report
{
	int nPetal;
	int nWin;
	int nLose;
};

int update_report(report* pReturn, int update, int mode);
int callPhoenix(knight& woundedKnight, int maxHP);
int hash(int eventCode);
report* walkthrough(knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal);
int reducePetal(knight& theKnight,int update,int& nPetal,int mode);
#endif