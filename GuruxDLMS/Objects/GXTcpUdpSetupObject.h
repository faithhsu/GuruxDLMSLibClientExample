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

class CGXTcpUdpSetupObject : public CGXObject
{
	int m_Port;
	basic_string<char> m_IPReference;
	int m_MaximumSimultaneousConnections;
	int m_InactivityTimeout;
	int m_MaximumSegmentSize;

	void Init()
	{
		m_Port = 4059;
		m_IPReference = "127.0.0.1";
		m_MaximumSimultaneousConnections = 1;
		SetInactivityTimeout(180);
        SetMaximumSegmentSize(576);
	}

public:
    /**  
     Constructor.
    */
	CGXTcpUdpSetupObject() :  CGXObject(OBJECT_TYPE_TCP_UDP_SETUP, "0.0.25.0.0.255")
    {
		Init();
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXTcpUdpSetupObject(basic_string<char> ln) : CGXObject(OBJECT_TYPE_TCP_UDP_SETUP, ln)
    {
		Init();
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXTcpUdpSetupObject(basic_string<char> ln, short sn) : CGXObject(OBJECT_TYPE_TCP_UDP_SETUP, sn)
    {
        Init();
    }	

    int GetPort()
    {
        return m_Port;
    }

    void SetPort(int value)
    {
       m_Port = value;
    }

    basic_string<char> GetIPReference()
    {
        return m_IPReference;
    }
    void SetIPReference(basic_string<char> value)
    {
       m_IPReference = value;
    }

    int GetMaximumSegmentSize()
    {
        return m_MaximumSegmentSize;
    }
    void SetMaximumSegmentSize(int value)
    {
       m_MaximumSegmentSize = value;
    }
   
    int GetMaximumSimultaneousConnections()
    {
        return m_MaximumSimultaneousConnections;
    }
    void SetMaximumSimultaneousConnections(int value)
    {
       m_MaximumSimultaneousConnections = value;
    }

    int GetInactivityTimeout()
    {
        return m_InactivityTimeout;
    }
    void SetInactivityTimeout(int value)
    {
       m_InactivityTimeout = value;
    }

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 6;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}

	// Returns value of given attribute.
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
			type = DLMS_DATA_TYPE_UINT16;
			value = GetPort();
			return ERROR_CODES_OK;
		}
		if (index == 3)
		{
			type = DLMS_DATA_TYPE_OCTET_STRING;
			value = GetIPReference();
			return ERROR_CODES_OK;
		}
		if (index == 4)
		{
			type = DLMS_DATA_TYPE_UINT16;
			value = GetMaximumSegmentSize();
			return ERROR_CODES_OK;
		}
		if (index == 5)
		{
			type = DLMS_DATA_TYPE_UINT8;
			value = GetMaximumSimultaneousConnections();
			return ERROR_CODES_OK;
		}
		if (index == 6)
		{
			type = DLMS_DATA_TYPE_UINT16;
			value = GetInactivityTimeout();
			return ERROR_CODES_OK;
		}
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
			return ERROR_CODES_OK;
		}
        if (index == 2)
		{
			SetPort(value.lVal);
			return ERROR_CODES_OK;			
		}
		else if (index == 3)
        {
            if (value.vt == DLMS_DATA_TYPE_NONE)
            {
                SetIPReference("");
            }
            else
            {
                if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
                {
					/*
                    String str = "";
                    for(int ch : (byte[]) value)
                    {
                        str += String.valueOf(ch) + ".";
                    }
                    str = str.substring(0, str.length() - 1);
                    setIPReference(str);
					*/
                }
                else
                {
                    SetIPReference(value.ToString());
                }
            }
			return ERROR_CODES_OK;
        }
        else if (index == 4)
        {
            if (value.vt == DLMS_DATA_TYPE_NONE)
            {
                SetMaximumSegmentSize(576);
            }
            else
            {
                SetMaximumSegmentSize(value.lVal);
            }
        }
        else if (index == 5)
        {
            if (value.vt == DLMS_DATA_TYPE_NONE)
            {
                SetMaximumSimultaneousConnections(1);
            }
            else
            {
                SetMaximumSimultaneousConnections(value.lVal);
            }
        }
        else if (index == 6)
        {
            if (value.vt == DLMS_DATA_TYPE_NONE)
            {
                SetInactivityTimeout(180);
            }
            else
            {
                SetInactivityTimeout(value.lVal);
            }
        }
		return ERROR_CODES_INVALID_PARAMETER;
    }
};
