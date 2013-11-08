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

#include "GXDLMSActionItem.h"

class CGXDLMSActionSet
{
	CGXDLMSActionItem m_ActionUp;
    CGXDLMSActionItem m_ActionDown;
public:
    /** 
     Constructor.
    */
    CGXDLMSActionSet()
    {
    }

    CGXDLMSActionItem& GetActionUp()
    {
        return m_ActionUp;
    }
    void SetActionUp(CGXDLMSActionItem& value)
    {
        m_ActionUp = value;
    }

    CGXDLMSActionItem GetActionDown()
    {
        return m_ActionDown;
    }
    void SetActionDown(CGXDLMSActionItem value)
    {
        m_ActionDown = value;
    }
};