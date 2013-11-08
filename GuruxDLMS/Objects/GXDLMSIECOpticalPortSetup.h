//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL:  $
//
// Version:         $Revision:  $,
//                  $Date:  $
//                  $Author: $
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
#pragma once

#include "IGXDLMSBase.h"
#include "GXObject.h"
#include "../GXHelpers.h"

/** 
 Defines the protocol used by the meter on the port.
*/
enum OPTICAL_PROTOCOL_MODE
{
    /**         
     Protocol according to IEC 62056-21 (modes A…E),
    */
    OPTICAL_PROTOCOL_MODE_DEFAULT = 0,
    /** 
     Protocol according to IEC 62056-46. 
     Using this enumeration value all other attributes of this IC are not applicable.
    */
    OPTICAL_PROTOCOL_MODE_NET = 1,
    /** 
     Protocol not specified. Using this enumeration value, 
     ProposedBaudrate is used for setting the communication speed on the port. 
     All other attributes are not applicable.
    */
    OPTICAL_PROTOCOL_MODE_UNKNOWN = 2
};

enum LOCAL_PORT_RESPONSE_TIME
{
    /** 
     Minimium time is 20 ms.
    */
    LOCAL_PORT_RESPONSE_TIME_20_MS = 0,
    /** 
     Minimium time is 200 ms.
    */
    LOCAL_PORT_RESPONSE_TIME_200_MS = 1
};

class CGXDLMSIECOpticalPortSetup : public CGXObject
{
	basic_string<char> m_Password2;
    basic_string<char> m_Password5;
    OPTICAL_PROTOCOL_MODE m_DefaultMode;
    BAUDRATE m_DefaultBaudrate;
    BAUDRATE m_ProposedBaudrate;
    LOCAL_PORT_RESPONSE_TIME m_ResponseTime;
    basic_string<char> m_DeviceAddress;
    basic_string<char> m_Password1;

	void Init()
	{
		m_DefaultMode = OPTICAL_PROTOCOL_MODE_DEFAULT;
		m_DefaultBaudrate = BAUDRATE_300;
		m_ProposedBaudrate = BAUDRATE_9600;
	}

public:	
	//Constructor.
	CGXDLMSIECOpticalPortSetup() : CGXObject(OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, "0.0.20.0.0.255")
	{
		Init();
	}

	//SN Constructor.
	CGXDLMSIECOpticalPortSetup(unsigned short sn) : CGXObject(OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, sn)
	{
		Init();
	}

	//LN Constructor.
	CGXDLMSIECOpticalPortSetup(basic_string<char> ln) : CGXObject(OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, ln)
	{
		Init();
	}

	OPTICAL_PROTOCOL_MODE GetDefaultMode()
    {
        return m_DefaultMode;
    }
    void SetDefaultMode(OPTICAL_PROTOCOL_MODE value)
    {
        m_DefaultMode = value;
    }

    BAUDRATE GetDefaultBaudrate()
    {
        return m_DefaultBaudrate;
    }
    void SetDefaultBaudrate(BAUDRATE value)
    {
        m_DefaultBaudrate = value;
    }

    BAUDRATE GetProposedBaudrate()
    {
        return m_ProposedBaudrate;
    }
    void SetProposedBaudrate(BAUDRATE value)
    {
        m_ProposedBaudrate = value;
    }

    LOCAL_PORT_RESPONSE_TIME GetResponseTime()
    {
        return m_ResponseTime;
    }
    void SetResponseTime(LOCAL_PORT_RESPONSE_TIME value)
    {
        m_ResponseTime = value;
    }

    basic_string<char> GetDeviceAddress()
    {
        return m_DeviceAddress;
    }
    void SetDeviceAddress(basic_string<char> value)
    {
        m_DeviceAddress = value;
    }

    basic_string<char> GetPassword1()
    {
        return m_Password1;
    }
    void SetPassword1(basic_string<char> value)
    {
        m_Password1 = value;
    }

    basic_string<char> GetPassword2()
    {
        return m_Password2;
    }
    void SetPassword2(basic_string<char> value)
    {
        m_Password2 = value;
    }

    basic_string<char> GetPassword5()
    {
        return m_Password5;
    }
    void SetPassword5(basic_string<char> value)
    {
        m_Password5 = value;
    }

    // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 9;
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
            type = DLMS_DATA_TYPE_ENUM;
            value = GetDefaultMode();
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = GetDefaultBaudrate();
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = GetProposedBaudrate();
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = GetResponseTime();
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;            
			value.Add(&m_DeviceAddress[0], m_DeviceAddress.size());
			return ERROR_CODES_OK;
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;
			value.Add(&m_Password1[0], m_Password1.size());
			return ERROR_CODES_OK;
        }
        if (index == 8)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;			
			value.Add(&m_Password2[0], m_Password2.size());
			return ERROR_CODES_OK;
        }
        if (index == 9)
        {
            type = DLMS_DATA_TYPE_OCTET_STRING;			
			value.Add(&m_Password5[0], m_Password5.size());
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
        else if (index == 2)
        {
			SetDefaultMode((OPTICAL_PROTOCOL_MODE) value.lVal);
			return ERROR_CODES_OK;
        }
        else if (index == 3)
        {
            SetDefaultBaudrate((BAUDRATE) value.lVal);
			return ERROR_CODES_OK;
        }
        else if (index == 4)
        {
            SetProposedBaudrate((BAUDRATE) value.lVal);
			return ERROR_CODES_OK;
        }
        else if (index == 5)
        {
            SetResponseTime((LOCAL_PORT_RESPONSE_TIME) value.lVal);
			return ERROR_CODES_OK;
        }
        else if (index == 6)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
			SetDeviceAddress(tmp.strVal);
			return ERROR_CODES_OK;
        }
        else if (index == 7)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
            SetPassword1(tmp.strVal);
			return ERROR_CODES_OK;
        }
        else if (index == 8)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
            SetPassword2(tmp.strVal);
			return ERROR_CODES_OK;
        }
        else if (index == 9)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp);
            SetPassword5(tmp.strVal);
			return ERROR_CODES_OK;
        }			
		return ERROR_CODES_INVALID_PARAMETER;
    }
};
