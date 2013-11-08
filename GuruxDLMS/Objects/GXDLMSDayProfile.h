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

#include "GXDLMSDayProfileAction.h"

class CGXDLMSDayProfile
{
	int m_DayId;
    vector<CGXDLMSDayProfileAction> m_DaySchedules;    
public:
    /** 
     Constructor.
    */
    CGXDLMSDayProfile()
    {
		m_DayId = 0;
    }

    /** 
     Constructor.
    */
    CGXDLMSDayProfile(int dayId, vector<CGXDLMSDayProfileAction> schedules)
    {
        SetDayId(dayId);
        SetDaySchedules(schedules);
    }

    /** 
     User defined identifier, identifying the currentday_profile.
    */
    int GetDayId()
    {
        return m_DayId;
    }
    void SetDayId(int value)
    {
        m_DayId = value;
    }
    
    vector<CGXDLMSDayProfileAction>& GetDaySchedules()
    {
        return m_DaySchedules;
    }
    void SetDaySchedules(vector<CGXDLMSDayProfileAction>& value)
    {
        m_DaySchedules = value;
    }
};