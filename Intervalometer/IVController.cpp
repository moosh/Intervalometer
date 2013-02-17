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

******************************************************************************/
int IVController::TriggerCameraCB(unsigned long now, int message, void* ctx)
{
	IVController* pThis = (IVController*)ctx;
	if (!pThis) return 0;

	pThis->TriggerCamera();
}

/******************************************************************************

******************************************************************************/
void IVController::TriggerCamera(void)
{
	TriggerShutter();
	mModel->IncrementFrameCount();
	mModel->UpdateState();
}

/******************************************************************************

******************************************************************************/
void IVController::TriggerShutter(void)
{
	digitalWrite(kPinShutterTrigger, HIGH);
	delay(100);
	digitalWrite(kPinShutterTrigger, LOW);
}

/******************************************************************************

******************************************************************************/
void IVController::Timeslice(void)
{
	const int kButtonPressDelay = 200;
	
	if (mModel->IsIntervalometerEnabled() && (mQueue.queueSize() == 0))
	{
		mQueue.scheduleFunction(TriggerCameraCB, "Trig", 0, mModel->FrameDelayInMilliseconds(), 0, this);
	}
	else if (!mModel->IsIntervalometerEnabled() && (mQueue.queueSize() != 0))
	{
		mQueue.scheduleRemoveFunction("Trig");
	}
	mQueue.Run(millis());
	
	if (digitalRead(kLeftButton)) 	{ mView->OnLeftButton(); 	delay(kButtonPressDelay); }
	if (digitalRead(kRightButton))	{ mView->OnRightButton(); 	delay(kButtonPressDelay); }
	if (digitalRead(kUpButton)) 	{ mView->OnUpButton(); 		delay(kButtonPressDelay); }
	if (digitalRead(kDownButton)) 	{ mView->OnDownButton(); 	delay(kButtonPressDelay); }
	if (digitalRead(kEnterButton)) 	{ mView->OnEnterButton();	delay(kButtonPressDelay); }

	mView->Refresh();
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
