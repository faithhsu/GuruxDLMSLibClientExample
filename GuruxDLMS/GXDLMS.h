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

#include "GXDLMSSNSettings.h"
#include "GXDLMSLNSettings.h"
#include "GXDLMSLimits.h"
#include "Objects/GXDLMSObject.h"
#include "Objects/GXDLMSObjectCollection.h"

#pragma once

class CGXDLMS
{
public:
	CGXDLMSVariant ServerID;
	unsigned long PacketIndex;
	GXDLMSLimits m_Limits;
	bool m_Server;
	CGXDLMSVariant ClientID;
	CGXDLMSLNSettings* m_pLNSettings;
	CGXDLMSSNSettings* m_pSNSettings;
	unsigned short m_FCS16Table[256];
	unsigned int m_PacketIndex;	
	bool m_bIsLastMsgKeepAliveMsg;
	unsigned short m_ExpectedFrame, m_FrameSequence;
	unsigned short m_ProgressPos, m_ProgressOffset, m_ProgressSize;
	long m_CachePosition;
	GXDLMS_INTERFACETYPE m_InterfaceType;
	// Is Logical or Short name referencing used.
	// Referencing depends from the used device.
	// Normally device supports only one referencing.<br>
	// Manufacture defines used referencing.
	// If referencing is wrong SNMR message will fail.
	bool m_UseLogicalNameReferencing;
	unsigned int m_MaxInfoRX;
	// Used DLMS version.
	// Default DLMS version is 6
	unsigned char m_DLMSVersion;
	// Maximum PDU receiver size.
	// PDU size tells maximum size of PDU packet.
	// Default value is 0xFFFF. Value is from 0 to 0xFFFF.
	unsigned short m_MaxReceivePDUSize;
	//Defines the used authentication password.
	const char* m_pPassword;
	//Defines used authentication.
	// In default authentication is not used. If authentication is used, password
	// is set using Password-property.
	GXDLMS_AUTHENTICATION m_Authentication;		

	//Makes sure that the basic settings are set.
	int CheckInit()
	{
		if (ClientID.vt == DLMS_DATA_TYPE_NONE)
		{
			return ERROR_CODES_INVALID_CLIENT_ADDRESS;
		}
		if (ServerID.vt == DLMS_DATA_TYPE_NONE)
		{
			return ERROR_CODES_INVALID_SERVER_ADDRESS;
		}
		return ERROR_CODES_OK;
	}

	// This generates a checksum table.
	void GenerateFCS16Table();
	CGXDLMSObject CreateObject(OBJECT_TYPE type);

	unsigned short CountCRC(unsigned char* pBuff, int Index, int Count);
	unsigned short CountCRC(std::vector<unsigned char>& Buff, int Index, int Count);

	bool IsDLMSPacketComplete(std::vector<unsigned char>& Data);
	bool IsDLMSPacketComplete(unsigned char* Data, int buffSize);
	int GetDataFromPacket(unsigned char* Packet, int PacketSize, unsigned char*& Data, int& DataSize, GXDLMS_DATA_REQUEST_TYPES& moreData, DLMS_COMMAND& cmd);

	//Generate I-frame: Information frame
	unsigned char GenerateIFrame();
	unsigned char GenerateNextFrame();
	unsigned char GenerateAliveFrame();
	//Return true if frame sequences are same.
	bool IsExpectedFrame(unsigned char send, unsigned char received);

	// Generate I-frame: Information frame
	//
	// 0 Receive Ready (denoted RR(R)) is a positive acknowledge ACK of all frames
	// up to and including frame number R-1.
	// 1 Reject (denoted RE.J(R)) is a negative acknowledge NAK
	// of a Go-back-N mechanism. ie start retransmitting from frame number R.
	// 2 Receive Not Ready (denoted RNR(R)) is a positive acknowledge of all
	// frames up to and including R-1 but the sender must pause until a
	// Receive Ready arrives. This can be used to pause the sender because of
	// temporary problems at the receiver.
	// 3 Selective Reject (denoted SREJ(R)) is a negative acknowledge in a
	// Selective Repeat mechanism. ie resend only frame R. It is not
	// supported in several implementations.
	unsigned char GenerateSupervisoryFrame(unsigned char type);

	bool IsReceiverReadyRequest(unsigned char val);

	bool IsRejectedFrame(unsigned char val)
	{
		return (val & 0x07) == 0x07;
	}

	void ClearProgress()
	{
		m_CachePosition = m_ProgressPos = m_ProgressOffset = m_ProgressSize = 0;
	}

	int GetDataFromHDLCFrame(unsigned char* Data, int dataSize, unsigned char& FrameType, unsigned char*& pData, int& DataLen, DLMS_COMMAND& Command, GXDLMS_DATA_REQUEST_TYPES& MoreData, bool bReply = true, unsigned int* pNextIndex = NULL, bool IncludeHeader = false, bool bCheckCRC = true, int* pError = NULL);
	/////////////////////////////////////////////////////////////////////////////
	// Add data to HDLC frame.
	/////////////////////////////////////////////////////////////////////////////	
	int AddFrame(int Type, bool MoreFrames, vector<unsigned char>& Data, int Index, int Count, vector< vector<unsigned char> >& Packets);

	int CheckLLCBytes(unsigned char* pBuff, int& pos, int length);
	int ParseSNObjects(unsigned char* pBuff, int len, CGXDLMSObjectCollection& objects);
	int ParseLNObjects(unsigned char* pBuff, int len, CGXDLMSObjectCollection& objects);	
	int SplitToFrames(vector<unsigned char>& Data, unsigned int blockIndex, unsigned int& index, unsigned int count, DLMS_COMMAND Cmd, vector< vector<unsigned char> >& Packets);
	int SplitToBlocks(vector<unsigned char>& Data, DLMS_COMMAND Cmd, vector< vector<unsigned char> >& Packets);

public:
	bool GetUseLogicalNameReferencing()
	{
		return m_UseLogicalNameReferencing;
	}

	GXDLMS_INTERFACETYPE GetInterfaceType()
	{
		return m_InterfaceType;
	}
	
	unsigned short GetMaxReceivePDUSize()
	{
		return m_MaxReceivePDUSize;
	}
	/////////////////////////////////////////////////////////////////////////////
	//Constructor.
	/////////////////////////////////////////////////////////////////////////////
	CGXDLMS(bool Server) : m_Server(Server), m_pLNSettings(NULL), m_pSNSettings(NULL),
					m_PacketIndex(0), m_bIsLastMsgKeepAliveMsg(false), 
					m_ExpectedFrame(0), m_FrameSequence(0),
					m_InterfaceType(GXDLMS_INTERFACETYPE_GENERAL), 
					m_UseLogicalNameReferencing(false), m_MaxInfoRX(0),
					m_DLMSVersion(6), m_MaxReceivePDUSize(0xFFFF),
					m_pPassword(NULL), m_Authentication(GXDLMS_AUTHENTICATION_NONE)
	{		
		GenerateFCS16Table();
	}

	/////////////////////////////////////////////////////////////////////////////
	// Returns zero if the packet is correct and an error number if not.
	/////////////////////////////////////////////////////////////////////////////
	// SendData: buffer containing the sent data
	// SendbuffSize: size of the sent data buffer.
	// ReceivedData: buffer containing the data from the meter.
	// ReceivedbuffSize: size of the reply buffer.
	// Returns: 0 if packet is reply. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int IsReplyPacket(unsigned char* SendData, int SendbuffSize, unsigned char* ReceivedData, int ReceivedbuffSize);

	int GetData(unsigned char* pBuff, int& pos1, int dataSize, bool bReply, DLMS_COMMAND& cmd, GXDLMS_DATA_REQUEST_TYPES& MoreData, int* pError);
	int GetLNData(unsigned char* pBuff, int dataSize, int& index, int* pError, GXDLMS_DATA_REQUEST_TYPES& MoreData, DLMS_COMMAND& cmd);
	int GetSNData(unsigned char* pBuff, int dataSize, int& index, int* pError, DLMS_COMMAND& cmd);
	int GenerateMessage(CGXDLMSVariant& name, int ParameterCount, vector<unsigned char>& data, OBJECT_TYPE interfaceClass, int AttributeOrdinal, DLMS_COMMAND cmd, vector< vector<unsigned char> >& Packets);
	static int GetActionInfo(OBJECT_TYPE objectType, int& value, int& count);
};
