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
#include "../GXHelpers.h"

enum GX_ASSOCIATION_STATUS
{
	GX_ASSOCIATION_STATUS_NO_NASSOCIATED, 
    GX_ASSOCIATION_STATUS_ASSOCIATION_PENDING, 
    GX_ASSOCIATION_STATUS_ASSOCIATED
};

class CGXAssociationLogicalNameObject : public CGXObject
{
	GX_ASSOCIATION_STATUS m_AssociationStatus;
    CGXObjectCollection m_ObjectList;
    CGXDLMSVariant m_AssociatedPartnersId;
    CGXDLMSVariant m_ApplicationContextName;
    CGXDLMSVariant m_XDLMSContextInfo;
    CGXDLMSVariant m_AuthenticationMechanismMame;
    CGXDLMSVariant m_Secret;

	void Init()
	{
		m_AssociationStatus = GX_ASSOCIATION_STATUS_NO_NASSOCIATED;
	}

public:	
	/**  
     Constructor.
    */
	CGXAssociationLogicalNameObject() : CGXObject(OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, "0.0.40.0.0.255")
    {
		Init();
    }

    /**  
     Constructor.
     @param ln Logican Name of the object.
    */
    CGXAssociationLogicalNameObject(basic_string<char> ln) : CGXObject(OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, ln)
    {
		Init();
    }
   
    CGXObjectCollection& GetObjectList()
    {
        return m_ObjectList;
    }

    CGXDLMSVariant GetAssociatedPartnersId()
    {
        return m_AssociatedPartnersId;
    }
    void SetAssociatedPartnersId(CGXDLMSVariant value)
    {
        m_AssociatedPartnersId = value;
    }

    CGXDLMSVariant GetApplicationContextName()
    {
        return m_ApplicationContextName;
    }
    void SetApplicationContextName(CGXDLMSVariant value)
    {
        m_ApplicationContextName = value;
    }

    CGXDLMSVariant GetXDLMSContextInfo()
    {
        return m_XDLMSContextInfo;
    }
    void SetXDLMSContextInfo(CGXDLMSVariant value)
    {
        m_XDLMSContextInfo = value;
    }

    CGXDLMSVariant GetAuthenticationMechanismMame()
    {
        return m_AuthenticationMechanismMame;
    }
    void SetAuthenticationMechanismMame(CGXDLMSVariant value)
    {
        m_AuthenticationMechanismMame = value;
    }

    CGXDLMSVariant GetSecret()
    {
        return m_Secret;
    }
    void SetSecret(CGXDLMSVariant value)
    {
        m_Secret = value;
    }    

	GX_ASSOCIATION_STATUS GetAssociationStatus()
    {
        return m_AssociationStatus;
    }

	void SetAssociationStatus(GX_ASSOCIATION_STATUS value)
    {
        m_AssociationStatus = value;
    }

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 9;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 4;
	}

	int GetAccessRights(CGXObject* pItem, vector<unsigned char>& data)
	{
		CGXAttributeCollection& attributes = pItem->GetAttributes();
		attributes.clear();
		data.push_back(DLMS_DATA_TYPE_STRUCTURE);
		data.push_back(2);
		data.push_back(DLMS_DATA_TYPE_ARRAY);
		data.push_back(attributes.size());
		for(CGXAttributeCollection::iterator it = attributes.begin(); it != attributes.end(); ++it)
		{
			int index = (*it).GetIndex();
			ACCESSMODE access = (*it).GetAccess();
			data.push_back(DLMS_DATA_TYPE_STRUCTURE); //attribute_access_item
			data.push_back(3);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, index);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_ENUM, access);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_NONE, 0);
		}

		data.push_back(DLMS_DATA_TYPE_ARRAY);
		CGXAttributeCollection& m = pItem->GetMethodAttributes();
		data.push_back(m.size());            
		for(CGXAttributeCollection::iterator it = m.begin(); it != m.end(); ++it)
		{
			int index = (*it).GetIndex();
			METHOD_ACCESSMODE access = (*it).GetMethodAccess();
			data.push_back(DLMS_DATA_TYPE_STRUCTURE); //attribute_access_item
			data.push_back(2);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, index);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_ENUM, access);
		}	
		return ERROR_CODES_OK;
	}

	// Returns LN Association View.
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
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, type);//ClassID
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, version);//Version
			CGXDLMSVariant ln((*it)->m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);
			CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, ln);//LN                    
			GetAccessRights(*it, data);//Access rights.
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
		//This should be never called. Server handles this.
        if (index == 2)
        {
			type = DLMS_DATA_TYPE_ARRAY;
			vector<unsigned char> Packets;
			int ret = GetObjects(Packets);
			value = Packets;
			return ret;            
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_NONE;
            value = GetAssociatedPartnersId();
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_NONE;
            value = GetApplicationContextName();
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_NONE;
            value = GetXDLMSContextInfo();
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
            type = DLMS_DATA_TYPE_NONE;
            value = GetAuthenticationMechanismMame();
			return ERROR_CODES_OK;
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_NONE;
            value = GetSecret();
			return ERROR_CODES_OK;
        }        
		if (index == 8)
		{
			type = DLMS_DATA_TYPE_ENUM;
			value = (unsigned char)m_AssociationStatus;
			return ERROR_CODES_OK;
		}
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
		if (index == 8)
		{
			m_AssociationStatus = (GX_ASSOCIATION_STATUS) value.bVal;
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
    }
};
