//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL:  $
//
// Version:         $Revision:  $,
//                  $Date:  $
//                  $Author: $
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
#pragma once

#include "IGXDLMSBase.h"
#include "GXObject.h"
#include "../GXHelpers.h"

class CGXDLMSDemandRegister : public CGXObject
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

public:
    /**  
     Constructor.
    */
	CGXDLMSDemandRegister() : CGXObject(OBJECT_TYPE_DEMAND_REGISTER)
    {
		m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSDemandRegister(basic_string<char> ln) : CGXObject(OBJECT_TYPE_DEMAND_REGISTER, ln)
    {
		m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSDemandRegister(int sn) : CGXObject(OBJECT_TYPE_DEMAND_REGISTER, sn)
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
            type = DLMS_DATA_TYPE_DATETIME;
            value = GetCaptureTime();
			return ERROR_CODES_OK;
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_DATETIME;
            value = GetStartTimeCurrent();
			return ERROR_CODES_OK;
        }
        if (index == 8)
        {
            type = DLMS_DATA_TYPE_UINT32;
            value = GetPeriod();
			return ERROR_CODES_OK;
        } 
        if (index == 9)
        {
            type = DLMS_DATA_TYPE_UINT16;
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
        if (index == 2)
        {
            SetCurrentAvarageValue(value.lVal);
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            SetLastAvarageValue(value);
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
			m_Scaler = value.Arr[0].bVal;
			m_Unit = value.Arr[1].bVal;
        }
        if (index == 5)
        {
			SetStatus(value.lVal);    
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);            
			SetCaptureTime(tmp.dateTime);
			return ERROR_CODES_OK;
        }
        if (index == 7)
        {
            CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
            SetStartTimeCurrent(tmp.dateTime);
			return ERROR_CODES_OK;
        }
        if (index == 8)
        {
			SetPeriod(value.ulVal);
			return ERROR_CODES_OK;
        }   
        if (index == 9)
        {
            SetNumberOfPeriods(value.lVal);
			return ERROR_CODES_OK;
        }   
        return ERROR_CODES_INVALID_PARAMETER;
    }
};