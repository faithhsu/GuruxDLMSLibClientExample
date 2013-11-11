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

#pragma once

#include "IGXDLMSBase.h"
#include "GXObject.h"
#include "../GXHelpers.h"

class CGXDataObject : public CGXObject
{
	CGXDLMSVariant m_Value;
public:	
	//Constructor.
	CGXDataObject() : CGXObject(OBJECT_TYPE_DATA)
	{
	}

	//SN Constructor.
	CGXDataObject(unsigned short sn) : CGXObject(OBJECT_TYPE_DATA, sn)
	{

	}

	//SN Constructor.
	CGXDataObject(unsigned short sn, CGXDLMSVariant value) : CGXObject(OBJECT_TYPE_DATA, sn)
	{
		m_Value = value;
	}

	//LN Constructor.
	CGXDataObject(basic_string<char> ln) : CGXObject(OBJECT_TYPE_DATA, ln)
	{

	}

	//LN Constructor.
	CGXDataObject(basic_string<char> ln, CGXDLMSVariant value) : CGXObject(OBJECT_TYPE_DATA, ln)
	{
		m_Value = value;
	}

	// Get value of COSEM Data object.
    CGXDLMSVariant GetValue()
    {
        return m_Value;
    }
	
    // Set value of COSEM Data object.
    void SetValue(CGXDLMSVariant& value)
    {
        m_Value = value;
    }

    // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 2;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
    {
		if (index == 1)
		{
			GXHelpers::AddRange(value.byteArr, m_LN, 6);
			type = value.vt = DLMS_DATA_TYPE_OCTET_STRING;
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
	int SetValue(int index, CGXDLMSVariant& value)
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
        if (index == 2)
		{
			SetValue(value);
			return ERROR_CODES_OK;			
		}				
		return ERROR_CODES_INVALID_PARAMETER;
    }
};
