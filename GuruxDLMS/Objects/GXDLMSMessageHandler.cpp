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

#include "GXDLMSMessageHandler.h"
#include "../GXDLMSClient.h"
#include <sstream> 

//Constructor.
CGXDLMSMessageHandler::CGXDLMSMessageHandler() : CGXDLMSObject(OBJECT_TYPE_MESSAGE_HANDLER)
{
}

//SN Constructor.
CGXDLMSMessageHandler::CGXDLMSMessageHandler(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_MESSAGE_HANDLER, sn)
{

}

//LN Constructor.
CGXDLMSMessageHandler::CGXDLMSMessageHandler(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_MESSAGE_HANDLER, ln)
{

}

vector<pair<CGXDateTime, CGXDateTime> >& CGXDLMSMessageHandler::GetListeningWindow()
{
    return m_ListeningWindow;
}

vector<string>& CGXDLMSMessageHandler::GetAllowedSenders()
{
    return m_AllowedSenders;
}    

vector<std::pair<string, std::pair<int, CGXDLMSScriptAction> > >& CGXDLMSMessageHandler::GetSendersAndActions()
{
    return m_SendersAndActions;
}

// Returns amount of attributes.
int CGXDLMSMessageHandler::GetAttributeCount()
{
	return 4;
}

// Returns amount of methods.
int CGXDLMSMessageHandler::GetMethodCount()
{
	return 0;
}

void CGXDLMSMessageHandler::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);

	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<pair<CGXDateTime, CGXDateTime> >::iterator it = m_ListeningWindow.begin(); it != m_ListeningWindow.end(); ++it)
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
	sb.str(std::string());

	sb << '[';
	empty = true;
	for(vector<string>::iterator it = m_AllowedSenders.begin(); it != m_AllowedSenders.end(); ++it)
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

	sb.str(std::string());
	sb << '[';
	empty = true;
	for(vector<std::pair<string, std::pair<int, CGXDLMSScriptAction> > >::iterator it = m_SendersAndActions.begin(); it != m_SendersAndActions.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;		
		sb.write(it->first.c_str(), it->first.size());
	}
	sb << ']';
	values.push_back(sb.str());	
}

void CGXDLMSMessageHandler::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//ListeningWindow
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //AllowedSenders
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //SendersAndActions
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
}

int CGXDLMSMessageHandler::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
	//ListeningWindow
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }
    //AllowedSenders
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }
    //SendersAndActions
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }        
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSMessageHandler::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {
        //TODO: value = m_ListeningWindow;
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        //TODO: value = m_AllowedSenders;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        //TODO: value = m_SendersAndActions;
		return ERROR_CODES_OK;
    }    
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMessageHandler::SetValue(int index, CGXDLMSVariant& value)
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
        m_ListeningWindow.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
            for(vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
            {
				CGXDLMSVariant tmp;				
				CGXDLMSClient::ChangeType(it->Arr[0].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
				CGXDateTime start = tmp.dateTime;
				CGXDLMSClient::ChangeType(it->Arr[1].byteArr, DLMS_DATA_TYPE_DATETIME, tmp);
                CGXDateTime end = tmp.dateTime;
				m_ListeningWindow.push_back(std::pair<CGXDateTime, CGXDateTime>(start, end));
            }
        }

    }
    else if (index == 3)
    {
		m_AllowedSenders.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {            
            for(vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
            {				
				m_AllowedSenders.push_back((char*) &it->byteArr[0]);
            }            
        }
    }
    else if (index == 4)
    {
        m_SendersAndActions.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {                    
            for(vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
            {
				string id((char*) &it->Arr[0].byteArr[0]);
                //Object[] tmp2 = (Object[]) tmp[1];
                /*TODO:
                KeyValuePair<int, GXDLMSScriptAction> executed_script = new KeyValuePair<int, GXDLMSScriptAction>(Convert.ToInt32(tmp2[1], tmp2[2]));
                m_SendersAndActions.Add(new KeyValuePair<string, KeyValuePair<int, GXDLMSScriptAction>>(id, tmp[1] as GXDateTime));
                 * */
            }
        }
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}
