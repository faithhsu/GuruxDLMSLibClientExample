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
#include "GXDLMSObject.h"
#include "../GXHelpers.h"
#include "../GXDLMSObjectFactory.h"

enum GX_ASSOCIATION_STATUS
{
	GX_ASSOCIATION_STATUS_NO_NASSOCIATED, 
    GX_ASSOCIATION_STATUS_ASSOCIATION_PENDING, 
    GX_ASSOCIATION_STATUS_ASSOCIATED
};

class CGXDLMSAssociationLogicalName : public CGXDLMSObject
{
private:

	GX_ASSOCIATION_STATUS m_AssociationStatus;
    CGXDLMSObjectCollection m_ObjectList;
    CGXDLMSVariant m_AssociatedPartnersId;
    CGXDLMSVariant m_ApplicationContextName;
    CGXDLMSVariant m_XDLMSContextInfo;
    CGXDLMSVariant m_AuthenticationMechanismMame;
    CGXDLMSVariant m_Secret;
    string m_SecuritySetupReference;   

	void Init()
	{
		m_AssociationStatus = GX_ASSOCIATION_STATUS_NO_NASSOCIATED;
	}

	void UpdateAccessRights(CGXDLMSObject* pObj, CGXDLMSVariant data)
    {    
		//for(Object access : (Object[]) Array.get(buff, 0))
		for (std::vector<CGXDLMSVariant >::iterator it = data.Arr[0].Arr.begin(); it != data.Arr[0].Arr.end(); ++it)                
        {                
            int id = it->Arr[0].ToInteger();            
            ACCESSMODE mode = (ACCESSMODE) it->Arr[1].ToInteger();
            pObj->SetAccess(id, mode);
        }        
        for (std::vector<CGXDLMSVariant >::iterator it = data.Arr[1].Arr.begin(); it != data.Arr[1].Arr.end(); ++it)
        {            
            int id = it->Arr[0].ToInteger();
			METHOD_ACCESSMODE mode = (METHOD_ACCESSMODE) it->Arr[1].ToInteger();
            pObj->SetMethodAccess(id, mode);
        }
    }

	int GetAccessRights(CGXDLMSObject* pItem, vector<unsigned char>& data)
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
		for(CGXDLMSObjectCollection::iterator it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
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

public:	
	/**  
     Constructor.
    */
	CGXDLMSAssociationLogicalName() : CGXDLMSObject(OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, "0.0.40.0.0.255")
    {
		Init();
    }

    /**  
     Constructor.
     @param ln Logican Name of the object.
    */
    CGXDLMSAssociationLogicalName(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, ln)
    {
		Init();
    }
   
    CGXDLMSObjectCollection& GetObjectList()
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

	string GetSecuritySetupReference()
    {
        return m_SecuritySetupReference;
    }
    void SetSecuritySetupReference(string value)
    {
        m_SecuritySetupReference = value;
    }

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		//Security Setup Reference is from version 1.
		if (GetVersion() > 0)
			return 9;
		return 8;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 4;
	}

	void GetAttributeIndexToRead(vector<int>& attributes)
    {
        //LN is static and read only once.
		if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
        {
            attributes.push_back(1);
        }
        //ObjectList is static and read only once.
        if (!IsRead(2))
        {
            attributes.push_back(2);
        }
        //associated_partners_id is static and read only once.
        if (!IsRead(3))
        {
            attributes.push_back(3);
        }
        //Application Context Name is static and read only once.
        if (!IsRead(4))
        {
            attributes.push_back(4);
        }
        //xDLMS Context Info
        if (!IsRead(5))
        {
            attributes.push_back(5);
        }
        // Authentication Mechanism Name
        if (!IsRead(6))
        {
            attributes.push_back(6);
        }
        // Secret
        if (!IsRead(7))
        {
            attributes.push_back(7);
        }
        // Association Status
        if (!IsRead(8))
        {
            attributes.push_back(8);
        }
        //Security Setup Reference is from version 1.
        if (GetVersion() > 0 && !IsRead(9))
        {
            attributes.push_back(9);
        }    
    }

	int GetDataType(int index, DLMS_DATA_TYPE& type)
    {
		if (index == 1)
		{
			type = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
		}
        if (index == 2)
        {
			type = DLMS_DATA_TYPE_ARRAY;
			return ERROR_CODES_OK;            
        }
        if (index == 3)
        {
			type = DLMS_DATA_TYPE_STRUCTURE;
			return ERROR_CODES_OK;            
        }
        if (index == 4)
        {
			type = DLMS_DATA_TYPE_STRUCTURE;
			return ERROR_CODES_OK;            
        }
        if (index == 5)
        {
			type = DLMS_DATA_TYPE_STRUCTURE;
			return ERROR_CODES_OK;            
        }
        if (index == 6)
        {
			type = DLMS_DATA_TYPE_STRUCTURE;
			return ERROR_CODES_OK;            
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;
            return ERROR_CODES_OK;
        }        
		if (index == 8)
		{
			type = DLMS_DATA_TYPE_ENUM;			
			return ERROR_CODES_OK;
		}
		if (index == 9)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;
            return ERROR_CODES_OK;
        } 
		return ERROR_CODES_INVALID_PARAMETER;
	}

    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
    {
		if (index == 1)
		{
			GXHelpers::AddRange(value.byteArr, m_LN, 6);
			value.vt = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
		}
        if (index == 2)
        {			
			vector<unsigned char> Packets;
			int ret = GetObjects(Packets);
			value = Packets;
			return ret;            
        }
        if (index == 3)
        {         
            value = GetAssociatedPartnersId();
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {         
            value = GetApplicationContextName();
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {            
            value = GetXDLMSContextInfo();
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {         
            value = GetAuthenticationMechanismMame();
			return ERROR_CODES_OK;
        }
        if (index == 7)
        {         
            value = GetSecret();
			return ERROR_CODES_OK;
        }        
		if (index == 8)
		{		
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
		}
		else if (index == 2)
        {
            m_ObjectList.clear();
            if (value.vt != DLMS_DATA_TYPE_NONE)
            {
				for (std::vector<CGXDLMSVariant >::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)                
                {                    
                    OBJECT_TYPE type = (OBJECT_TYPE) (*it).Arr[0].ToInteger();
                    int version = (*it).Arr[1].ToInteger();
                    string ln;
					CGXOBISTemplate::GetLogicalName(&(*it).Arr[2].byteArr[0], ln);
					CGXDLMSObject* pObj = GetParent()->FindByLN(type, ln);
					if (pObj == NULL)
					{
						pObj = CGXDLMSObjectFactory::CreateObject(type);
                        pObj->SetLogicalName(ln);
						pObj->SetVersion(version);
					}                    
                    UpdateAccessRights(pObj, (*it).Arr[3]);                    
                    m_ObjectList.push_back(pObj);
                }               
            }
        }
        else if (index == 3)
        {            
             m_AssociatedPartnersId = value;            
        }
        else if (index == 4)
        {
            m_ApplicationContextName = value;
        }
        else if (index == 5)
        {
            m_XDLMSContextInfo = value;
        }
        else if (index == 6)
        {
            m_AuthenticationMechanismMame = value;                                    
        }
        else if (index == 7)
        {
            m_Secret = value;
        }
        else if (index == 8)
        {
			m_AssociationStatus = (GX_ASSOCIATION_STATUS) value.ToInteger();
        }
        else if (index == 9)
        {
            m_SecuritySetupReference = value.ToString();
        }
        else
        {
			return ERROR_CODES_INVALID_PARAMETER;
        }
		return ERROR_CODES_OK;
    }
};
