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

#pragma once

#include "GXDLMSObject.h"

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

class CGXDLMSAutoConnect : public CGXDLMSObject
{
	AUTOCONNECTMODE Mode;
	std::vector<std::pair< CGXDateTime, CGXDateTime> > m_CallingWindow;	
    vector< basic_string<char> > m_Destinations;   
    int m_RepetitionDelay;
    int m_Repetitions;

	void Init();

public:	
	//Constructor.
	CGXDLMSAutoConnect();

	//SN Constructor.
	CGXDLMSAutoConnect(unsigned short sn);

	//LN Constructor.
	CGXDLMSAutoConnect(basic_string<char> ln);

	AUTOCONNECTMODE GetMode();
    void SetMode(AUTOCONNECTMODE value);
    
    int GetRepetitions();
    
	void SetRepetitions(int value);

    int GetRepetitionDelay();
    void SetRepetitionDelay(int value);
    
    std::vector<std::pair< CGXDateTime, CGXDateTime> >& GetCallingWindow();
    void SetCallingWindow(std::vector<std::pair< CGXDateTime, CGXDateTime> > value);

    vector< basic_string<char> >& GetDestinations();

	void SetDestinations(vector< basic_string<char> >& value);

    // Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	void GetAttributeIndexToRead(vector<int>& attributes);
	
	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
