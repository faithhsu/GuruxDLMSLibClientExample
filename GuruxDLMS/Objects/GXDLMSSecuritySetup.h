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


 /** 
    Security policy Enforces authentication and/or encryption algorithm provided with security_suite.
 */
enum SECURITY_POLICY
{
    SECURITY_POLICY_NOTHING,
    /** 
     All messages to be authenticated.
    */
    SECURITY_POLICY_AUTHENTICATED,
    /** 
     All messages to be encrypted.
    */
    SECURITY_POLICY_ENCRYPTED,
    /** 
     All messages to be authenticated and encrypted.
    */
    SECURITY_POLICY_AUTHENTICATED_ENCRYPTED
};


//Security suite Specifies authentication, encryption and key wrapping algorithm.
enum SECURITY_SUITE
{
    /** 
     AES-GCM-128 for authenticated encryption and AES-128 for key wrapping.
    */
    SECURITY_SUITE_AES_GCM_128    
};

class CGXDLMSSecuritySetup : public CGXDLMSObject
{
	SECURITY_POLICY m_SecurityPolicy;
    SECURITY_SUITE m_SecuritySuite;
    string m_ServerSystemTitle;
    string m_ClientSystemTitle;	
public:	
	//Constructor.
	CGXDLMSSecuritySetup() : CGXDLMSObject(OBJECT_TYPE_SECURITY_SETUP)
	{
	}

	//SN Constructor.
	CGXDLMSSecuritySetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_SECURITY_SETUP, sn)
	{

	}

	//LN Constructor.
	CGXDLMSSecuritySetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_SECURITY_SETUP, ln)
	{

	}

	SECURITY_POLICY GetSecurityPolicy()
    {
		return m_SecurityPolicy;
    }
    
	void SetSecurityPolicy(SECURITY_POLICY value)
    {
		m_SecurityPolicy = value;
    }

    SECURITY_SUITE GetSecuritySuite()
    {
		return m_SecuritySuite;
    }
    
	void SetSecuritySuite(SECURITY_SUITE value)
    {
		m_SecuritySuite = value;
    }

    string GetClientSystemTitle()
    {
		return m_ClientSystemTitle;
    }
    void SetClientSystemTitle(string value)
    {
		m_ClientSystemTitle = value;
    }

    string GetServerSystemTitle()
    {
		return m_ServerSystemTitle;
    }
    void SetServerSystemTitle(string value)
    {
		m_ServerSystemTitle = value;
    }

    // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 5;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 2;
	}

	void GetAttributeIndexToRead(vector<int>& attributes)
	{
		//LN is static and read only once.
		if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
        {
            attributes.push_back(1);
        }
		//SECURITY_POLICY
        if (CanRead(2))
        {
            attributes.push_back(2);
        }
        //SECURITY_SUITE
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

	int GetDataType(int index, DLMS_DATA_TYPE& type)
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
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
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
            m_SecurityPolicy = (SECURITY_POLICY) value.ToInteger();
        }
        else if (index == 3)
        {
            m_SecuritySuite = (SECURITY_SUITE) value.ToInteger();
        }
        else if (index == 4)
        {
			if (value.vt == DLMS_DATA_TYPE_STRING)
            {
                m_ClientSystemTitle = value.ToString();
            }
            else
            {
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
				m_ClientSystemTitle = tmp.ToString();
            }
        }
        else if (index == 5)
        {
			if (value.vt == DLMS_DATA_TYPE_STRING)
            {
                m_ServerSystemTitle = value.ToString();
            }
            else
            {
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_OCTET_STRING, tmp);
				m_ServerSystemTitle = tmp.ToString();
            }
        }	
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		return ERROR_CODES_OK;
    }
};
