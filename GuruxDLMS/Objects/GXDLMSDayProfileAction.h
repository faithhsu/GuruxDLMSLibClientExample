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

//Activity Calendar's Day Profile Action is defined on the standard.
class CGXDLMSDayProfileAction
{
	CGXDateTime m_StartTime;
    basic_string<char> m_ScriptLogicalName;
    int m_ScriptSelector;    
public:    
    /** 
     Constructor.
    */
    CGXDLMSDayProfileAction()
    {
		m_ScriptSelector = 0;
    }

    /** 
     Constructor.
    */
    CGXDLMSDayProfileAction(CGXDateTime startTime, basic_string<char> scriptLogicalName, int scriptSelector)
    {
        SetStartTime(startTime);
        SetScriptLogicalName(scriptLogicalName);
        SetScriptSelector(scriptSelector);
    }

    /** 
     Defines the time when the script is to be executed.
    */   
    CGXDateTime GetStartTime()
    {
        return m_StartTime;
    }
    void SetStartTime(CGXDateTime value)
    {
        m_StartTime = value;
    }

    /** 
     Defines the logical name of the "Script table" object;
    */
    basic_string<char> GetScriptLogicalName()
    {
        return m_ScriptLogicalName;
    }
    void SetScriptLogicalName(basic_string<char> value)
    {
        m_ScriptLogicalName = value;
    }

    /** 
     Defines the script_identifier of the script to be executed.
    */    
    int GetScriptSelector()
    {
        return m_ScriptSelector;
    }
    void SetScriptSelector(int value)
    {
        m_ScriptSelector = value;
    }
};