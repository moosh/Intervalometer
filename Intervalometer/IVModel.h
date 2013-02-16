/******************************************************************************

	IVModel.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

class IVModel
{
private:
	long mFrameDelayInSeconds;
	long mCurrentFrameCount;
	long mMaxFrameCount;
	long mFrameRate;	// fps
	long mPlaybackTimeInSeconds;
	long mRealTimeInSeconds;
	
public:
	IVModel(void);
	~IVModel(void);
	void Init(void);
	
	int FrameDelayHours(void);
	int FrameDelayMinutes(void);
	int FrameDelaySeconds(void);
	
	int CurrentFrameCount(void);
	int MaxFrameCount(void);
	int FrameRate(void);
	
	int PlaybackTimeHours(void);
	int PlaybackTimeMinutes(void);
	int PlaybackTimeSeconds(void);
	
	int RealTimeHours(void);
	int RealTimeMinutes(void);
	int RealTimeSeconds(void);
};


/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
