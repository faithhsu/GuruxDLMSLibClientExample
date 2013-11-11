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
#include "../GXDateTime.h"

enum SINGLE_ACTION_SCHEDULE_TYPE
{
    /** 
     Size of execution_time = 1. Wildcard in date allowed.
    */
    SINGLE_ACTION_SCHEDULE_TYPE1 = 0,
    /** 
     Size of execution_time = n. 
     All time values are the same, wildcards in date not allowed.
    */
    SINGLE_ACTION_SCHEDULE_TYPE2 = 1,
    /** 
     Size of execution_time = n. 
     All time values are the same, wildcards in date are allowed,
    */
    SINGLE_ACTION_SCHEDULE_TYPE3 = 2,
    /** 
     Size of execution_time = n.
     Time values may be different, wildcards in date not allowed,
    */
    SINGLE_ACTION_SCHEDULE_TYPE4 = 3,
    /** 
     Size of execution_time = n.
     Time values may be different, wildcards in date are allowed
    */
    SINGLE_ACTION_SCHEDULE_TYPE5 = 4
};

class CGXDLMSActionSchedule : public CGXObject
{
	basic_string<char> m_ExecutedScriptLogicalName;
    int m_ExecutedScriptSelector;
    SINGLE_ACTION_SCHEDULE_TYPE m_Type;
    vector<CGXDateTime> m_ExecutionTime;
    
	void Init()
	{
		m_ExecutedScriptSelector = 0;
		m_Type = SINGLE_ACTION_SCHEDULE_TYPE1;
	}
public:

    /**  
     Constructor.
    */
	CGXDLMSActionSchedule() : CGXObject(OBJECT_TYPE_ACTION_SCHEDULE)
    {     
		Init();
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSActionSchedule(basic_string<char> ln) : CGXObject(OBJECT_TYPE_ACTION_SCHEDULE, ln)
    {
		Init();
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSActionSchedule(int sn) : CGXObject(OBJECT_TYPE_ACTION_SCHEDULE, sn)
    {        
		Init();
    }
        
    basic_string<char> GetExecutedScriptLogicalName()
    {
        return m_ExecutedScriptLogicalName;
    }
    void SetExecutedScriptLogicalName(basic_string<char> value)
    {
        m_ExecutedScriptLogicalName = value;
    }

    int GetExecutedScriptSelector()
    {
        return m_ExecutedScriptSelector;
    }
    void SetExecutedScriptSelector(int value)
    {
        m_ExecutedScriptSelector = value;
    }

    SINGLE_ACTION_SCHEDULE_TYPE GetType()
    {
        return m_Type;
    }
    void SetType(SINGLE_ACTION_SCHEDULE_TYPE value)
    {
        m_Type = value;
    }

    vector<CGXDateTime> GetExecutionTime()
    {
        return m_ExecutionTime;
    }
    void SetExecutionTime(vector<CGXDateTime> value)
    {
        m_ExecutionTime = value;
    }

   // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 4;
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
            type = DLMS_DATA_TYPE_ARRAY;
            vector<unsigned char> stream;
			stream.push_back(DLMS_DATA_TYPE_STRUCTURE);
            stream.push_back(2);
			CGXDLMSVariant tmp;
			tmp.Add(GetExecutedScriptLogicalName());
            CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_OCTET_STRING, tmp);
            CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_UINT16, GetExecutedScriptSelector());
            value = stream;
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = GetType();
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            vector<unsigned char> stream;
            stream.push_back(DLMS_DATA_TYPE_ARRAY);
            CGXOBISTemplate::SetObjectCount(GetExecutionTime().size(), stream);
			for (vector<CGXDateTime>::iterator it = m_ExecutionTime.begin(); it != m_ExecutionTime.end(); ++it)
            {
                stream.push_back(DLMS_DATA_TYPE_STRUCTURE);
                stream.push_back(2); //Count
                CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_TIME, *it); //Time
                CGXOBISTemplate::SetData(stream, DLMS_DATA_TYPE_DATE, *it); //Date
            }
            value = stream;
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
        else if (index == 2)
        {                
            CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.Arr[0].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
			SetExecutedScriptLogicalName(tmp.strVal);
			SetExecutedScriptSelector(value.Arr[1].lVal);
			return ERROR_CODES_OK;
        }
        else if (index == 3)
        {
			SetType((SINGLE_ACTION_SCHEDULE_TYPE) value.lVal);
			return ERROR_CODES_OK;
        }        
        else if (index == 4)
        {
            m_ExecutionTime.clear();
			for (vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); 
				it != value.Arr.end(); ++it)
            {
				CGXDLMSVariant time, date;
				CGXDLMSClient::ChangeType((*it).Arr[0].byteArr, DLMS_DATA_TYPE_TIME, time);
				CGXDLMSClient::ChangeType((*it).Arr[1].byteArr, DLMS_DATA_TYPE_DATE, date);
				tm tm2 = time.dateTime.GetValue();
				tm dt2 = date.dateTime.GetValue();
				m_ExecutionTime.push_back(CGXDateTime(dt2.tm_year, dt2.tm_mon, dt2.tm_mday, tm2.tm_hour, tm2.tm_min, tm2.tm_sec, 0));
            }
			return ERROR_CODES_OK;
        }                       
        return ERROR_CODES_INVALID_PARAMETER;
    }
};
