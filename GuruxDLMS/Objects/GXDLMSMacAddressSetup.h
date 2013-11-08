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

class CGXDLMSMacAddressSetup : public CGXObject
{
	basic_string<char> m_MacAddress;
public:
    /**  
     Constructor.
    */
	CGXDLMSMacAddressSetup() : CGXObject(OBJECT_TYPE_MAC_ADDRESS_SETUP, "0.0.25.2.0.255")
    {        
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSMacAddressSetup(basic_string<char> ln) : CGXObject(OBJECT_TYPE_MAC_ADDRESS_SETUP, ln)
    {
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
	CGXDLMSMacAddressSetup(int sn) : CGXObject(OBJECT_TYPE_MAC_ADDRESS_SETUP, sn)
    {
        
    }

    /** 
     Value of COSEM Data object.
    */
    basic_string<char> GetMacAddress()
    {
        return m_MacAddress;
    }
    void SetMacAddress(basic_string<char> value)
    {
        m_MacAddress = value;
    }

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 2;
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
            type = DLMS_DATA_TYPE_ARRAY;
			basic_string<char> add = GetMacAddress();
			GXHelpers::Replace(add, ":", ".");			
			vector<unsigned char> data;
			int ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, add);
			value = data;
			return ret;
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
			CGXDLMSVariant newValue;
			int ret = CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_OCTET_STRING, newValue);
			if (ret != ERROR_CODES_OK)
			{
				return ret;
			}
			basic_string<char> add = newValue.ToString();
			GXHelpers::Replace(add, ".", ":");
            SetMacAddress(add);
			return ERROR_CODES_OK;
        }
		return ERROR_CODES_INVALID_PARAMETER;
	}
};
