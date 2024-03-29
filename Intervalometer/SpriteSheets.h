/******************************************************************************

	SpriteSheets.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

const int kSpriteCellWidth		= 5;
const int kSpriteCellHeight		= 8;

const int kSelectedNumberCharacter	= 0x01;
const int kResetCharacter 			= 0x02;
const int kPlayPauseCharacter 		= 0x03;

const int kSelectedNumberSpriteCellCount = 10;
const uint8_t kSelectedNumberSpriteSheet[] =
{
	// 0
	B10001,
	B01110,
	B01100,
	B01010,
	B00110,
	B01110,
	B10001,
	B11111,
	
	// 1
	B11011,
	B10011,
	B11011,
	B11011,
	B11011,
	B11011,
	B10001,
	B11111,
	
	// 2
	B10001,
	B01110,
	B11110,
	B11101,
	B11011,
	B10111,
	B00000,
	B11111,
	
	// 3
	B00000,
	B11101,
	B11011,
	B11101,
	B11110,
	B01110,
	B10001,
	B11111,
	
	// 4
	B11101,
	B11001,
	B10101,
	B01101,
	B00000,
	B11101,
	B11101,
	B11111,
	
	// 5
	B00000,
	B01111,
	B00001,
	B11110,
	B11110,
	B01110,
	B10001,
	B11111,
	
	// 6
	B11001,
	B10111,
	B01111,
	B00001,
	B01110,
	B01110,
	B10001,
	B11111,
	
	// 7
	B00000,
	B01110,
	B11110,
	B11101,
	B11011,
	B11011,
	B11011,
	B11111,
	
	// 8
	B10001,
	B01110,
	B01110,
	B10001,
	B01110,
	B01110,
	B10001,
	B11111,
	
	// 9
	B10001,
	B01110,
	B01110,
	B10000,
	B11110,
	B11101,
	B10011,
	B11111,
};

const int kResetSelectedSpriteIndex 	= 0;
const int kResetSpriteIndex				= 1;
const int kPlaySelectedSpriteIndex 		= 2;
const int kPlaySpriteIndex				= 3;
const int kPauseSelectedSpriteIndex 	= 4;
const int kPauseSpriteIndex				= 5;

const int kPlayPauseResetSpriteCellCount = 6;
const uint8_t kPlayPauseResetSpriteSheet[] =
{
	// Reset (selected)
	B01110,
	B01100,
	B01000,
	B00000,
	B00000,
	B01000,
	B01100,
	B01110,

	// Reset
	B10001,
	B10011,
	B10111,
	B11111,
	B11111,
	B10111,
	B10011,
	B10001,

	// Play (selected)
	B11111,
	B10111,
	B10011,
	B10001,
	B10001,
	B10011,
	B10111,
	B11111,

	// Play
	B00000,
	B01000,
	B01100,
	B01110,
	B01110,
	B01100,
	B01000,
	B00000,

	// Pause (selected)
	B11111,
	B10101,
	B10101,
	B10101,
	B10101,
	B10101,
	B10101,
	B11111,

	// Pause
	B00000,
	B11011,
	B11011,
	B11011,
	B11011,
	B11011,
	B11011,
	B00000,
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/

