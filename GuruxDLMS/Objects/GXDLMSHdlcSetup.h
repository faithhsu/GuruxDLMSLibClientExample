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

class CGXDLMSHdlcSetup : public CGXDLMSObject
{
	int m_InactivityTimeout;
    int m_DeviceAddress;
    int m_MaximumInfoLengthTransmit;
    BAUDRATE m_CommunicationSpeed;
    int m_WindowSizeTransmit;
    int m_WindowSizeReceive;
    int m_InterCharachterTimeout;
    int m_MaximumInfoLengthReceive;

public:	
	//Constructor.
	CGXDLMSHdlcSetup();

	//SN Constructor.
	CGXDLMSHdlcSetup(unsigned short sn);

	//LN Constructor.
	CGXDLMSHdlcSetup(basic_string<char> ln);

	BAUDRATE GetCommunicationSpeed();
    
	void SetCommunicationSpeed(BAUDRATE value);

    int GetWindowSizeTransmit();   
	void SetWindowSizeTransmit(int value);

    int GetWindowSizeReceive();    
	void SetWindowSizeReceive(int value);
    int GetMaximumInfoLengthTransmit();
    void SetMaximumInfoLengthTransmit(int value);
    int GetMaximumInfoLengthReceive();
	void SetMaximumInfoLengthReceive(int value);

    int GetInterCharachterTimeout();
    void SetInterCharachterTimeout(int value);
    

    int GetInactivityTimeout();
    void SetInactivityTimeout(int value);
    
    int GetDeviceAddress();
    void SetDeviceAddress(int value);

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
