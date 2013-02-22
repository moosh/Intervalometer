/******************************************************************************

	IVView.cpp
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#include "Prefix.h"
#include "IVView.h"
#include "SpriteSheets.h"

const int kRS = 0;
const int kRW = 1;
const int kEN = 2;
const int kD0 = 3;
const int kD1 = 4;
const int kD2 = 5;
const int kD3 = 6;
const int kD4 = 7;
const int kD5 = 8;
const int kD6 = 9;
const int kD7 = 10;

/******************************************************************************

******************************************************************************/
IVView::IVView(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
IVView::~IVView(void)
{
	Clear();
}

/******************************************************************************

******************************************************************************/
void IVView::Clear(void)
{
	mLCD 						= NULL;
	mModel 						= NULL;
	mState 						= kStateSplashPanel;
	mSplashPanelSelection 		= 2;
	mSettingsPanelSelection 	= 0;
	mFrameDelaySelection 		= kFrameDelaySelectionS2;
	mMainPanelSelection 		= 1;
	mFrameCountSelection 		= kFrameCount1;
	mFrameRateSelection			= kFrameRate1;
	mMaxPlaybackTimeSelection	= kMaxPlaybackTimeSelectionS2;
}

/******************************************************************************

******************************************************************************/
void IVView::Init(IVModel* model)
{
	mModel = model;
	mLCD = new LiquidCrystal(kRS, kRW, kEN, kD0, kD1, kD2, kD3, kD4, kD5, kD6, kD7);
	mLCD->begin(16, 4);
}

/******************************************************************************

******************************************************************************/
void IVView::ClearAllLines(void)
{
	char clearTxt[] = "                ";
	strcpy(mOutputLines[0], clearTxt);
	strcpy(mOutputLines[1], clearTxt);
	strcpy(mOutputLines[2], clearTxt);
	strcpy(mOutputLines[3], clearTxt);
}

/******************************************************************************

******************************************************************************/
void IVView::WriteChar(uint8_t c)
{
	mLCD->write(c);
}

/******************************************************************************

******************************************************************************/
void IVView::WriteStringAtPosition(int row, int col, char* text)
{
	SetCursorPosition(row, col);
	mLCD->print(text);
}

/******************************************************************************

******************************************************************************/
void IVView::SetCharRAM(int charIndex, const uint8_t* bitmap)
{
	const int kCreateCharDelayUSec = 300;
	
	mLCD->createChar(charIndex, (uint8_t*)bitmap);
	delayMicroseconds(kCreateCharDelayUSec);
}

/******************************************************************************

******************************************************************************/
void IVView::SetCursorPosition(Position pos)
{
	SetCursorPosition(pos.row, pos.col);
}

/******************************************************************************

******************************************************************************/
void IVView::SetCursorPosition(int row, int col)
{
	if (row > 1)
	{
		// LCD library doesn't exactly support setting
		// the cursor by (row, col) when display is 16x4
		// The following fixup handles the conversion.
		row -= 2;
		col += 16;
	}
	
	mLCD->setCursor(col, row);
}

/******************************************************************************

******************************************************************************/
void IVView::ShiftTextLeft(char* text)
{
	if (!text) return;
	
	int len = strlen(text);
	for (int i = 0; i < len-1; ++i) text[i] = text[i+1];
	text[len-1] = ' ';
}

/******************************************************************************

******************************************************************************/
void IVView::ShiftTextRight(char* text)
{
	if (!text) return;
	
	int len = strlen(text);
	for (int i = len-1; i > 0; --i) text[i] = text[i-1];
	text[0] = ' ';
}

/******************************************************************************

******************************************************************************/
void IVView::ExitStageLeft(void)
{
	const int kSlideDelay = 1;
	char* line = NULL;
	
	int rowBytes = kNumCols+1;
	for (int col = 0; col < kNumCols; ++col)
	{
		for (int row = 0; row < kNumRows; ++row)
		{
			line = mOutputLines[row];
			SetCursorPosition(row,0); ShiftTextLeft(line);
			mLCD->print(line);
			delay(kSlideDelay);
		}
	}
}

/******************************************************************************

******************************************************************************/
void IVView::ExitStageRight(void)
{
	const int kSlideDelay = 1;
	char* line = NULL;
	
	int rowBytes = kNumCols+1;
	for (int col = 0; col < kNumCols; ++col)
	{
		for (int row = 0; row < kNumRows; ++row)
		{
			line = mOutputLines[row];
			SetCursorPosition(row,0); ShiftTextRight(line);
			mLCD->print(line);
			delay(kSlideDelay);
		}
	}
}

/******************************************************************************

******************************************************************************/
void IVView::SelectLine(int line)
{
	char* lineText = mOutputLines[line];
	if (!lineText) return;
	
	for (int col = kLeftCol; col <= kRightCol; ++col)
	{
		if (lineText[col] == ' ') lineText[col] = kSelectionCharacter;
		else break;
	}

	for (int col = kRightCol; col >= kLeftCol; --col)
	{
		if (lineText[col] == ' ') lineText[col] = kSelectionCharacter;
		else break;
	}
}

/******************************************************************************

******************************************************************************/
void IVView::WriteLine(int line)
{
	if ((line < kLeftCol) || (line > kRightCol)) return;
	WriteStringAtPosition(line, 0, mOutputLines[line]);
}

/******************************************************************************

******************************************************************************/
void IVView::SetTextForLine(int line, char* text, TextAlign align)
{
	if ((line < kTopRow) || (line > kBottomRow)) return;
	
	int len = strlen(text);
	if (len > kNumCols)
	{
		text[kNumCols] = 0;
		len = kNumCols;
	}

	int spaceCount = kNumCols - len;
	*(mOutputLines[line]) = 0;	// reset the string
	switch (align)
	{
		case kTextAlignLeft:
		{
			strcpy(mOutputLines[line], text);

			for (int i = 0; i < spaceCount; ++i)
				strcat(mOutputLines[line], " ");
			break;
		}
			
		case kTextAlignCenter:
		{
			int leftSpaceCount = spaceCount / 2;
			for (int i = 0; i < leftSpaceCount; ++i)
				strcat(mOutputLines[line], " ");
				
			strcat(mOutputLines[line], text);

			int rightSpaceCount = spaceCount - leftSpaceCount;
			for (int i = 0; i < rightSpaceCount; ++i)
				strcat(mOutputLines[line], " ");
				
			break;
		}
		
		case kTextAlignRight:
		{
			for (int i = 0; i < spaceCount; ++i)
				strcat(mOutputLines[line], " ");
				
			strcat(mOutputLines[line], text);
			break;
		}
		
		default:
			break;
	}
}

/******************************************************************************

******************************************************************************/
void IVView::OnLeftButton(void)
{
	int prevState = mState;
	
	switch (mState)
	{
		case kStateSplashPanel:
			// vibrate, do nothing
			break;
			
		case kStateMainPanel:
			mMainPanelSelection--;
			if (mMainPanelSelection < kMainPanelSelectionReset)
			{
				mState = kStateSplashPanel;
				mMainPanelSelection = kMainPanelSelectionReset;
			}
			break;
			
		case kStateSettingsPanel:
			mState = kStateSplashPanel;
			break;
			
		case kStateFrameDelayPanel:
		{
			mFrameDelaySelection--;
			if (mFrameDelaySelection < kFrameDelaySelectionH1) mFrameDelaySelection = kFrameDelaySelectionS2;
			break;
		}
		
		case kStateFrameCountPanel:
		{
			mFrameCountSelection--;
			if (mFrameCountSelection < kFrameCount10000) mFrameCountSelection = kFrameCount1;
			break;
		}
		
		case kStateFrameRatePanel:
		{
			mFrameRateSelection--;
			if (mFrameRateSelection < kFrameRate10) mFrameRateSelection = kFrameRate1;
			break;
		}
		
		case kStatePlaybackTimePanel:
		{
			mMaxPlaybackTimeSelection--;
			if (mMaxPlaybackTimeSelection < kMaxPlaybackTimeSelectionH1) mMaxPlaybackTimeSelection = kMaxPlaybackTimeSelectionS2;
			break;
		}
	}
	
	if (prevState != mState)
		ExitStageRight();
}

/******************************************************************************

******************************************************************************/
void IVView::OnRightButton(void)
{
	int prevState = mState;
	
	switch (mState)
	{
		case kStateSplashPanel:
		{
			switch (mSplashPanelSelection)
			{
				case 2:	mState = kStateMainPanel; break;
				case 3: mState = kStateSettingsPanel; break;
				default: break;
			}
			break;
		}
			
		case kStateMainPanel:
			mMainPanelSelection++;
			if (mMainPanelSelection > kMainPanelSelectionPlayPause)
			{
				// vibrate, maybe
				mMainPanelSelection = kMainPanelSelectionPlayPause;
			}
			break;
			
		case kStateSettingsPanel:
		{
			switch (mSettingsPanelSelection)
			{
				case 0:	mState = kStateFrameDelayPanel;	break;
				case 1: mState = kStateFrameCountPanel;	break;
				case 2:	mState = kStateFrameRatePanel; break;
				case 3: mState = kStatePlaybackTimePanel; break;
				default: break;
			}
			break;
		}
			
		case kStateFrameDelayPanel:
		{
			mFrameDelaySelection++;
			if (mFrameDelaySelection > kFrameDelaySelectionS2) mFrameDelaySelection = kFrameDelaySelectionH1;
			break;
		}
		
		case kStateFrameCountPanel:
		{
			mFrameCountSelection++;
			if (mFrameCountSelection > kFrameCount1) mFrameCountSelection = kFrameCount10000;
			break;
		}

		case kStateFrameRatePanel:
		{
			mFrameRateSelection++;
			if (mFrameRateSelection > kFrameRate1) mFrameRateSelection = kFrameRate10;
			break;
		}

		case kStatePlaybackTimePanel:
		{
			mMaxPlaybackTimeSelection++;
			if (mMaxPlaybackTimeSelection > kMaxPlaybackTimeSelectionS2) mMaxPlaybackTimeSelection = kMaxPlaybackTimeSelectionH1;
			break;
		}
	}
	
	if (prevState != mState)
		ExitStageLeft();
}

/******************************************************************************

******************************************************************************/
void IVView::OnUpButton(void)
{
	switch (mState)
	{
		case kStateSplashPanel:
		{
			// Range is from [2,3]
			mSplashPanelSelection -= 1;
			if (mSplashPanelSelection < 2) mSplashPanelSelection = 3; // wrap
			break;
		}
			
		case kStateMainPanel:
			// vibrate, do nothing;
			break;
			
		case kStateSettingsPanel:
			mSettingsPanelSelection -= 1;
			if (mSettingsPanelSelection < 0) mSettingsPanelSelection = 3; // wrap
			break;
			
		case kStateFrameDelayPanel:
		{
			UpdateFrameDelay(1);
			break;
		}
				
		case kStateFrameCountPanel:
		{
			UpdateFrameCount(1);
			break;
		}
		
		case kStateFrameRatePanel:
		{
			UpdateFrameRate(1);
			break;
		}
		
		case kStatePlaybackTimePanel:
		{
			UpdateMaxPlaybackTime(1);
			break;
		}
	}
}

/******************************************************************************

******************************************************************************/
void IVView::OnDownButton(void)
{
	switch (mState)
	{
		case kStateSplashPanel:
		{
			// Range is from [2,3]
			mSplashPanelSelection += 1;
			if (mSplashPanelSelection > 3) mSplashPanelSelection = 2;	// wrap
			break;
		}
			
		case kStateMainPanel:
			// vibrate, do nothing;
			break;
			
		case kStateSettingsPanel:
			mSettingsPanelSelection += 1;
			if (mSettingsPanelSelection > 3) mSettingsPanelSelection = 0; // wrap
			break;
			
		case kStateFrameDelayPanel:
		{
			UpdateFrameDelay(-1);
			break;
		}
		
		case kStateFrameCountPanel:
		{
			UpdateFrameCount(-1);
			break;
		}
			
		case kStateFrameRatePanel:
		{
			UpdateFrameRate(-1);
			break;
		}
				
		case kStatePlaybackTimePanel:
		{
			UpdateMaxPlaybackTime(-1);
			break;
		}
	}
}

/******************************************************************************

******************************************************************************/
void IVView::OnEnterButton(void)
{
	int prevState = mState;
	
	switch (mState)
	{
		case kStateMainPanel:
		{
			switch (mMainPanelSelection)
			{
				case kMainPanelSelectionReset:
					mModel->Reset();
					break;
					
				case kMainPanelSelectionPlayPause:
					mModel->ToggleIntervalometer();
					break;
			}
			break;
		}
			
		case kStateSettingsPanel:
		case kStateSplashPanel:
			break;
			
		case kStateFrameDelayPanel:
		case kStateFrameCountPanel:
		case kStateFrameRatePanel:
		case kStatePlaybackTimePanel:
			mState = kStateSettingsPanel;
			break;
	}

	if (prevState != mState)
		ExitStageRight();
}

/******************************************************************************

******************************************************************************/
void IVView::Refresh(void)
{
	switch (mState)
	{
		case kStateSplashPanel:
		{
			DrawSplashPanel();
			break;
		}
			
		case kStateMainPanel:
		{
			DrawMainPanel();
			break;
		}
			
		case kStateSettingsPanel:
		{
			DrawSettingsPanel();
			break;
		}
			
		case kStateFrameDelayPanel:
		{
			DrawFrameDelayPanel();
			break;
		}
			
		case kStateFrameCountPanel:
		{
			DrawFrameCountPanel();
			break;
		}
			
		case kStateFrameRatePanel:
		{
			DrawFrameRatePanel();
			break;
		}
			
		case kStatePlaybackTimePanel:
		{
			DrawPlaybackTimePanel();
			break;
		}
	}
}

/******************************************************************************

******************************************************************************/
void IVView::DrawSplashPanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Intervalometer");
	SetTextForLine(0, text, kTextAlignCenter);
	
	sprintf(text, " ");
	SetTextForLine(1, text, kTextAlignLeft);
	
	sprintf(text, "Main Panel");
	SetTextForLine(2, text, kTextAlignCenter);
	
	sprintf(text, "Settings");
	SetTextForLine(3, text, kTextAlignCenter);
	
	SelectLine(mSplashPanelSelection);
	
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
void IVView::DrawMainPanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Frame:  %d", mModel->CurrentFrameCount());
	SetTextForLine(0, text, kTextAlignLeft);
	
	UnpackedTime time;
	UnpackTime(mModel->CurrentPlaybackTimeInSeconds(), &time);
	sprintf(text, "PlayTm: %d%d:%d%d:%d%d", time.fH1, time.fH2, time.fM1, time.fM2, time.fS1, time.fS2);
	SetTextForLine(1, text, kTextAlignLeft);
	
	UnpackTime(mModel->ElapsedTimeInSeconds(), &time);
	sprintf(text, "RealTm: %d%d:%d%d:%d%d", time.fH1, time.fH2, time.fM1, time.fM2, time.fS1, time.fS2);
	SetTextForLine(2, text, kTextAlignLeft);
		
	switch (mMainPanelSelection)
	{
		case kMainPanelSelectionReset:
		{
			int playPauseIdx = 0;
			if (mModel->IsIntervalometerEnabled())	playPauseIdx = kPauseSpriteIndex;
			else									playPauseIdx = kPlaySpriteIndex;
			
			SetCharRAM(kResetCharacter, PlayPauseResetBitmap(kResetSelectedSpriteIndex));
			SetCharRAM(kPlayPauseCharacter, PlayPauseResetBitmap(playPauseIdx));
			sprintf(text, "%c%c%c  %c%c%c",
					kSelectionCharacter,
					kResetCharacter,
					kSelectionCharacter,
					' ',
					kPlayPauseCharacter,
					' ');
			break;
		}
			
		case kMainPanelSelectionPlayPause:
		{
			int playPauseIdx = 0;
			if (mModel->IsIntervalometerEnabled())	playPauseIdx = kPauseSelectedSpriteIndex;
			else									playPauseIdx = kPlaySelectedSpriteIndex;
			
			SetCharRAM(kResetCharacter, PlayPauseResetBitmap(kResetSpriteIndex));
			SetCharRAM(kPlayPauseCharacter, PlayPauseResetBitmap(playPauseIdx));
			sprintf(text, "%c%c%c  %c%c%c",
					' ',
					kResetCharacter,
					' ',
					kSelectionCharacter,
					kPlayPauseCharacter,
					kSelectionCharacter);
			break;
		}
	}
	
	SetTextForLine(3, text, kTextAlignCenter);
	
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
void IVView::DrawSettingsPanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Frame Delay");
	SetTextForLine(0, text, kTextAlignCenter);
	
	sprintf(text, "Frame Count");
	SetTextForLine(1, text, kTextAlignCenter);
	
	sprintf(text, "Frames Rate");
	SetTextForLine(2, text, kTextAlignCenter);
	
	sprintf(text, "Playback Time");
	SetTextForLine(3, text, kTextAlignCenter);
	
	SelectLine(mSettingsPanelSelection);
	
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
void IVView::DrawFrameDelayPanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Frame Delay");
	SetTextForLine(0, text, kTextAlignCenter);
	
	sprintf(text, " ");
	SetTextForLine(1, text, kTextAlignCenter);
	
	UnpackedTime time;
	UnpackTime(mModel->FrameDelayInSeconds(), &time);
	switch (mFrameDelaySelection)
	{
		case kFrameDelaySelectionH1:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fH1));
			sprintf(text, "%c%d:%d%d:%d%d", kSelectedNumberCharacter, time.fH2, time.fM1, time.fM2, time.fS1, time.fS2);
			break;
		}

		case kFrameDelaySelectionH2:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fH2));
			sprintf(text, "%d%c:%d%d:%d%d", time.fH1, kSelectedNumberCharacter, time.fM1, time.fM2, time.fS1, time.fS2);
			break;
		}

		case kFrameDelaySelectionM1:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fM1));
			sprintf(text, "%d%d:%c%d:%d%d", time.fH1, time.fH2, kSelectedNumberCharacter, time.fM2, time.fS1, time.fS2);
			break;
		}

		case kFrameDelaySelectionM2:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fM2));
			sprintf(text, "%d%d:%d%c:%d%d", time.fH1, time.fH2, time.fM1,kSelectedNumberCharacter, time.fS1, time.fS2);
			break;
		}

		case kFrameDelaySelectionS1:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fS1));
			sprintf(text, "%d%d:%d%d:%c%d", time.fH1, time.fH2, time.fM1, time.fM2, kSelectedNumberCharacter, time.fS2);
			break;
		}

		case kFrameDelaySelectionS2:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fS2));
			sprintf(text, "%d%d:%d%d:%d%c", time.fH1, time.fH2, time.fM1, time.fM2, time.fS1, kSelectedNumberCharacter);
			break;
		}
	}
	SetTextForLine(2, text, kTextAlignCenter);
	
	sprintf(text, "hh:mm:ss");
	SetTextForLine(3, text, kTextAlignCenter);
	
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
void IVView::DrawFrameCountPanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Frame Count");
	SetTextForLine(0, text, kTextAlignCenter);
	
	sprintf(text, " ");
	SetTextForLine(1, text, kTextAlignCenter);
	
	UnpackedNumber num;
	UnpackValue(mModel->MaxFrameCount(), &num);
	switch (mFrameCountSelection)
	{
		case kFrameCount1:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f1));
			sprintf(text, "Max: %d%d%d%d%c", num.f10000, num.f1000, num.f100, num.f10, kSelectedNumberCharacter);
			break;
			
		case kFrameCount10:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f10));
			sprintf(text, "Max: %d%d%d%c%d", num.f10000, num.f1000, num.f100, kSelectedNumberCharacter, num.f1);
			break;
			
		case kFrameCount100:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f100));
			sprintf(text, "Max: %d%d%c%d%d", num.f10000, num.f1000, kSelectedNumberCharacter, num.f10, num.f1);
			break;
			
		case kFrameCount1000:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f1000));
			sprintf(text, "Max: %d%c%d%d%d", num.f10000, kSelectedNumberCharacter, num.f100, num.f10, num.f1);
			break;
			
		case kFrameCount10000:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f10000));
			sprintf(text, "Max: %c%d%d%d%d", kSelectedNumberCharacter, num.f1000, num.f100, num.f10, num.f1);
			break;
	}
	SetTextForLine(2, text, kTextAlignCenter);
	
	sprintf(text, "(0 = no maximum)");
	SetTextForLine(3, text, kTextAlignCenter);
		
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
void IVView::DrawFrameRatePanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Frame Rate");
	SetTextForLine(0, text, kTextAlignCenter);
	
	sprintf(text, " ");
	SetTextForLine(1, text, kTextAlignCenter);
	
	UnpackedNumber num;
	UnpackValue(mModel->FrameRate(), &num);
	switch (mFrameRateSelection)
	{
		case kFrameRate1:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f1));
			sprintf(text, "%d%c fps", num.f10, kSelectedNumberCharacter);
			break;
			
		case kFrameRate10:
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(num.f10));
			sprintf(text, "%c%d fps", kSelectedNumberCharacter, num.f1);
			break;
	}
	SetTextForLine(2, text, kTextAlignCenter);
	
	sprintf(text, " ");
	SetTextForLine(3, text, kTextAlignCenter);
		
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
void IVView::DrawPlaybackTimePanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Playback Time");
	SetTextForLine(0, text, kTextAlignCenter);
	
	sprintf(text, " ");
	SetTextForLine(1, text, kTextAlignCenter);
	
	UnpackedTime time;
	UnpackTime(mModel->MaxPlaybackTimeInSeconds(), &time);
	sprintf(text, "%d%d:%d%d:%d%d", time.fH1, time.fH2, time.fM1, time.fM2, time.fS1, time.fS2);
	
	switch (mMaxPlaybackTimeSelection)
	{
		case kMaxPlaybackTimeSelectionH1:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fH1));
			sprintf(text, "%c%d:%d%d:%d%d", kSelectedNumberCharacter, time.fH2, time.fM1, time.fM2, time.fS1, time.fS2);
			break;
		}

		case kMaxPlaybackTimeSelectionH2:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fH2));
			sprintf(text, "%d%c:%d%d:%d%d", time.fH1, kSelectedNumberCharacter, time.fM1, time.fM2, time.fS1, time.fS2);
			break;
		}

		case kMaxPlaybackTimeSelectionM1:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fM1));
			sprintf(text, "%d%d:%c%d:%d%d", time.fH1, time.fH2, kSelectedNumberCharacter, time.fM2, time.fS1, time.fS2);
			break;
		}

		case kMaxPlaybackTimeSelectionM2:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fM2));
			sprintf(text, "%d%d:%d%c:%d%d", time.fH1, time.fH2, time.fM1,kSelectedNumberCharacter, time.fS1, time.fS2);
			break;
		}

		case kMaxPlaybackTimeSelectionS1:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fS1));
			sprintf(text, "%d%d:%d%d:%c%d", time.fH1, time.fH2, time.fM1, time.fM2, kSelectedNumberCharacter, time.fS2);
			break;
		}

		case kMaxPlaybackTimeSelectionS2:
		{
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(time.fS2));
			sprintf(text, "%d%d:%d%d:%d%c", time.fH1, time.fH2, time.fM1, time.fM2, time.fS1, kSelectedNumberCharacter);
			break;
		}
	}
	SetTextForLine(2, text, kTextAlignCenter);
	
	sprintf(text, "hh:mm:ss");
	SetTextForLine(3, text, kTextAlignCenter);
	
	WriteLine(0);
	WriteLine(1);
	WriteLine(2);
	WriteLine(3);
}

/******************************************************************************

******************************************************************************/
const uint8_t* IVView::SelectedCharacterBitmap(int idx)
{
	return &(kSelectedNumberSpriteSheet[idx * kCellHeight]);
}

/******************************************************************************

******************************************************************************/
const uint8_t* IVView::PlayPauseResetBitmap(int idx)
{
	return &(kPlayPauseResetSpriteSheet[idx * kCellHeight]);
}

/******************************************************************************

******************************************************************************/
void IVView::UpdateFrameDelay(int increment)
{
	UnpackedTime time;
	UnpackTime(mModel->FrameDelayInSeconds(), &time);
	
	switch (mFrameDelaySelection)
	{
		case kFrameDelaySelectionH1:
		{
			// increment ten hours
			time.fH1 += increment;
			if (time.fH1 < 0) time.fH1 = 9;
			else if (time.fH1 > 9) time.fH1 = 0;
			break;
		}
			
		case kFrameDelaySelectionH2:
		{
			// increment 1 hour
			time.fH2 += increment;
			if (time.fH2 < 0) time.fH2 = 9;
			else if (time.fH2 > 9) time.fH2 = 0;
			break;
		}
			
		case kFrameDelaySelectionM1:
		{
			// increment ten minutes
			time.fM1 += increment;
			if (time.fM1 < 0) time.fM1 = 5;
			else if (time.fM1 > 5) time.fM1 = 0;
			break;
		}
			
		case kFrameDelaySelectionM2:
		{
			// increment 1 minute
			time.fM2 += increment;
			if (time.fM2 < 0) time.fM2 = 9;
			else if (time.fM2 > 9) time.fM2 = 0;
			break;
		}
			
		case kFrameDelaySelectionS1:
		{
			// increment ten seconds
			time.fS1 += increment;
			if (time.fS1 < 0) time.fS1 = 5;
			else if (time.fS1 > 5) time.fS1 = 0;
			break;
		}
			
		case kFrameDelaySelectionS2:
		{
			// increment 1 second
			time.fS2 += increment;
			if (time.fS2 < 0) time.fS2 = 9;
			else if (time.fS2 > 9) time.fS2 = 0;
			break;
		}
	}
	
	mModel->SetFrameDelayInSeconds(time.TotalSeconds());
}

/******************************************************************************

******************************************************************************/
void IVView::UpdateFrameCount(int increment)
{
	UnpackedNumber num;
	UnpackValue(mModel->MaxFrameCount(), &num);

	switch (mFrameCountSelection)
	{
		case kFrameCount1:
			num.f1 += increment;
			if (num.f1 < 0) num.f1 = 9;
			else if (num.f1 > 9) num.f1 = 0;
			break;
			
		case kFrameCount10:
			num.f10 += increment;
			if (num.f10 < 0) num.f10 = 9;
			else if (num.f10 > 9) num.f10 = 0;
			break;
			
		case kFrameCount100:
			num.f100 += increment;
			if (num.f100 < 0) num.f100 = 9;
			else if (num.f100 > 9) num.f100 = 0;
			break;
			
		case kFrameCount1000:
			num.f1000 += increment;
			if (num.f1000 < 0) num.f1000 = 9;
			else if (num.f1000 > 9) num.f1000 = 0;
			break;
			
		case kFrameCount10000:
			num.f10000 += increment;
			if (num.f10000 < 0) num.f10000 = 9;
			else if (num.f10000 > 9) num.f10000 = 0;
			break;
	}
	
	mModel->SetMaxFrameCount(num.CombinedValue());
}

/******************************************************************************

******************************************************************************/
void IVView::UpdateFrameRate(int increment)
{
	UnpackedNumber num;
	UnpackValue(mModel->FrameRate(), &num);

	switch (mFrameRateSelection)
	{
		case kFrameRate1:
			num.f1 += increment;
			if (num.f1 < 0) num.f1 = 9;
			else if (num.f1 > 9) num.f1 = 0;
			break;
			
		case kFrameRate10:
			num.f10 += increment;
			if (num.f10 < 0) num.f10 = 9;
			else if (num.f10 > 9) num.f10 = 0;
			break;			
	}
	
	mModel->SetFrameRate(num.CombinedValue());
}

/******************************************************************************

******************************************************************************/
void IVView::UpdateMaxPlaybackTime(int increment)
{
	UnpackedTime time;
	UnpackTime(mModel->MaxPlaybackTimeInSeconds(), &time);
	
	switch (mMaxPlaybackTimeSelection)
	{
		case kMaxPlaybackTimeSelectionH1:
		{
			// increment ten hours
			time.fH1 += increment;
			if (time.fH1 < 0) time.fH1 = 9;
			else if (time.fH1 > 9) time.fH1 = 0;
			break;
		}
			
		case kMaxPlaybackTimeSelectionH2:
		{
			// increment 1 hour
			time.fH2 += increment;
			if (time.fH2 < 0) time.fH2 = 9;
			else if (time.fH2 > 9) time.fH2 = 0;
			break;
		}
			
		case kMaxPlaybackTimeSelectionM1:
		{
			// increment ten minutes
			time.fM1 += increment;
			if (time.fM1 < 0) time.fM1 = 5;
			else if (time.fM1 > 5) time.fM1 = 0;
			break;
		}
			
		case kMaxPlaybackTimeSelectionM2:
		{
			// increment 1 minute
			time.fM2 += increment;
			if (time.fM2 < 0) time.fM2 = 9;
			else if (time.fM2 > 9) time.fM2 = 0;
			break;
		}
			
		case kMaxPlaybackTimeSelectionS1:
		{
			// increment ten seconds
			time.fS1 += increment;
			if (time.fS1 < 0) time.fS1 = 5;
			else if (time.fS1 > 5) time.fS1 = 0;
			break;
		}
			
		case kMaxPlaybackTimeSelectionS2:
		{
			// increment 1 second
			time.fS2 += increment;
			if (time.fS2 < 0) time.fS2 = 9;
			else if (time.fS2 > 9) time.fS2 = 0;
			break;
		}
	}
	
	mModel->SetMaxPlaybackTimeInSeconds(time.TotalSeconds());
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
