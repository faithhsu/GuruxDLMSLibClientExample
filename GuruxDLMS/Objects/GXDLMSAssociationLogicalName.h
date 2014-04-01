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
#include "GXApplicationContextName.h"
#include "GXxDLMSContextType.h"
#include "GXAuthenticationMechanismName.h"

enum GX_ASSOCIATION_STATUS
{
	GX_ASSOCIATION_STATUS_NO_NASSOCIATED, 
    GX_ASSOCIATION_STATUS_ASSOCIATION_PENDING, 
    GX_ASSOCIATION_STATUS_ASSOCIATED
};

class CGXDLMSAssociationLogicalName : public CGXDLMSObject
{
private:

	GX_ASSOCIATION_STATUS m_AssociationStatus;
    CGXDLMSObjectCollection m_ObjectList;
	unsigned char m_ClientSAP;
	unsigned short m_ServerSAP;
    CGXApplicationContextName m_ApplicationContextName;
    CGXxDLMSContextType m_XDLMSContextInfo;
    CGXAuthenticationMechanismName m_AuthenticationMechanismMame;
    vector<unsigned char> m_Secret;
    string m_SecuritySetupReference;   

	void Init();

	void UpdateAccessRights(CGXDLMSObject* pObj, CGXDLMSVariant data);

	int GetAccessRights(CGXDLMSObject* pItem, vector<unsigned char>& data);

	// Returns LN Association View.
	int GetObjects(vector<unsigned char>& data);

public:	
	/**  
     Constructor.
    */
	CGXDLMSAssociationLogicalName();
    
    /**  
     Constructor.
     @param ln Logican Name of the object.
    */
    CGXDLMSAssociationLogicalName(basic_string<char> ln);

	CGXDLMSObjectCollection& GetObjectList();


    /// Contains the identifiers of the COSEM client APs within the physical devices hosting these APs, 
    /// which belong to the AA modelled by the “Association LN” object.
	unsigned char GetClientSAP();
	void SetClientSAP(unsigned char value);

    /// Contains the identifiers of the COSEM server (logical device) APs within the physical 
    /// devices hosting these APs, which belong to the AA modelled by the “Association LN” object.
	unsigned short GetServerSAP();
	void SetServerSAP(unsigned short value);

    CGXApplicationContextName GetApplicationContextName();

    CGXxDLMSContextType GetXDLMSContextInfo();
    
    CGXAuthenticationMechanismName GetAuthenticationMechanismMame();
   
    vector<unsigned char>& GetSecret();
    
	void SetSecret(vector<unsigned char>& value);

	GX_ASSOCIATION_STATUS GetAssociationStatus();

	void SetAssociationStatus(GX_ASSOCIATION_STATUS value);

	string GetSecuritySetupReference();
    void SetSecuritySetupReference(string value);
    
	// Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	//Get attribute values of object.
	void GetValues(vector<string>& values);

	void GetAttributeIndexToRead(vector<int>& attributes);

	int GetDataType(int index, DLMS_DATA_TYPE& type);

    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);
	int SetValue(int index, CGXDLMSVariant& value);
};
