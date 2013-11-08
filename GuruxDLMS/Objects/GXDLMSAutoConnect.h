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
#include "../GXDateTime.h"
#include "../GXOBISTemplate.h"
#include "../GXDLMSClient.h"

enum AUTOCONNECTMODE
{
	/*
     * No auto dialling,
     */
    AUTOCONNECTMODE_NO_AUTO_DIALLING = 0,
    /**
     * Auto dialling allowed anytime,
     */
    AUTOCONNECTMODE_AUTO_DIALLING_ALLOWED_ANYTIME = 1,
    /**
     * Auto dialling allowed within the validity time of the calling window.
     */
    AUTOCONNECTMODE_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 2,
    /**
     * “regular” auto dialling allowed within the validity time
     * of the calling window; “alarm” initiated auto dialling allowed anytime,
     */
    AUTOCONNECTMODE_REGULAR_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 3,
    /**
     * SMS sending via Public Land Mobile Network (PLMN),
     */
    AUTOCONNECTMODE_SMS_SENDING_PLMN = 4,
    /*
     * SMS sending via PSTN.
     */
    AUTOCONNECTMODE_SMS_SENDING_PSTN = 5,
    /*
     * Email sending.
     */
    AUTOCONNECTMODE_EMAIL_SENDING = 6
};

class CGXDLMSAutoConnect : public CGXObject
{
	AUTOCONNECTMODE Mode;
	std::vector<std::pair< CGXDateTime, CGXDateTime> > m_CallingWindow;	
    vector< basic_string<char> > m_Destinations;   
    int m_RepetitionDelay;
    int m_Repetitions;

	void Init()
	{
		Mode = AUTOCONNECTMODE_NO_AUTO_DIALLING;
		m_RepetitionDelay = m_Repetitions = 0;
	}

public:	
	//Constructor.
	CGXDLMSAutoConnect() : CGXObject(OBJECT_TYPE_AUTO_CONNECT, "0.0.2.1.0.255")
	{
	}

	//SN Constructor.
	CGXDLMSAutoConnect(unsigned short sn) : CGXObject(OBJECT_TYPE_AUTO_CONNECT, sn)
	{

	}

	//LN Constructor.
	CGXDLMSAutoConnect(basic_string<char> ln) : CGXObject(OBJECT_TYPE_AUTO_CONNECT, ln)
	{

	}

	AUTOCONNECTMODE GetMode()
    {
        return Mode;
    }
    void SetMode(AUTOCONNECTMODE value)
    {
        Mode = value;
    }

    int GetRepetitions()
    {
        return m_Repetitions;
    }
    void SetRepetitions(int value)
    {
        m_Repetitions = value;
    }

    int GetRepetitionDelay()
    {
        return m_RepetitionDelay;
    }
    void SetRepetitionDelay(int value)
    {
        m_RepetitionDelay = value;
    }
   
    std::vector<std::pair< CGXDateTime, CGXDateTime> >& GetCallingWindow()
    {
        return m_CallingWindow;
    }
    void SetCallingWindow(std::vector<std::pair< CGXDateTime, CGXDateTime> > value)
    {
        m_CallingWindow = value;
    }

    vector< basic_string<char> >& GetDestinations()
    {
        return m_Destinations;
    }

    void SetDestinations(vector< basic_string<char> >& value)
    {
        m_Destinations = value;
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
            type = DLMS_DATA_TYPE_ENUM;
            value = (unsigned char) GetMode();
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_UINT8;
            value = GetRepetitions();
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_UINT16;
            value = GetRepetitionDelay();
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            int cnt = m_CallingWindow.size();
			vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
            if (cnt != 0)
            {
				for (std::vector<std::pair< CGXDateTime, CGXDateTime> >::iterator it = m_CallingWindow.begin(); it != m_CallingWindow.end(); ++it)
                {
                    data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                    data.push_back(2); //Count
					CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->first); //start_time
					CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->second); //end_time                                        
                }
            }
            value = data;
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
            type = DLMS_DATA_TYPE_ARRAY;             
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            int cnt = m_Destinations.size();
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);				                			
			for (vector< basic_string<char> >::iterator it = m_Destinations.begin(); it != m_Destinations.end(); ++it)
            {			
				CGXDLMSVariant value;				
				value.Add(&(*it)[0], it->size());
				CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, value); //destination
            }
            value = data;
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
};
