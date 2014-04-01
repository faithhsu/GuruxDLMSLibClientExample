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

#include "GXDLMSMBusMasterPortSetup.h"
#include "../GXDLMSConverter.h"

//Constructor.
CGXDLMSMBusMasterPortSetup::CGXDLMSMBusMasterPortSetup() : CGXDLMSObject(OBJECT_TYPE_MBUS_MASTER_PORT_SETUP)
{
	m_CommSpeed = BAUDRATE_2400;
}

//SN Constructor.
CGXDLMSMBusMasterPortSetup::CGXDLMSMBusMasterPortSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_MBUS_MASTER_PORT_SETUP, sn)
{
	m_CommSpeed = BAUDRATE_2400;
}

//LN Constructor.
CGXDLMSMBusMasterPortSetup::CGXDLMSMBusMasterPortSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_MBUS_MASTER_PORT_SETUP, ln)
{
	m_CommSpeed = BAUDRATE_2400;
}

/** 
The communication speed supported by the port.
*/
BAUDRATE CGXDLMSMBusMasterPortSetup::GetCommSpeed()
{
    return m_CommSpeed;
}

void CGXDLMSMBusMasterPortSetup::SetCommSpeed(BAUDRATE value)
{
    m_CommSpeed = value;
}

// Returns amount of attributes.
int CGXDLMSMBusMasterPortSetup::GetAttributeCount()
{
	return 2;
}

// Returns amount of methods.
int CGXDLMSMBusMasterPortSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSMBusMasterPortSetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(CGXDLMSConverter::ToString(m_CommSpeed));
}

void CGXDLMSMBusMasterPortSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//CommSpeed
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSMBusMasterPortSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
	{			
		type = DLMS_DATA_TYPE_ENUM;
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSMBusMasterPortSetup::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
	{
		value = m_CommSpeed;
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMBusMasterPortSetup::SetValue(int index, CGXDLMSVariant& value)
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
		m_CommSpeed = (BAUDRATE) value.ToInteger();
	}
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}