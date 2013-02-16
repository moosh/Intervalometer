/******************************************************************************

	IVController.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "IVController.h"

const int kLeftButton	= 11;
const int kRightButton	= 12;
const int kUpButton		= 14;
const int kDownButton	= 15;
const int kEnterButton	= 16;

/******************************************************************************

******************************************************************************/
IVController::IVController(void)
{
	mModel 	= NULL;
	mView	= NULL;
}

/******************************************************************************

******************************************************************************/
IVController::~IVController(void)
{
	mModel 	= NULL;
	mView	= NULL;
}

/******************************************************************************

******************************************************************************/
void IVController::Init(IVModel* model, IVView* view)
{
	const int kShortestSpriteDelay = 300;
	const int kLongestSpriteDelay = 900;
	
	mModel = model;
	mView = view;
	
	//mView->ShowSplash();
	//mQueue.scheduleFunction(AdvanceSpriteCB, "Ship", 0, 200, kShipSpriteID, this);
}

/******************************************************************************

******************************************************************************
int IVController::AdvanceSpriteCB(unsigned long now, int message, void* ctx)
{
	IVController* pthis = (IVController*)ctx;
	if (!pthis) return 0;
	
	uint8_t spriteID = (uint8_t)message;
	pthis->AdvanceSprite(spriteID);
}

/******************************************************************************

******************************************************************************
int IVController::AdvanceSprite(uint8_t spriteID)
{
	Sprite* sprite = mModel->SpriteWithID(spriteID);
	if (!sprite) return 0;
	
	PositionVec curPos, nextPos;
	curPos	= sprite->CurPositionVec();
	nextPos = sprite->NextPositionVec();
	
	sprite->SetDirectionVec(nextPos.dirVec);
	mModel->MoveSpriteToPosition(spriteID, nextPos.position);
}

/******************************************************************************

******************************************************************************/
void IVController::Timeslice(void)
{
	mQueue.Run(millis());
	
	if (digitalRead(kLeftButton)) 	mView->OnLeftButton();
	if (digitalRead(kRightButton))	mView->OnRightButton();
	if (digitalRead(kUpButton)) 	mView->OnUpButton();
	if (digitalRead(kDownButton)) 	mView->OnDownButton();
	if (digitalRead(kEnterButton)) 	mView->OnEnterButton();
	delay(180);

	mView->Refresh();
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
