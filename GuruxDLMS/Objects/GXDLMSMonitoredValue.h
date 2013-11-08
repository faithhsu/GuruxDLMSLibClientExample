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

#include "GXObject.h"

class CGXDLMSMonitoredValue
{
	OBJECT_TYPE m_ObjectType;
    basic_string<char> m_LogicalName;
    int m_AttributeIndex;
public:

	CGXDLMSMonitoredValue()
	{
		m_ObjectType = OBJECT_TYPE_NONE;
		m_AttributeIndex = 0;
	}

	void Update(CGXObject* pObj, int attributeIndex)
    {
        m_ObjectType = pObj->GetObjectType();
        m_LogicalName = pObj->GetLogicalName();
        m_AttributeIndex = attributeIndex;
    }

    OBJECT_TYPE GetObjectType()
    {
        return m_ObjectType;
    }
    void SetObjectType(OBJECT_TYPE value)
    {
        m_ObjectType = value;
    }

    basic_string<char> GetLogicalName()
    {
        return m_LogicalName;
    }
    void SetLogicalName(basic_string<char> value)
    {
        m_LogicalName = value;
    }

    int GetAttributeIndex()
    {
        return m_AttributeIndex;
    }
    void SetAttributeIndex(int value)
    {
        m_AttributeIndex = value;
    }
};