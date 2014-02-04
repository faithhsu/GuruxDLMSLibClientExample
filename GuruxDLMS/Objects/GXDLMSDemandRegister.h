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

#include <cmath>
#include "IGXDLMSBase.h"
#include "GXDLMSObject.h"
#include "../GXHelpers.h"

class CGXDLMSDemandRegister : public CGXDLMSObject
{
	CGXDLMSVariant m_CurrentAvarageValue;    
    CGXDLMSVariant m_LastAvarageValue;    
    unsigned char m_Scaler;
	unsigned char m_Unit;
    CGXDLMSVariant m_Status;
    CGXDateTime m_CaptureTime;
    CGXDateTime m_StartTimeCurrent;
    int m_NumberOfPeriods;
    unsigned long m_Period;

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
    /**  
     Constructor.
    */
	CGXDLMSDemandRegister() : CGXDLMSObject(OBJECT_TYPE_DEMAND_REGISTER)
    {
		m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSDemandRegister(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_DEMAND_REGISTER, ln)
    {
		m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSDemandRegister(int sn) : CGXDLMSObject(OBJECT_TYPE_DEMAND_REGISTER, sn)
    {
		m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
    }
    
    /** 
     Current avarage value of COSEM Data object.
    */
    CGXDLMSVariant GetCurrentAvarageValue()
    {
        return m_CurrentAvarageValue;
    }
    void SetCurrentAvarageValue(CGXDLMSVariant value)
    {
        m_CurrentAvarageValue = value;
    }

    /** 
     Last avarage value of COSEM Data object.
    */
    CGXDLMSVariant GetLastAvarageValue()
    {
        return m_LastAvarageValue;
    }
    void SetLastAvarageValue(CGXDLMSVariant value)
    {
        m_LastAvarageValue = value;
    }

    /** 
     Scaler of COSEM Register object.
    */
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

    /** 
     Scaler of COSEM Register object.
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
     Capture time of COSEM Register object.
    */
    CGXDateTime GetCaptureTime()
    {
        return m_CaptureTime;
    }
    void SetCaptureTime(CGXDateTime value)
    {
        m_CaptureTime = value;
    }

    /** 
     Current start time of COSEM Register object.
    */
    CGXDateTime GetStartTimeCurrent()
    {
        return m_StartTimeCurrent;
    }
    void SetStartTimeCurrent(CGXDateTime value)
    {
        m_StartTimeCurrent = value;
    }

    unsigned long GetPeriod()
    {
        return m_Period;
    }

    void SetPeriod(unsigned long value)
    {
        m_Period = value;
    }
    
    int GetNumberOfPeriods()
    {
        return m_NumberOfPeriods;
    }

    void SetNumberOfPeriods(int value)
    {
        m_NumberOfPeriods = value;
    }

    /*
     * Reset value.
     */
    void Reset()
    {

    }
    
    /*
     * Next period.
     */
    void NextPeriod()
    {

    }    
    
	void GetAttributeIndexToRead(vector<int>& attributes)
	{
		//LN is static and read only once.
		if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
        {
            attributes.push_back(1);
        }
		//ScalerUnit
        if (!IsRead(4))
        {
            attributes.push_back(4);
        }
        //CurrentAvarageValue
        if (CanRead(2))
        {
            attributes.push_back(2);
        }
        //LastAvarageValue            
        if (CanRead(3))
        {
            attributes.push_back(3);
        }        
        //Status
        if (CanRead(5))
        {
            attributes.push_back(5);
        }
        //CaptureTime
        if (CanRead(6))
        {
            attributes.push_back(6);
        }
        //StartTimeCurrent
        if (CanRead(7))
        {
            attributes.push_back(7);
        }
        //Period
        if (CanRead(8))
        {
            attributes.push_back(8);
        }
        //NumberOfPeriods
        if (CanRead(9))
        {
            attributes.push_back(9);
        }
	}
    
	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 5;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 2;
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

	int GetDataType(int index, DLMS_DATA_TYPE& type)
    {
		if (index == 1)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }
        if (index == 2)
        {
            type = DLMS_DATA_TYPE_NONE;
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_NONE;
			return ERROR_CODES_OK;
        }      
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_STRUCTURE;
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_NONE;
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
            type = DLMS_DATA_TYPE_DATETIME;
            return ERROR_CODES_OK;
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_DATETIME;
            return ERROR_CODES_OK;
        }
        if (index == 8)
        {
            type = DLMS_DATA_TYPE_UINT32;
            return ERROR_CODES_OK;
        } 
        if (index == 9)
        {
            type = DLMS_DATA_TYPE_UINT16;
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
            value = GetCurrentAvarageValue();
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            value = GetLastAvarageValue();
			return ERROR_CODES_OK;
        }      
        if (index == 4)
        {
            value.Clear();
			value.vt = DLMS_DATA_TYPE_STRUCTURE;
			value.Arr.push_back(m_Scaler);
			value.Arr.push_back(m_Unit);
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            value = GetStatus();
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
            value = GetCaptureTime();
			return ERROR_CODES_OK;
        }
        if (index == 7)
        {
            value = GetStartTimeCurrent();
			return ERROR_CODES_OK;
        }
        if (index == 8)
        {
            value = GetPeriod();
			return ERROR_CODES_OK;
        } 
        if (index == 9)
        {
            value = GetNumberOfPeriods();
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
        else if (index == 2)
        {
            SetCurrentAvarageValue(value.lVal);
        }
        else if (index == 3)
        {
            SetLastAvarageValue(value);
        }
        else if (index == 4)
        {
			m_Scaler = value.Arr[0].bVal;
			m_Unit = value.Arr[1].bVal;
        }
        else if (index == 5)
        {
			SetStatus(value.lVal);    
        }
        else if (index == 6)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);            
			SetCaptureTime(tmp.dateTime);
        }
        else if (index == 7)
        {
            CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
            SetStartTimeCurrent(tmp.dateTime);
        }
        else if (index == 8)
        {
			SetPeriod(value.ulVal);
        }   
        else if (index == 9)
        {
            SetNumberOfPeriods(value.lVal);			
        }   
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		return ERROR_CODES_OK;
    }
};