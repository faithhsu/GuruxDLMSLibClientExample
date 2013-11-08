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
#include "../GXDateTime.h"

enum GXDLMS_CLOCK_STATUS
{
	GXDLMS_CLOCK_STATUS_OK = 0x0,
	GXDLMS_CLOCK_STATUS_INVALID_VALUE = 0x1,
	GXDLMS_CLOCK_STATUS_DOUBTFUL_VALUE = 0x2,
	GXDLMS_CLOCK_STATUS_DIFFERENT_CLOCK_BASE = 0x4,
    GXDLMS_CLOCK_STATUS_RESERVED1 = 0x8,
	GXDLMS_CLOCK_STATUS_RESERVED2 = 0x10,
    GXDLMS_CLOCK_STATUS_RESERVED3 = 0x20,
    GXDLMS_CLOCK_STATUS_RESERVED4 = 0x40,
    GXDLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE = 0x80,
};

class CGXClockObject : public CGXObject
{
    char m_ClockBase;
    char m_Deviation;
    bool m_Enabled;
    CGXDateTime m_End;
    GXDLMS_CLOCK_STATUS m_Status;
    CGXDateTime m_Begin;
    unsigned short m_TimeZone;
    CGXDateTime m_Time;

	void Init()
	{
	    m_Deviation = m_ClockBase = 0;		
		m_Enabled = false;		
		m_TimeZone = 0;
		m_Status = GXDLMS_CLOCK_STATUS_OK;
	}
public:
    /**  
     Constructor.
    */
	CGXClockObject() : CGXObject(OBJECT_TYPE_CLOCK, "0.0.1.0.0.255")
    {
		Init();
    }

    /**  
     Constructor.
     @param ln Logican Name of the object.
    */
    CGXClockObject(basic_string<char> ln) : CGXObject(OBJECT_TYPE_CLOCK, ln)
    {
		Init();
    }

    /**  
     Constructor.
     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXClockObject(basic_string<char> ln, int sn) : CGXObject(OBJECT_TYPE_CLOCK, ln)
    {
		Init();
		SetShortName(sn);
    }
	
	/// <summary>
    /// Data type that user want's to see.
    /// </summary>
	DLMS_DATA_TYPE GetUIDataType(int index)
    {
		if (index == 2 || index == 5 || index == 6)
		{
			return DLMS_DATA_TYPE_DATETIME;
		}
		return CGXObject::GetUIDataType(index);            
    }
	
    /** 
     Time of COSEM Clock object.
    */	
    CGXDateTime GetTime()
    {
        return m_Time;
    }
    void SetTime(CGXDateTime& value)
    {
        m_Time = value;
    }

    /** 
     TimeZone of COSEM Clock object.
    */
    unsigned short GetTimeZone()
    {
        return m_TimeZone;
    }
    void SetTimeZone(unsigned short value)
    {
        m_TimeZone = value;
    }

    /** 
     Status of COSEM Clock object.
    */
    GXDLMS_CLOCK_STATUS GetStatus()
    {
        return m_Status;
    }
    void SetStatus(GXDLMS_CLOCK_STATUS value)
    {
        m_Status = value;
    }

    CGXDateTime GetBegin()
    {
        return m_Begin;
    }

    void SetBegin(CGXDateTime& value)
    {
        m_Begin = value;
    }

    CGXDateTime GetEnd()
    {
        return m_End;
    }
    void SetEnd(CGXDateTime& value)
    {
        m_End = value;
    }

    char GetDeviation()
    {
        return m_Deviation;
    }
    void SetDeviation(char value)
    {
        m_Deviation = value;
    }

    bool GetEnabled()
    {
        return m_Enabled;
    }
    void SetEnabled(bool value)
    {
        m_Enabled = value;
    }

    /** 
     Clock base of COSEM Clock object.
    */
    char GetClockBase()
    {
        return m_ClockBase;
    }
    void SetClockBase(char value)
    {
        m_ClockBase = value;
    }
    
	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 9;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}

    /*
     * Returns value of given attribute.
     */    
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
			value = GetTime();
			type = DLMS_DATA_TYPE_DATETIME;
			return 0;
        }
        if (index == 3)
        {            
			type = DLMS_DATA_TYPE_INT16;
            value = GetTimeZone();
			return 0;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_UINT8;
            value = (unsigned char) GetStatus();
			return 0;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_DATETIME;
			value = GetBegin();
			return 0;
        }
        if (index == 6)
        {
            type = DLMS_DATA_TYPE_DATETIME;
			value = GetEnd();
			return 0;
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_INT8;
            value = GetDeviation();
			return 0;
        }
        if (index == 8)
        {
            type = DLMS_DATA_TYPE_BOOLEAN;
            value = GetEnabled();
			return 0;
        }
        if (index == 9)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = GetClockBase();
			return 0;
        }
        return -1;
    }
    
    /*
     * Set value of given attribute.
     */
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
        /*
        else if (index == 2)
        {
            SetTime(value);
        }
        else if (index == 3)
        {
            SetTimeZone(value);
        }
        else if (index == 4)
        {
            SetStatus(value);
        }
        else if (index == 5)
        {
            SetBegin(value);
        }
        else if (index == 6)
        {
            SetEnd(value);
        }
        else if (index == 7)
        {
            SetDeviation(value);
        }
        else if (index == 8)
        {
            SetEnabled(value);
        }
        else if (index == 9)
        {
            SetClockBase(value);
        }
        * */
        else
        {
            return -1;
        }
    }
};
