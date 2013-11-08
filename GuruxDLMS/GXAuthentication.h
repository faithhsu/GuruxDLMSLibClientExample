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

#include "GXDLMSVariant.h"

class GXAuthentication
{
	CGXDLMSVariant m_ClientID;
    GXDLMS_AUTHENTICATION m_Type;
	basic_string<char> m_Password;
public:
	//Constructor.
	GXAuthentication(void)
	{
	}

	//Constructor.
	GXAuthentication(GXDLMS_AUTHENTICATION type, std::basic_string<char> password, CGXDLMSVariant clientID)
	{
		m_Type = type;
		m_ClientID = clientID;
	}
	

	/// <summary>
    /// Authentication type
    /// </summary>
    GXDLMS_AUTHENTICATION GetType()
	{
		return m_Type;
	}

	/// <summary>
    /// Authentication type
    /// </summary>
    void SetType(GXDLMS_AUTHENTICATION value)
	{
		m_Type = value;
	}

    /// <summary>
    /// Client address.
    /// </summary>
    CGXDLMSVariant GetClientID()
    {
        return m_ClientID;
    }

    /// <summary>
    /// Client address.
    /// </summary>
    void SetClientID(CGXDLMSVariant value)
    {
        m_ClientID = value;
    }

    /// <summary>
    /// Get Used password.
    /// </summary>
    basic_string<char> GetPassword()
    {
		return m_Password;
    } 

	/// <summary>
    /// Set Used password.
    /// </summary>
    void SetPassword(basic_string<char> value)
    {
		m_Password = value;
    } 
};
