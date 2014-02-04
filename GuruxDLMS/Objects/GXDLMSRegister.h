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
#include "GXDLMSObject.h"
#include "../GXHelpers.h"


class CGXDLMSRegister : public CGXDLMSObject
{
	void Init()
	{
		m_Unit = 0;
		m_Scaler = 0;
	}

protected:
	CGXDLMSVariant m_Value;
	unsigned char m_Scaler;
	unsigned char m_Unit;

	//SN Constructor.
	CGXDLMSRegister(OBJECT_TYPE type, unsigned short sn) : CGXDLMSObject(type, sn)
	{
		Init();
	}

	//LN Constructor.
	CGXDLMSRegister(OBJECT_TYPE type, basic_string<char> ln) : CGXDLMSObject(type, ln)
	{
		Init();
	}

	bool IsRead(int index)
    {
        if (index == 3)
        {
            return m_Unit != 0;
        }
		return CGXDLMSObject::IsRead(index);
    }

public:
	//Constructor.
	CGXDLMSRegister(void) : CGXDLMSObject(OBJECT_TYPE_REGISTER)
	{
		Init();
	}

	//SN Constructor.
	CGXDLMSRegister(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_REGISTER, sn)
	{
		Init();
	}

	//SN Constructor.
	CGXDLMSRegister(unsigned short sn, double scaler, int unit, CGXDLMSVariant value) : CGXDLMSObject(OBJECT_TYPE_REGISTER, sn)
	{
		m_Value = value;
		Init();
	}

	//LN Constructor.
	CGXDLMSRegister(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_REGISTER, ln)
	{
		Init();
	}

	//LN Constructor.
	CGXDLMSRegister(basic_string<char> ln, double scaler, int unit, CGXDLMSVariant value) : CGXDLMSObject(OBJECT_TYPE_REGISTER, ln)
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

	void GetAttributeIndexToRead(vector<int>& attributes)
	{
		//LN is static and read only once.
		if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
        {
            attributes.push_back(1);
        }
		//ScalerUnit
        if (!IsRead(3))
        {
            attributes.push_back(3);
        }
        //Value
        if (CanRead(2))
        {
            attributes.push_back(2);
        }
	}	

	int GetDataType(int index, DLMS_DATA_TYPE& type)
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
		if (index == 3)
		{
			type = DLMS_DATA_TYPE_STRUCTURE;
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
	}

	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
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
		}
        else if (index == 2)
		{
			SetValue(value);			
		}
        else if (index == 3 && value.vt == DLMS_DATA_TYPE_STRUCTURE)
		{
			m_Scaler = value.Arr[0].bVal;
			m_Unit = value.Arr[1].bVal;			
		}
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		return ERROR_CODES_OK;
    }    
};
