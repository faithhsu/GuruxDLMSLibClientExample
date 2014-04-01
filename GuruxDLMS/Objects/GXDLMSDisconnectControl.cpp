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
#include "GXDLMSDisconnectControl.h"
#include "../GXDLMSConverter.h"

//Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl() : CGXDLMSObject(OBJECT_TYPE_DISCONNECT_CONTROL)
{
}

//SN Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_DISCONNECT_CONTROL, sn)
{

}

//LN Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_DISCONNECT_CONTROL, ln)
{

}

/** 
 Output state of COSEM Disconnect Control object.
*/
bool CGXDLMSDisconnectControl::GetOutputState()
{
    return m_OutputState;
}
void CGXDLMSDisconnectControl::SetOutputState(bool value)
{
    m_OutputState = value;
}

/** 
 Control state of COSEM Disconnect Control object.
*/
CONTROLSTATE CGXDLMSDisconnectControl::GetControlState()
{
    return m_ControlState;
}
void CGXDLMSDisconnectControl::SetControlState(CONTROLSTATE value)
{
    m_ControlState = value;
}

 /** 
 Control mode of COSEM Disconnect Control object.
*/
CONTROLMODE CGXDLMSDisconnectControl::GetControlMode()
{
    return m_ControlMode;
}
void CGXDLMSDisconnectControl::SetControlMode(CONTROLMODE value)
{
    m_ControlMode = value;
}

// Returns amount of attributes.
int CGXDLMSDisconnectControl::GetAttributeCount()
{
	return 4;
}

// Returns amount of methods.
int CGXDLMSDisconnectControl::GetMethodCount()
{
	return 2;
}

void CGXDLMSDisconnectControl::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(CGXDLMSVariant(m_OutputState).ToString());
	values.push_back(CGXDLMSConverter::ToString(m_ControlState));
	values.push_back(CGXDLMSConverter::ToString(m_ControlMode));
}

void CGXDLMSDisconnectControl::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//OutputState
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //ControlState
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //ControlMode
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
}

int CGXDLMSDisconnectControl::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
    }    
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }    
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }  
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSDisconnectControl::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {
        value = m_OutputState;
		return ERROR_CODES_OK;
    }    
    if (index == 3)
    {
        value = m_ControlState;
		return ERROR_CODES_OK;
    }    
    if (index == 4)
    {
        value = m_ControlMode;
		return ERROR_CODES_OK;
    }    
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSDisconnectControl::SetValue(int index, CGXDLMSVariant& value)
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
		m_OutputState = value.boolVal;
    }
    else if (index == 3)
    {
        m_ControlState = (CONTROLSTATE) value.ToInteger();            
    }
    else if (index == 4)
    {
        m_ControlMode = (CONTROLMODE) value.ToInteger();            
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}