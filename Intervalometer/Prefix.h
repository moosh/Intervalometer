/******************************************************************************

	Prefix.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Arduino.h"

const long kSecondsPerHour		= 3600;
const long kSecondsPerMinute	= 60;

const int kNumRows			= 4;
const int kNumCols			= 16;
const int kLeftCol			= 0;
const int kTopRow			= 0;
const int kRightCol 		= kNumCols - 1;
const int kBottomRow		= kNumRows - 1;
const int kBoardSize		= kNumCols * kNumRows;
const int kCellWidth 		= 5;
const int kCellHeight		= 8;

const uint8_t kClearCharacter		= ' ';
const uint8_t kSelectionCharacter	= 0xFF;

const int kButtonCount		= 5;
const int kLeftButton		= 11;
const int kRightButton		= 12;
const int kUpButton			= 14;
const int kDownButton		= 15;
const int kEnterButton		= 16;
const int kShutterTrigger	= 17;

typedef struct
{
	int col;
	int row;
}Position;

typedef struct
{
	int x, y;
}Vec2;

typedef struct
{
	Position position;
	Vec2 dirVec;
}PositionVec;

typedef struct
{
	int f1;
	int f10;
	int f100;
	int f1000;
	int f10000;
	
	long CombinedValue(void) { return 10000*(long)f10000 + 1000*(long)f1000 + 100*(long)f100 + 10*(long)f10 + (long)f1; }
} UnpackedNumber;

typedef struct
{
	int fH1;
	int fH2;
	int fM1;
	int fM2;
	int fS1;
	int fS2;
	
	long TotalSeconds(void)
	{
		return (10 * (long)fH1 + (long)fH2) * kSecondsPerHour
			 + (10 * (long)fM1 + (long)fM2) * kSecondsPerMinute
			 + (10 * (long)fS1 + (long)fS2);
	}

} UnpackedTime;

/******************************************************************************

******************************************************************************/
bool PositionsEqual(Position a, Position b);
Position NormalizePosition(Position& inOutPos);
bool IsPositionValid(Position pos);
void UnpackValue(long value, UnpackedNumber* outNum);
void UnpackTime(long valueInSeconds, UnpackedTime* outTime);


/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
