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
#include "GXDLMSActionSchedule.h"

    
void CGXDLMSActionSchedule::Init()
{
	m_ExecutedScriptSelector = 0;
	m_Type = SINGLE_ACTION_SCHEDULE_TYPE1;
}

/**  
 Constructor.
*/
CGXDLMSActionSchedule::CGXDLMSActionSchedule() : CGXDLMSObject(OBJECT_TYPE_ACTION_SCHEDULE)
{     
	Init();
}

/**  
 Constructor.

 @param ln Logican Name of the object.
*/
CGXDLMSActionSchedule::CGXDLMSActionSchedule(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_ACTION_SCHEDULE, ln)
{
	Init();
}

/**  
 Constructor.

 @param ln Logican Name of the object.
 @param sn Short Name of the object.
*/
CGXDLMSActionSchedule::CGXDLMSActionSchedule(int sn) : CGXDLMSObject(OBJECT_TYPE_ACTION_SCHEDULE, sn)
{        
	Init();
}
    
basic_string<char> CGXDLMSActionSchedule::GetExecutedScriptLogicalName()
{
    return m_ExecutedScriptLogicalName;
}
void CGXDLMSActionSchedule::SetExecutedScriptLogicalName(basic_string<char> value)
{
    m_ExecutedScriptLogicalName = value;
}

int CGXDLMSActionSchedule::GetExecutedScriptSelector()
{
    return m_ExecutedScriptSelector;
}
void CGXDLMSActionSchedule::SetExecutedScriptSelector(int value)
{
    m_ExecutedScriptSelector = value;
}

SINGLE_ACTION_SCHEDULE_TYPE CGXDLMSActionSchedule::GetType()
{
    return m_Type;
}
void CGXDLMSActionSchedule::SetType(SINGLE_ACTION_SCHEDULE_TYPE value)
{
    m_Type = value;
}

vector<CGXDateTime> CGXDLMSActionSchedule::GetExecutionTime()
{
    return m_ExecutionTime;
}
void CGXDLMSActionSchedule::SetExecutionTime(vector<CGXDateTime> value)
{
    m_ExecutionTime = value;
}

// Returns amount of attributes.
int CGXDLMSActionSchedule::GetAttributeCount()
{
	return 4;
}

// Returns amount of methods.
int CGXDLMSActionSchedule::GetMethodCount()
{
	return 0;
}

void CGXDLMSActionSchedule::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//ExecutedScriptLogicalName is static and read only once.
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //Type is static and read only once.
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //ExecutionTime is static and read only once.
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
}

int CGXDLMSActionSchedule::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ENUM;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }  
    return ERROR_CODES_INVALID_PARAMETER;

}

// Returns value of given attribute.
int CGXDLMSActionSchedule::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
    if (index == 1)
    {
        GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {
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
        value = GetType();
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
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
int CGXDLMSActionSchedule::SetValue(int index, CGXDLMSVariant& value)
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
        //CGXDLMSVariant tmp;
		//CGXDLMSClient::ChangeType(value.Arr[0].byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
		SetExecutedScriptLogicalName(value.Arr[0].ToString());
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