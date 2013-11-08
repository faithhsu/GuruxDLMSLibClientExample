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

class CGXDLMSActionItem
{
	basic_string<char> m_LogicalName;
    int m_ScriptSelector;
public:
    //Constructor.
	CGXDLMSActionItem()
	{
		m_ScriptSelector = 0;
	}

    basic_string<char> GetLogicalName()
    {
        return m_LogicalName;
    }
    void SetLogicalName(basic_string<char> value)
    {
        m_LogicalName = value;
    }

    int GetScriptSelector()
    {
        return m_ScriptSelector;
    }
    void SetScriptSelector(int value)
    {
        m_ScriptSelector = value;
    }
};