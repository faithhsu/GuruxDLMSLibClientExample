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
#include "GXDLMSObject.h"
#include "../GXHelpers.h"
#include "GXDLMSSeasonProfile.h"
#include "GXDLMSWeekProfile.h"
#include "GXDLMSDayProfile.h"
#include "../GXDateTime.h"

class CGXDLMSActivityCalendar : public CGXDLMSObject
{
	basic_string<char> m_CalendarNameActive;
    basic_string<char> m_CalendarNamePassive;
    vector<CGXDLMSSeasonProfile> m_SeasonProfileActive;
    vector<CGXDLMSWeekProfile> m_WeekProfileTableActive;
    vector<CGXDLMSDayProfile> m_DayProfileTableActive;
    vector<CGXDLMSSeasonProfile> m_SeasonProfilePassive;    
    vector<CGXDLMSDayProfile> m_DayProfileTablePassive;
    vector<CGXDLMSWeekProfile> m_WeekProfileTablePassive;
    CGXDateTime m_Time;
public:	
	//Constructor.
	CGXDLMSActivityCalendar() : CGXDLMSObject(OBJECT_TYPE_ACTIVITY_CALENDAR, "0.0.13.0.0.255")
	{
	}

	//SN Constructor.
	CGXDLMSActivityCalendar(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_ACTIVITY_CALENDAR, sn)
	{

	}
	
	//LN Constructor.
	CGXDLMSActivityCalendar(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_ACTIVITY_CALENDAR, ln)
	{

	}

	basic_string<char> GetCalendarNameActive()
    {
        return m_CalendarNameActive;
    }
    void SetCalendarNameActive(basic_string<char> value)
    {
        m_CalendarNameActive = value;
    }

    vector<CGXDLMSSeasonProfile> GetSeasonProfileActive()
    {
        return m_SeasonProfileActive;
    }
    void SetSeasonProfileActive(vector<CGXDLMSSeasonProfile> value)
    {
        m_SeasonProfileActive = value;
    }

    vector<CGXDLMSWeekProfile> GetWeekProfileTableActive()
    {
        return m_WeekProfileTableActive;
    }
    void SetWeekProfileTableActive(vector<CGXDLMSWeekProfile> value)
    {
        m_WeekProfileTableActive = value;
    }

    vector<CGXDLMSDayProfile> GetDayProfileTableActive()
    {
        return m_DayProfileTableActive;
    }
    void SetDayProfileTableActive(vector<CGXDLMSDayProfile> value)
    {
        m_DayProfileTableActive = value;
    }

    basic_string<char> GetCalendarNamePassive()
    {
        return m_CalendarNamePassive;
    }
    void SetCalendarNamePassive(basic_string<char> value)
    {
        m_CalendarNamePassive = value;
    }

    vector<CGXDLMSSeasonProfile> GetSeasonProfilePassive()
    {
        return m_SeasonProfilePassive;
	}
    void SetSeasonProfilePassive(vector<CGXDLMSSeasonProfile> value)
    {
        m_SeasonProfilePassive = value;
    }

    vector<CGXDLMSWeekProfile> GetWeekProfileTablePassive()
    {
        return m_WeekProfileTablePassive;
    }
    void SetWeekProfileTablePassive(vector<CGXDLMSWeekProfile> value)
    {
        m_WeekProfileTablePassive = value;
    }

    vector<CGXDLMSDayProfile> GetDayProfileTablePassive()
    {
        return m_DayProfileTablePassive;
    }
    void SetDayProfileTablePassive(vector<CGXDLMSDayProfile> value)
    {
        m_DayProfileTablePassive = value;
    }

    CGXDateTime& GetTime()
    {
        return m_Time;
    }
    void SetTime(CGXDateTime& value)
    {
        m_Time = value;
    }

    // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 10;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 1;
	}

	void GetAttributeIndexToRead(vector<int>& attributes)
	{
		//LN is static and read only once.
		if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
        {
            attributes.push_back(1);
        }
        //CalendarNameActive
        if (CanRead(2))
        {
            attributes.push_back(2);
        }            
        //SeasonProfileActive
        if (CanRead(3))
        {
            attributes.push_back(3);
        } 
        
        //WeekProfileTableActive
        if (CanRead(4))
        {
            attributes.push_back(4);
        } 
        //DayProfileTableActive
        if (CanRead(5))
        {
            attributes.push_back(5);
        } 
        //CalendarNamePassive
        if (CanRead(6))
        {
            attributes.push_back(6);
        } 
        //SeasonProfileActive
        if (CanRead(7))
        {
            attributes.push_back(7);
        }
        //WeekProfileTableActive
        if (CanRead(8))
        {
            attributes.push_back(8);
        }
        //DayProfileTableActive
        if (CanRead(9))
        {
            attributes.push_back(9);
        }
        //Time.
        if (CanRead(10))
        {
            attributes.push_back(10);
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
            type = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_ARRAY;            
            return ERROR_CODES_OK;
        }
        if (index == 6)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }        
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_ARRAY;            
            return ERROR_CODES_OK;

        }
        if (index == 8)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            return ERROR_CODES_OK;
        }
        if (index == 9)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            return ERROR_CODES_OK;
        }
        if (index == 10)
        {
            type = DLMS_DATA_TYPE_DATETIME;
            return ERROR_CODES_OK;
        }
		return ERROR_CODES_INVALID_PARAMETER;
	}

	// Returns value of given attribute.
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
			value.Add(&m_CalendarNameActive[0], m_CalendarNameActive.size());
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_SeasonProfileActive.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
			for (vector<CGXDLMSSeasonProfile>::iterator it = m_SeasonProfileActive.begin(); it != m_SeasonProfileActive.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(3);
				CGXDLMSVariant tmp;
				tmp.Add((*it).GetName());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).GetStart());
				tmp.Clear();
				tmp.Add((*it).GetWeekName());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
            }
			value = data;
            return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_WeekProfileTableActive.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
			for (vector<CGXDLMSWeekProfile>::iterator it = m_WeekProfileTableActive.begin(); it != m_WeekProfileTableActive.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_ARRAY);
                data.push_back(8);
				CGXDLMSVariant tmp;
				tmp.Add((*it).GetName());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetMonday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetTuesday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetWednesday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetThursday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetFriday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetSaturday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetSunday());
            }
			value = data;
            return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_DayProfileTableActive.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);            
			for (vector<CGXDLMSDayProfile>::iterator it = m_DayProfileTableActive.begin(); it != m_DayProfileTableActive.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(2);
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetDayId());
                data.push_back(DLMS_DATA_TYPE_ARRAY);
                //Add count            
				vector<CGXDLMSDayProfileAction>& schedules = (*it).GetDaySchedules();
                CGXOBISTemplate::SetObjectCount(schedules.size(), data);                        
				for (vector<CGXDLMSDayProfileAction>::iterator action = schedules.begin(); action != schedules.end(); ++action)
                {
                    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*action).GetStartTime());
                    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*action).GetScriptLogicalName());
                    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*action).GetScriptSelector());
                }
            }
			value = data;
            return ERROR_CODES_OK;
        }
        if (index == 6)
        {
			value.Add(m_CalendarNamePassive);
			return ERROR_CODES_OK;
        }
        //
        if (index == 7)
        {
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_SeasonProfileActive.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
			for (vector<CGXDLMSSeasonProfile>::iterator it = m_SeasonProfileActive.begin(); it != m_SeasonProfileActive.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(3);
				CGXDLMSVariant tmp;
				tmp.Add((*it).GetName());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).GetStart());
				tmp.Clear();
				tmp.Add((*it).GetWeekName());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
            }
            value = data;
            return ERROR_CODES_OK;

        }
        if (index == 8)
        {
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_WeekProfileTableActive.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
			for (vector<CGXDLMSWeekProfile>::iterator it = m_WeekProfileTableActive.begin(); it != m_WeekProfileTableActive.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_ARRAY);
                data.push_back(8);
				CGXDLMSVariant tmp;
				tmp.Add((*it).GetName());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp);
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetMonday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetTuesday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetWednesday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetThursday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetFriday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetSaturday());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetSunday());
            }
			value = data;
            return ERROR_CODES_OK;
        }
        if (index == 9)
        {
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_DayProfileTableActive.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
			for (vector<CGXDLMSDayProfile>::iterator it = m_DayProfileTableActive.begin(); it != m_DayProfileTableActive.end(); ++it)
			{
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(2);
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetDayId());
                data.push_back(DLMS_DATA_TYPE_ARRAY);
                //Add count            
                CGXOBISTemplate::SetObjectCount((*it).GetDaySchedules().size(), data);
				for (vector<CGXDLMSDayProfileAction>::iterator action = (*it).GetDaySchedules().begin(); 
					action != (*it).GetDaySchedules().end(); ++action)
                {
                    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*action).GetStartTime());
                    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*action).GetScriptLogicalName());
                    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*action).GetScriptSelector());
                }
            }
            value = data;
            return ERROR_CODES_OK;
        }
        if (index == 10)
        {
            value = GetTime();
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
		}
        else if (index == 2)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
			SetCalendarNameActive(tmp.strVal);
        }
        else if (index == 3)
        {
            m_SeasonProfileActive.clear();
			for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
                CGXDLMSSeasonProfile it;
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType((*item).Arr[0].byteArr, DLMS_DATA_TYPE_STRING, tmp);
				it.SetName(tmp.strVal);
				CGXDLMSClient::ChangeType((*item).Arr[1].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
				it.SetStart(tmp.dateTime);
				CGXDLMSClient::ChangeType((*item).Arr[2].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
                it.SetWeekName(tmp.strVal);
                m_SeasonProfileActive.push_back(it);
            }
        }
        else if (index == 4)
        {
            for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
				CGXDLMSVariant tmp;
                CGXDLMSWeekProfile it;				
				CGXDLMSClient::ChangeType((*item).Arr[0].byteArr, DLMS_DATA_TYPE_STRING, tmp);
				it.SetName(tmp.strVal);
				it.SetMonday((*item).Arr[1].lVal);
                it.SetTuesday((*item).Arr[1].lVal);
                it.SetWednesday((*item).Arr[1].lVal);
                it.SetThursday((*item).Arr[1].lVal);
                it.SetFriday((*item).Arr[1].lVal);
                it.SetSaturday((*item).Arr[1].lVal);
                it.SetSunday((*item).Arr[1].lVal);
                m_WeekProfileTableActive.push_back(it);
            }
        }
        else if (index == 5)
        {
            for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
                CGXDLMSDayProfile it;
                it.SetDayId((*item).Arr[0].lVal);
				for(vector<CGXDLMSVariant>::iterator it2 = (*item).Arr[1].Arr.begin(); it2 != (*item).Arr[1].Arr.end(); ++it2)
                {
                    CGXDLMSDayProfileAction ac;
					CGXDLMSVariant tmp;
					CGXDLMSClient::ChangeType((*it2).Arr[0].byteArr, DLMS_DATA_TYPE_TIME, tmp);
					ac.SetStartTime(tmp.dateTime);
					CGXDLMSClient::ChangeType((*it2).Arr[1].byteArr, DLMS_DATA_TYPE_STRING, tmp);
					ac.SetScriptLogicalName(tmp.strVal);
					ac.SetScriptSelector((*it2).Arr[2].lVal);                    
					it.GetDaySchedules().push_back(ac);
                }
				m_DayProfileTableActive.push_back(it);
            }
        }                
        else if (index == 6)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
			SetCalendarNamePassive(tmp.strVal);
        }
        else if (index == 7)
        {
            for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
                CGXDLMSSeasonProfile it;
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType((*item).Arr[0].byteArr, DLMS_DATA_TYPE_STRING, tmp);
				it.SetName(tmp.strVal);				
				CGXDLMSClient::ChangeType((*item).Arr[1].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
				it.SetStart(tmp.dateTime);
				CGXDLMSClient::ChangeType((*item).Arr[2].byteArr, DLMS_DATA_TYPE_STRING, tmp);
                it.SetWeekName(tmp.strVal);
                m_SeasonProfilePassive.push_back(it);
            }
        }
        else if (index == 8)
        {
            for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
                CGXDLMSWeekProfile it;
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType((*item).Arr[0].byteArr, DLMS_DATA_TYPE_STRING, tmp);
                it.SetName(tmp.strVal);
				it.SetMonday((*item).Arr[1].lVal);
                it.SetTuesday((*item).Arr[2].lVal);
                it.SetWednesday((*item).Arr[3].lVal);
                it.SetThursday((*item).Arr[4].lVal);
                it.SetFriday((*item).Arr[5].lVal);
                it.SetSaturday((*item).Arr[6].lVal);
                it.SetSunday((*item).Arr[7].lVal);
                m_WeekProfileTablePassive.push_back(it);
            }
        }
        else if (index == 9)
        {
            for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
                CGXDLMSDayProfile it;
				it.SetDayId((*item).Arr[0].lVal);
				for(vector<CGXDLMSVariant>::iterator it2 = (*item).Arr[1].Arr.begin(); it2 != (*item).Arr[1].Arr.end(); ++it2)
                {
                    CGXDLMSDayProfileAction ac;
					CGXDLMSVariant tmp;
					CGXDLMSClient::ChangeType((*it2).Arr[0].byteArr, DLMS_DATA_TYPE_TIME, tmp);
					ac.SetStartTime(tmp.dateTime);
					CGXDLMSClient::ChangeType((*it2).Arr[1].byteArr, DLMS_DATA_TYPE_STRING, tmp);
					ac.SetScriptLogicalName(tmp.strVal);					
					ac.SetScriptSelector((*it2).Arr[2].lVal);
					it.GetDaySchedules().push_back(ac);
                }                
                m_DayProfileTablePassive.push_back(it);
            }
        }
        else if (index == 10)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
			SetTime(tmp.dateTime);
        }			
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		return ERROR_CODES_OK;
    }
};
