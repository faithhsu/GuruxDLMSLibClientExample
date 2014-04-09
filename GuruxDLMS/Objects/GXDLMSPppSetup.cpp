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

#include "GXDLMSPppSetup.h"
#include "../GXDLMSClient.h"
#include <sstream> 

//Constructor.
CGXDLMSPppSetup::CGXDLMSPppSetup() : CGXDLMSObject(OBJECT_TYPE_PPP_SETUP)
{
}

//SN Constructor.
CGXDLMSPppSetup::CGXDLMSPppSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_PPP_SETUP, sn)
{

}

//LN Constructor.
CGXDLMSPppSetup::CGXDLMSPppSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_PPP_SETUP, ln)
{

}

PPP_AUTHENTICATION_TYPE CGXDLMSPppSetup::GetAuthentication()
{
    return m_Authentication;
}
void CGXDLMSPppSetup::SetAuthentication(PPP_AUTHENTICATION_TYPE value)
{
    m_Authentication = value;
}    

/** 
PPP authentication procedure user name.
*/    
vector<unsigned char> CGXDLMSPppSetup::GetUserName()
{
    return m_UserName;
}

void CGXDLMSPppSetup::SetUserName(vector<unsigned char> value)
{
    m_UserName = value;
}

/** 
 PPP authentication procedure password.
*/

vector<unsigned char>& CGXDLMSPppSetup::GetPassword()
{
    return m_Password;
}

void CGXDLMSPppSetup::SetPassword(vector<unsigned char> value)
{
    m_Password = value;
}

string CGXDLMSPppSetup::GetPHYReference()
{
    return m_PHYReference;
}
void CGXDLMSPppSetup::SetPHYReference(string value)
{
    m_PHYReference = value;
}

vector<CGXDLMSPppSetupLcpOption>& CGXDLMSPppSetup::GetLCPOptions()
{
    return m_LCPOptions;
}


vector<CGXDLMSPppSetupIPCPOption>& CGXDLMSPppSetup::GetIPCPOptions()
{
    return m_IPCPOptions;
}

// Returns amount of attributes.
int CGXDLMSPppSetup::GetAttributeCount()
{
	return 5;
}

// Returns amount of methods.
int CGXDLMSPppSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSPppSetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(m_PHYReference);	
	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<CGXDLMSPppSetupLcpOption>::iterator it = m_LCPOptions.begin(); it != m_LCPOptions.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;		
		string str = it->ToString();
		sb.write(str.c_str(), str.size());
	}
	sb << ']';
	values.push_back(sb.str());	
	
	//Clear str.
	sb.str(std::string());		
	sb << '[';
	empty = true;
	for(vector<CGXDLMSPppSetupIPCPOption>::iterator it = m_IPCPOptions.begin(); it != m_IPCPOptions.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;
		string str = it->ToString();
		sb.write(str.c_str(), str.size());
	}
	sb << ']';
	values.push_back(sb.str());	

	string str;		
	if (m_UserName.size() != 0)
	{
		str.append((char*) &m_UserName[0], m_UserName.size());
	}
	if (m_Password.size() != 0)
	{
		str.append(" ");
		str.append((char*) &m_Password[0], m_Password.size());
	}
	values.push_back(str);
}

void CGXDLMSPppSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//PHYReference
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //LCPOptions
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //IPCPOptions
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //PPPAuthentication
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
}

int CGXDLMSPppSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    } 
	else 
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSPppSetup::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}		
	if (index == 2)
    {
        value = m_PHYReference;
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        data.push_back(m_IPCPOptions.size());
		for(vector<CGXDLMSPppSetupLcpOption>::iterator it = m_LCPOptions.begin(); it != m_LCPOptions.end(); ++it)
        {
            data.push_back(DLMS_DATA_TYPE_STRUCTURE);
            data.push_back(3);
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, it->GetType());                    
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, it->GetLength());
            CGXOBISTemplate::SetData(data, it->GetData().vt, it->GetData());
        }                       
        value = data;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        data.push_back(m_IPCPOptions.size());
		for(vector<CGXDLMSPppSetupIPCPOption>::iterator it = m_IPCPOptions.begin(); it != m_IPCPOptions.end(); ++it)
        {
            data.push_back(DLMS_DATA_TYPE_STRUCTURE);
            data.push_back(3);
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, it->GetType());
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, it->GetLength());
            CGXOBISTemplate::SetData(data, it->GetData().vt, it->GetData());
        }		
        value = data;
		return ERROR_CODES_OK;
    }
    else if (index == 5)
    {
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        data.push_back(2);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, m_UserName);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, m_Password);
        value = data;
		return ERROR_CODES_OK;
    }
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSPppSetup::SetValue(int index, CGXDLMSVariant& value)
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
		if (value.vt == DLMS_DATA_TYPE_STRING)
        {
            m_PHYReference = value.ToString();
        }
        else
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
			m_PHYReference = tmp.ToString();
        }
    }
    else if (index == 3)
    {
        m_LCPOptions.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
			for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)                
            {
                CGXDLMSPppSetupLcpOption it;
				it.SetType((*item).Arr[0].ToInteger());
                it.SetLength((*item).Arr[1].ToInteger());
                it.SetData((*item).Arr[2]);
                m_LCPOptions.push_back(it);
            }
        }            
    }
    else if (index == 4)
    {
		m_IPCPOptions.clear();            
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
			for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)                
            {
                CGXDLMSPppSetupIPCPOption it;
                it.SetType((PPP_SETUP_IPCP_OPTION_TYPE)(*item).Arr[0].ToInteger());
                it.SetLength((*item).Arr[1].ToInteger());
                it.SetData((*item).Arr[2]);
                m_IPCPOptions.push_back(it);
            }
        }            
    }
    else if (index == 5)
    {
		m_UserName = value.Arr[0].byteArr;
        m_Password = value.Arr[1].byteArr;		
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}