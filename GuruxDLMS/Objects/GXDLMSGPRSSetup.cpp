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
#include "GXDLMSGPRSSetup.h"

	//Constructor.
CGXDLMSGPRSSetup::CGXDLMSGPRSSetup() : CGXDLMSObject(OBJECT_TYPE_GPRS_SETUP)
{
}

//SN Constructor.
CGXDLMSGPRSSetup::CGXDLMSGPRSSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_GPRS_SETUP, sn)
{

}

//LN Constructor.
CGXDLMSGPRSSetup::CGXDLMSGPRSSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_GPRS_SETUP, ln)
{

}

string CGXDLMSGPRSSetup::GetAPN()
{
    return m_APN;
}
void CGXDLMSGPRSSetup::SetAPN(string value)
{
    m_APN = value;
}

long CGXDLMSGPRSSetup::GetPINCode()
{
    return m_PINCode;
}
void CGXDLMSGPRSSetup::SetPINCode(long value)
{
    m_PINCode = value;
}

CGXDLMSQualityOfService& CGXDLMSGPRSSetup::GetDefaultQualityOfService()
{
    return m_DefaultQualityOfService;
}

CGXDLMSQualityOfService& CGXDLMSGPRSSetup::GetRequestedQualityOfService()
{
    return m_RequestedQualityOfService;
}

// Returns amount of attributes.
int CGXDLMSGPRSSetup::GetAttributeCount()
{
	return 4;
}

// Returns amount of methods.
int CGXDLMSGPRSSetup::GetMethodCount()
{
	return 0;
}

void CGXDLMSGPRSSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//APN
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }            
    //PINCode
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //DefaultQualityOfService + RequestedQualityOfService
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
}

int CGXDLMSGPRSSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }  
    if (index == 3)
    {
		type = DLMS_DATA_TYPE_UINT16;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
		type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }  
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSGPRSSetup::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
    {
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {
        value = m_APN;
		return ERROR_CODES_OK;
    }  
    if (index == 3)
    {
        value = m_PINCode;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
		vector<unsigned char> data;									
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        data.push_back(2);
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);            
        data.push_back(5);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_DefaultQualityOfService.GetPrecedence());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_DefaultQualityOfService.GetDelay());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_DefaultQualityOfService.GetReliability());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_DefaultQualityOfService.GetPeakThroughput());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_DefaultQualityOfService.GetMeanThroughput());
        data.push_back(5);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_RequestedQualityOfService.GetPrecedence());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_RequestedQualityOfService.GetDelay());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_RequestedQualityOfService.GetReliability());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_RequestedQualityOfService.GetPeakThroughput());
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_RequestedQualityOfService.GetMeanThroughput());                
		value = data;
		return ERROR_CODES_OK;
    } 		
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSGPRSSetup::SetValue(int index, CGXDLMSVariant& value)
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
        if (value.vt == DLMS_DATA_TYPE_STRING)            
        {
            m_APN = value.ToString();
        }
        else
        {         
			CGXDLMSVariant tmp;
			int ret;
			if ((ret = CGXDLMSClient::ChangeType(value.byteArr, DLMS_DATA_TYPE_STRING, tmp)) != 0)
			{
				return ret;
			}
			m_APN = tmp.strVal;
        }
    }
    else if (index == 3)
    {            
		m_PINCode = value.uiVal;
    }
    else if (index == 4)
    {            			
		m_DefaultQualityOfService.SetPrecedence(value.Arr[0].Arr[0].iVal);
        m_DefaultQualityOfService.SetDelay(value.Arr[0].Arr[1].iVal);
        m_DefaultQualityOfService.SetReliability(value.Arr[0].Arr[2].iVal);
        m_DefaultQualityOfService.SetPeakThroughput(value.Arr[0].Arr[3].iVal);
        m_DefaultQualityOfService.SetMeanThroughput(value.Arr[0].Arr[4].iVal);

        m_RequestedQualityOfService.SetPrecedence(value.Arr[1].Arr[0].iVal);
        m_RequestedQualityOfService.SetDelay(value.Arr[1].Arr[1].iVal);
        m_RequestedQualityOfService.SetReliability(value.Arr[1].Arr[2].iVal);
        m_RequestedQualityOfService.SetPeakThroughput(value.Arr[1].Arr[3].iVal);
        m_RequestedQualityOfService.SetMeanThroughput(value.Arr[1].Arr[4].iVal);
    }	
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

