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

#include "GXDLMSPushSetup.h"
#include "../GXDLMSClient.h"
#include <sstream> 

//Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup() : CGXDLMSObject(OBJECT_TYPE_PUSH_SETUP)
{
	m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
}

//SN Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_PUSH_SETUP, sn)
{
	m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
}

//LN Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_PUSH_SETUP, ln)
{
	m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
}

// Returns amount of attributes.
int CGXDLMSPushSetup::GetAttributeCount()
{
	return 7;
}

// Returns amount of methods.
int CGXDLMSPushSetup::GetMethodCount()
{
	return 1;
}

void CGXDLMSPushSetup::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);

	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<CGXDLMSPushObject>::iterator it = m_PushObjectList.begin(); it != m_PushObjectList.end(); ++it)
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
	
	sb.str(string());
	sb << m_SendDestinationAndMethod.GetService();
	sb << " ";
	sb << m_SendDestinationAndMethod.GetDestination().c_str();
	sb << " ";
	sb << m_SendDestinationAndMethod.GetMessage();
	values.push_back(sb.str());

	sb.str(string());
	sb << '[';
	empty = true;
	for(vector<pair<CGXDateTime, CGXDateTime> >::iterator it = m_CommunicationWindow.begin(); it != m_CommunicationWindow.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;
		string str = it->first.ToString();
		sb.write(str.c_str(), str.size());
		sb << " ";
		str = it->second.ToString();
		sb.write(str.c_str(), str.size());
	}
	sb << ']';
	values.push_back(sb.str());
	
	values.push_back(CGXDLMSVariant(m_RandomisationStartInterval).ToString());
	values.push_back(CGXDLMSVariant(m_NumberOfRetries).ToString());
	values.push_back(CGXDLMSVariant(m_RepetitionDelay).ToString());
}

void CGXDLMSPushSetup::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//PushObjectList
    if (CanRead(2))
    {
        attributes.push_back(2);
    }

    //SendDestinationAndMethod
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //CommunicationWindow
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //RandomisationStartInterval
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //NumberOfRetries
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
    //RepetitionDelay
    if (CanRead(7))
    {
        attributes.push_back(7);
    }
}

int CGXDLMSPushSetup::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT16;
    } 
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

// Returns value of given attribute.
int CGXDLMSPushSetup::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {
        //TODO: value = m_PushObjectList;
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        //TODO: value = m_SendDestinationAndMethod;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        //TODO: value = m_CommunicationWindow;
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {
        value = m_RandomisationStartInterval;
		return ERROR_CODES_OK;
    }
    if (index == 6)
    {
        value = m_NumberOfRetries;
		return ERROR_CODES_OK;
    }
    if (index == 7)
    {
        value = m_RepetitionDelay;
		return ERROR_CODES_OK;
    }   
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSPushSetup::SetValue(int index, CGXDLMSVariant& value)
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
        m_PushObjectList.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
            for(vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
            {
                CGXDLMSPushObject obj;
				obj.SetType((OBJECT_TYPE) it->Arr[0].ToInteger());
				CGXDLMSVariant tmp;
				CGXDLMSClient::ChangeType(it->Arr[1].byteArr, DLMS_DATA_TYPE_BIT_STRING, tmp);
				obj.SetLogicalName(tmp.ToString());
                obj.SetAttributeIndex(it->Arr[2].ToInteger());
                obj.SetDataIndex(it->Arr[3].ToInteger());
                m_PushObjectList.push_back(obj);
            }
        }
    }
    else if (index == 3)
    {
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
			m_SendDestinationAndMethod.SetService((GXDLMS_SERVICE_TYPE) value.Arr[0].ToInteger());
			if (value.Arr[2].byteArr.size() == 0)
			{
				m_SendDestinationAndMethod.SetDestination("");
			}
			else
			{
				m_SendDestinationAndMethod.SetDestination((char*) &value.Arr[2].byteArr[0]);
			}
            m_SendDestinationAndMethod.SetMessage((GXDLMS_MESSAGE_TYPE) value.Arr[2].ToInteger());
        }
    }
    else if (index == 4)
    {
        m_CommunicationWindow.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
			int ret;
            for(vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
            {          
				CGXDLMSVariant tmp;
				if ((ret = CGXDLMSClient::ChangeType(it->Arr[0].byteArr, DLMS_DATA_TYPE_DATETIME, tmp)) != 0)
				{
					return ret;
				}
				CGXDateTime start = tmp.dateTime;
				if ((ret = CGXDLMSClient::ChangeType(it->Arr[1].byteArr, DLMS_DATA_TYPE_DATETIME, tmp)) != 0)
				{
					return ret;
				}
                CGXDateTime end = tmp.dateTime;
                m_CommunicationWindow.push_back(pair<CGXDateTime, CGXDateTime>(start, end));
            }
        }
    }
    else if (index == 5)
    {
        m_RandomisationStartInterval = value.ToInteger();
    }
    else if (index == 6)
    {
        m_NumberOfRetries = value.ToInteger();
    }
    else if (index == 7)
    {
        m_RepetitionDelay = value.ToInteger();
    }    
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}
