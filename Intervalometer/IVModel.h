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
	long mFrameRate;
	long mCurPlaybackTimeInSeconds;
	long mMaxPlaybackTimeInSeconds;
	long mElapsedTimeInSeconds;
	bool mEnableIntervalometer;
	
public:
	IVModel(void);
	~IVModel(void);
	void Init(void);

	void Reset(void);
	void UpdateState(void);
	void SaveModel(void);
	
	long FrameDelayInSeconds(void) { return mFrameDelayInSeconds; }
	long FrameDelayInMilliseconds(void) { return 1000 * mFrameDelayInSeconds; }
	void SetFrameDelayInSeconds(long value) { mFrameDelayInSeconds = value; SaveModel(); }
		
	void IncrementFrameCount(void) { mCurrentFrameCount++; }
	int CurrentFrameCount(void) { return mCurrentFrameCount; }
	long MaxFrameCount(void) { return mMaxFrameCount; }
	void SetMaxFrameCount(long value) { mMaxFrameCount = value;  SaveModel(); }
	int FrameRate(void) { return mFrameRate; }
	void SetFrameRate(int value) { mFrameRate = value;  SaveModel(); }
	
	long CurrentPlaybackTimeInSeconds(void) { return mCurPlaybackTimeInSeconds; }
	long MaxPlaybackTimeInSeconds(void) { return mMaxPlaybackTimeInSeconds; }
	void SetMaxPlaybackTimeInSeconds(long value) { mMaxPlaybackTimeInSeconds = value;  SaveModel(); }
	
	int ElapsedTimeInSeconds(void) { return mElapsedTimeInSeconds; }
	
	bool CanIntervalometerBeEnabled(void);
	bool IsIntervalometerEnabled(void) { return mEnableIntervalometer; }
	void EnableIntervalometer(bool bEnable);
	void ToggleIntervalometer(void);
	
};


/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
