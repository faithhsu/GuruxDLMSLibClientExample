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

#include "GXDLMSHdlcSetup.h"

//Constructor.
CGXDLMSHdlcSetup::CGXDLMSHdlcSetup() : CGXDLMSObject(OBJECT_TYPE_IEC_HDLC_SETUP)
{
	m_CommunicationSpeed = BAUDRATE_9600;
    m_WindowSizeTransmit = m_WindowSizeReceive = 1;
    m_MaximumInfoLengthTransmit = m_MaximumInfoLengthReceive = 128;
}

//SN Constructor.
CGXDLMSHdlcSetup::CGXDLMSHdlcSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_IEC_HDLC_SETUP, sn)
{
	m_CommunicationSpeed = BAUDRATE_9600;
    m_WindowSizeTransmit = m_WindowSizeReceive = 1;
    m_MaximumInfoLengthTransmit = m_MaximumInfoLengthReceive = 128;
}

//LN Constructor.
CGXDLMSHdlcSetup::CGXDLMSHdlcSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_IEC_HDLC_SETUP, ln)
{
	m_CommunicationSpeed = BAUDRATE_9600;
    m_WindowSizeTransmit = m_WindowSizeReceive = 1;
    m_MaximumInfoLengthTransmit = m_MaximumInfoLengthReceive = 128;
}

BAUDRATE CGXDLMSHdlcSetup::GetCommunicationSpeed()
{
    return m_CommunicationSpeed;
}
void CGXDLMSHdlcSetup::SetCommunicationSpeed(BAUDRATE value)
{
    m_CommunicationSpeed = value;
}

int CGXDLMSHdlcSetup::GetWindowSizeTransmit()
{
    return m_WindowSizeTransmit;
}
void CGXDLMSHdlcSetup::SetWindowSizeTransmit(int value)
{
    m_WindowSizeTransmit = value;
}

int CGXDLMSHdlcSetup::GetWindowSizeReceive()
{
    return m_WindowSizeReceive;
}
void CGXDLMSHdlcSetup::SetWindowSizeReceive(int value)
{
    m_WindowSizeReceive = value;
}

int CGXDLMSHdlcSetup::GetMaximumInfoLengthTransmit()
{
    return m_MaximumInfoLengthTransmit;
}
void CGXDLMSHdlcSetup::SetMaximumInfoLengthTransmit(int value)
{
    m_MaximumInfoLengthTransmit = value;
}

int CGXDLMSHdlcSetup::GetMaximumInfoLengthReceive()
{
    return m_MaximumInfoLengthReceive;
}
void CGXDLMSHdlcSetup::SetMaximumInfoLengthReceive(int value)
{
    m_MaximumInfoLengthReceive = value;
}

int CGXDLMSHdlcSetup::GetInterCharachterTimeout()
{
    return m_InterCharachterTimeout;
}
void CGXDLMSHdlcSetup::SetInterCharachterTimeout(int value)
{
    m_InterCharachterTimeout = value;
}

int CGXDLMSHdlcSetup::GetInactivityTimeout()
{
    return m_InactivityTimeout;
}
void CGXDLMSHdlcSetup::SetInactivityTimeout(int value)
{
    m_InactivityTimeout = value;
}

int CGXDLMSHdlcSetup::GetDeviceAddress()
{
    return m_DeviceAddress;
}
void CGXDLMSHdlcSetup::SetDeviceAddress(int value)
{
    m_DeviceAddress = value;
}

// Returns amount of attributes.
int CGXDLMSHdlcSetup::GetAttributeCount()
{
	return 9;
}

// Returns amount of methods.
int CGXDLMSHdlcSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSHdlcSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//CommunicationSpeed
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //WindowSizeTransmit
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //WindowSizeReceive
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //MaximumInfoLengthTransmit
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //MaximumInfoLengthReceive
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    //InterCharachterTimeout
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    //InactivityTimeout
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }
    //DeviceAddress
    if (!IsRead(9))
    {
        attributes.push_back(9);
    }
}

int CGXDLMSHdlcSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;		
	}
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 9)
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
int CGXDLMSHdlcSetup::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        value = m_CommunicationSpeed;
    }
    else if (index == 3)
    {
        value = m_WindowSizeTransmit;
    }
    else if (index == 4)
    {
        value = m_WindowSizeReceive;
    }
    else if (index == 5)
    {
        value = m_MaximumInfoLengthTransmit;
    }
    else if (index == 6)
    {
        value = m_MaximumInfoLengthReceive;
    }
    else if (index == 7)
    {
        value = m_InterCharachterTimeout;
    }
    else if (index == 8)
    {
        value = m_InactivityTimeout;
    }
    else if (index == 9)
    {
        value = m_DeviceAddress;
    } 
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Set value of given attribute.
int CGXDLMSHdlcSetup::SetValue(int index, CGXDLMSVariant& value)
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
        m_CommunicationSpeed = (BAUDRATE) value.ToInteger();
    }
    else if (index == 3)
    {
        m_WindowSizeTransmit = value.ToInteger();
    }
    else if (index == 4)
    {
        m_WindowSizeReceive = value.ToInteger();
    }
    else if (index == 5)
    {
        m_MaximumInfoLengthTransmit = value.ToInteger();
    }
    else if (index == 6)
    {
        m_MaximumInfoLengthReceive = value.ToInteger();
    }
    else if (index == 7)
    {
        m_InterCharachterTimeout = value.ToInteger();
    }
    else if (index == 8)
    {
        m_InactivityTimeout = value.ToInteger();
    }
    else if (index == 9)
    {
        m_DeviceAddress = value.ToInteger();
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}