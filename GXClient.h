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
#include "stdafx.h"
#include "GuruxDLMS/GXDLMSClient.h"

class GXClient
{
public:
	CGXDLMSClient* m_Parser;
	int m_socket;
#if _MSC_VER > 1000
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
#if _MSC_VER > 1000
	int Open(const char* pPortName, bool IEC);
#endif
	int ReadDLMSPacket(vector<unsigned char>& data, int& ReplySize);
	int ReadDLMSPacket(vector<unsigned char>& data, std::vector<unsigned char>& reply);
	int ReadDataBlock(vector< vector<unsigned char> >& data, std::vector<unsigned char>& reply);
	
	///Get object that is used in sorting profile generic columns.
	int GetSortObject(CGXObject* pObject, CGXObject*& pSortObject);

	int InitializeConnection();
	int GetObjects(CGXObjectCollection& objects);
	//Update objects access.
	int UpdateAccess(CGXObject* pObject, CGXObjectCollection& objects);

	int Read(CGXObject* pObject, int attributeIndex, CGXDLMSVariant& value);
	int GetColumns(CGXObject* pObject, CGXObjectCollection* pColumns);
	int ReadRowsByRange(CGXDLMSVariant& Name, CGXObject* pSortObject, struct tm* start, struct tm* end, CGXDLMSVariant& rows);
	int ReadRowsByEntry(CGXDLMSVariant& Name, unsigned int Index, unsigned int Count, CGXDLMSVariant& rows);
};
