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

class CGXDLMSSNSettings
{
public:
	CGXDLMSSNSettings(void);
	~CGXDLMSSNSettings(void);

	unsigned char m_ConformanceBlock[3];	

	void SetConformanceBlock(unsigned char* pBuff)
	{
		memcpy(pBuff, m_ConformanceBlock, 3);
//		DumpValues();
	}

	bool GetRead();
	void SetRead(bool newVal);
	bool GetWrite();
	void SetWrite(bool newVal);
	bool GetUnconfirmedWrite();
	void SetUnconfirmedWrite(bool newVal);
	bool GetInformationReport();
	void SetInformationReport(bool newVal);
	bool GetMultibleReferences();
	void SetMultibleReferences(bool newVal);
	bool GetParametrizedAccess();
	void SetParametrizedAccess(bool newVal);
};
