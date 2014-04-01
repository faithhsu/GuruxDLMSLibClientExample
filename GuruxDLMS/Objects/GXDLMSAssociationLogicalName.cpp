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
#include "../GXDLMSObjectFactory.h"
#include "GXDLMSAssociationLogicalName.h"


void CGXDLMSAssociationLogicalName::Init()
{
	m_AssociationStatus = GX_ASSOCIATION_STATUS_NO_NASSOCIATED;
}

void CGXDLMSAssociationLogicalName::UpdateAccessRights(CGXDLMSObject* pObj, CGXDLMSVariant data)
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

int CGXDLMSAssociationLogicalName::GetAccessRights(CGXDLMSObject* pItem, vector<unsigned char>& data)
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
int CGXDLMSAssociationLogicalName::GetObjects(vector<unsigned char>& data)
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

/**  
 Constructor.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName() : CGXDLMSObject(OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, "0.0.40.0.0.255")
{
	Init();
}

/**  
 Constructor.
 @param ln Logican Name of the object.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, ln)
{
	Init();
}

CGXDLMSObjectCollection& CGXDLMSAssociationLogicalName::GetObjectList()
{
    return m_ObjectList;
}

unsigned char CGXDLMSAssociationLogicalName::GetClientSAP()
{
	return m_ClientSAP;
}
void CGXDLMSAssociationLogicalName::SetClientSAP(unsigned char value)
{
	m_ClientSAP = value;
}

unsigned short CGXDLMSAssociationLogicalName::GetServerSAP()
{
	return m_ServerSAP;
}

void CGXDLMSAssociationLogicalName::SetServerSAP(unsigned short value)
{
	m_ServerSAP = value;
}

CGXApplicationContextName CGXDLMSAssociationLogicalName::GetApplicationContextName()
{
    return m_ApplicationContextName;
}

CGXxDLMSContextType CGXDLMSAssociationLogicalName::GetXDLMSContextInfo()
{
    return m_XDLMSContextInfo;
}

CGXAuthenticationMechanismName CGXDLMSAssociationLogicalName::GetAuthenticationMechanismMame()
{
    return m_AuthenticationMechanismMame;
}

vector<unsigned char>& CGXDLMSAssociationLogicalName::GetSecret()
{
    return m_Secret;
}
void CGXDLMSAssociationLogicalName::SetSecret(vector<unsigned char>& value)
{
    m_Secret = value;
}    

GX_ASSOCIATION_STATUS CGXDLMSAssociationLogicalName::GetAssociationStatus()
{
    return m_AssociationStatus;
}

void CGXDLMSAssociationLogicalName::SetAssociationStatus(GX_ASSOCIATION_STATUS value)
{
    m_AssociationStatus = value;
}

string CGXDLMSAssociationLogicalName::GetSecuritySetupReference()
{
    return m_SecuritySetupReference;
}
void CGXDLMSAssociationLogicalName::SetSecuritySetupReference(string value)
{
    m_SecuritySetupReference = value;
}

// Returns amount of attributes.
int CGXDLMSAssociationLogicalName::GetAttributeCount()
{
	//Security Setup Reference is from version 1.
	if (GetVersion() > 0)
		return 9;
	return 8;
}

// Returns amount of methods.
int CGXDLMSAssociationLogicalName::GetMethodCount()
{
	return 4;
}

void CGXDLMSAssociationLogicalName::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(m_ObjectList.ToString());	
	string str = CGXDLMSVariant(m_ClientSAP).ToString();
	str += "/";
	str += CGXDLMSVariant(m_ServerSAP).ToString();
	values.push_back(str);
	values.push_back(m_ApplicationContextName.ToString());
	values.push_back(m_XDLMSContextInfo.ToString());
	values.push_back(m_AuthenticationMechanismMame.ToString());
	if (!m_Secret.empty())
	{
		values.push_back(GXHelpers::bytesToHex(&m_Secret[0], m_Secret.size()));
	}
	else
	{
		values.push_back(string());
	}
	values.push_back(CGXDLMSVariant(m_AssociationStatus).ToString());
	//Security Setup Reference is from version 1.
    if (GetVersion() > 0)
    {
		values.push_back(m_SecuritySetupReference);
	}
}

void CGXDLMSAssociationLogicalName::GetAttributeIndexToRead(vector<int>& attributes)
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

int CGXDLMSAssociationLogicalName::GetDataType(int index, DLMS_DATA_TYPE& type)
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

int CGXDLMSAssociationLogicalName::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
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
		vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        //Add count            
        data.push_back(2);
		data.push_back(DLMS_DATA_TYPE_UINT8);
        data.push_back(m_ClientSAP);
        data.push_back(DLMS_DATA_TYPE_UINT16);
		GXHelpers::SetUInt16(m_ServerSAP, data);
        value = data;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {         
		vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        //Add count            
        data.push_back(0x7);
		int ret;
		if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_ApplicationContextName.GetJointIsoCtt())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_ApplicationContextName.GetCountry())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, m_ApplicationContextName.GetCountryName())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_ApplicationContextName.GetIdentifiedOrganization())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_ApplicationContextName.GetDlmsUA())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_ApplicationContextName.GetApplicationContext())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_ApplicationContextName.GetContextId())) != 0)
		{
			return ret;
		}
        value = data;
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {            
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        data.push_back(6);
		int ret;

		if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_BIT_STRING, m_XDLMSContextInfo.GetConformance())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, m_XDLMSContextInfo.GetMaxReceivePduSize())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, m_XDLMSContextInfo.GetMaxSendPpuSize())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_XDLMSContextInfo.GetDlmsVersionNumber())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, m_XDLMSContextInfo.GetQualityOfService())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, m_XDLMSContextInfo.GetCypheringInfo())) != 0)
		{
			return ret;
		}
		value = data;
		return ERROR_CODES_OK;
    }
    if (index == 6)
    {         
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        //Add count            
        data.push_back(0x7);
		int ret;
		if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_AuthenticationMechanismMame.GetJointIsoCtt())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_AuthenticationMechanismMame.GetCountry())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, m_AuthenticationMechanismMame.GetCountryName())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_AuthenticationMechanismMame.GetIdentifiedOrganization())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_AuthenticationMechanismMame.GetDlmsUA())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_AuthenticationMechanismMame.GetAuthenticationMechanismName())) != 0 ||
			(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_AuthenticationMechanismMame.GetMechanismId())) != 0)
		{
			return ret;
		}
		value = data;
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

int CGXDLMSAssociationLogicalName::SetValue(int index, CGXDLMSVariant& value)
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
		m_ClientSAP = value.Arr[0].ToInteger();
		m_ServerSAP = value.Arr[1].ToInteger();
    }
    else if (index == 4)
    {
        //Value of the object identifier encoded in BER
		if (!value.byteArr.empty())
        {                    
            int pos = -1;
            if (value.byteArr[0] == 0x60)
            {
                m_ApplicationContextName.SetJointIsoCtt(0);
                ++pos;                        
                m_ApplicationContextName.SetCountry(0);
                ++pos;
                m_ApplicationContextName.SetCountryName(0);
                ++pos;
                m_ApplicationContextName.SetIdentifiedOrganization(value.byteArr[++pos]);
                m_ApplicationContextName.SetDlmsUA(value.byteArr[++pos]);
                m_ApplicationContextName.SetApplicationContext(value.byteArr[++pos]);
                m_ApplicationContextName.SetContextId(value.byteArr[++pos]);
            }
            else
            {
                //Get Tag and Len.
                if (value.byteArr[++pos] != 2 && value.byteArr[++pos] != 7)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                //Get tag
                if (value.byteArr[++pos] != 0x11)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetJointIsoCtt(value.byteArr[++pos]);
                //Get tag
                if (value.byteArr[++pos] != 0x11)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetCountry(value.byteArr[++pos]);
                //Get tag
                if (value.byteArr[++pos] != 0x12)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetCountryName(CGXOBISTemplate::GetUInt16(&value.byteArr[pos]));
				pos += 2;
				//Get tag
                if (value.byteArr[++pos] != 0x11)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetIdentifiedOrganization(value.byteArr[++pos]);
                //Get tag
                if (value.byteArr[++pos] != 0x11)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetDlmsUA(value.byteArr[++pos]);
                //Get tag
                if (value.byteArr[++pos] != 0x11)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetApplicationContext(value.byteArr[++pos]);
                //Get tag
                if (value.byteArr[++pos] != 0x11)
                {
                    return ERROR_CODES_INVALID_PARAMETER;
                }
                m_ApplicationContextName.SetContextId(value.byteArr[++pos]);
            }
        }
        else
        {
			m_ApplicationContextName.SetJointIsoCtt(value.Arr[0].ToInteger());
            m_ApplicationContextName.SetCountry(value.Arr[1].ToInteger());
            m_ApplicationContextName.SetCountryName(value.Arr[2].ToInteger());
            m_ApplicationContextName.SetIdentifiedOrganization(value.Arr[3].ToInteger());
            m_ApplicationContextName.SetDlmsUA(value.Arr[4].ToInteger());
            m_ApplicationContextName.SetApplicationContext(value.Arr[5].ToInteger());
            m_ApplicationContextName.SetContextId(value.Arr[6].ToInteger());
        }
    }
    else if (index == 5)
    {
		if (value.vt == DLMS_DATA_TYPE_STRUCTURE)
        {
			m_XDLMSContextInfo.SetConformance(value.Arr[0].ToString());
			m_XDLMSContextInfo.SetMaxReceivePduSize(value.Arr[1].ToInteger());
            m_XDLMSContextInfo.SetMaxSendPpuSize(value.Arr[2].ToInteger());
            m_XDLMSContextInfo.SetDlmsVersionNumber(value.Arr[3].ToInteger());
            m_XDLMSContextInfo.SetQualityOfService(value.Arr[4].ToInteger());
			m_XDLMSContextInfo.SetCypheringInfo(value.Arr[5].byteArr);
        }
    }
    else if (index == 6)
    {
        if (value.vt != DLMS_DATA_TYPE_NONE)
        {
            //Value of the object identifier encoded in BER
			if (!value.byteArr.empty())
            {
                int pos = -1;
                if (value.byteArr[0] == 0x60)
                {
                    m_AuthenticationMechanismMame.SetJointIsoCtt(0);
                    ++pos;
                    m_AuthenticationMechanismMame.SetCountry(0);
                    ++pos;
                    m_AuthenticationMechanismMame.SetCountryName(0);
                    ++pos;
                    m_AuthenticationMechanismMame.SetIdentifiedOrganization(value.byteArr[++pos]);
                    m_AuthenticationMechanismMame.SetDlmsUA(value.byteArr[++pos]);
                    m_AuthenticationMechanismMame.SetAuthenticationMechanismName(value.byteArr[++pos]);
                    m_AuthenticationMechanismMame.SetMechanismId((GXDLMS_AUTHENTICATION) value.byteArr[++pos]);
                }
                else
                {
                    //Get Tag and Len.
                    if (value.byteArr[++pos] != 2 && value.byteArr[++pos] != 7)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    //Get tag
                    if (value.byteArr[++pos] != 0x11)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetJointIsoCtt(value.byteArr[++pos]);
                    //Get tag
                    if (value.byteArr[++pos] != 0x11)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetCountry(value.byteArr[++pos]);
                    //Get tag
                    if (value.byteArr[++pos] != 0x12)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetCountryName(CGXOBISTemplate::GetUInt16(&value.byteArr[pos]));
					pos += 2;
                    //Get tag
                    if (value.byteArr[++pos] != 0x11)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetIdentifiedOrganization(value.byteArr[++pos]);
                    //Get tag
                    if (value.byteArr[++pos] != 0x11)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetDlmsUA(value.byteArr[++pos]);
                    //Get tag
                    if (value.byteArr[++pos] != 0x11)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetAuthenticationMechanismName(value.byteArr[++pos]);
                    //Get tag
                    if (value.byteArr[++pos] != 0x11)
                    {
                        return ERROR_CODES_INVALID_PARAMETER;
                    }
                    m_AuthenticationMechanismMame.SetMechanismId((GXDLMS_AUTHENTICATION) value.byteArr[++pos]);
                }
            }
            else
            {                       
                m_AuthenticationMechanismMame.SetJointIsoCtt(value.Arr[0].ToInteger());
                m_AuthenticationMechanismMame.SetCountry(value.Arr[1].ToInteger());
                m_AuthenticationMechanismMame.SetCountryName(value.Arr[2].ToInteger());
                m_AuthenticationMechanismMame.SetIdentifiedOrganization(value.Arr[3].ToInteger());
                m_AuthenticationMechanismMame.SetDlmsUA(value.Arr[4].ToInteger());
                m_AuthenticationMechanismMame.SetAuthenticationMechanismName(value.Arr[5].ToInteger());
                m_AuthenticationMechanismMame.SetMechanismId((GXDLMS_AUTHENTICATION) value.Arr[6].ToInteger());
            }                                           
        }                           
    }
    else if (index == 7)
    {
		m_Secret = value.byteArr;
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