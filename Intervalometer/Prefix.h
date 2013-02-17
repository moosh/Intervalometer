/******************************************************************************

	Prefix.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Arduino.h"

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

const int kPinLeftButton		= 11;
const int kPinRightButton		= 12;
const int kPinUpButton			= 14;
const int kPinDownButton		= 15;
const int kPinEnterButton		= 16;
const int kPinShutterTrigger	= 17;

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

/******************************************************************************

******************************************************************************/
bool PositionsEqual(Position a, Position b);
Position NormalizePosition(Position& inOutPos);
bool IsPositionValid(Position pos);
bool IsAnyButtonPressed(void);

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
