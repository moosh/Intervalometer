/******************************************************************************

	IVController.h
	
	Copyright (c) 2013 Mooshwerks
	All Rights Reserved.
	
******************************************************************************/

#pragma once

#include "Queue.h"
#include "IVModel.h"
#include "IVView.h"

class IVController
{
private:
	IVModel* mModel;
	IVView* mView;
	Queue mQueue;
	
	static int TriggerCameraCB(unsigned long now, int message, void* ctx);
	void TriggerCamera(void);
	
public:
	IVController(void);
	~IVController(void);
	void Init(IVModel* model, IVView* view);
	void Timeslice();
	
	void TriggerShutter(void);
};

/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
/******************************************************************************

******************************************************************************/
