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

enum AUTO_CONNECT_MODE 
{
    /*
     * No auto dialling,
     */
    AUTO_CONNECT_MODE_NO_AUTO_DIALLING = 0,
    /**
     * Auto dialling allowed anytime,
     */
    AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_ANYTIME = 1,
    /**
     * Auto dialling allowed within the validity time of the calling window.
     */
    AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 2,
    /**
     * “regular” auto dialling allowed within the validity time
     * of the calling window; “alarm” initiated auto dialling allowed anytime,
     */
    AUTO_CONNECT_MODE_REGULAR_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 3,
    /**
     * SMS sending via Public Land Mobile Network (PLMN),
     */
    AUTO_CONNECT_MODE_SMS_SENDING_PLMN = 4,
    /*
     * SMS sending via PSTN.
     */
    AUTO_CONNECT_MODE_SMS_SENDING_PSTN = 5,
    /*
     * Email sending.
     */
    AUTO_CONNECT_MODE_EMAIL_SENDING = 6
};

enum AUTO_ANSWER_STATUS
{
    AUTO_ANSWER_STATUS_INACTIVE = 0,
    AUTO_ANSWER_STATUS_ACTIVE = 1,
    AUTO_ANSWER_STATUS_LOCKED = 2
};

class CGXDLMSAutoAnswer : public CGXObject
{
	int m_NumberOfRingsInListeningWindow, m_NumberOfRingsOutListeningWindow;
	AUTO_CONNECT_MODE m_Mode;
    std::vector<std::pair< CGXDateTime, CGXDateTime> > m_ListeningWindow;
    AUTO_ANSWER_STATUS m_Status;
    int m_NumberOfCalls;
    CGXDLMSVariant m_NumberOfRings;
    
	void Init()
	{
		m_NumberOfRingsInListeningWindow = m_NumberOfRingsOutListeningWindow = 0;
		m_Mode = AUTO_CONNECT_MODE_NO_AUTO_DIALLING;
		m_Status = AUTO_ANSWER_STATUS_INACTIVE;
		m_NumberOfCalls = 0;
		m_NumberOfRings = 0;
	}

public:
    /**  
     Constructor.
    */
	CGXDLMSAutoAnswer() : CGXObject(OBJECT_TYPE_AUTO_ANSWER, "0.0.2.2.0.255")
    {
		Init();		
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSAutoAnswer(basic_string<char> ln) : CGXObject(OBJECT_TYPE_AUTO_ANSWER, ln)
    {
		Init();
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSAutoAnswer(int sn) : CGXObject(OBJECT_TYPE_AUTO_ANSWER, sn)
    {        
		Init();
    }

    AUTO_CONNECT_MODE GetMode()
    {
        return m_Mode;
    }
    void SetMode(AUTO_CONNECT_MODE value)
    {
        m_Mode = value;
    }

    std::vector<std::pair< CGXDateTime, CGXDateTime> >& GetListeningWindow()
    {
        return m_ListeningWindow;
    }
    void SetListeningWindow(std::vector<std::pair< CGXDateTime, CGXDateTime> >& value)
    {
        m_ListeningWindow = value;
    }

    AUTO_ANSWER_STATUS GetStatus()
    {
        return m_Status;
    }
    void SetStatus(AUTO_ANSWER_STATUS value)
    {
        m_Status = value;
    }

    int GetNumberOfCalls()
    {
        return m_NumberOfCalls;
    }
    void SetNumberOfCalls(int value)
    {
        m_NumberOfCalls = value;
    }	

    // Number of rings within the window defined by ListeningWindow.
    int GetNumberOfRingsInListeningWindow()
    {
        return m_NumberOfRingsInListeningWindow;
    }
    void SetNumberOfRingsInListeningWindow(int value)
    {
        m_NumberOfRingsInListeningWindow = value;
    }

    //Number of rings outside the window defined by ListeningWindow.
    int GetNumberOfRingsOutListeningWindow()
    {
        return m_NumberOfRingsOutListeningWindow;
    }
    void SetNumberOfRingsOutListeningWindow(int value)
    {
        m_NumberOfRingsOutListeningWindow = value;
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
            value = GetMode();
			return ERROR_CODES_OK;
        }    
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            int cnt = m_ListeningWindow.size();
			vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
			for (std::vector<std::pair< CGXDateTime, CGXDateTime> >::iterator it = 
				m_ListeningWindow.begin(); it != m_ListeningWindow.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(2); //Count
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).first); //start_time
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).second); //end_time
            }
            value = data;                
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = GetStatus();
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            type = DLMS_DATA_TYPE_UINT8;
            value = GetNumberOfCalls();
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {
			type = DLMS_DATA_TYPE_ARRAY;
            vector<unsigned char> data;
			data.push_back(DLMS_DATA_TYPE_STRUCTURE);
            CGXOBISTemplate::SetObjectCount(2, data);
			int ret;
            if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_NumberOfRingsInListeningWindow)) != ERROR_CODES_OK ||
				(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, m_NumberOfRingsOutListeningWindow)) != ERROR_CODES_OK)
			{
				return ret;
			}
            value = data;
			return ERROR_CODES_OK;  
        }
        return ERROR_CODES_INVALID_PARAMETER;
    }
    
    /*
     * Set value of given attribute.
     */
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
            SetMode((AUTO_CONNECT_MODE) value.lVal);
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            m_ListeningWindow.clear();
			for (vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
            {            
                CGXDLMSVariant start, end;
				CGXDLMSClient::ChangeType((*item).Arr[0].byteArr, DLMS_DATA_TYPE_DATETIME, start);
                CGXDLMSClient::ChangeType((*item).Arr[1].byteArr, DLMS_DATA_TYPE_DATETIME, end);
				m_ListeningWindow.push_back(std::pair< CGXDateTime, CGXDateTime>(start.dateTime, end.dateTime));
            }
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            SetStatus((AUTO_ANSWER_STATUS) value.lVal);
			return ERROR_CODES_OK;
        }
        if (index == 5)
        {
            SetNumberOfCalls(value.lVal);
			return ERROR_CODES_OK;
        }
        if (index == 6)
        {          
			m_NumberOfRingsInListeningWindow = m_NumberOfRingsOutListeningWindow = 0;
            if (value.vt != DLMS_DATA_TYPE_NONE)
            {
                m_NumberOfRingsInListeningWindow = value.Arr[0].bVal;
                m_NumberOfRingsOutListeningWindow = value.Arr[1].bVal;
            }           
			return ERROR_CODES_OK;
        }
        return ERROR_CODES_INVALID_PARAMETER;
    }
};
