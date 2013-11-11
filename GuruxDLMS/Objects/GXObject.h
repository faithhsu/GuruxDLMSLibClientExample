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
#include <string.h>
#include <assert.h>
#include "../ManufacturerSettings/GXAttributeCollection.h"
#include "../GXDLMSVariant.h"
#include "IGXDLMSBase.h"

using namespace std;

class CGXObject : public IGXDLMSBase
{
	CGXAttributeCollection m_Attributes;
	CGXAttributeCollection m_MethodAttributes;
	void Initialize(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>* pLogicalName);
public:
	basic_string<char> m_Description;
	unsigned short m_SN;
	OBJECT_TYPE m_ObjectType;
	unsigned short m_Version;
	unsigned char m_LN[6];
	char m_AttributeIndex;	
	unsigned short m_DataIndex;	
public:	
	CGXObject(void);
	CGXObject(OBJECT_TYPE type);

	//SN Constructor.
	CGXObject(OBJECT_TYPE type, unsigned short sn);

	//LN Constructor.
	CGXObject(OBJECT_TYPE type, basic_string<char> ln);
	CGXObject(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>& ln);
	
	~CGXObject(void);	

	//Get Object's Logican or Short Name as a string.
	CGXDLMSVariant GetName();

	int SetName(CGXDLMSVariant value);

	//Get Object's Interface class type.
	OBJECT_TYPE GetObjectType();

	//Get Object's Short Name.
	unsigned short GetShortName();
	
	//Set Object's Short Name.
	void SetShortName(unsigned short value);

	//Get Object's Logical Name.
	basic_string<char> GetLogicalName();
	
	//Set Object's Logical Name.
	int SetLogicalName(basic_string<char> value);
		
	unsigned short GetVersion();

	CGXAttributeCollection& GetAttributes();
	CGXAttributeCollection& GetMethodAttributes();
	DLMS_DATA_TYPE GetDataType(int index);
	
	virtual DLMS_DATA_TYPE GetUIDataType(int index);
	void SetUIDataType(int index, DLMS_DATA_TYPE type);

	ACCESSMODE GetAccess(int index);
	void SetAccess(int index, ACCESSMODE access);
	METHOD_ACCESSMODE GetMethodAccess(int index);
	void SetMethodAccess(int index, METHOD_ACCESSMODE access);

	//Get description of the object.
	basic_string<char> GetDescription();
	
	//Set description of the object.
	void SetDescription(basic_string<char> value);

	//Get Object's attribute index.
	char GetAttributeIndex();
	//Set Object's attribute index.
	void SetAttributeIndex(char value);

	//Get Object's data index.
	unsigned short GetDataIndex();	
	//Set Object's data index.
	void SetDataIndex(unsigned short value);

	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 0;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
    {		
		return ERROR_CODES_INVALID_PARAMETER;
    }

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value)
    {
		return ERROR_CODES_INVALID_PARAMETER;		
    }

	// Set value of given attribute.
	int Invoke(int index, CGXDLMSVariant& parameters)
    {
		return ERROR_CODES_INVALID_PARAMETER;		
    }
};
