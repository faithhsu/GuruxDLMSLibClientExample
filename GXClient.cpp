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
#include "GuruxDLMS/Objects/GXDLMSProfileGeneric.h"

GXClient::GXClient(CGXDLMSClient* pParser, int wt, bool trace) :
						m_WaitTime(wt), m_Parser(pParser),
						m_socket(-1), m_Receivebuff(NULL),
						m_SendSize(60), m_ReceiveSize(60), m_Trace(trace)
{
	InitializeBuffers(m_SendSize, m_ReceiveSize);
#if defined(_WIN32) || defined(_WIN64)//Windows includes
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
		//Show error but continue close.			
	}	
#if defined(_WIN32) || defined(_WIN64)//Windows includes
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
#if defined(_WIN32) || defined(_WIN64)//Windows includes
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

#if defined(_WIN32) || defined(_WIN64)//Windows includes
int GXClient::GXGetCommState(HANDLE hWnd, LPDCB DCB)
{
	ZeroMemory(DCB, sizeof(LPDCB));
	DCB->DCBlength = sizeof(DCB);
	if (!GetCommState(hWnd, DCB))
	{
		DWORD err = GetLastError(); //Save occured error.
		if (err == 995)
		{
			COMSTAT comstat;
			unsigned long RecieveErrors;
			if (!ClearCommError(hWnd, &RecieveErrors, &comstat))
			{
				return GetLastError();
			}
			if (!GetCommState(hWnd, DCB))
			{
				return GetLastError(); //Save occured error.
			}
		}
		else
		{
			//If USB to serial port converters do not implement this.
			if (err != ERROR_INVALID_FUNCTION)
			{
				return err;
			}
		}
	}
	return ERROR_CODES_OK;
}

int GXClient::GXSetCommState(HANDLE hWnd, LPDCB DCB)
{
	if (!SetCommState(hWnd, DCB))
	{
		DWORD err = GetLastError(); //Save occured error.
		if (err == 995)
		{
			COMSTAT comstat;
			unsigned long RecieveErrors;
			if (!ClearCommError(hWnd, &RecieveErrors, &comstat))
			{
				return GetLastError();
			}
			if (!SetCommState(hWnd, DCB))
			{
				return GetLastError();
			}
		}
		else
		{
			//If USB to serial port converters do not implement this.
			if (err != ERROR_INVALID_FUNCTION)
			{
				return err;
			}
		}
	}
	return ERROR_CODES_OK;
}

int GXClient::Read(unsigned char* pData, int len, unsigned char eop, bool removeEcho, int& index)
{
	//Read reply data.				
	COMSTAT comstat;
	unsigned long RecieveErrors;
	bool bFound = false;
	do
	{
		//We do not want to read byte at the time.
		if (index != 0)
		{
			Sleep(100);
		}
		DWORD bytesRead = 0;
		if (!ClearCommError(m_hComPort, &RecieveErrors, &comstat))
		{
			return ERROR_CODES_SEND_FAILED;
		}
		int cnt = 1;
		//Try to read at least one byte.
		if (comstat.cbInQue > 0)
		{
			cnt = comstat.cbInQue;
		}
		if (!ReadFile(m_hComPort, m_Receivebuff + index, cnt, &bytesRead, &m_osReader))
		{
			DWORD nErr = GetLastError();
			if (nErr != ERROR_IO_PENDING)     
			{
				return ERROR_CODES_RECEIVE_FAILED;
			}			
			//Wait until data is actually read
			if (::WaitForSingleObject(m_osReader.hEvent, m_WaitTime) != WAIT_OBJECT_0)
			{
				return ERROR_CODES_RECEIVE_FAILED;
			}
			if (!GetOverlappedResult(m_hComPort, &m_osReader, &bytesRead, TRUE))
			{
				return ERROR_CODES_RECEIVE_FAILED;
			}
		}
		//Note! Some USB converters can return true for ReadFile and Zero as bytesRead.
		//In that case wait for a while and read again.
		if (bytesRead == 0)
		{
			Sleep(100);
			continue;
		}
		if (m_Trace)
		{
			string tmp = GXHelpers::bytesToHex(m_Receivebuff + index, bytesRead);
			TRACE("%s\r\n", tmp.c_str());
		}
		if (index > 5 || bytesRead > 5)
		{
			//Some optical strobes can return extra bytes.
			for(int pos = bytesRead - 1; pos != -1; --pos)
			{
				if(m_Receivebuff[index + pos] == eop)
				{
					bFound = true;
					break;
				}
			}
		}
		index += bytesRead;
	}
	while(!bFound && index < m_ReceiveSize);
	string tmp;
	Now(tmp);
	tmp = "-> " + tmp; 
	tmp += "\t";
	tmp += GXHelpers::bytesToHex(m_Receivebuff, index);
	tmp += "\r\n";
	GXHelpers::Write("trace.txt", tmp);
	if (removeEcho && memcmp(pData, m_Receivebuff, len) == 0)//Remove echo.
	{
		memcpy(m_Receivebuff, m_Receivebuff + len, index - len);
		index -= len;
		if (index == 0)
		{
			return Read(pData, len, eop, removeEcho, index);
		}
	}
	return ERROR_CODES_OK;
}

//Open serial port.
int GXClient::Open(const char* pPortName, bool IEC, int maxBaudrate)
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
	DCB dcb = {0};
	dcb.DCBlength = sizeof(DCB);
	dcb.fBinary = 1;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fRtsControl = DTR_CONTROL_ENABLE;
	dcb.fOutX = dcb.fInX = 0;
    //CTS handshaking on output.
	dcb.fOutxCtsFlow = DTR_CONTROL_DISABLE;
    //DSR handshaking on output
	dcb.fOutxDsrFlow = DTR_CONTROL_DISABLE;    
	//Abort all reads and writes on Error.
	dcb.fAbortOnError = 1;
	if (IEC)
	{
		dcb.BaudRate = CBR_300; 
		dcb.ByteSize = 7; 
		dcb.StopBits = ONESTOPBIT; 
		dcb.Parity = EVENPARITY; 
	}
	else
	{
		dcb.BaudRate = CBR_9600; 
		dcb.ByteSize = 8; 
		dcb.StopBits = ONESTOPBIT; 
		dcb.Parity = NOPARITY; 
	}
	int ret;	
	if ((ret = GXSetCommState(m_hComPort, &dcb)) != 0)	
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	int cnt;
	if (IEC)
	{	
#if _MSC_VER > 1000
		strcpy_s(buff, 10, "/?!\r\n");
#else
		strcpy(buff, "/?!\r\n");
#endif		
		int len = strlen(buff);
		DWORD sendSize = 0;		
		if (m_Trace)
		{
			TRACE1("\r\n<-");
			for(int pos = 0; pos != len; ++pos)
			{
				TRACE("%.2X ", buff[pos]);
			}
			TRACE1("\r\n");
		}
		string tmp;
		Now(tmp);
		tmp = "<- " + tmp; 
		tmp += "\t";
		tmp += GXHelpers::bytesToHex((unsigned char*) buff, len);
		tmp += "\r\n";
		GXHelpers::Write("trace.txt", tmp);
		BOOL bRes = ::WriteFile(m_hComPort, buff, len, &sendSize, &m_osWrite);
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
		cnt = 0;
		if (Read((unsigned char*) buff, len, '\n', true, cnt) != 0)
		{
            return ERROR_CODES_INVALID_PARAMETER;
		}
		if (m_Trace)
		{
			TRACE1("\r\n");
		}
		if (m_Receivebuff[0] != '/')
		{
			return ERROR_CODES_SEND_FAILED;
		}
		char baudrate = m_Receivebuff[4];
		if (maxBaudrate != 0)
		{
			if (maxBaudrate < CBR_300 || maxBaudrate > CBR_19200 ||
				maxBaudrate % CBR_300 != 0)
			{
				return ERROR_CODES_INVALID_PARAMETER;				
			}
			char ch = 0;
			while (maxBaudrate > (300 << ch))
			{
				++ch;
			}
			ch += '0';	
			if (ch < baudrate)
			{
				baudrate = ch;
			}
		}	
        int bitrate = 0;
        switch (baudrate)
        {
            case '0':
                bitrate = CBR_300;
                break;
            case '1':
                bitrate = CBR_600;
                break;
            case '2':
                bitrate = CBR_1200;
                break;
            case '3':
                bitrate = CBR_2400;
                break;
            case '4':
                bitrate = CBR_4800;
                break;
            case '5':                            
                bitrate = CBR_9600;
                break;
            case '6':
                bitrate = CBR_19200;
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
		len = 6;
		if (m_Trace)
		{
			TRACE1("\r\n<-");
			for(int pos = 0; pos != len; ++pos)
			{
				TRACE("%.2X ", buff[pos]);
			}
			TRACE1("\r\n");
		}
		bRes = ::WriteFile(m_hComPort, buff, len, &sendSize, &m_osWrite);
		if (!bRes)
		{
			int err = GetLastError();
			//If error occurs...
			if (err != ERROR_IO_PENDING)
			{				
				TRACE("WriteFile %d\r\n", err);
				return ERROR_CODES_SEND_FAILED;
			}
			//Wait until data is actually sent
			::WaitForSingleObject(m_osWrite.hEvent, INFINITE);			
		}
		tmp.clear();
		Now(tmp);
		tmp = "<- " + tmp; 
		tmp += "\t";
		tmp += GXHelpers::bytesToHex((unsigned char*)buff, len);
		tmp += "\r\n";
		GXHelpers::Write("trace.txt", tmp);
		cnt = 0;
		//This sleep is in standard. Do not remove.
		Sleep(1000);	
		dcb.BaudRate = bitrate;
		if ((ret = GXSetCommState(m_hComPort, &dcb)) != 0)
		{
			TRACE("GXSetCommState %d\r\n", ret);
			return ERROR_CODES_INVALID_PARAMETER;
		}
		TRACE("New bitrate %d\r\n", bitrate);
		len = 6;
		if ((ret = Read((unsigned char*)buff, len, '\n', false, cnt)) != 0)
		{
			TRACE("Read %d\r\n", ret);
            return ERROR_CODES_INVALID_PARAMETER;
		}
		dcb.ByteSize = 8; 
		dcb.StopBits = ONESTOPBIT; 
		dcb.Parity = NOPARITY; 		
		if ((ret = GXSetCommState(m_hComPort, &dcb)) != 0)
		{
			TRACE("GXSetCommState %d\r\n", ret);
			return ERROR_CODES_INVALID_PARAMETER;
		}
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
	string tmp;
	Now(tmp);
	tmp = "<- " + tmp; 
	tmp += "\t" + GXHelpers::bytesToHex(&data[0], data.size());
	GXHelpers::Write("trace.txt", tmp + "\r\n");

#if defined(_WIN32) || defined(_WIN64)//Windows includes
	int len = data.size();
	if (m_hComPort != INVALID_HANDLE_VALUE)
	{
		DWORD sendSize = 0;
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
#if defined(_WIN32) || defined(_WIN64)//Windows includes
		if (m_hComPort != INVALID_HANDLE_VALUE)
		{
			if(Read(&data[0], len, 0x7E, false, ReplySize) != 0)
			{
				return ERROR_CODES_SEND_FAILED;
			}
		}
		else
#endif
		{
			if ((ret = recv(m_socket, (char*) m_Receivebuff + ReplySize, cnt, 0)) == -1)
			{
				return ERROR_CODES_RECEIVE_FAILED;
			}
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
			ReplySize += ret;
		}
    } 
    while (!m_Parser->IsDLMSPacketComplete(m_Receivebuff, ReplySize));
	GXHelpers::Write("trace.txt", "\r\n");

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
		int replySize = 0;
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
				TRACE1("-");
				if ((ret = m_Parser->ReceiverReady(GXDLMS_DATA_REQUEST_TYPES_FRAME, data1)) != ERROR_CODES_OK)
				{
					return ret;
				}
			}
			else if ((type & GXDLMS_DATA_REQUEST_TYPES_BLOCK) != 0)
			{					
				TRACE1("+");
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
		(ret = m_Parser->ParseObjects(reply, objects, false)) != 0)
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
	value.Clear();
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	CGXDLMSVariant name = pObject->GetName();
	if ((ret = m_Parser->Read(name, pObject->GetObjectType(), attributeIndex, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 || 
		(ret = m_Parser->UpdateValue(reply, pObject, attributeIndex, value)) != 0)
	{		
		return ret;
	}
	//Update data type.
	DLMS_DATA_TYPE type;
	if ((ret = pObject->GetDataType(attributeIndex, type)) != 0)
	{		
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
	
	//Get read value as string.
	//Note! This is for example. It's faster if you handle read COSEM object directly.
	vector<string> values;
	pObject->GetValues(values);
	value = values[attributeIndex - 1];
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
		return ret;
	}
	return ERROR_CODES_OK;
}

int GXClient::ReadRowsByRange(CGXDLMSObject* pObject, struct tm* start, struct tm* end, CGXDLMSVariant& rows)
{
	rows.Clear();
	//Read last day from Profile Generic.                    
	CGXDLMSObject* pSortObject = ((CGXDLMSProfileGeneric*) pObject)->GetSortObject();
	if (pSortObject == NULL)
	{
		pSortObject = ((CGXDLMSProfileGeneric*) pObject)->GetCaptureObjects()[0].first;
	}

	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	CGXDLMSVariant name = pObject->GetName();
	if ((ret = m_Parser->ReadRowsByRange(name, pSortObject, start, end, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 || 
		(ret = m_Parser->UpdateValue(reply, pObject, 2, rows)) != 0)
	{
		return ret;
	}
	//Get read value as string.
	//Note! This is for example. It's faster if you handle read COSEM object directly.
	vector<string> values;
	pObject->GetValues(values);
	rows = values[2 - 1];	
	return ERROR_CODES_OK;
}

int GXClient::ReadRowsByEntry(CGXDLMSObject* pObject, unsigned int Index, unsigned int Count, CGXDLMSVariant& rows)
{
	rows.Clear();
	int ret;
	vector< vector<unsigned char> > data;
	vector<unsigned char> reply;
	//Get meter's send and receive buffers size.
	CGXDLMSVariant name = pObject->GetName();
	if ((ret = m_Parser->ReadRowsByEntry(name, Index, Count, data)) != 0 ||
		(ret = ReadDataBlock(data, reply)) != 0 || 
		(ret = m_Parser->UpdateValue(reply, pObject, 2, rows)) != 0)		
	{
		return ret;
	}
	//Get read value as string.
	//Note! This is for example. It's faster if you handle read COSEM object directly.
	vector<string> values;
	pObject->GetValues(values);
	rows = values[2 - 1];	
	return ERROR_CODES_OK;
}
