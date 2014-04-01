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

/** 
 Defines the protocol used by the meter on the port.
*/
enum OPTICAL_PROTOCOL_MODE
{
    /**         
     Protocol according to IEC 62056-21 (modes A…E),
    */
    OPTICAL_PROTOCOL_MODE_DEFAULT = 0,
    /** 
     Protocol according to IEC 62056-46. 
     Using this enumeration value all other attributes of this IC are not applicable.
    */
    OPTICAL_PROTOCOL_MODE_NET = 1,
    /** 
     Protocol not specified. Using this enumeration value, 
     ProposedBaudrate is used for setting the communication speed on the port. 
     All other attributes are not applicable.
    */
    OPTICAL_PROTOCOL_MODE_UNKNOWN = 2
};

enum LOCAL_PORT_RESPONSE_TIME
{
    /** 
     Minimium time is 20 ms.
    */
    LOCAL_PORT_RESPONSE_TIME_20_MS = 0,
    /** 
     Minimium time is 200 ms.
    */
    LOCAL_PORT_RESPONSE_TIME_200_MS = 1
};

class CGXDLMSIECOpticalPortSetup : public CGXDLMSObject
{
	basic_string<char> m_Password2;
    basic_string<char> m_Password5;
    OPTICAL_PROTOCOL_MODE m_DefaultMode;
    BAUDRATE m_DefaultBaudrate;
    BAUDRATE m_ProposedBaudrate;
    LOCAL_PORT_RESPONSE_TIME m_ResponseTime;
    basic_string<char> m_DeviceAddress;
    basic_string<char> m_Password1;

	void Init();

public:	
	//Constructor.
	CGXDLMSIECOpticalPortSetup();
	//SN Constructor.
	CGXDLMSIECOpticalPortSetup(unsigned short sn);
	//LN Constructor.
	CGXDLMSIECOpticalPortSetup(basic_string<char> ln);

	OPTICAL_PROTOCOL_MODE GetDefaultMode();
    void SetDefaultMode(OPTICAL_PROTOCOL_MODE value);
    
	BAUDRATE GetDefaultBaudrate();
    void SetDefaultBaudrate(BAUDRATE value);
    
    BAUDRATE GetProposedBaudrate();
    void SetProposedBaudrate(BAUDRATE value);

    LOCAL_PORT_RESPONSE_TIME GetResponseTime();    
    void SetResponseTime(LOCAL_PORT_RESPONSE_TIME value);    

    basic_string<char> GetDeviceAddress();
    void SetDeviceAddress(basic_string<char> value);
    
    basic_string<char> GetPassword1();    
	void SetPassword1(basic_string<char> value);

    basic_string<char> GetPassword2();
    void SetPassword2(basic_string<char> value);

    basic_string<char> GetPassword5();
    void SetPassword5(basic_string<char> value);

    // Returns amount of attributes.
	int GetAttributeCount();
	
    // Returns amount of methods.
	int GetMethodCount();

	//Get attribute values of object.
	void GetValues(vector<string>& values);

	void GetAttributeIndexToRead(vector<int>& attributes);

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
