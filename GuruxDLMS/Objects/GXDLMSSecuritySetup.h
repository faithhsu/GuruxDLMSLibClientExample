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
    Security policy Enforces authentication and/or encryption algorithm provided with security_suite.
 */
enum SECURITY_POLICY
{
    SECURITY_POLICY_NOTHING,
    /** 
     All messages to be authenticated.
    */
    SECURITY_POLICY_AUTHENTICATED,
    /** 
     All messages to be encrypted.
    */
    SECURITY_POLICY_ENCRYPTED,
    /** 
     All messages to be authenticated and encrypted.
    */
    SECURITY_POLICY_AUTHENTICATED_ENCRYPTED
};


//Security suite Specifies authentication, encryption and key wrapping algorithm.
enum SECURITY_SUITE
{
    /** 
     AES-GCM-128 for authenticated encryption and AES-128 for key wrapping.
    */
    SECURITY_SUITE_AES_GCM_128    
};

class CGXDLMSSecuritySetup : public CGXDLMSObject
{
	SECURITY_POLICY m_SecurityPolicy;
    SECURITY_SUITE m_SecuritySuite;
    string m_ServerSystemTitle;
    string m_ClientSystemTitle;	
public:	
	//Constructor.
	CGXDLMSSecuritySetup();
	
	//SN Constructor.
	CGXDLMSSecuritySetup(unsigned short sn);
	

	//LN Constructor.
	CGXDLMSSecuritySetup(basic_string<char> ln);
	
	SECURITY_POLICY GetSecurityPolicy();
    
	void SetSecurityPolicy(SECURITY_POLICY value);
    
    SECURITY_SUITE GetSecuritySuite();
    
	void SetSecuritySuite(SECURITY_SUITE value);
    
    string GetClientSystemTitle();
    
	void SetClientSystemTitle(string value);
    
    string GetServerSystemTitle();
    
	void SetServerSystemTitle(string value);
    
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
