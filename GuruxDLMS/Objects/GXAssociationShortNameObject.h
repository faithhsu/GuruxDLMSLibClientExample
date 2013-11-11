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
#include "GXObject.h"
#include "GXObjectCollection.h"
#include "../GXOBISTemplate.h"
#include "../GXHelpers.h"

class CGXAssociationShortNameObject : public CGXObject
{
	//TODO: Object m_AccessRightsList;
    CGXObjectCollection m_ObjectList;
    //TODO: Object m_SecuritySetupReference;	
public:	
	//Constructor.
	CGXAssociationShortNameObject() : CGXObject(OBJECT_TYPE_ASSOCIATION_SHORT_NAME)
	{
		SetLogicalName("0.0.40.0.0.255");
		m_SN = 0xFA00;
	}

	CGXObjectCollection& GetObjectList()
    {
        return m_ObjectList;
    }

	/* TODO:
    Object GetAccessRightsList()
    {
        return m_AccessRightsList;
    }
    void SetAccessRightsList(Object value)
    {
        m_AccessRightsList = value;
    }

    Object GetSecuritySetupReference()
    {
        return m_SecuritySetupReference;
    }
    void SetSecuritySetupReference(Object value)
    {
        m_SecuritySetupReference = value;
    }
*/

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 4;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 8;
	}

	// Returns SN Association View.
	int GetObjects(vector<unsigned char>& data)
	{
		data.push_back(DLMS_DATA_TYPE_ARRAY);
		//Add count
		CGXOBISTemplate::SetObjectCount(m_ObjectList.size(), data);
		for(CGXObjectCollection::iterator it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
		{
			data.push_back(DLMS_DATA_TYPE_STRUCTURE);
			data.push_back(4);//Count    
			OBJECT_TYPE type = (*it)->GetObjectType();
			unsigned short version = (*it)->GetVersion();
			unsigned short sn = (*it)->GetShortName();
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, sn); //base address.
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, type); //ClassID
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, version); //Version
			CGXDLMSVariant ln((*it)->m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, ln); //LN
		}
		return ERROR_CODES_OK;
	}

    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
    {
		if (index == 1)
		{
			GXHelpers::AddRange(value.byteArr, m_LN, 6);
			type = value.vt = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
		}
		if (index == 2)
		{
			vector<unsigned char> Packets;
			int ret = GetObjects(Packets);
			value = Packets;
			return ret;
		}
		//This should be never called. Server handles this.
		return ERROR_CODES_INVALID_PARAMETER;
    }

	int SetValue(int index, CGXDLMSVariant& value)
    {
		if (index == 1)
        {
            if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
			{
				return ERROR_CODES_INVALID_PARAMETER;
			}
			memcpy(m_LN, &value.byteArr[0], 6);
			return ERROR_CODES_OK;
        }
		/*
		if (index == 0)
		{
			LogicalName;
		}
        if (index == 1)
		{
			Value = value;
		}
		*/
		return ERROR_CODES_INVALID_PARAMETER;
    }
};
