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
#include "GXDLMSModemConfiguration.h"
#include "../GXDLMSConverter.h"
#include <sstream> 

void CGXDLMSModemConfiguration::Init()
{
    m_CommunicationSpeed = BAUDRATE_9600;
	m_ModemProfile.push_back("OK");
	m_ModemProfile.push_back("CONNECT");
	m_ModemProfile.push_back("RING");
	m_ModemProfile.push_back("NO CARRIER");
	m_ModemProfile.push_back("ERROR");
	m_ModemProfile.push_back("CONNECT 1200");
	m_ModemProfile.push_back("NO DIAL TONE");
	m_ModemProfile.push_back("BUSY");
	m_ModemProfile.push_back("NO ANSWER");
	m_ModemProfile.push_back("CONNECT 600");
	m_ModemProfile.push_back("CONNECT 2400");
	m_ModemProfile.push_back("CONNECT 4800");
	m_ModemProfile.push_back("CONNECT 9600");
	m_ModemProfile.push_back("CONNECT 14 400");
	m_ModemProfile.push_back("CONNECT 28 800");
	m_ModemProfile.push_back("CONNECT 33 600");
	m_ModemProfile.push_back("CONNECT 56 000");
}

// Constructor.
CGXDLMSModemConfiguration::CGXDLMSModemConfiguration() : CGXDLMSObject(OBJECT_TYPE_MODEM_CONFIGURATION, "0.0.2.0.0.255")
{
    Init();
}

/**  
 Constructor.
 @param ln Logican Name of the object.
*/
CGXDLMSModemConfiguration::CGXDLMSModemConfiguration(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_MODEM_CONFIGURATION, ln)
{   
    Init();
}

/**  
 Constructor.
 @param ln Logican Name of the object.
 @param sn Short Name of the object.
*/
CGXDLMSModemConfiguration::CGXDLMSModemConfiguration(int sn) : CGXDLMSObject(OBJECT_TYPE_MODEM_CONFIGURATION, sn)
{        
    Init();
}   

BAUDRATE CGXDLMSModemConfiguration::GetCommunicationSpeed()
{
    return m_CommunicationSpeed;
}
void CGXDLMSModemConfiguration::SetCommunicationSpeed(BAUDRATE value)
{
    m_CommunicationSpeed = value;
}

vector<CGXDLMSModemInitialisation>& CGXDLMSModemConfiguration::GetInitialisationStrings()
{
    return m_InitialisationStrings;
}
void CGXDLMSModemConfiguration::SetInitialisationStrings(vector<CGXDLMSModemInitialisation>& value)
{
    m_InitialisationStrings = value;
}

vector< basic_string<char> > CGXDLMSModemConfiguration::GetModemProfile()
{
    return m_ModemProfile;
}

void CGXDLMSModemConfiguration::SetModemProfile(vector< basic_string<char> >& value)
{
    m_ModemProfile = value;
}              

// Returns amount of attributes.
int CGXDLMSModemConfiguration::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSModemConfiguration::GetMethodCount()
{
    return 0;
}    

void CGXDLMSModemConfiguration::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	values.push_back(CGXDLMSConverter::ToString(m_CommunicationSpeed));
	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<CGXDLMSModemInitialisation>::iterator it = m_InitialisationStrings.begin(); it != m_InitialisationStrings.end(); ++it)
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
	for(vector< basic_string<char> >::iterator it = m_ModemProfile.begin(); it != m_ModemProfile.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;
		sb.write(it->c_str(), it->size());
	}
	sb << ']';
	values.push_back(sb.str());		

}

void CGXDLMSModemConfiguration::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//CommunicationSpeed
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //InitialisationStrings
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //ModemProfile
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
}

int CGXDLMSModemConfiguration::GetDataType(int index, DLMS_DATA_TYPE& type)
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
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSModemConfiguration::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
    if (index == 1)
    {
        GXHelpers::AddRange(value.byteArr, m_LN, 6);
        value.vt = DLMS_DATA_TYPE_OCTET_STRING;
        return ERROR_CODES_OK;
    }
    if (index == 2)
    {
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        //Add count
		int ret;
        int cnt = m_InitialisationStrings.size();
        CGXOBISTemplate::SetObjectCount(cnt, data);
        for (vector<CGXDLMSModemInitialisation>::iterator it = m_InitialisationStrings.begin(); 
            it != m_InitialisationStrings.end(); ++it)
        {
            data.push_back(DLMS_DATA_TYPE_STRUCTURE);
            data.push_back(3); //Count                        
            if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->GetRequest())) != 0 ||
				(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->GetResponse())) != 0 ||
				(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, it->GetDelay())) != 0)
			{
				return ret;
			}
        }
        value = data;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {            
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        //Add count
		int ret;
        int cnt = m_ModemProfile.size();
        CGXOBISTemplate::SetObjectCount(cnt, data);
        //for(String it : m_ModemProfile)
		for (vector< basic_string<char> >::iterator it = m_ModemProfile.begin(); 
            it != m_ModemProfile.end(); ++it)
        {
            if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, *it)) != 0)
			{
				return ret;
			}
        }
        value = data;
		return ERROR_CODES_OK;
    }
    return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSModemConfiguration::SetValue(int index, CGXDLMSVariant& value)
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
		m_CommunicationSpeed = (BAUDRATE) value.bVal;
		return ERROR_CODES_OK;
    }
    else if (index == 3)
    {
        m_InitialisationStrings.clear();  
		int ret;
		for (vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
		{
            CGXDLMSModemInitialisation item;                                        
			CGXDLMSVariant tmp;
			if((ret = CGXDLMSClient::ChangeType(it->Arr[0].byteArr, DLMS_DATA_TYPE_STRING, tmp)) != ERROR_CODES_OK)
			{
				return ret;
			}
			item.SetRequest(tmp.ToString());
			if((ret = CGXDLMSClient::ChangeType(it->Arr[1].byteArr, DLMS_DATA_TYPE_STRING, tmp)) != ERROR_CODES_OK)
			{
				return ret;
			}
			item.SetResponse(tmp.ToString());
            if (it->Arr.size() > 2)
            {
                item.SetDelay(it->Arr[2].uiVal);
            }
            m_InitialisationStrings.push_back(item);
        }
		return ERROR_CODES_OK;
    }
    else if (index == 4)
    {
        m_ModemProfile.clear();
		int ret;
        for (vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)			
        {
			CGXDLMSVariant tmp;
			if((ret = CGXDLMSClient::ChangeType(it->byteArr, DLMS_DATA_TYPE_STRING, tmp)) != ERROR_CODES_OK)
			{
				return ret;
			}
            m_ModemProfile.push_back(tmp.ToString());
        }
		return ERROR_CODES_OK;
    }
    return ERROR_CODES_INVALID_PARAMETER;
}
