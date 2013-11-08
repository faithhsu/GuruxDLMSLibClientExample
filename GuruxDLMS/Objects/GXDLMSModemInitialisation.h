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

class CGXDLMSModemInitialisation
{
	basic_string<char> m_Request;
    basic_string<char> m_Response;
    int m_Delay;

public:

	CGXDLMSModemInitialisation()
	{
		m_Delay = 0;
	}

    basic_string<char> GetRequest()
    {
        return m_Request;
    }
    void SetRequest(basic_string<char> value)
    {
        m_Request = value;
    }

    basic_string<char> GetResponse()
    {
        return m_Response;
    }
    void SetResponse(basic_string<char> value)
    {
        m_Response = value;
    }

    int GetDelay()
    {
        return m_Delay;
    }

    void SetDelay(int value)
    {
        m_Delay = value;
    }	
};