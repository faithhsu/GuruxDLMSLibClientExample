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

#include "GXDLMSIECOpticalPortSetup.h"
#include "../GXDLMSClient.h"
#include "../GXDLMSConverter.h"

void CGXDLMSIECOpticalPortSetup::Init()
{
	m_DefaultMode = OPTICAL_PROTOCOL_MODE_DEFAULT;
	m_DefaultBaudrate = BAUDRATE_300;
	m_ProposedBaudrate = BAUDRATE_9600;
}

//Constructor.
CGXDLMSIECOpticalPortSetup::CGXDLMSIECOpticalPortSetup() : CGXDLMSObject(OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, "0.0.20.0.0.255")
{
	Init();
}

//SN Constructor.
CGXDLMSIECOpticalPortSetup::CGXDLMSIECOpticalPortSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, sn)
{
	Init();
}

//LN Constructor.
CGXDLMSIECOpticalPortSetup::CGXDLMSIECOpticalPortSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, ln)
{
	Init();
}

OPTICAL_PROTOCOL_MODE CGXDLMSIECOpticalPortSetup::GetDefaultMode()
{
    return m_DefaultMode;
}
void CGXDLMSIECOpticalPortSetup::SetDefaultMode(OPTICAL_PROTOCOL_MODE value)
{
    m_DefaultMode = value;
}

BAUDRATE CGXDLMSIECOpticalPortSetup::GetDefaultBaudrate()
{
    return m_DefaultBaudrate;
}
void CGXDLMSIECOpticalPortSetup::SetDefaultBaudrate(BAUDRATE value)
{
    m_DefaultBaudrate = value;
}

BAUDRATE CGXDLMSIECOpticalPortSetup::GetProposedBaudrate()
{
    return m_ProposedBaudrate;
}
void CGXDLMSIECOpticalPortSetup::SetProposedBaudrate(BAUDRATE value)
{
    m_ProposedBaudrate = value;
}

LOCAL_PORT_RESPONSE_TIME CGXDLMSIECOpticalPortSetup::GetResponseTime()
{
    return m_ResponseTime;
}
void CGXDLMSIECOpticalPortSetup::SetResponseTime(LOCAL_PORT_RESPONSE_TIME value)
{
    m_ResponseTime = value;
}

basic_string<char> CGXDLMSIECOpticalPortSetup::GetDeviceAddress()
{
    return m_DeviceAddress;
}
void CGXDLMSIECOpticalPortSetup::SetDeviceAddress(basic_string<char> value)
{
    m_DeviceAddress = value;
}

basic_string<char> CGXDLMSIECOpticalPortSetup::GetPassword1()
{
    return m_Password1;
}
void CGXDLMSIECOpticalPortSetup::SetPassword1(basic_string<char> value)
{
    m_Password1 = value;
}

basic_string<char> CGXDLMSIECOpticalPortSetup::GetPassword2()
{
    return m_Password2;
}
void CGXDLMSIECOpticalPortSetup::SetPassword2(basic_string<char> value)
{
    m_Password2 = value;
}

basic_string<char> CGXDLMSIECOpticalPortSetup::GetPassword5()
{
    return m_Password5;
}
void CGXDLMSIECOpticalPortSetup::SetPassword5(basic_string<char> value)
{
    m_Password5 = value;
}

// Returns amount of attributes.
int CGXDLMSIECOpticalPortSetup::GetAttributeCount()
{
	return 9;
}

// Returns amount of methods.
int CGXDLMSIECOpticalPortSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSIECOpticalPortSetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(CGXDLMSVariant(m_DefaultMode).ToString());
	values.push_back(CGXDLMSConverter::ToString(m_DefaultBaudrate));
	values.push_back(CGXDLMSConverter::ToString(m_ProposedBaudrate));
	values.push_back(CGXDLMSVariant(m_ResponseTime).ToString());	
	values.push_back(m_DeviceAddress);
	values.push_back(m_Password1);
	values.push_back(m_Password2);
	values.push_back(m_Password5);
}

void CGXDLMSIECOpticalPortSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//DefaultMode
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //DefaultBaudrate
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //ProposedBaudrate
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //ResponseTime
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //DeviceAddress
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    //Password1
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    //Password2
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }
    //Password5
    if (!IsRead(9))
    {
        attributes.push_back(9);
    }	
}

int CGXDLMSIECOpticalPortSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
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
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }   
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSIECOpticalPortSetup::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {            
        value = GetDefaultMode();
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        value = GetDefaultBaudrate();
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        value = GetProposedBaudrate();
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {
        value = GetResponseTime();
		return ERROR_CODES_OK;
    }
    if (index == 6)
    {
		value.Add(&m_DeviceAddress[0], m_DeviceAddress.size());
		return ERROR_CODES_OK;
    }
    if (index == 7)
    {
		value.Add(&m_Password1[0], m_Password1.size());
		return ERROR_CODES_OK;
    }
    if (index == 8)
    {
		value.Add(&m_Password2[0], m_Password2.size());
		return ERROR_CODES_OK;
    }
    if (index == 9)
    {
		value.Add(&m_Password5[0], m_Password5.size());
		return ERROR_CODES_OK;
    }
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSIECOpticalPortSetup::SetValue(int index, CGXDLMSVariant& value)
{
	if (index == 1)
	{			
		if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		memcpy(m_LN, &value.byteArr[0], 6);
		return ERROR_CODES_OK;
	}
    else if (index == 2)
    {
		SetDefaultMode((OPTICAL_PROTOCOL_MODE) value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 3)
    {
        SetDefaultBaudrate((BAUDRATE) value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 4)
    {
        SetProposedBaudrate((BAUDRATE) value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 5)
    {
        SetResponseTime((LOCAL_PORT_RESPONSE_TIME) value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 6)
    {
		CGXDLMSVariant tmp;
		CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
		SetDeviceAddress(tmp.strVal);
		return ERROR_CODES_OK;
    }
    else if (index == 7)
    {
		CGXDLMSVariant tmp;
		CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
        SetPassword1(tmp.strVal);
		return ERROR_CODES_OK;
    }
    else if (index == 8)
    {
		CGXDLMSVariant tmp;
		CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
        SetPassword2(tmp.strVal);
		return ERROR_CODES_OK;
    }
    else if (index == 9)
    {
		CGXDLMSVariant tmp;
		CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
        SetPassword5(tmp.strVal);
		return ERROR_CODES_OK;
    }			
	return ERROR_CODES_INVALID_PARAMETER;
}