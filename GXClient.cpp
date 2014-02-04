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

#include "stdafx.h"
#include "GXClient.h"

GXClient::GXClient(CGXDLMSClient* pParser, bool trace) : m_Parser(pParser),
						m_socket(-1), m_Receivebuff(NULL),
						m_SendSize(60), m_ReceiveSize(60), m_Trace(trace)
{
	InitializeBuffers(m_SendSize, m_ReceiveSize);
#if _MSC_VER > 1000
	ZeroMemory(&m_osReader, sizeof(OVERLAPPED));
	ZeroMemory(&m_osWrite, sizeof(OVERLAPPED));
	m_hComPort = INVALID_HANDLE_VALUE;	
	m_osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
#endif
}

void GXClient::InitializeBuffers(int SendSize, int ReceiveSize)
{
	//Allocate 50 bytes more because some meters count this wrong and send few bytes too many.
	m_SendSize = SendSize + 50;
	m_ReceiveSize = ReceiveSize + 50;
	if (m_Receivebuff != NULL)
	{
		delete m_Receivebuff;
		m_Receivebuff = NULL;
	}
	if (ReceiveSize > 0)
	{
		m_Receivebuff = new unsigned char[m_ReceiveSize];	
	}
}

GXClient::~GXClient(void)
{
	Close();
	InitializeBuffers(0, 0);
	CloseHandle(m_osReader.hEvent);
	CloseHandle(m_osWrite.hEvent);
}

//Close connection to the meter.
int GXClient::Close()
{	
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	if ((ret = m_Parser->DisconnectRequest(data)) != 0 ||
			(ret = ReadDataBlock(data, reply)) != 0)
	{
		//Show error.			
	}	
#if _MSC_VER > 1000
	if (m_hComPort != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hComPort);
		m_hComPort = INVALID_HANDLE_VALUE;
		CloseHandle(m_osReader.hEvent);
		CloseHandle(m_osWrite.hEvent);
	}
#endif	
	if (m_socket != -1)
	{
		closesocket(m_socket);
		m_socket = -1;
	}
	return ret;
}

//Make TCP/IP connection to the meter.
int GXClient::Connect(const char* pAddress, unsigned short Port)
{
	//create socket.
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);	
	if (m_socket == -1)
	{		
		assert(0);	
		return ERROR_CODES_INVALID_PARAMETER;
	}
	sockaddr_in add;
	add.sin_port = htons(Port);
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = inet_addr(pAddress);
	//If address is give as name
	if(add.sin_addr.s_addr == INADDR_NONE)
	{
		hostent *Hostent = gethostbyname(pAddress);
		if (Hostent == NULL)
		{
#ifdef WIN32
			int err = WSAGetLastError();
#else
			int err = h_errno;
#endif
			Close();
			return err;
		};
		add.sin_addr = *(in_addr*)(void*)Hostent->h_addr_list[0];
	};

	//Connect to the meter.
	int ret = connect(m_socket, (sockaddr*)&add, sizeof(sockaddr_in));
	if (ret == -1)
	{	
		return ERROR_CODES_INVALID_PARAMETER;
	};
	return ERROR_CODES_OK;
}

#if _MSC_VER > 1000
//Open serial port.
int GXClient::Open(const char* pPortName, bool IEC)
{	
	char buff[10];
#if _MSC_VER > 1000
	sprintf_s(buff, 10, "\\\\.\\%s", pPortName);
#else
	sprintf(buff, "\\\\.\\%s", pPortName);
#endif
	//Open serial port for read / write. Port can't share.
	m_hComPort = CreateFileA(buff, 
					GENERIC_READ | GENERIC_WRITE, 0, NULL, 
					OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComPort == INVALID_HANDLE_VALUE)
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}	
	COMMCONFIG conf = {0};	
	DWORD dwSize = sizeof(conf);
	conf.dwSize = dwSize;
	//This might fail with virtual COM ports are used.
	GetDefaultCommConfigA(buff, &conf, &dwSize);
	if (IEC)
	{
		conf.dcb.BaudRate = CBR_300; 
		conf.dcb.ByteSize = 7; 
		conf.dcb.StopBits = ONESTOPBIT; 
		conf.dcb.Parity = EVENPARITY; 
	}
	else
	{
		conf.dcb.BaudRate = CBR_9600; 
		conf.dcb.ByteSize = 8; 
		conf.dcb.StopBits = ONESTOPBIT; 
		conf.dcb.Parity = NOPARITY; 
	}
	conf.dcb.fDtrControl = DTR_CONTROL_ENABLE; 
	conf.dcb.fRtsControl = DTR_CONTROL_ENABLE; 
	SetCommState(m_hComPort, &conf.dcb); 	
	int cnt;
	if (IEC)
	{	
#if _MSC_VER > 1000
		strcpy_s(buff, 10, "/?!\r\n");
#else
		strcpy(buff, "/?!\r\n");
#endif		
		cnt = strlen(buff);
		DWORD sendSize = 0;		
		if (m_Trace)
		{
			TRACE1("\r\n<-");
			for(int pos = 0; pos != cnt; ++pos)
			{
				TRACE("%.2X ", buff[pos]);
			}
			TRACE1("\r\n");
		}
		BOOL bRes = ::WriteFile(m_hComPort, buff, cnt, &sendSize, &m_osWrite);
		if (!bRes)
		{				
			DWORD err = GetLastError();
			//If error occurs...
			if (err != ERROR_IO_PENDING)
			{				
				return ERROR_CODES_SEND_FAILED;
			}
			//Wait until data is actually sent
			::WaitForSingleObject(m_osWrite.hEvent, INFINITE);			
		}
		if (m_Trace)
		{
			TRACE1("\r\n->");
		}
		//Read reply data.				
		DWORD bytesRead = 0;
		do
		{
			cnt = 0;
			do
			{
				//Read reply one byte at time.
				if (!ReadFile(m_hComPort, m_Receivebuff + cnt, 1, &bytesRead, &m_osReader))
				{
					DWORD nErr = GetLastError();
					if (nErr != ERROR_IO_PENDING)     
					{
						return ERROR_CODES_SEND_FAILED;
					}			
					//Wait until data is actually read
					::WaitForSingleObject(m_osReader.hEvent, INFINITE);
				}
				if (m_Trace)
				{
					TRACE("%.2X ", m_Receivebuff[cnt]);
				}
				++cnt;
			}while(m_Receivebuff[cnt - 1] != 0x0A);
			m_Receivebuff[cnt] = 0;			
		}
		while(memcmp(buff, m_Receivebuff, cnt) == 0);//Remove echo.
		if (m_Trace)
		{
			TRACE1("\r\n");
		}
		if (m_Receivebuff[0] != '/')
		{
			return ERROR_CODES_SEND_FAILED;
		}
		char baudrate = m_Receivebuff[4];
		if (baudrate == ' ')
        {
            baudrate = '5';
        }
        int bitrate = 0;
        switch (baudrate)
        {
            case '0':
                bitrate = 300;
                break;
            case '1':
                bitrate = 600;
                break;
            case '2':
                bitrate = 1200;
                break;
            case '3':
                bitrate = 2400;
                break;
            case '4':
                bitrate = 4800;
                break;
            case '5':                            
                bitrate = 9600;
                break;
            case '6':
                bitrate = 19200;
                break;
            default:
                return ERROR_CODES_INVALID_PARAMETER;
        }   
		//Send ACK
		buff[0] = 0x06;
        //Send Protocol control character
        buff[1] = '2';// "2" HDLC protocol procedure (Mode E)
		buff[2] = baudrate;
		buff[3] = '2';
		buff[4] = (char) 0x0D;
		buff[5] = 0x0A;
		if (m_Trace)
		{
			TRACE1("\r\n<-");
			for(int pos = 0; pos != 6; ++pos)
			{
				TRACE("%.2X ", buff[pos]);
			}
			TRACE1("\r\n");
		}
		bRes = ::WriteFile(m_hComPort, buff, 6, &sendSize, &m_osWrite);
		if (!bRes)
		{
			DWORD err = GetLastError();
			//If error occurs...
			if (err != ERROR_IO_PENDING)
			{				
				return ERROR_CODES_SEND_FAILED;
			}
			//Wait until data is actually sent
			::WaitForSingleObject(m_osWrite.hEvent, INFINITE);			
		}
		m_Receivebuff[cnt] = 0;					
		//Read reply data.				
		bytesRead = 0;
		cnt = 0;
		//This sleep is in standard. Do not remove.
		Sleep(500);
		//Change bit rate.
		conf.dcb.BaudRate = bitrate;
		SetCommState(m_hComPort, &conf.dcb);
		if (m_Trace)
		{
			TRACE1("\r\n->");
		}
		do
		{
			//Read reply one byte at time.
			if (!ReadFile(m_hComPort, m_Receivebuff + cnt, 1, &bytesRead, &m_osReader))
			{
				DWORD nErr = GetLastError();
				if (nErr != ERROR_IO_PENDING)     
				{
					return ERROR_CODES_SEND_FAILED;
				}			
				//Wait until data is actually read
				::WaitForSingleObject(m_osReader.hEvent, INFINITE);
			}
			TRACE("%.2x ", m_Receivebuff[cnt]);
			++cnt;
		}
		while(m_Receivebuff[cnt - 1] != 0x0A);				
		if (m_Trace)
		{
			TRACE1("\r\n");
		}
		TRACE("Changing bit rate.\r\n", 0);
		conf.dcb.ByteSize = 8; 
		conf.dcb.StopBits = ONESTOPBIT; 
		conf.dcb.Parity = NOPARITY; 		
		SetCommState(m_hComPort, &conf.dcb); 	
		//Some meters need this sleep. Do not remove.
		Sleep(300);
	}
	return ERROR_CODES_OK;
}
#endif

//Initialize connection to the meter.
int GXClient::InitializeConnection()
{
	TRACE1("InitializeConnection\r\n");
	std::vector< std::vector<unsigned char> > data;
	vector<unsigned char> reply;
	int ret = 0;
	//Get meter's send and receive buffers size.
	if ((ret = m_Parser->SNRMRequest(data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 ||
		(ret = m_Parser->ParseUAResponse(reply)) != 0)
	{
		TRACE("SNRMRequest failed %d.\r\n", ret);
		return ret;
	}	
	reply.clear();
	if (m_Parser->GetIntefaceType() == GXDLMS_INTERFACETYPE_NET)
	{
		InitializeBuffers(0xFFFF, 0xFFFF);	
	}
	else
	{
		//Initialize send and receive buffers to same as meter's buffers.
		GXDLMSLimits limits = m_Parser->GetLimits();
		CGXDLMSVariant rx = limits.GetMaxInfoRX();
		rx.ChangeType(DLMS_DATA_TYPE_INT32);	
		CGXDLMSVariant tx = limits.GetMaxInfoTX();
		tx.ChangeType(DLMS_DATA_TYPE_INT32);
		InitializeBuffers(rx.lVal, tx.lVal);	
	}
	if ((ret = m_Parser->AARQRequest(data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 ||
		(ret = m_Parser->ParseAAREResponse(reply)) != 0)
	{
		if (ret == ERROR_CODES_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED)
		{
			TRACE1("Use Logical Name referencing is wrong. Change it!\r\n");
			return ret;
		}
		TRACE("AARQRequest failed %d.\r\n", ret);
		return ret;
	}	
	return ERROR_CODES_OK;
}

// Read DLMS Data frame from the device.
int GXClient::ReadDLMSPacket(vector<unsigned char>& data, int& ReplySize)
{
	ReplySize = 0;
    if (data.size() == 0)
    {		
		return ERROR_CODES_OK;
    }
	if (m_Trace)
	{
		string tmp;
		Now(tmp);
		tmp = "<- " + tmp; 
		tmp += "\t" + GXHelpers::bytesToHex(&data[0], data.size());
		GXHelpers::Write("trace.txt", tmp + "\r\n");
	}
#if _MSC_VER > 1000
	int len = data.size();
	if (m_hComPort != INVALID_HANDLE_VALUE)
	{
		DWORD sendSize;
		BOOL bRes = ::WriteFile(m_hComPort, &data[0], len, &sendSize, &m_osWrite);
		if (!bRes)
		{				
			DWORD err = GetLastError();
			//If error occurs...
			if (err != ERROR_IO_PENDING)
			{
				return ERROR_CODES_SEND_FAILED;
			}
			//Wait until data is actually sent
			::WaitForSingleObject(m_osWrite.hEvent, INFINITE);			
		}
	}
	else
	{		
		if (send(m_socket, (const char*) &data[0], len, 0) == -1)
		{
			//If error has occured
			return ERROR_CODES_SEND_FAILED;
		}
	}
#else
	if (send(m_socket, (const char*) &data[0], data.size(), 0) == -1)
	{
		//If error has occured
		return ERROR_CODES_SEND_FAILED;
	}
#endif

	int ret;
	bool bFirstByte = true;
	//Loop until packet is compleate.
	do
    {
		int cnt = m_ReceiveSize - ReplySize;
		if (cnt == 0)
		{
			return ERROR_CODES_OUTOFMEMORY;
		}
#if _MSC_VER > 1000
		if (m_hComPort != INVALID_HANDLE_VALUE)
		{			
			DWORD bytesRead;
			int index = 0;
			do
			{
				if (!ReadFile(m_hComPort, m_Receivebuff + ReplySize + index, 1, &bytesRead, &m_osReader))
				{
					DWORD nErr = GetLastError();
					if (nErr != ERROR_IO_PENDING)     
					{
						return ERROR_CODES_SEND_FAILED;
					}
					//Wait until data is actually sent
					::WaitForSingleObject(m_osReader.hEvent, INFINITE);
					//How many bytes we can read...
					if (!GetOverlappedResult(m_hComPort, &m_osReader, &bytesRead, TRUE))
					{
						return ERROR_CODES_RECEIVE_FAILED;
					}				
				}
				index += bytesRead;
				//Find HDLC EOP char.
				if (m_Receivebuff[ReplySize + index - 1] == 0x7E)
				{
					break;
				}
			}
			while(index < m_ReceiveSize);			
			ret = index;
		}
		else
#endif
		{
			if ((ret = recv(m_socket, (char*) m_Receivebuff + ReplySize, cnt, 0)) == -1)
			{
				return ERROR_CODES_RECEIVE_FAILED;
			}
		}
		if (m_Trace)
		{
			if (bFirstByte)
			{				
				string tmp;
				Now(tmp);
				tmp = "-> " + tmp; 
				tmp += "\t";
				GXHelpers::Write("trace.txt", tmp);
				bFirstByte = false;
			}
			string tmp = GXHelpers::bytesToHex(m_Receivebuff + ReplySize, ret);
			GXHelpers::Write("trace.txt", tmp);
		}
		ReplySize += ret;
    } 
    while (!m_Parser->IsDLMSPacketComplete(m_Receivebuff, ReplySize));
	if (m_Trace)
	{
		GXHelpers::Write("trace.txt", "\r\n");
	}
	//Check errors
	if ((ret = m_Parser->CheckReplyErrors(&data[0], data.size(), m_Receivebuff, ReplySize)) != 0)
	{
		return ret;
	}
	return 0;
}

int GXClient::ReadDataBlock(vector< vector<unsigned char> >& data, vector<unsigned char>& reply)
{	
	//If ther is no data to send.
	if (data.size() == 0)
	{
		return ERROR_CODES_OK;
	}	
	int ret;	
	//Send data.
	for(vector< vector<unsigned char> >::iterator it = data.begin(); it != data.end(); ++it)
	{		
		//Send data.
		int replySize;
		if ((ret = ReadDLMSPacket(*it, replySize)) != ERROR_CODES_OK)
		{
			return ret;
		}
		GXDLMS_DATA_REQUEST_TYPES type = GXDLMS_DATA_REQUEST_TYPES_NONE;
		if ((ret = m_Parser->GetDataFromPacket(m_Receivebuff, replySize, reply, type)) != ERROR_CODES_OK)
		{
			return ret;
		}
		//Check is there errors or more data from server		
		while ((type & (GXDLMS_DATA_REQUEST_TYPES_FRAME | GXDLMS_DATA_REQUEST_TYPES_BLOCK)) != 0)
		{			
			vector< vector<unsigned char> > data1;
			if ((type & GXDLMS_DATA_REQUEST_TYPES_FRAME) != 0)
			{									
				if ((ret = m_Parser->ReceiverReady(GXDLMS_DATA_REQUEST_TYPES_FRAME, data1)) != ERROR_CODES_OK)
				{
					return ret;
				}
			}
			else if ((type & GXDLMS_DATA_REQUEST_TYPES_BLOCK) != 0)
			{					
				if ((ret = m_Parser->ReceiverReady(GXDLMS_DATA_REQUEST_TYPES_BLOCK, data1)) != ERROR_CODES_OK)
				{
					return ret;
				}
			}
			replySize = 0;
			if ((ret = ReadDLMSPacket(data1[0], replySize)) != ERROR_CODES_OK)
			{
				return ret;
			}
			//return ReadDataBlock(data1, reply);		
			GXDLMS_DATA_REQUEST_TYPES tmp;
			if ((ret = m_Parser->GetDataFromPacket(m_Receivebuff, replySize, reply, tmp)) != ERROR_CODES_OK)
			{
				return ret;
			}
			if ((type & GXDLMS_DATA_REQUEST_TYPES_FRAME) != 0)
			{
				//If this was last frame.
                if ((tmp & GXDLMS_DATA_REQUEST_TYPES_FRAME) == 0)
                {
                    type = (GXDLMS_DATA_REQUEST_TYPES) (type & ~ GXDLMS_DATA_REQUEST_TYPES_FRAME);
                }
			}
			else
			{
				type = tmp;
			}
		};
	}
	return ERROR_CODES_OK;
}

//Get Accosiation view.
int GXClient::GetObjects(CGXDLMSObjectCollection& objects)
{	
	TRACE1("GetAssociationView\r\n");
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;	
	if ((ret = m_Parser->GetObjectsRequest(data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 ||
		(ret = m_Parser->ParseObjects(reply, objects, true)) != 0)
	{
		TRACE("GetObjects failed %d.\r\n", ret);
		return ret;
	}
	return ERROR_CODES_OK;
}

//Update SN or LN access list.
int GXClient::UpdateAccess(CGXDLMSObject* pObject, CGXDLMSObjectCollection& Objects)
{	
	CGXDLMSVariant data;
	int ret = Read(pObject, 2, data);
	if (ret != ERROR_CODES_OK)
	{
		return ret;
	}
	if (data.vt != DLMS_DATA_TYPE_ARRAY)
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	for(vector<CGXDLMSVariant>::iterator obj = data.Arr.begin(); obj != data.Arr.end(); ++obj)
	{
		if (obj->vt != DLMS_DATA_TYPE_STRUCTURE || obj->Arr.size() != 4)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		CGXDLMSVariant& access_rights = obj->Arr[3];
		if (access_rights.vt != DLMS_DATA_TYPE_STRUCTURE || access_rights.Arr.size() != 2)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		OBJECT_TYPE type = (OBJECT_TYPE) obj->Arr[0].uiVal;
		// unsigned char version = obj->Arr[1].bVal;
		CGXDLMSObject* pObj = Objects.FindByLN(type, obj->Arr[2].byteArr);
		if (pObj != NULL)
		{
			//Attribute access.
			for(vector<CGXDLMSVariant>::iterator it = access_rights.Arr[0].Arr.begin();
				it != access_rights.Arr[0].Arr.end(); ++it)
			{
				unsigned char id = it->Arr[0].bVal;
				ACCESSMODE access = (ACCESSMODE) it->Arr[1].bVal;
				pObj->SetAccess(id, access);
			}
			//Method access.			
			for(vector<CGXDLMSVariant>::iterator it = access_rights.Arr[1].Arr.begin();
				it != access_rights.Arr[1].Arr.end(); ++it)
			{
				unsigned char id = it->Arr[0].bVal;
				METHOD_ACCESSMODE access = (METHOD_ACCESSMODE) it->Arr[1].bVal;
				pObj->SetMethodAccess(id, access);
			}
		}		
	}
	return ERROR_CODES_OK;
}

//Read selected object.
int GXClient::Read(CGXDLMSObject* pObject, int attributeIndex, CGXDLMSVariant& value)
{	
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	CGXDLMSVariant name = pObject->GetName();
	if ((ret = m_Parser->Read(name, pObject->GetObjectType(), attributeIndex, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 || 
		(ret = m_Parser->UpdateValue(reply, pObject, attributeIndex, value)) != 0)
	{
		printf("Error! %d: read failed: %d\r\n", attributeIndex, ret);
		return ret;
	}
	//Update data type.
	DLMS_DATA_TYPE type;
	if ((ret = pObject->GetDataType(attributeIndex, type)) != 0)
	{
		TRACE("Read failed %d.\r\n", ret);
		return ret;
	}	
	if (type == DLMS_DATA_TYPE_NONE)
	{
		
		if ((ret = m_Parser->GetDataType(reply, type)) != 0 ||
			(ret = pObject->SetDataType(attributeIndex, type)) != 0)
		{
			return ret;
		}
	}
	return ERROR_CODES_OK;
}

//Write selected object.
int GXClient::Write(CGXDLMSObject* pObject, int attributeIndex, CGXDLMSVariant& value)
{	
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	CGXDLMSVariant name = pObject->GetName();
	if ((ret = m_Parser->Write(name, pObject->GetObjectType(), attributeIndex, value, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0)
	{
		TRACE("Write failed %d.\r\n", ret);
		return ret;
	}
	return ERROR_CODES_OK;
}

//Write selected object.
int GXClient::Method(CGXDLMSObject* pObject, int attributeIndex, CGXDLMSVariant& value)
{	
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	CGXDLMSVariant name = pObject->GetName();
	if ((ret = m_Parser->Method(name, pObject->GetObjectType(), attributeIndex, value, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0)
	{
		TRACE("Method failed %d.\r\n", ret);
		return ret;
	}
	return ERROR_CODES_OK;
}

int GXClient::ReadRowsByRange(CGXDLMSVariant& Name, CGXDLMSObject* pSortObject, struct tm* start, struct tm* end, CGXDLMSVariant& rows)
{
	rows.Clear();
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	if ((ret = m_Parser->ReadRowsByRange(Name, pSortObject, start, end, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 || 
		(ret = m_Parser->GetValue(reply, rows)) != 0)
	{
		TRACE("Read failed %d.\r\n", ret);
		return ret;
	}
	return ERROR_CODES_OK;
}

int GXClient::ReadRowsByEntry(CGXDLMSVariant& Name, unsigned int Index, unsigned int Count, CGXDLMSVariant& rows)
{
	rows.Clear();
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	if ((ret = m_Parser->ReadRowsByEntry(Name, Index, Count, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 || 
		(ret = m_Parser->GetValue(reply, rows)) != 0)
	{
		TRACE("Read failed %d.\r\n", ret);
		return ret;
	}
	return ERROR_CODES_OK;
}
