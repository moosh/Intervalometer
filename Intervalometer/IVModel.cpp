/******************************************************************************

	IVModel.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "IVModel.h"

const long kSecondsPerMinute	= 60;
const long kMinutesPerHour		= 60;
const long kSecondsPerHour 		= 3600;

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
}

/******************************************************************************

******************************************************************************/
void IVModel::Init(void)
{
	mFrameDelayHours		= 0;
	mFrameDelayMinutes		= 0;
	mFrameDelaySeconds		= 1;
	mCurrentFrameCount		= 0;
	mMaxFrameCount			= 30;
	mFrameRate				= 30;	// fps
	mPlaybackTimeInSeconds	= mCurrentFrameCount / mFrameRate;
	mRealTimeInSeconds		= mPlaybackTimeInSeconds * (mFrameDelayHours * kSecondsPerHour + mFrameDelayMinutes * kSecondsPerMinute + mFrameDelaySeconds);
	mEnableIntervalometer	= false;
}

/******************************************************************************

******************************************************************************/
int IVModel::CurrentFrameCount(void)
{
	return mCurrentFrameCount;
}

/******************************************************************************

******************************************************************************/
int IVModel::MaxFrameCount(void)
{
	return mMaxFrameCount;
}

/******************************************************************************

******************************************************************************/
int IVModel::FrameRate(void)
{
	return mFrameRate;
}

/******************************************************************************

******************************************************************************/
int IVModel::PlaybackTimeHours(void)
{
	return (int)(mPlaybackTimeInSeconds / kSecondsPerHour);
}

/******************************************************************************

******************************************************************************/
int IVModel::PlaybackTimeMinutes(void)
{
	long timeInMinutes = mPlaybackTimeInSeconds / kSecondsPerMinute;
	timeInMinutes %= kMinutesPerHour;
	
	return (int)timeInMinutes;
}

/******************************************************************************

******************************************************************************/
int IVModel::PlaybackTimeSeconds(void)
{
	long timeInSeconds = mPlaybackTimeInSeconds % kSecondsPerMinute;
	return timeInSeconds;
}

/******************************************************************************

******************************************************************************/
int IVModel::RealTimeHours(void)
{
	return (int)(mRealTimeInSeconds / kSecondsPerHour);
}

/******************************************************************************

******************************************************************************/
int IVModel::RealTimeMinutes(void)
{
	long timeInMinutes = mRealTimeInSeconds / kSecondsPerMinute;
	timeInMinutes %= kMinutesPerHour;
	
	return (int)timeInMinutes;
}

/******************************************************************************

******************************************************************************/
int IVModel::RealTimeSeconds(void)
{
	long timeInSeconds = mRealTimeInSeconds % kSecondsPerMinute;
	return timeInSeconds;
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
