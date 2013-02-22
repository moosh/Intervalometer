/******************************************************************************

	Prefix.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Prefix.h"

/******************************************************************************

******************************************************************************/
bool PositionsEqual(Position a, Position b)
{
	return ((a.row == b.row) && (a.col == b.col));
}

/******************************************************************************

******************************************************************************/
Position NormalizePosition(Position& inOutPos)
{
	if (inOutPos.col < kLeftCol) 		inOutPos.col = kRightCol;
	else if (inOutPos.col > kRightCol)	inOutPos.col = 0;
	if (inOutPos.row < kTopRow)			inOutPos.row = kBottomRow;
	else if (inOutPos.row > kBottomRow)	inOutPos.row = 0;
}

/******************************************************************************

******************************************************************************/
bool IsPositionValid(Position pos)
{
	if (pos.col < kLeftCol) 	return false;
	if (pos.col > kRightCol)	return false;
	if (pos.row < kTopRow)		return false;
	if (pos.row > kBottomRow)	return false;
	
	return true;
}

/******************************************************************************

******************************************************************************/
void UnpackValue(long value, UnpackedNumber* outNum)
{
	memset(outNum, 0, sizeof(UnpackedNumber));
	
	outNum->f10000 	= value / 10000;
	outNum->f1000	= value / 1000 - 10 * outNum->f10000;
	outNum->f100	= value / 100 - 100 * outNum->f10000 - 10 * outNum->f1000;
	outNum->f10		= value / 10 - 1000 * outNum->f10000 - 100 * outNum->f1000 - 10 * outNum->f100;
	outNum->f1		= value / 1 - 10000 * outNum->f10000 - 1000 * outNum->f1000 - 100 * outNum->f100 - 10 * outNum->f10;
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
