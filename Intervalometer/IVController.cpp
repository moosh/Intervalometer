/******************************************************************************

	IVController.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "IVController.h"

/******************************************************************************

******************************************************************************/
IVController::IVController(void)
{
	mModel 	= NULL;
	mView	= NULL;
	
	memset(mButtonBounceLastPressTime, 0, kButtonCount * sizeof(unsigned long));
}

/******************************************************************************

******************************************************************************/
IVController::~IVController(void)
{
	mModel 	= NULL;
	mView	= NULL;

	memset(mButtonBounceLastPressTime, 0, kButtonCount * sizeof(unsigned long));
}

/******************************************************************************

******************************************************************************/
void IVController::Init(IVModel* model, IVView* view)
{
	mModel = model;
	mView = view;
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
	int kCameraShutterDelay = 400;	// Anything lower than this doesn't seem to please the camera (frames get dropped).
	
	CheckForButtonPresses(); // Sigh, this is what happens in a cooperative "threading" environment
	
	digitalWrite(kShutterTrigger, HIGH);
	delay(kCameraShutterDelay);
	digitalWrite(kShutterTrigger, LOW);
	
	CheckForButtonPresses(); // Ditto...
}

/******************************************************************************

******************************************************************************/
bool IVController::IsButtonPressed(int buttonID)
{
	// Check for a button press AND debounces
	const unsigned long kBounceDelay = 300;
	
	unsigned long* lastPressTime = NULL;
	switch (buttonID)
	{
		case kLeftButton:	lastPressTime = &mButtonBounceLastPressTime[0]; break;
		case kRightButton:	lastPressTime = &mButtonBounceLastPressTime[1]; break;
		case kUpButton:		lastPressTime = &mButtonBounceLastPressTime[2]; break;
		case kDownButton:	lastPressTime = &mButtonBounceLastPressTime[3]; break;
		case kEnterButton:	lastPressTime = &mButtonBounceLastPressTime[4]; break;
	}
	
	if (false == digitalRead(buttonID))
		*lastPressTime = 0;
	else
	{
		int now = millis();
		if ((now - *lastPressTime) > kBounceDelay)
		{
			*lastPressTime = now;
			return true;
		}
	}
	
	return false;
}

/******************************************************************************

******************************************************************************/
void IVController::CheckForButtonPresses(void)
{
	const int kButtonPressDelay = 400;
	if (IsButtonPressed(kLeftButton)) 	{ mView->OnLeftButton(); }
	if (IsButtonPressed(kRightButton))	{ mView->OnRightButton(); }
	if (IsButtonPressed(kUpButton)) 	{ mView->OnUpButton(); }
	if (IsButtonPressed(kDownButton)) 	{ mView->OnDownButton(); }
	if (IsButtonPressed(kEnterButton)) 	{ mView->OnEnterButton(); }
}

/******************************************************************************

******************************************************************************/
void IVController::Timeslice(void)
{
	CheckForButtonPresses();
	
	if (mModel->IsIntervalometerEnabled() && (mQueue.queueSize() == 0))
	{
		mQueue.scheduleFunction(TriggerCameraCB, "Trig", 0, mModel->FrameDelayInMilliseconds(), 0, this);
	}
	else if (!mModel->IsIntervalometerEnabled() && (mQueue.queueSize() != 0))
	{
		mQueue.scheduleRemoveFunction("Trig");
	}
	mQueue.Run(millis());
	mView->Refresh();
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
