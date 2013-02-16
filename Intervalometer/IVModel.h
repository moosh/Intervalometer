/******************************************************************************

	IVModel.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

class IVModel
{
private:
	int mFrameDelayHours;
	int mFrameDelayMinutes;
	int mFrameDelaySeconds;
	long mCurrentFrameCount;
	long mMaxFrameCount;
	long mFrameRate;	// fps
	long mPlaybackTimeInSeconds;
	long mRealTimeInSeconds;
	bool mEnableIntervalometer;
	
public:
	IVModel(void);
	~IVModel(void);
	void Init(void);
	
	int FrameDelayHours(void) { return mFrameDelayHours; }
	int FrameDelayMinutes(void) { return mFrameDelayMinutes; }
	int FrameDelaySeconds(void) { return mFrameDelaySeconds; }
	
	void SetFrameDelayHours(int value) { mFrameDelayHours = value; }
	void SetFrameDelayMinutes(int value) { mFrameDelayMinutes = value; }
	void SetFrameDelaySeconds(int value) { mFrameDelaySeconds = value; }
	
	int CurrentFrameCount(void);
	int MaxFrameCount(void);
	int FrameRate(void);
	
	int PlaybackTimeHours(void);
	int PlaybackTimeMinutes(void);
	int PlaybackTimeSeconds(void);
	
	int RealTimeHours(void);
	int RealTimeMinutes(void);
	int RealTimeSeconds(void);
	
	bool IsIntervalometerEnabled(void) { return mEnableIntervalometer; }
	void EnableIntervalometer(bool bEnable) { mEnableIntervalometer = bEnable; }
	void ToggleIntervalometer(void) { mEnableIntervalometer = !mEnableIntervalometer; }
};


/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
