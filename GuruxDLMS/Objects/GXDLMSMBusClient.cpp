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

#include "GXDLMSMBusClient.h"
#include "../GXDLMSClient.h"
#include <sstream> 

//Constructor.
CGXDLMSMBusClient::CGXDLMSMBusClient() : CGXDLMSObject(OBJECT_TYPE_MBUS_CLIENT)
{
}

//SN Constructor.
CGXDLMSMBusClient::CGXDLMSMBusClient(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_MBUS_CLIENT, sn)
{

}

//LN Constructor.
CGXDLMSMBusClient::CGXDLMSMBusClient(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_MBUS_CLIENT, ln)
{

}

/** 
Provides reference to an "M-Bus master port setup" object, used to configure
an M-Bus port, each interface allowing to exchange data with one or more
M-Bus slave devices
*/
string CGXDLMSMBusClient::GetMBusPortReference()
{
    return m_MBusPortReference;
}
void CGXDLMSMBusClient::SetMBusPortReference(string value)
{
    m_MBusPortReference = value;
}

vector<pair<string, string> >& CGXDLMSMBusClient::GetCaptureDefinition()
{
    return m_CaptureDefinition;
}

long CGXDLMSMBusClient::GetCapturePeriod()
{
    return m_CapturePeriod;
}
void CGXDLMSMBusClient::SetCapturePeriod(long value)
{
    m_CapturePeriod = value;
}

int CGXDLMSMBusClient::GetPrimaryAddress()
{
    return m_PrimaryAddress;
}
void CGXDLMSMBusClient::SetPrimaryAddress(int value)
{
    m_PrimaryAddress = value;
}

long CGXDLMSMBusClient::GetIdentificationNumber()
{
    return m_IdentificationNumber;
}
void CGXDLMSMBusClient::SetIdentificationNumber(long value)
{
    m_IdentificationNumber = value;
}

int CGXDLMSMBusClient::GetManufacturerID()
{
    return m_ManufacturerID;
}
void CGXDLMSMBusClient::SetManufacturerID(int value)
{
    m_ManufacturerID = value;
}

/*
 * Carries the Version element of the data header as specified in EN
 * 13757-3 sub-clause 5.6.
 */
int CGXDLMSMBusClient::GetDataHeaderVersion()
{
    return m_DataHeaderVersion;
}
void CGXDLMSMBusClient::SetDataHeaderVersion(int value)
{
    m_DataHeaderVersion = value;
}

int CGXDLMSMBusClient::GetDeviceType()
{
    return m_DeviceType;
}
void CGXDLMSMBusClient::SetDeviceType(int value)
{
    m_DeviceType = value;
}

int CGXDLMSMBusClient::GetAccessNumber()
{
    return m_AccessNumber;
}
void CGXDLMSMBusClient::SetAccessNumber(int value)
{
    m_AccessNumber = value;
}

int CGXDLMSMBusClient::GetStatus()
{
    return m_Status;
}
void CGXDLMSMBusClient::SetStatus(int value)
{
    m_Status = value;
}

int CGXDLMSMBusClient::GetAlarm()
{
    return m_Alarm;
}
void CGXDLMSMBusClient::SetAlarm(int value)
{
    m_Alarm = value;
}


// Returns amount of attributes.
int CGXDLMSMBusClient::GetAttributeCount()
{
	return 12;
}

// Returns amount of methods.
int CGXDLMSMBusClient::GetMethodCount()
{
	return 8;
}

void CGXDLMSMBusClient::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(m_MBusPortReference);	
	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<pair<string, string> >::iterator it = m_CaptureDefinition.begin(); it != m_CaptureDefinition.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;
		sb.write(it->first.c_str(), it->first.size());
		sb << " ";
		sb.write(it->second.c_str(), it->second.size());	
	}
	sb << ']';
	values.push_back(sb.str());		

	values.push_back(CGXDLMSVariant(m_CapturePeriod).ToString());
	values.push_back(CGXDLMSVariant(m_PrimaryAddress).ToString());
	values.push_back(CGXDLMSVariant(m_IdentificationNumber).ToString());
	values.push_back(CGXDLMSVariant(m_ManufacturerID).ToString());
	values.push_back(CGXDLMSVariant(m_DataHeaderVersion).ToString());
	values.push_back(CGXDLMSVariant(m_DeviceType).ToString());
	values.push_back(CGXDLMSVariant(m_AccessNumber).ToString());
	values.push_back(CGXDLMSVariant(m_Status).ToString());
	values.push_back(CGXDLMSVariant(m_Alarm).ToString());
}

void CGXDLMSMBusClient::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//MBusPortReference
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //CaptureDefinition
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //CapturePeriod
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //PrimaryAddress
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //IdentificationNumber
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
    //ManufacturerID
    if (CanRead(7))
    {
        attributes.push_back(7);
    }
    //Version
    if (CanRead(8))
    {
        attributes.push_back(8);
    }
    //DeviceType
    if (CanRead(9))
    {
        attributes.push_back(9);
    }
    //AccessNumber
    if (CanRead(10))
    {
        attributes.push_back(10);
    }
    //Status
    if (CanRead(11))
    {
        attributes.push_back(11);
    }
    //Alarm
    if (CanRead(12))
    {
        attributes.push_back(12);
    }
}

int CGXDLMSMBusClient::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
	}
	else if (index == 2)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 10)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 11)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 12)
    {
        type = DLMS_DATA_TYPE_UINT8;
    } 
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSMBusClient::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        value = m_MBusPortReference;
    }
    else if (index == 3)
    {
        //value = m_CaptureDefinition;//TODO;
    }
    else if (index == 4)
    {
        value = m_CapturePeriod;
    }
    else if (index == 5)
    {
        value = m_PrimaryAddress;
    }
    else if (index == 6)
    {
        value = m_IdentificationNumber;
    }
    else if (index == 7)
    {
        value = m_ManufacturerID;
    }
    else if (index == 8)
    {
        value = m_DataHeaderVersion;
    }
    else if (index == 9)
    {
        value = m_DeviceType;
    }
    else if (index == 10)
    {
        value = m_AccessNumber;
    }
    else if (index == 11)
    {
        value = m_Status;
    }
    else if (index == 12)
    {
        value = m_Alarm;
    }  
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Set value of given attribute.
int CGXDLMSMBusClient::SetValue(int index, CGXDLMSVariant& value)
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
		CGXDLMSVariant tmp;
		CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
		m_MBusPortReference = tmp.ToString();
    }
    else if (index == 3)
    {
        m_CaptureDefinition.clear();            
		CGXDLMSVariant tmp1, tmp2;
		for(vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
        {
			CGXDLMSClient::ChangeType((*it).Arr[0].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp1);
			CGXDLMSClient::ChangeType((*it).Arr[1].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp2);
			m_CaptureDefinition.push_back(std::pair<string, string>(tmp1.ToString(), tmp2.ToString()));                    
        }            
    }
    else if (index == 4)
    {
        m_CapturePeriod = value.ToInteger();
    }
    else if (index == 5)
    {
        m_PrimaryAddress = value.ToInteger();
    }
    else if (index == 6)
    {
        m_IdentificationNumber = value.ToInteger();
    }
    else if (index == 7)
    {
        m_ManufacturerID = value.ToInteger();
    }
    else if (index == 8)
    {
        m_DataHeaderVersion = value.ToInteger();
    }
    else if (index == 9)
    {
        m_DeviceType = value.ToInteger();
    }
    else if (index == 10)
    {
        m_AccessNumber = value.ToInteger();
    }
    else if (index == 11)
    {
        m_Status = value.ToInteger();
    }
    else if (index == 12)
    {
		m_Alarm = value.ToInteger();
    }	
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}
