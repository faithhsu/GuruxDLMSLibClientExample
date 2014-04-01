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
#include "GXDLMSSecuritySetup.h"
#include "../GXDLMSConverter.h"

//Constructor.
CGXDLMSSecuritySetup::CGXDLMSSecuritySetup() : CGXDLMSObject(OBJECT_TYPE_SECURITY_SETUP)
{
}

//SN Constructor.
CGXDLMSSecuritySetup::CGXDLMSSecuritySetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_SECURITY_SETUP, sn)
{

}

//LN Constructor.
CGXDLMSSecuritySetup::CGXDLMSSecuritySetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_SECURITY_SETUP, ln)
{

}

SECURITY_POLICY CGXDLMSSecuritySetup::GetSecurityPolicy()
{
	return m_SecurityPolicy;
}

void CGXDLMSSecuritySetup::SetSecurityPolicy(SECURITY_POLICY value)
{
	m_SecurityPolicy = value;
}

SECURITY_SUITE CGXDLMSSecuritySetup::GetSecuritySuite()
{
	return m_SecuritySuite;
}

void CGXDLMSSecuritySetup::SetSecuritySuite(SECURITY_SUITE value)
{
	m_SecuritySuite = value;
}

vector<unsigned char>& CGXDLMSSecuritySetup::GetClientSystemTitle()
{
	return m_ClientSystemTitle;
}
void CGXDLMSSecuritySetup::SetClientSystemTitle(vector<unsigned char>& value)
{
	m_ClientSystemTitle = value;
}

vector<unsigned char>& CGXDLMSSecuritySetup::GetServerSystemTitle()
{
	return m_ServerSystemTitle;
}
void CGXDLMSSecuritySetup::SetServerSystemTitle(vector<unsigned char>& value)
{
	m_ServerSystemTitle = value;
}

// Returns amount of attributes.
int CGXDLMSSecuritySetup::GetAttributeCount()
{
	return 5;
}

// Returns amount of methods.
int CGXDLMSSecuritySetup::GetMethodCount()
{
	return 2;
}

void CGXDLMSSecuritySetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(CGXDLMSConverter::ToString(m_SecurityPolicy));
	values.push_back(CGXDLMSConverter::ToString(m_SecuritySuite));
	string str;
	if (m_ClientSystemTitle.size() != 0)
	{
		str = GXHelpers::bytesToHex(&m_ClientSystemTitle[0], m_ClientSystemTitle.size());		
	}
	else
	{
		str.append("");
	}
	values.push_back(str);
	str.clear();
	if (m_ServerSystemTitle.size() != 0)
	{
		str = GXHelpers::bytesToHex(&m_ServerSystemTitle[0], m_ServerSystemTitle.size());				
	}
	else
	{
		str.append("");
	}
	values.push_back(str);
}

void CGXDLMSSecuritySetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//SecurityPolicy
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //SecuritySuite
    if (CanRead(3))
    {
        attributes.push_back(3);
    }

    //ClientSystemTitle
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //ServerSystemTitle
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
}

int CGXDLMSSecuritySetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }   
	else 
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSSecuritySetup::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;			
	}
    else if (index == 2)
    {
        value = m_SecurityPolicy;
    }
    else if (index == 3)
    {
        value = m_SecuritySuite;
    }
    else if (index == 4)
    {
        value = m_ClientSystemTitle;
    }
    else if (index == 5)
    {
        value = m_ServerSystemTitle;
    }   
	else 
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Set value of given attribute.
int CGXDLMSSecuritySetup::SetValue(int index, CGXDLMSVariant& value)
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
        m_SecurityPolicy = (SECURITY_POLICY) value.ToInteger();
    }
    else if (index == 3)
    {
        m_SecuritySuite = (SECURITY_SUITE) value.ToInteger();
    }
    else if (index == 4)
    {
		m_ClientSystemTitle = value.byteArr;		
    }
    else if (index == 5)
    {
		m_ServerSystemTitle = value.byteArr;
    }	
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}