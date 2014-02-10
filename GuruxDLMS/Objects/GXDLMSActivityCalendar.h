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


#include "GXDLMSObject.h"
#include "GXDLMSSeasonProfile.h"
#include "GXDLMSWeekProfile.h"
#include "GXDLMSDayProfile.h"

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
	CGXDLMSActivityCalendar();

	//SN Constructor.
	CGXDLMSActivityCalendar(unsigned short sn);
	
	//LN Constructor.
	CGXDLMSActivityCalendar(basic_string<char> ln);

	basic_string<char> GetCalendarNameActive();
    void SetCalendarNameActive(basic_string<char> value);
    
    vector<CGXDLMSSeasonProfile> GetSeasonProfileActive();
    void SetSeasonProfileActive(vector<CGXDLMSSeasonProfile> value);

    vector<CGXDLMSWeekProfile> GetWeekProfileTableActive();
    void SetWeekProfileTableActive(vector<CGXDLMSWeekProfile> value);

    vector<CGXDLMSDayProfile> GetDayProfileTableActive();
    void SetDayProfileTableActive(vector<CGXDLMSDayProfile> value);

    basic_string<char> GetCalendarNamePassive();
    void SetCalendarNamePassive(basic_string<char> value);

    vector<CGXDLMSSeasonProfile> GetSeasonProfilePassive();
    void SetSeasonProfilePassive(vector<CGXDLMSSeasonProfile> value);

    vector<CGXDLMSWeekProfile> GetWeekProfileTablePassive();
    void SetWeekProfileTablePassive(vector<CGXDLMSWeekProfile> value);

    vector<CGXDLMSDayProfile> GetDayProfileTablePassive();
    void SetDayProfileTablePassive(vector<CGXDLMSDayProfile> value);

    CGXDateTime& GetTime();
    void SetTime(CGXDateTime& value);

    // Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	void GetAttributeIndexToRead(vector<int>& attributes);

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
