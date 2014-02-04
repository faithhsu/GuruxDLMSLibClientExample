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

 enum PPP_SETUP_IPCP_OPTION_TYPE
 {
    PPP_SETUP_IPCP_OPTION_TYPE_IPCOMPRESSIONPROTOCOL = 2,
    PPP_SETUP_IPCP_OPTION_TYPE_PREFLOCALIP = 3,
    PPP_SETUP_IPCP_OPTION_TYPE_PREFPEERIP = 20,
    PPP_SETUP_IPCP_OPTION_TYPE_GAO = 21,
    PPP_SETUP_IPCP_OPTION_TYPE_USIP = 22
};

 enum PPP_SETUP_LCP_OPTION_TYPE
{
    PPP_SETUP_LCP_OPTION_TYPE_MAX_REC_UNIT = 1,
    PPP_SETUP_LCP_OPTION_TYPE_ASYNC_CONTROL_CHAR_MAP = 2,
    PPP_SETUP_LCP_OPTION_TYPE_AUTH_PROTOCOL = 3,
    PPP_SETUP_LCP_OPTION_TYPE_MAGIC_NUMBER = 5,
    PPP_SETUP_LCP_OPTION_TYPE_PROTOCOL_FIELD_COMPRESSION = 7,
    PPP_SETUP_LCP_OPTION_TYPE_ADDRESS_AND_CTRL_COMPRESSION = 8,
    PPP_SETUP_LCP_OPTION_TYPE_FCS_ALTERNATIVES = 9,
    PPP_SETUP_LCP_OPTION_TYPE_CALLBACK = 13
};

/** 
PPP Authentication Type
 */
enum PPP_AUTHENTICATION_TYPE
{
    /** 
     No authentication.
    */
    PPP_AUTHENTICATION_TYPE_NONE = 0,
    /** 
     PAP Login
    */
    PPP_AUTHENTICATION_TYPE_PAP = 1,
    /** 
     CHAP-algorithm
    */
    PPP_AUTHENTICATION_TYPE_CHAP = 2
};

class CGXDLMSPppSetupIPCPOption
{
    PPP_SETUP_IPCP_OPTION_TYPE m_Type;
    int m_Length;
    CGXDLMSVariant m_Data;
public:

    PPP_SETUP_IPCP_OPTION_TYPE GetType()
    {
        return m_Type;
    }
    void SetType(PPP_SETUP_IPCP_OPTION_TYPE value)
    {
        m_Type = value;
    }

    int GetLength()
    {
        return m_Length;
    }
    void SetLength(int value)
    {
        m_Length = value;
    }

    CGXDLMSVariant GetData()
    {
        return m_Data;
    }
    void SetData(CGXDLMSVariant value)
    {
        m_Data = value;
    }
};

class CGXDLMSPppSetupLcpOption
{
    CGXDLMSVariant m_Type;
    CGXDLMSVariant m_Data;
    int m_Length;   
public:

    CGXDLMSVariant GetType()
    {
        return m_Type;
    }
    void SetType(CGXDLMSVariant value)
    {
        m_Type = value;
    }

    int GetLength()
    {
        return m_Length;
    }

    void SetLength(int value)
    {
        m_Length = value;
    }

    CGXDLMSVariant GetData()
    {
        return m_Data;
    }

    void SetData(CGXDLMSVariant value)
    {
        m_Data = value;
    }
};

class CGXDLMSPppSetup : public CGXDLMSObject
{
	vector<CGXDLMSPppSetupIPCPOption> m_IPCPOptions;
    string m_PHYReference;
    vector<CGXDLMSPppSetupLcpOption> m_LCPOptions;
    vector<unsigned char> m_UserName;
    vector<unsigned char> m_Password;
	PPP_AUTHENTICATION_TYPE m_Authentication;
    
public:	
	//Constructor.
	CGXDLMSPppSetup() : CGXDLMSObject(OBJECT_TYPE_PPP_SETUP)
	{
	}

	//SN Constructor.
	CGXDLMSPppSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_PPP_SETUP, sn)
	{

	}

	//LN Constructor.
	CGXDLMSPppSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_PPP_SETUP, ln)
	{

	}

	PPP_AUTHENTICATION_TYPE getAuthentication()
    {
        return m_Authentication;
    }
    void SetAuthentication(PPP_AUTHENTICATION_TYPE value)
    {
        m_Authentication = value;
    }    
    
    /** 
    PPP authentication procedure user name.
   */    
    vector<unsigned char> GetUserName()
    {
        return m_UserName;
    }

    void SetUserName(vector<unsigned char> value)
    {
        m_UserName = value;
    }

    /** 
     PPP authentication procedure password.
    */

    vector<unsigned char>& getPassword()
    {
        return m_Password;
    }
    
	void SetPassword(vector<unsigned char> value)
    {
        m_Password = value;
    }

	string GetPHYReference()
    {
        return m_PHYReference;
    }
    void SetPHYReference(string value)
    {
        m_PHYReference = value;
    }

    vector<CGXDLMSPppSetupLcpOption>& GetLCPOptions()
    {
        return m_LCPOptions;
    }
    

    vector<CGXDLMSPppSetupIPCPOption>& GetIPCPOptions()
    {
        return m_IPCPOptions;
    }

    // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 5;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}

	void GetAttributeIndexToRead(vector<int>& attributes)
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

	int GetDataType(int index, DLMS_DATA_TYPE& type)
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
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
    {
		if (index == 1)
		{
			GXHelpers::AddRange(value.byteArr, m_LN, 6);
			value.vt = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
		}		
		//TODO:
		return ERROR_CODES_INVALID_PARAMETER;
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
};
