/******************************************************************************

	IVView.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include <LiquidCrystal.h>
#include "IVModel.h"

enum TextAlign
{
	kTextAlignLeft,
	kTextAlignCenter,
	kTextAlignRight
};

enum ViewState
{
	kStateNone,
	kStateSplashPanel,
	kStateMainPanel,
	kStateSettingsPanel,
	kStateFrameDelayPanel,
	kStateFrameCountPanel,
	kStateFrameRatePanel,
	kStatePlaybackTimePanel
};

enum MainPanelSelection
{
	kMainPanelSelectionReset,
	kMainPanelSelectionPlayPause,
};

enum FrameDelaySelection
{
	kFrameDelaySelectionH1,
	kFrameDelaySelectionH2,
	kFrameDelaySelectionM1,
	kFrameDelaySelectionM2,
	kFrameDelaySelectionS1,
	kFrameDelaySelectionS2
};

enum FrameCountSelection
{
	kFrameCount10000,
	kFrameCount1000,
	kFrameCount100,
	kFrameCount10,
	kFrameCount1,
};

enum FrameRateSelection
{
	kFrameRate10,
	kFrameRate1
};

class IVView
{
private:
	LiquidCrystal* mLCD;
	IVModel* mModel;
	char mOutputLines[kNumRows][kNumCols+1];	// room for null terminator
	int mState;
	int mSplashPanelSelection;
	int mMainPanelSelection;
	int mSettingsPanelSelection;
	int mFrameDelaySelection;
	int mFrameCountSelection;
	int mFrameRateSelection;
	
	void Clear(void);
	void SelectLine(int line);
	void WriteLine(int line);
	void SetTextForLine(int line, char* text, TextAlign align);
	
	const uint8_t* SelectedCharacterBitmap(int idx);
	const uint8_t* PlayPauseResetBitmap(int idx);
	void ShiftTextLeft(char* text);
	void ShiftTextRight(char* text);
	void ExitStageLeft(void);
	void ExitStageRight(void);
	
	void ClearAllLines(void);
	void DrawPlaybackTimePanel(void);
	void DrawFrameRatePanel(void);
	void DrawFrameCountPanel(void);
	void DrawFrameDelayPanel(void);
	void DrawSettingsPanel(void);
	void DrawMainPanel(void);
	void DrawSplashPanel(void);
	
	void UpdateFrameDelay(int increment);
	void UpdateFrameCount(int increment);
	void UpdateFrameRate(int increment);
	
public:
	IVView(void);
	~IVView(void);
	void Init(IVModel* model);
	
	void ClearBoard(uint8_t clearChar);
	void WriteChar(uint8_t c);
	void WriteStringAtPosition(int row, int col, char* text);

	void SetCharRAM(int charIndex, const uint8_t* bitmap);
	void SetCursorPosition(Position pos);
	void SetCursorPosition(int row, int col);
	void Refresh(void);
	
	void OnLeftButton(void);
	void OnRightButton(void);
	void OnUpButton(void);
	void OnDownButton(void);
	void OnEnterButton(void);
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
