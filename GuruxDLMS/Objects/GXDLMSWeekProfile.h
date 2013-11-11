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

class CGXDLMSWeekProfile
{
    basic_string<char> m_Name;
    int m_Monday;
    int m_Tuesday;
    int m_Wednesday;
    int m_Thursday;
    int m_Friday;
    int m_Saturday;
    int m_Sunday;    
public:
    /** 
     Constructor.
    */
    CGXDLMSWeekProfile()
    {
		m_Monday = m_Tuesday = m_Wednesday = m_Thursday = m_Friday = m_Saturday = m_Sunday = 0;
    }

    /** 
     Constructor.
    */
    CGXDLMSWeekProfile(basic_string<char> name, int monday, int tuesday, int wednesday, int thursday, int friday, int saturday, int sunday)
    {
        SetName(name);
        SetMonday(monday);
        SetTuesday(tuesday);
        SetWednesday(wednesday);
        SetThursday(thursday);
        SetFriday(friday);
        SetSaturday(saturday);
        SetSunday(sunday);
    }

    basic_string<char> GetName()
    {
        return m_Name;
    }
    void SetName(basic_string<char> value)
    {
        m_Name = value;
    }
    int GetMonday()
    {
        return m_Monday;
    }
    void SetMonday(int value)
    {
        m_Monday = value;
    }

    int GetTuesday()
    {
        return m_Tuesday;
    }
    void SetTuesday(int value)
    {
        m_Tuesday = value;
    }

    int GetWednesday()
    {
        return m_Wednesday;
    }
    void SetWednesday(int value)
    {
        m_Wednesday = value;
    }

    int GetThursday()
    {
        return m_Thursday;
    }
    void SetThursday(int value)
    {
        m_Thursday = value;
    }

    int GetFriday()
    {
        return m_Friday;
    }
    void SetFriday(int value)
    {
        m_Friday = value;
    }

    int GetSaturday()
    {
        return m_Saturday;
    }
    void SetSaturday(int value)
    {
        m_Saturday = value;
    }

    int GetSunday()
    {
        return m_Sunday;
    }
    void SetSunday(int value)
    {
        m_Sunday = value;
    }
};