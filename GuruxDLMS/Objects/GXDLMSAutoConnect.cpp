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
#include "GXDLMSAutoConnect.h"
#include <sstream> 

void CGXDLMSAutoConnect::Init()
{
	m_Mode = AUTOCONNECTMODE_NO_AUTO_DIALLING;
	m_RepetitionDelay = m_Repetitions = 0;
}

//Constructor.
CGXDLMSAutoConnect::CGXDLMSAutoConnect() : CGXDLMSObject(OBJECT_TYPE_AUTO_CONNECT, "0.0.2.1.0.255")
{
}

//SN Constructor.
CGXDLMSAutoConnect::CGXDLMSAutoConnect(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_AUTO_CONNECT, sn)
{

}

//LN Constructor.
CGXDLMSAutoConnect::CGXDLMSAutoConnect(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_AUTO_CONNECT, ln)
{

}

AUTOCONNECTMODE CGXDLMSAutoConnect::GetMode()
{
    return m_Mode;
}
void CGXDLMSAutoConnect::SetMode(AUTOCONNECTMODE value)
{
    m_Mode = value;
}

int CGXDLMSAutoConnect::GetRepetitions()
{
    return m_Repetitions;
}
void CGXDLMSAutoConnect::SetRepetitions(int value)
{
    m_Repetitions = value;
}

int CGXDLMSAutoConnect::GetRepetitionDelay()
{
    return m_RepetitionDelay;
}
void CGXDLMSAutoConnect::SetRepetitionDelay(int value)
{
    m_RepetitionDelay = value;
}

std::vector<std::pair< CGXDateTime, CGXDateTime> >& CGXDLMSAutoConnect::GetCallingWindow()
{
    return m_CallingWindow;
}
void CGXDLMSAutoConnect::SetCallingWindow(std::vector<std::pair< CGXDateTime, CGXDateTime> > value)
{
    m_CallingWindow = value;
}

vector< basic_string<char> >& CGXDLMSAutoConnect::GetDestinations()
{
    return m_Destinations;
}

void CGXDLMSAutoConnect::SetDestinations(vector< basic_string<char> >& value)
{
    m_Destinations = value;
}

// Returns amount of attributes.
int CGXDLMSAutoConnect::GetAttributeCount()
{
	return 6;
}

// Returns amount of methods.
int CGXDLMSAutoConnect::GetMethodCount()
{
	return 0;
}

void CGXDLMSAutoConnect::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);	
	values.push_back(CGXDLMSVariant(m_Mode).ToString());
	values.push_back(CGXDLMSVariant(m_Repetitions).ToString());
	values.push_back(CGXDLMSVariant(m_RepetitionDelay).ToString());
	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<pair< CGXDateTime, CGXDateTime> >::iterator it = m_CallingWindow.begin(); it != m_CallingWindow.end(); ++it)
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

	//Clear str.
	sb.str(std::string());		
	sb << '[';
	empty = true;
	for(vector< basic_string<char> >::iterator it = m_Destinations.begin(); it != m_Destinations.end(); ++it)
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

void CGXDLMSAutoConnect::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
	}
	//Mode
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //Repetitions
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //RepetitionDelay
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //CallingWindow
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //Destinations
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
}

int CGXDLMSAutoConnect::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ENUM;
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_UINT8;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT16;
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_ARRAY;             
		return ERROR_CODES_OK;
    }
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSAutoConnect::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {
        value = (unsigned char) GetMode();
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        value = GetRepetitions();
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        value = GetRepetitionDelay();
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {
        int cnt = m_CallingWindow.size();
		vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
		int ret;
        //Add count            
        CGXOBISTemplate::SetObjectCount(cnt, data);
        if (cnt != 0)
        {
			for (std::vector<std::pair< CGXDateTime, CGXDateTime> >::iterator it = m_CallingWindow.begin(); it != m_CallingWindow.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(2); //Count
				if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->first)) != 0 || //start_time
					(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->second)) != 0) //end_time
				{
					return ret;
				}
            }
        }
        value = data;
		return ERROR_CODES_OK;
    }
    if (index == 6)
    {
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
		int ret;
        int cnt = m_Destinations.size();
        //Add count            
        CGXOBISTemplate::SetObjectCount(cnt, data);				                			
		for (vector< basic_string<char> >::iterator it = m_Destinations.begin(); it != m_Destinations.end(); ++it)
        {			
			CGXDLMSVariant value;				
			value.Add(&(*it)[0], it->size());
			if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, value)) != 0) //destination
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
int CGXDLMSAutoConnect::SetValue(int index, CGXDLMSVariant& value)
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
		SetMode((AUTOCONNECTMODE) value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 3)
    {
		SetRepetitions(value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 4)
    {
        SetRepetitionDelay(value.lVal);
		return ERROR_CODES_OK;
    }
    else if (index == 5)
    {
        m_CallingWindow.clear();
		for (vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
        {
			CGXDLMSVariant tmp;
			CGXDLMSClient::ChangeType(item->Arr[0].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
			CGXDateTime start = tmp.dateTime;
			CGXDLMSClient::ChangeType(item->Arr[1].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
			CGXDateTime end = tmp.dateTime;				
            m_CallingWindow.push_back(std::make_pair(start, end));
        }
		return ERROR_CODES_OK;
    }
    else if (index == 6)
	{			
        m_Destinations.clear();
        vector< basic_string<char> > items;
		for (vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
        {
			CGXDLMSVariant value;
			CGXDLMSClient::ChangeType(item->byteArr, DLMS_DATA_TYPE_STRING, value);
            items.push_back(value.ToString());
        }
        SetDestinations(items);
		return ERROR_CODES_OK;
    }
	return ERROR_CODES_INVALID_PARAMETER;
}
