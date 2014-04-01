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

#include "GXDLMSMBusSlavePortSetup.h"
#include "../GXDLMSConverter.h"

//Constructor.
CGXDLMSMBusSlavePortSetup::CGXDLMSMBusSlavePortSetup() : CGXDLMSObject(OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP)
{
}

//SN Constructor.
CGXDLMSMBusSlavePortSetup::CGXDLMSMBusSlavePortSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP, sn)
{

}

//LN Constructor.
CGXDLMSMBusSlavePortSetup::CGXDLMSMBusSlavePortSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP, ln)
{

}

 /** 
 Defines the baud rate for the opening sequence.
*/
BAUDRATE CGXDLMSMBusSlavePortSetup::GetDefaultBaud()
{
    return m_DefaultBaud;
}
void CGXDLMSMBusSlavePortSetup::SetDefaultBaud(BAUDRATE value)
{
	m_DefaultBaud = value;
}    
/** 
 Defines the baud rate for the opening sequence.
*/
BAUDRATE CGXDLMSMBusSlavePortSetup::GetAvailableBaud()
{
    return m_AvailableBaud;
}
void CGXDLMSMBusSlavePortSetup::SetAvailableBaud(BAUDRATE value)
{
	m_AvailableBaud = value;
}
    
/** 
 Defines whether or not the device has been assigned an address
 * since last power up of the device.
*/
ADDRESS_STATE CGXDLMSMBusSlavePortSetup::GetAddressState()
{
    return m_AddressState;
}
void CGXDLMSMBusSlavePortSetup::SetAddressState(ADDRESS_STATE value)
{
    m_AddressState = value;
}


/** 
 Defines the baud rate for the opening sequence.
*/
int CGXDLMSMBusSlavePortSetup::GetBusAddress()
{
    return m_BusAddress;
}
void CGXDLMSMBusSlavePortSetup::SetBusAddress(int value)
{
	m_BusAddress = value;
}

// Returns amount of attributes.
int CGXDLMSMBusSlavePortSetup::GetAttributeCount()
{
	return 5;
}

// Returns amount of methods.
int CGXDLMSMBusSlavePortSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSMBusSlavePortSetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);	
	values.push_back(CGXDLMSConverter::ToString(m_DefaultBaud));
	values.push_back(CGXDLMSConverter::ToString(m_AvailableBaud));
	values.push_back(CGXDLMSConverter::ToString(m_AddressState));
	values.push_back(CGXDLMSVariant(m_BusAddress).ToString());
}

void CGXDLMSMBusSlavePortSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//DefaultBaud
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //AvailableBaud
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //m_AddressState
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //BusAddress
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
}

int CGXDLMSMBusSlavePortSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
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
        type = DLMS_DATA_TYPE_UINT16;
    } 
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSMBusSlavePortSetup::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        value = m_DefaultBaud;
    }
    else if (index == 3)
    {
        value = m_AvailableBaud;
    }
    else if (index == 4)
    {
        value = m_AddressState;
    }
    else if (index == 5)
    {
        value = m_BusAddress;
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Set value of given attribute.
int CGXDLMSMBusSlavePortSetup::SetValue(int index, CGXDLMSVariant& value)
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
		m_DefaultBaud = (BAUDRATE) value.ToInteger();            
    }
    else if (index == 3)
    {
        m_AvailableBaud = (BAUDRATE) value.ToInteger();                       
    }
    else if (index == 4)
    {
		m_AddressState = (ADDRESS_STATE) value.ToInteger();            
    }
    else if (index == 5)
    {
        m_BusAddress = value.ToInteger();
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}