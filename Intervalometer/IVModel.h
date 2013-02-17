/******************************************************************************

	IVModel.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

class IVModel
{
private:
	int mFrameDelayHoursPart;
	int mFrameDelayMinutesPart;
	int mFrameDelaySecondsPart;
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

	void Reset(void);
	void UpdateState(void);
	
	long FrameDelayInSeconds(void);
	long FrameDelayInMilliseconds(void);
	int FrameDelayHoursPart(void) { return mFrameDelayHoursPart; }
	int FrameDelayMinutesPart(void) { return mFrameDelayMinutesPart; }
	int FrameDelaySecondsPart(void) { return mFrameDelaySecondsPart; }
	
	void SetFrameDelayHoursPart(int value) { mFrameDelayHoursPart = value; }
	void SetFrameDelayMinutesPart(int value) { mFrameDelayMinutesPart = value; }
	void SetFrameDelaySecondsPart(int value) { mFrameDelaySecondsPart = value; }
	
	void IncrementFrameCount(void) { mCurrentFrameCount++; }
	int CurrentFrameCount(void) { return mCurrentFrameCount; }
	int MaxFrameCount(void) { return mMaxFrameCount; }
	int FrameRate(void) { return mFrameRate; }
	
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
