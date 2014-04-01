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

class CGXDLMSMonitoredValue
{
	OBJECT_TYPE m_ObjectType;
    basic_string<char> m_LogicalName;
    int m_AttributeIndex;
public:

	CGXDLMSMonitoredValue();
	void Update(CGXDLMSObject* pObj, int attributeIndex);

    OBJECT_TYPE GetObjectType();
    void SetObjectType(OBJECT_TYPE value);

    basic_string<char> GetLogicalName();    
	void SetLogicalName(basic_string<char> value);

    int GetAttributeIndex();
    void SetAttributeIndex(int value);

	string ToString();
};