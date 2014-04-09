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

class CGXDLMSMBusClient : public CGXDLMSObject
{
	long m_CapturePeriod;
    int m_PrimaryAddress;    
    string m_MBusPortReference;
    vector<pair<string, string> > m_CaptureDefinition;
    long m_IdentificationNumber;
    int m_ManufacturerID;
    int m_DataHeaderVersion;
    int m_DeviceType;
    int m_AccessNumber;
    int m_Status;
    int m_Alarm;

public:	
	//Constructor.
	CGXDLMSMBusClient();

	//SN Constructor.
	CGXDLMSMBusClient(unsigned short sn);

	//LN Constructor.
	CGXDLMSMBusClient(basic_string<char> ln);

	/** 
    Provides reference to an "M-Bus master port setup" object, used to configure
    an M-Bus port, each interface allowing to exchange data with one or more
    M-Bus slave devices
*/
    string GetMBusPortReference();
    void SetMBusPortReference(string value);
    
    vector<pair<string, string> >& GetCaptureDefinition();
    
	long GetCapturePeriod();    
	void SetCapturePeriod(long value);

    int GetPrimaryAddress();
    void SetPrimaryAddress(int value);
    
    long GetIdentificationNumber();
    void SetIdentificationNumber(long value);
    
	int GetManufacturerID();    
	void SetManufacturerID(int value);

    /*
     * Carries the Version element of the data header as specified in EN
     * 13757-3 sub-clause 5.6.
     */
    int GetDataHeaderVersion();
	void SetDataHeaderVersion(int value);

    int GetDeviceType();
	void SetDeviceType(int value);

    int GetAccessNumber();
	void SetAccessNumber(int value);

    int GetStatus();
	void SetStatus(int value);

    int GetAlarm();
    void SetAlarm(int value);

    // Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	//Get attribute values of object.
	void GetValues(vector<string>& values);

	void GetAttributeIndexToRead(vector<int>& attributes);

	int GetDataType(int index, DLMS_DATA_TYPE& type);
    
	// Returns value of given attribute.
	int GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
