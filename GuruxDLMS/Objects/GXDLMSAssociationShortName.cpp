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

#include "../GXDLMSVariant.h"
#include "../GXDLMSClient.h"
#include "GXDLMSAssociationShortName.h"
#include "../GXDLMSObjectFactory.h"

int CGXDLMSAssociationShortName::GetAccessRights(CGXDLMSObject* pObj, vector<unsigned char>& data) 
{        
    data.push_back(DLMS_DATA_TYPE_STRUCTURE);
    data.push_back(3);
    CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, pObj->GetShortName());
    data.push_back(DLMS_DATA_TYPE_ARRAY);
    data.push_back(pObj->GetAttributes().size());
    CGXDLMSVariant empty;
	for(vector<CGXDLMSAttribute>::iterator att = pObj->GetAttributes().begin(); att != pObj->GetAttributes().end(); ++att)
    {
        data.push_back(DLMS_DATA_TYPE_STRUCTURE); //attribute_access_item
        data.push_back(3);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, att->GetIndex());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_ENUM, att->GetAccess());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_NONE, empty);
    }
    data.push_back(DLMS_DATA_TYPE_ARRAY);
    data.push_back(pObj->GetMethodAttributes().size());
	for(vector<CGXDLMSAttribute>::iterator it = pObj->GetMethodAttributes().begin(); it != pObj->GetMethodAttributes().end(); ++it)
    {
        data.push_back(DLMS_DATA_TYPE_STRUCTURE); //attribute_access_item
        data.push_back(2);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, it->GetIndex());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_ENUM, it->GetMethodAccess());
    }  
	return ERROR_CODES_OK;
}

void CGXDLMSAssociationShortName::UpdateAccessRights(CGXDLMSVariant& buff)
{     
	for(vector<CGXDLMSVariant>::iterator access = buff.Arr.begin(); access != buff.Arr.end(); ++access)
    //for (Object access : buff)
    {            
		int sn = access->Arr[0].ToInteger();
        CGXDLMSObject* pObj = m_ObjectList.FindBySN(sn);    
        if (pObj != NULL)
        {            
			for(vector<CGXDLMSVariant>::iterator attributeAccess = access->Arr[1].Arr.begin(); access != access->Arr[1].Arr.end(); ++access)                
            {                          
				int id = attributeAccess->Arr[0].ToInteger();
                int tmp = attributeAccess->Arr[1].ToInteger();
                pObj->SetAccess(id, (ACCESSMODE) tmp);
            } 
			for(vector<CGXDLMSVariant>::iterator methodAccess = access->Arr[2].Arr.begin(); access != access->Arr[2].Arr.end(); ++access)                
            {
                int id = methodAccess->Arr[0].ToInteger();
                int tmp = methodAccess->Arr[1].ToInteger();                    
                pObj->SetMethodAccess(id, (METHOD_ACCESSMODE) tmp);
            }
        }
    }
}

//Constructor.
CGXDLMSAssociationShortName::CGXDLMSAssociationShortName() : CGXDLMSObject(OBJECT_TYPE_ASSOCIATION_SHORT_NAME)
{
	SetLogicalName("0.0.40.0.0.255");
	m_SN = 0xFA00;
}

CGXDLMSObjectCollection& CGXDLMSAssociationShortName::GetObjectList()
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

void CGXDLMSAssociationShortName::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(m_ObjectList.ToString());	
	values.push_back(m_AccessRightsList.ToString());
	values.push_back(m_SecuritySetupReference);
}

void CGXDLMSAssociationShortName::GetAttributeIndexToRead(vector<int>& attributes)
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
    //AccessRightsList is static and read only once.
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //SecuritySetupReference is static and read only once.
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
}

// Returns amount of attributes.
int CGXDLMSAssociationShortName::GetAttributeCount()
{
	return 4;
}

// Returns amount of methods.
int CGXDLMSAssociationShortName::GetMethodCount()
{
	return 8;
}

int CGXDLMSAssociationShortName::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;			
	}
	else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;                  
    }  
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }  
    else if (index == 4)
    {
        
    }  
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns SN Association View.
int CGXDLMSAssociationShortName::GetObjects(vector<unsigned char>& data)
{
	int ret;
	data.push_back(DLMS_DATA_TYPE_ARRAY);
	//Add count
	CGXOBISTemplate::SetObjectCount(m_ObjectList.size(), data);
	for(CGXDLMSObjectCollection::iterator it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
	{
		data.push_back(DLMS_DATA_TYPE_STRUCTURE);
		data.push_back(4);//Count    
		OBJECT_TYPE type = (*it)->GetObjectType();
		unsigned short version = (*it)->GetVersion();
		unsigned short sn = (*it)->GetShortName();
		CGXDLMSVariant ln((*it)->m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);
		if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, sn)) != 0 || //base address.
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, type)) != 0 || //ClassID
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, version)) != 0 || //Version			
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, ln)) != 0) //LN
		{
			return ret;
		}
	}
	return ERROR_CODES_OK;
}

int CGXDLMSAssociationShortName::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
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
		int ret;
		bool lnExists = m_ObjectList.FindBySN(GetShortName()) != NULL;
        //Add count        
        int cnt = m_ObjectList.size();
        if (!lnExists)
        {
            ++cnt;
        }            
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        CGXOBISTemplate::SetObjectCount(cnt, data);
		for(vector<CGXDLMSObject*>::iterator it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
        {
            if ((ret = GetAccessRights(*it, data)) != 0)
			{
				return ret;
			}
        }
        if (!lnExists)
        {
            if ((ret = GetAccessRights(this, data)) != 0)
			{
				return ret;
			}
        }
        value = data;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

int CGXDLMSAssociationShortName::SetValue(int index, CGXDLMSVariant& value)
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
	else if (index == 2)
    {
        m_ObjectList.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
			for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {
				int sn = item->Arr[0].ToInteger();
				CGXDLMSObject* pObj = GetParent()->FindBySN(sn);
				if (pObj == NULL)
				{
                    OBJECT_TYPE type = (OBJECT_TYPE) item->Arr[1].ToInteger();
					int version = item->Arr[2].ToInteger();
					string ln;
					CGXOBISTemplate::GetLogicalName(&(*item).Arr[3].byteArr[0], ln);
					pObj = CGXDLMSObjectFactory::CreateObject(type);
                    pObj->SetLogicalName(ln);
					pObj->SetShortName(sn);
					pObj->SetVersion(version);						
				}
				m_ObjectList.push_back(pObj);
            }               
        }
    }  
    else if (index == 3)
    {
        if (value.vt == DLMS_DATA_TYPE_NONE)
        {
			for(vector<CGXDLMSObject*>::iterator it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
            {
                for(int pos = 1; pos != (*it)->GetAttributeCount(); ++pos)
                {
					(*it)->SetAccess(pos, ACCESSMODE_NONE);
                }
            }
        }
        else
        {
            UpdateAccessRights(value);
        }
    }
	return ERROR_CODES_INVALID_PARAMETER;
}
