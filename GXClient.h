//
// --------------------------------------------------------------------------
//  Gurux Ltd
// 
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2. 
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#pragma once
#include "stdafx.h"
#include "GuruxDLMS/GXDLMSClient.h"

class GXClient
{
public:
	CGXDLMSClient* m_Parser;
	int m_socket;
#if defined(_WIN32) || defined(_WIN64)//Windows includes
	HANDLE			m_hComPort;
	OVERLAPPED		m_osWrite;
	OVERLAPPED		m_osReader;
#endif
public:
	unsigned char* m_Receivebuff;
	int m_SendSize, m_ReceiveSize;
	bool m_Trace;

	GXClient(CGXDLMSClient* pCosem, bool trace);
	~GXClient(void);
	
	void InitializeBuffers(int sendSize, int receiveSize);
	int Close();
	int Connect(const char* pAddress, unsigned short port = 4059);
#if defined(_WIN32) || defined(_WIN64)//Windows includes
	int Open(const char* pPortName, bool IEC);
#endif

	static inline void Now(string& str)
	{		
		time_t tm1 = time(NULL);
		struct tm dt;
		char tmp[10];
#if _MSC_VER > 1000
		localtime_s(&dt, &tm1);		
		sprintf_s(tmp, 10, "%.2d:%.2d:%.2d", dt.tm_hour, dt.tm_min, dt.tm_sec);
#else
		dt = *localtime(&tm1);			
		sprintf(tmp, "%.2d:%.2d:%.2d", dt.tm_hour, dt.tm_min, dt.tm_sec);
	#endif		
		str = tmp;
	}


	int ReadDLMSPacket(vector<unsigned char>& data, int& ReplySize);
	int ReadDLMSPacket(vector<unsigned char>& data, std::vector<unsigned char>& reply);
	int ReadDataBlock(vector< vector<unsigned char> >& data, std::vector<unsigned char>& reply);
	
	int InitializeConnection();
	int GetObjects(CGXDLMSObjectCollection& objects);
	//Update objects access.
	int UpdateAccess(CGXDLMSObject* pObject, CGXDLMSObjectCollection& objects);

	//Read selected object.
	int Read(CGXDLMSObject* pObject, int attributeIndex, CGXDLMSVariant& value);
	
	//Write selected object.
	int Write(CGXDLMSObject* pObject, int attributeIndex, CGXDLMSVariant& value);

	//Call action of selected object.
	int Method(CGXDLMSObject* pObject, int ActionIndex, CGXDLMSVariant& value);

	int ReadRowsByRange(CGXDLMSVariant& Name, CGXDLMSObject* pSortObject, struct tm* start, struct tm* end, CGXDLMSVariant& rows);
	int ReadRowsByEntry(CGXDLMSVariant& Name, unsigned int Index, unsigned int Count, CGXDLMSVariant& rows);
};
