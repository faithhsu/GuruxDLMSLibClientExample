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

#include "../GXDLMSVariant.h"
#include "../GXDLMSClient.h"
#include "GXDLMSTcpUdpSetup.h"


void CGXDLMSTcpUdpSetup::Init()
{
	m_Port = 4059;
	m_IPReference = "127.0.0.1";
	m_MaximumSimultaneousConnections = 1;
	SetInactivityTimeout(180);
    SetMaximumSegmentSize(576);
}

/**  
 Constructor.
*/
CGXDLMSTcpUdpSetup::CGXDLMSTcpUdpSetup() :  CGXDLMSObject(OBJECT_TYPE_TCP_UDP_SETUP, "0.0.25.0.0.255")
{
	Init();
}

/**  
 Constructor.

 @param ln Logican Name of the object.
*/
CGXDLMSTcpUdpSetup::CGXDLMSTcpUdpSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_TCP_UDP_SETUP, ln)
{
	Init();
}

/**  
 Constructor.

 @param ln Logican Name of the object.
 @param sn Short Name of the object.
*/
CGXDLMSTcpUdpSetup::CGXDLMSTcpUdpSetup(basic_string<char> ln, short sn) : CGXDLMSObject(OBJECT_TYPE_TCP_UDP_SETUP, sn)
{
    Init();
}	

int CGXDLMSTcpUdpSetup::GetPort()
{
    return m_Port;
}

void CGXDLMSTcpUdpSetup::SetPort(int value)
{
   m_Port = value;
}

basic_string<char> CGXDLMSTcpUdpSetup::GetIPReference()
{
    return m_IPReference;
}
void CGXDLMSTcpUdpSetup::SetIPReference(basic_string<char> value)
{
   m_IPReference = value;
}

int CGXDLMSTcpUdpSetup::GetMaximumSegmentSize()
{
    return m_MaximumSegmentSize;
}
void CGXDLMSTcpUdpSetup::SetMaximumSegmentSize(int value)
{
   m_MaximumSegmentSize = value;
}

int CGXDLMSTcpUdpSetup::GetMaximumSimultaneousConnections()
{
    return m_MaximumSimultaneousConnections;
}
void CGXDLMSTcpUdpSetup::SetMaximumSimultaneousConnections(int value)
{
   m_MaximumSimultaneousConnections = value;
}

int CGXDLMSTcpUdpSetup::GetInactivityTimeout()
{
    return m_InactivityTimeout;
}
void CGXDLMSTcpUdpSetup::SetInactivityTimeout(int value)
{
   m_InactivityTimeout = value;
}

// Returns amount of attributes.
int CGXDLMSTcpUdpSetup::GetAttributeCount()
{
	return 6;
}

// Returns amount of methods.
int CGXDLMSTcpUdpSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSTcpUdpSetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(CGXDLMSVariant(m_Port).ToString());
	values.push_back(m_IPReference);
	values.push_back(CGXDLMSVariant(m_MaximumSegmentSize).ToString());
	values.push_back(CGXDLMSVariant(m_MaximumSimultaneousConnections).ToString());
	values.push_back(CGXDLMSVariant(m_InactivityTimeout).ToString());
}

void CGXDLMSTcpUdpSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
	}
	//Port
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //IPReference
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //MaximumSegmentSize
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //MaximumSimultaneousConnections
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //InactivityTimeout
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
}

int CGXDLMSTcpUdpSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;		
	}
    else if (index == 2)
	{
		type = DLMS_DATA_TYPE_UINT16;			
	}
	else if (index == 3)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;			
	}
	else if (index == 4)
	{
		type = DLMS_DATA_TYPE_UINT16;			
	}
	else if (index == 5)
	{
		type = DLMS_DATA_TYPE_UINT8;			
	}
	else if (index == 6)
	{
		type = DLMS_DATA_TYPE_UINT16;						
	}
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSTcpUdpSetup::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)    
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
	{
		value = GetPort();
		return ERROR_CODES_OK;
	}
	if (index == 3)
	{
		value = GetIPReference();
		return ERROR_CODES_OK;
	}
	if (index == 4)
	{
		value = GetMaximumSegmentSize();
		return ERROR_CODES_OK;
	}
	if (index == 5)
	{
		value = GetMaximumSimultaneousConnections();
		return ERROR_CODES_OK;
	}
	if (index == 6)
	{
		value = GetInactivityTimeout();
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSTcpUdpSetup::SetValue(int index, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		memcpy(m_LN, &value.byteArr[0], 6);
	}
    else if (index == 2)
	{
		SetPort(value.ToInteger());
		return ERROR_CODES_OK;			
	}
	else if (index == 3)
    {
        if (value.vt == DLMS_DATA_TYPE_NONE)
        {
            SetIPReference("");
        }
        else
        {
            if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
				SetIPReference(value.ToString());
				/*
                String str = "";
                for(int ch : (byte[]) value)
                {
                    str += String.valueOf(ch) + ".";
                }
                str = str.substring(0, str.length() - 1);
                setIPReference(str);
				*/
            }
            else
            {
                SetIPReference(value.ToString());
            }
        }			
    }
    else if (index == 4)
    {
        if (value.vt == DLMS_DATA_TYPE_NONE)
        {
            SetMaximumSegmentSize(576);
        }
        else
        {
            SetMaximumSegmentSize(value.ToInteger());
        }
    }
    else if (index == 5)
    {
        if (value.vt == DLMS_DATA_TYPE_NONE)
        {
            SetMaximumSimultaneousConnections(1);
        }
        else
        {
            SetMaximumSimultaneousConnections(value.ToInteger());
        }
    }
    else if (index == 6)
    {
        if (value.vt == DLMS_DATA_TYPE_NONE)
        {
            SetInactivityTimeout(180);
        }
        else
        {
            SetInactivityTimeout(value.ToInteger());
        }
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}