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
#include "GXDLMSRegisterActivation.h"

//Constructor.
CGXDLMSRegisterActivation::CGXDLMSRegisterActivation() : CGXDLMSObject(OBJECT_TYPE_DATA)
{
}

//SN Constructor.
CGXDLMSRegisterActivation::CGXDLMSRegisterActivation(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_DATA, sn)
{

}

//LN Constructor.
CGXDLMSRegisterActivation::CGXDLMSRegisterActivation(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_DATA, ln)
{

}

// Get value of COSEM Data object.
CGXDLMSVariant CGXDLMSRegisterActivation::GetValue()
{
    return m_Value;
}

// Set value of COSEM Data object.
void CGXDLMSRegisterActivation::SetValue(CGXDLMSVariant& value)
{
    m_Value = value;
}

// Returns amount of attributes.
int CGXDLMSRegisterActivation::GetAttributeCount()
{
	return 2;
}

// Returns amount of methods.
int CGXDLMSRegisterActivation::GetMethodCount()
{
	return 0;
}

void CGXDLMSRegisterActivation::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//Value
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSRegisterActivation::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
	{			
		return CGXDLMSObject::GetDataType(index, type);			
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSRegisterActivation::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
	{
		value = m_Value;
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSRegisterActivation::SetValue(int index, CGXDLMSVariant& value)
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
		SetValue(value);			
	}	
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}