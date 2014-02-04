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


class CGXDLMSExtendedRegister : public CGXDLMSRegister
{
private:
	CGXDateTime m_CaptureTime;
    CGXDLMSVariant m_Status;

protected:
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
	CGXDLMSExtendedRegister(void) : CGXDLMSRegister(OBJECT_TYPE_EXTENDED_REGISTER, 0)
	{
	}

	//SN Constructor.
	CGXDLMSExtendedRegister(unsigned short sn) : CGXDLMSRegister(OBJECT_TYPE_EXTENDED_REGISTER, sn)
	{
	}

	//LN Constructor.
	CGXDLMSExtendedRegister(basic_string<char> ln) : CGXDLMSRegister(OBJECT_TYPE_EXTENDED_REGISTER, ln)
	{
	}

	/** 
     Status of COSEM Extended Register object.
    */
    CGXDLMSVariant GetStatus()
    {
        return m_Status;
    }
    void SetStatus(CGXDLMSVariant value)
    {
        m_Status = value;
    }
   
    /** 
     Capture time of COSEM Extended Register object.
    */
    CGXDateTime& GetCaptureTime()
    {
        return m_CaptureTime;
    }

	void SetCaptureTime(CGXDateTime value)
    {
        m_CaptureTime = value;
    }

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 5;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 1;
	}

	void GetAttributeIndexToRead(vector<int>& attributes)
	{
		CGXDLMSRegister::GetAttributeIndexToRead(attributes);
		//Status
        if (!IsRead(4))
        {
            attributes.push_back(4);
        }
        //CaptureTime
        if (CanRead(5))
        {
            attributes.push_back(5);
        }
	}
	
	int GetDataType(int index, DLMS_DATA_TYPE& type)
    {
		if (index < 4)
		{
			return CGXDLMSRegister::GetDataType(index, type);
		}
		if (index == 4)
        {
			type = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }
		if (index == 5)
        {
			type = DLMS_DATA_TYPE_OCTET_STRING;
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
		if (index < 4)
		{
			return CGXDLMSRegister::SetValue(index, value);
		}
        else if (index == 4)
        {                
            m_Status = value;
        }
        else if (index == 5)
        {
			if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
			{
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
				m_CaptureTime = tmp.dateTime;
			}
			else
			{
				m_CaptureTime = value.dateTime;
			}
        }		
		else 
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		return ERROR_CODES_OK;
    }    
};
