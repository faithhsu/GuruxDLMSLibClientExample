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
#include <math.h>
#include "IGXDLMSBase.h"
#include "GXObject.h"
#include "../GXHelpers.h"


class CGXRegisterObject : public CGXObject
{
	CGXDLMSVariant m_Value;
	unsigned char m_Scaler;
	unsigned char m_Unit;

	void Init()
	{
		m_Unit = 0;
		m_Scaler = 0;
	}

public:
	//Constructor.
	CGXRegisterObject(void) : CGXObject(OBJECT_TYPE_REGISTER)
	{
		Init();
	}

	//SN Constructor.
	CGXRegisterObject(unsigned short sn) : CGXObject(OBJECT_TYPE_REGISTER, sn)
	{
		Init();
	}

	//SN Constructor.
	CGXRegisterObject(unsigned short sn, double scaler, int unit, CGXDLMSVariant value) : CGXObject(OBJECT_TYPE_REGISTER, sn)
	{
		m_Value = value;
		Init();
	}

	//LN Constructor.
	CGXRegisterObject(basic_string<char> ln) : CGXObject(OBJECT_TYPE_REGISTER, ln)
	{
		Init();
	}

	//LN Constructor.
	CGXRegisterObject(basic_string<char> ln, double scaler, int unit, CGXDLMSVariant value) : CGXObject(OBJECT_TYPE_REGISTER, ln)
	{
		m_Value = value;
		Init();
	}

	/// <summary>
    /// Get value of COSEM Data object.
    /// </summary>        
    CGXDLMSVariant GetValue()
    {
        return m_Value;
    }

	/// <summary>
    /// Set value of COSEM Data object.
    /// </summary>        
    void SetValue(CGXDLMSVariant& value)
    {
        m_Value = value;
    }

	// Scaler of COSEM Register object.    
    double GetScaler()
    {
		return pow((float) 10, m_Scaler);
    }

    void SetScaler(double value)
    {
		m_Scaler = (unsigned char) log10(value);
    }

    // Unit of COSEM Register object.    
    int GetUnit()
    {
        return m_Unit;
    }

	void SetUnit(unsigned char value)
    {
        m_Unit = value;
    }

	/*
     * Reset value.
     */
    void Reset()
    {

    }

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 3;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 1;
	}

	int Invoke(int index, CGXDLMSVariant& value)
	{
		if (index == 1)
		{
			Reset();
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
	}

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
		if (index == 3)
		{
			value.Clear();
			value.vt = DLMS_DATA_TYPE_STRUCTURE;
			value.Arr.push_back(m_Scaler);
			value.Arr.push_back(m_Unit);
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
	}

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
        if (index == 3 && value.vt == DLMS_DATA_TYPE_STRUCTURE)
		{
			m_Scaler = value.Arr[0].bVal;
			m_Unit = value.Arr[1].bVal;
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
    }    
};
