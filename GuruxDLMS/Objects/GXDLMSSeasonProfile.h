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

#include "../GXDateTime.h"

class CGXDLMSSeasonProfile
{
	basic_string<char> m_Name;
    CGXDateTime m_Start;  
    basic_string<char> m_WeekName;
    
public:
    /** 
     Constructor.
    */
    CGXDLMSSeasonProfile()
    {

    }

    /** 
     Constructor.
    */
    CGXDLMSSeasonProfile(basic_string<char> name, CGXDateTime start, basic_string<char> weekName)
    {
        SetName(name);
        SetStart(start);
        SetWeekName(weekName);
    }

    /** 
     Name of season profile.
    */
    basic_string<char> GetName()
    {
        return m_Name;
    }
    void SetName(basic_string<char> value)
    {
        m_Name = value;
    }

    /** 
     Season Profile start time.
    */    
    CGXDateTime GetStart()
    {
        return m_Start;
    }
    void SetStart(CGXDateTime value)
    {
        m_Start = value;
    }

    /** 
     Week name of season profile.
    */    
    basic_string<char> GetWeekName()
    {
        return m_WeekName;
    }
    void SetWeekName(basic_string<char> value)
    {
        m_WeekName = value;
    }
};