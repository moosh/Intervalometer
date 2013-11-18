/******************************************************************************

	IVModel.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "IVModel.h"

/******************************************************************************

******************************************************************************/
IVModel::IVModel(void)
{
	Init();
}

/******************************************************************************

******************************************************************************/
IVModel::~IVModel(void)
{
	Init();
}

/******************************************************************************

******************************************************************************/
void IVModel::Init(void)
{
	mFrameDelayInSeconds		= 1;
	mCurrentFrameCount			= 0;
	mMaxFrameCount				= 0;	// 0 == no max count
	mFrameRate					= 30;	// fps
	mCurPlaybackTimeInSeconds	= 0;
	mMaxPlaybackTimeInSeconds	= 0;	// 0 == no max time
	mElapsedTimeInSeconds		= 0;
	mEnableIntervalometer		= false;
}

/******************************************************************************

******************************************************************************/
void IVModel::Reset(void)
{
	mCurrentFrameCount			= 0;
	mCurPlaybackTimeInSeconds	= 0;
	mElapsedTimeInSeconds		= 0;
	mEnableIntervalometer		= false;
	
	int i = 0;
	++i;
}

/******************************************************************************

******************************************************************************/
void IVModel::SaveModel(void)
{
	// save some parameters to NVRAM in the ATMega

}

/******************************************************************************

******************************************************************************/
bool IVModel::CanIntervalometerBeEnabled(void)
{
	// If a max frame count is defined stop the intervalometer if that count has been reached
	if (mMaxFrameCount && (mCurrentFrameCount >= mMaxFrameCount))
		return false;
		
	// If a max playback time is defined stop the intervalometer if that time has been reached
	if (mMaxPlaybackTimeInSeconds && (mCurPlaybackTimeInSeconds >= mMaxPlaybackTimeInSeconds))
		return false;

	return true;
}

/******************************************************************************

******************************************************************************/
void IVModel::EnableIntervalometer(bool bEnable)
{
	mEnableIntervalometer = bEnable && CanIntervalometerBeEnabled();
}

/******************************************************************************

******************************************************************************/
void IVModel::ToggleIntervalometer(void)
{
	mEnableIntervalometer = !mEnableIntervalometer && CanIntervalometerBeEnabled();
}

/******************************************************************************

******************************************************************************/
void IVModel::UpdateState(void)
{
	mCurPlaybackTimeInSeconds	= mCurrentFrameCount / mFrameRate;
	mElapsedTimeInSeconds		= mCurrentFrameCount * mFrameDelayInSeconds;
	
	if (!CanIntervalometerBeEnabled())
		mEnableIntervalometer = false;
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
