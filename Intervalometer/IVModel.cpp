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
	Reset();
}

/******************************************************************************

******************************************************************************/
IVModel::~IVModel(void)
{
	Reset();
}

/******************************************************************************

******************************************************************************/
void IVModel::Init(void)
{
}

/******************************************************************************

******************************************************************************/
void IVModel::Reset(void)
{
	mFrameDelayMinutesPart	= 0;
	mFrameDelayMinutesPart	= 0;
	mFrameDelaySecondsPart	= 1;
	mCurrentFrameCount		= 0;
	mMaxFrameCount			= 0;	// 0 == no max count
	mFrameRate				= 30;	// fps
	mPlaybackTimeInSeconds	= 0;
	mRealTimeInSeconds		= 0;
	mEnableIntervalometer	= false;
}

/******************************************************************************

******************************************************************************/
void IVModel::UpdateState(void)
{
	mPlaybackTimeInSeconds	= mCurrentFrameCount / mFrameRate;
	mRealTimeInSeconds		= mCurrentFrameCount * (mFrameDelayHoursPart * kSecondsPerHour + mFrameDelayMinutesPart * kSecondsPerMinute + mFrameDelaySecondsPart);
	
	// If a max frame count is defined stop the intervalometer if that count has been reached
	if (mMaxFrameCount && (mCurrentFrameCount >= mMaxFrameCount))
		mEnableIntervalometer = false;

}

/******************************************************************************

******************************************************************************/
long IVModel::FrameDelayInSeconds(void)
{
	return mFrameDelayHoursPart * kSecondsPerHour
			+ mFrameDelayMinutesPart * kSecondsPerMinute
			+ mFrameDelaySecondsPart;
}

/******************************************************************************

******************************************************************************/
long IVModel::FrameDelayInMilliseconds(void)
{
	return 1000 * FrameDelayInSeconds();
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
