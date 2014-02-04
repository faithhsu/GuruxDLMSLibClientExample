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

#include <map>
#include "GXAuthentication.h"
#include "Objects/GXDLMSObject.h"
#include "Objects/GXDLMSObjectCollection.h"
#include "GXDLMS.h"

struct CGXDLMSServerBase
{	
	CGXDLMS m_Base;
	bool m_Initialized;	   
	unsigned long m_FrameIndex;
	vector<CGXDLMSVariant> m_ServerIDs;
	vector<unsigned char> m_ReceivedData;
	vector< vector<unsigned char> > m_SendData;
	vector<GXAuthentication*> m_Authentications;
	map<unsigned short, CGXDLMSObject*> m_SortedItems;
	CGXDLMSObjectCollection m_Items;
public:
	//Constructor.
	CGXDLMSServerBase(bool UseLogicalNameReferencing = true,
				GXDLMS_INTERFACETYPE IntefaceType = GXDLMS_INTERFACETYPE_GENERAL, unsigned short MaxReceivePDUSize = 0xFFFF);

	//Destructor.
	~CGXDLMSServerBase(void);

	/// <summary>
    /// Used Authentication password pairs.
    /// </summary>
    vector<GXAuthentication*> GetAuthentications()
    {
		return m_Authentications;
    }

    //Is Logical Name referencing used.
	bool GetUseLogicalNameReferencing();

	//Get Interface type.
	GXDLMS_INTERFACETYPE GetInterfaceType();

	//Get Max Receive PDU Size.
	unsigned short GetMaxReceivePDUSize();

	//Get Server ID.
	CGXDLMSVariant GetServerID();

	//Set Server ID.
	void SetServerID(CGXDLMSVariant& value);

	//Initialize server.
	//This must call after server objects are set.
	int Initialize();

	// Reset after connection is closed.    
    void Reset();

	CGXDLMSObjectCollection& GetItems()
	{
		return m_Items;
	}

	vector<CGXDLMSVariant>& GetServerIDs()
	{
		return m_ServerIDs;
	}

	// Count server ID from physical and logical addresses.	
	int CountServerID(CGXDLMSVariant physicalAddress, int LogicalAddress, CGXDLMSVariant& value);

	int HandleRequest(vector<unsigned char>& data, unsigned char*& pReply, int& ReplySize);
	int HandleRequest(unsigned char* pData, int size, unsigned char*& pReply, int& ReplySize);

	virtual int OnRead(CGXDLMSObject* pItem, int index, CGXDLMSVariant& value, DLMS_DATA_TYPE& type) = 0;
	virtual int OnWrite(CGXDLMSObject* pItem, int index, CGXDLMSVariant& value) = 0;
	virtual int OnAction(CGXDLMSObject* pItem, int index, CGXDLMSVariant& data) = 0;
	virtual int OnInvalidConnection() = 0;

private:
	int Acknowledge(DLMS_COMMAND cmd, unsigned char status, vector< vector<unsigned char> >& Packets);
	int SendData(vector< vector<unsigned char> >& buff, int index, unsigned char*& pReply, int& ReplySize);
	int GetAddress(unsigned char* pData, int size, CGXDLMSVariant& clientId, CGXDLMSVariant& serverId);
	int HandleSNRMRequest(vector< vector<unsigned char> >& Packets);
	int HandleAARQRequest(unsigned char* pData, int DataSize, vector< vector<unsigned char> >& Packets);
	int GenerateDisconnectRequest(vector< vector<unsigned char> >& Packets);
	int ServerReportError(unsigned char serviceErrorCode, unsigned char type, unsigned char code, vector< vector<unsigned char> >& Packets);
	int GetCommand(unsigned char* pData, int DataSize, OBJECT_TYPE& type, CGXDLMSVariant& name, int& attributeIndex, unsigned char*& pParameters, int& ParameterSize);	
	int GetValue(CGXDLMSObject* pItem, int index, unsigned char* pParameters, int count, vector< vector<unsigned char> >& Packets);
	int ReadReply(CGXDLMSVariant name, OBJECT_TYPE objectType, int attributeOrdinal, CGXDLMSVariant& value, DLMS_DATA_TYPE type, vector< vector<unsigned char> >& Packets);
};
