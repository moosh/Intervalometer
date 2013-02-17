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
	mLCD = NULL;
	mModel = NULL;
	mState = kStateSplashPanel;
	mSplashPanelSelection = 2;
	mSettingsPanelSelection = 0;
	mFrameDelaySelection = kFrameDelaySelectionS2;
	mMainPanelSelection = 1;
}

/******************************************************************************

******************************************************************************/
IVView::~IVView(void)
{
	mLCD = NULL;
	mModel = NULL;
	mState = kStateSplashPanel;
	mSplashPanelSelection = 2;
	mSettingsPanelSelection = 0;
	mFrameDelaySelection = kFrameDelaySelectionS2;
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
		case kStateFrameRatePanel:
		case kStatePlaybackTimePanel:
			// vibrate, do nothing;
			break;
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
			switch (mFrameDelaySelection)
			{
				case kFrameDelaySelectionH1:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// add ten hours
					valTens++;
					if (valTens > 9) valTens = 0;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionH2:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// add 1 hour
					valOnes++;
					if (valOnes > 9) valOnes = 0;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionM1:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// add ten minutes
					valTens++;
					if (valTens > 5) valTens = 0;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionM2:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// add 1 minute
					valOnes++;
					if (valOnes > 9) valOnes = 0;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionS1:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelaySecondsPart(), &valTens, &valOnes);

					// add ten seconds
					valTens++;
					if (valTens > 5) valTens = 0;
					mModel->SetFrameDelaySecondsPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionS2:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelaySecondsPart(), &valTens, &valOnes);

					// add 1 second
					valOnes++;
					if (valOnes > 9) valOnes = 0;
					mModel->SetFrameDelaySecondsPart(10 * valTens + valOnes);
					break;
				}
			}
			break;
		}
				
		case kStateFrameCountPanel:
		case kStateFrameRatePanel:
		case kStatePlaybackTimePanel:
			// TBD
			break;
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
			switch (mFrameDelaySelection)
			{
				case kFrameDelaySelectionH1:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// subtract ten hours
					valTens--;
					if (valTens < 0) valTens = 9;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionH2:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// subtract 1 hour
					valOnes--;
					if (valOnes < 0) valOnes = 9;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionM1:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// subtract ten minutes
					valTens--;
					if (valTens < 0) valTens = 5;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionM2:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);

					// subtract 1 minute
					valOnes--;
					if (valOnes < 0) valOnes = 9;
					mModel->SetFrameDelayMinutesPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionS1:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelaySecondsPart(), &valTens, &valOnes);

					// subtract ten seconds
					valTens--;
					if (valTens < 0) valTens = 5;
					mModel->SetFrameDelaySecondsPart(10 * valTens + valOnes);
					break;
				}
					
				case kFrameDelaySelectionS2:
				{
					int valTens, valOnes;
					UnpackValue(mModel->FrameDelaySecondsPart(), &valTens, &valOnes);

					// subtract 1 second
					valOnes--;
					if (valOnes < 0) valOnes = 9;
					mModel->SetFrameDelaySecondsPart(10 * valTens + valOnes);
					break;
				}
					
			}
			break;
		}
		
		case kStateFrameCountPanel:
		case kStateFrameRatePanel:
		case kStatePlaybackTimePanel:
			// TBD
			break;
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
			mState = kStateSettingsPanel;
			break;
			
		case kStateFrameCountPanel:
		case kStateFrameRatePanel:
		case kStatePlaybackTimePanel:
			// vibrate, do nothing
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
const int kResetSelectedSpriteIndex 	= 0;
const int kResetSpriteIndex				= 1;
const int kPlaySelectedSpriteIndex 		= 2;
const int kPlaypriteIndex				= 3;
const int kPauseSelectedSpriteIndex 	= 4;
const int kPauseSpriteIndex				= 5;

const int kPlayPauseResetSpriteCellCount = 6;

const int kResetCharacter 		= 0x02;
const int kPlayPauseCharacter 	= 0x03;


******************************************************************************/
void IVView::DrawMainPanel(void)
{
	ClearAllLines();
	
	char text[20];
	sprintf(text, "Frame:  %d", mModel->CurrentFrameCount());
	SetTextForLine(0, text, kTextAlignLeft);
	
	sprintf(text, "PlayTm: %02d:%02d:%02d", mModel->PlaybackTimeHours(), mModel->PlaybackTimeMinutes(), mModel->PlaybackTimeSeconds());
	SetTextForLine(1, text, kTextAlignLeft);
	
	sprintf(text, "RealTm: %02d:%02d:%02d", mModel->RealTimeHours(), mModel->RealTimeMinutes(), mModel->RealTimeSeconds());
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
	
	switch (mFrameDelaySelection)
	{
		case kFrameDelaySelectionH1:
		{
			int valTens, valOnes;
			UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(valTens));
			sprintf(text, "%c%d:%02d:%02d", kSelectedNumberCharacter, valOnes, mModel->FrameDelayMinutesPart(), mModel->FrameDelaySecondsPart());
			break;
		}

		case kFrameDelaySelectionH2:
		{
			int valTens, valOnes;
			UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(valOnes));
			sprintf(text, "%d%c:%02d:%02d", valTens, kSelectedNumberCharacter, mModel->FrameDelayMinutesPart(), mModel->FrameDelaySecondsPart());
			break;
		}

		case kFrameDelaySelectionM1:
		{
			int valTens, valOnes;
			UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(valTens));
			sprintf(text, "%02d:%c%d:%02d", mModel->FrameDelayMinutesPart(), kSelectedNumberCharacter, valOnes, mModel->FrameDelaySecondsPart());
			break;
		}

		case kFrameDelaySelectionM2:
		{
			int valTens, valOnes;
			UnpackValue(mModel->FrameDelayMinutesPart(), &valTens, &valOnes);
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(valOnes));
			sprintf(text, "%02d:%d%c:%02d", mModel->FrameDelayMinutesPart(), valTens, kSelectedNumberCharacter, mModel->FrameDelaySecondsPart());
			break;
		}

		case kFrameDelaySelectionS1:
		{
			int valTens, valOnes;
			UnpackValue(mModel->FrameDelaySecondsPart(), &valTens, &valOnes);
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(valTens));
			sprintf(text, "%02d:%02d:%c%d", mModel->FrameDelayMinutesPart(), mModel->FrameDelayMinutesPart(), kSelectedNumberCharacter, valOnes);
			break;
		}

		case kFrameDelaySelectionS2:
		{
			int valTens, valOnes;
			UnpackValue(mModel->FrameDelaySecondsPart(), &valTens, &valOnes);
			SetCharRAM(kSelectedNumberCharacter, SelectedCharacterBitmap(valOnes));
			sprintf(text, "%02d:%02d:%d%c", mModel->FrameDelayMinutesPart(), mModel->FrameDelayMinutesPart(), valTens, kSelectedNumberCharacter);
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
	
	sprintf(text, "Max: %05d", mModel->MaxFrameCount());
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
	
	sprintf(text, "%02d fps", mModel->FrameRate());
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
	
	sprintf(text, "%02d:%02d:%02d", mModel->PlaybackTimeHours(), mModel->PlaybackTimeMinutes(), mModel->PlaybackTimeSeconds());
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
void IVView::UnpackValue(int value, int* outTens, int* outOnes)
{
	int valTens = value / 10;
	int valOnes	= value - 10 * valTens;
	
	*outTens = valTens;
	*outOnes = valOnes;
}

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
