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

class CGXDLMSAssociationShortName : public CGXDLMSObject
{
	CGXDLMSVariant m_AccessRightsList;
    CGXDLMSObjectCollection m_ObjectList;
    string m_SecuritySetupReference;	

	int GetAccessRights(CGXDLMSObject* pObj, vector<unsigned char>& data);
	void UpdateAccessRights(CGXDLMSVariant& buff);

public:	
	//Constructor.
	CGXDLMSAssociationShortName();

	CGXDLMSObjectCollection& GetObjectList();
    
    CGXDLMSVariant& GetAccessRightsList()
    {
        return m_AccessRightsList;
    }
    void SetAccessRightsList(CGXDLMSVariant& value)
    {
        m_AccessRightsList = value;
    }

    string& GetSecuritySetupReference()
    {
        return m_SecuritySetupReference;
    }
    void SetSecuritySetupReference(string& value)
    {
        m_SecuritySetupReference = value;
    }

	//Get attribute values of object.
	void GetValues(vector<string>& values);

	void GetAttributeIndexToRead(vector<int>& attributes);

	// Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns SN Association View.
	int GetObjects(vector<unsigned char>& data);

    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

	int SetValue(int index, CGXDLMSVariant& value);
};
