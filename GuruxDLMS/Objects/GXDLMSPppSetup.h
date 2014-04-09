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

#include "GXDLMSPppSetupIPCPOption.h"
#include "GXDLMSPppSetupLcpOption.h"
/** 
PPP Authentication Type
 */
enum PPP_AUTHENTICATION_TYPE
{
    /** 
     No authentication.
    */
    PPP_AUTHENTICATION_TYPE_NONE = 0,
    /** 
     PAP Login
    */
    PPP_AUTHENTICATION_TYPE_PAP = 1,
    /** 
     CHAP-algorithm
    */
    PPP_AUTHENTICATION_TYPE_CHAP = 2
};

class CGXDLMSPppSetup : public CGXDLMSObject
{
	vector<CGXDLMSPppSetupIPCPOption> m_IPCPOptions;
    string m_PHYReference;
    vector<CGXDLMSPppSetupLcpOption> m_LCPOptions;
    vector<unsigned char> m_UserName;
    vector<unsigned char> m_Password;
	PPP_AUTHENTICATION_TYPE m_Authentication;
    
public:	
	//Constructor.
	CGXDLMSPppSetup();

	//SN Constructor.
	CGXDLMSPppSetup(unsigned short sn);

	//LN Constructor.
	CGXDLMSPppSetup(basic_string<char> ln);

	PPP_AUTHENTICATION_TYPE GetAuthentication();
    void SetAuthentication(PPP_AUTHENTICATION_TYPE value);
    
    /** 
    PPP authentication procedure user name.
   */    
    vector<unsigned char> GetUserName();    
    void SetUserName(vector<unsigned char> value);
    
    /** 
     PPP authentication procedure password.
    */
    vector<unsigned char>& GetPassword();  
	void SetPassword(vector<unsigned char> value);

	string GetPHYReference();    
	void SetPHYReference(string value);

    vector<CGXDLMSPppSetupLcpOption>& GetLCPOptions();
    vector<CGXDLMSPppSetupIPCPOption>& GetIPCPOptions();
    
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
