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
#include "GXDLMSIp4SetupIpOption.h"

class CGXDLMSIp4Setup : public CGXDLMSObject
{
	string m_DataLinkLayerReference;
    long m_IPAddress;
    vector<unsigned long> m_MulticastIPAddress;
    vector<CGXDLMSIp4SetupIpOption> m_IPOptions;
    unsigned long m_SubnetMask;
    unsigned long m_GatewayIPAddress;
    bool m_UseDHCP;
    unsigned long m_PrimaryDNSAddress;
    unsigned long m_SecondaryDNSAddress;

	CGXDLMSVariant m_Value;
public:	
	//Constructor.
	CGXDLMSIp4Setup();

	//SN Constructor.
	CGXDLMSIp4Setup(unsigned short sn);

	//LN Constructor.
	CGXDLMSIp4Setup(basic_string<char> ln);

	string& GetDataLinkLayerReference();
    void SetDataLinkLayerReference(string value);
    
    unsigned long GetIPAddress();   
    void SetIPAddress(unsigned long value);

    vector<unsigned long>& GetMulticastIPAddress();
    
    vector<CGXDLMSIp4SetupIpOption>& GetIPOptions();
    
    void SetIPOptions(vector<CGXDLMSIp4SetupIpOption> value);
    
    unsigned long GetSubnetMask();    
    void SetSubnetMask(unsigned long value);    

    unsigned long GetGatewayIPAddress();    
    void SetGatewayIPAddress(unsigned long value);
    
    bool GetUseDHCP();
    void SetUseDHCP(bool value);
    
    unsigned long GetPrimaryDNSAddress();
    void SetPrimaryDNSAddress(unsigned long value);
    
	unsigned long GetSecondaryDNSAddress();    
    void SetSecondaryDNSAddress(unsigned long value);

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
