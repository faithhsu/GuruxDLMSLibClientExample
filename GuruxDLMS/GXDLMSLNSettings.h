//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL:  $
//
// Version:         $Revision:  $,
//                  $Date:  $
//                  $Author: $
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------

#pragma once
#include <string.h>

struct CGXDLMSLNSettings
{
public:
	CGXDLMSLNSettings(void);
	~CGXDLMSLNSettings(void);

	unsigned char m_ConformanceBlock[3];	
	void SetConformanceBlock(unsigned char* pBuff)
	{
		memcpy(m_ConformanceBlock, pBuff, 3);
		//DumpValues();
	}

	bool GetAttribute0SetReferencing();
	void SetAttribute0SetReferencing(bool newVal);
	bool GetPriorityManagement();
	void SetPriorityManagement(bool newVal);
	bool GetAttribute0GetReferencing();
	void SetAttribute0GetReferencing(bool newVal);
	bool GetGetBlockTransfer();
	void SetGetBlockTransfer(bool newVal);
	bool GetSetBlockTransfer();
	void SetSetBlockTransfer(bool newVal);
	bool GetActionBlockTransfer();
	void SetActionBlockTransfer(bool newVal);
	bool GetMultibleReferences();
	void SetMultibleReferences(bool newVal);
	bool GetGet();
	void SetGet(bool newVal);
	bool GetSet();
	void SetSet(bool newVal);
	bool GetAction();
	void SetAction(bool newVal);
	bool GetEventNotification();
	void SetEventNotification(bool newVal);
	bool GetSelectiveAccess();
	void SetSelectiveAccess(bool newVal);	
};
