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
#include <map>
#include <string.h>
#include <assert.h>
#include "../ManufacturerSettings/GXAttributeCollection.h"
#include "../GXDLMSVariant.h"
#include "IGXDLMSBase.h"
#include "../GXOBISTemplate.h"
#include "../GXHelpers.h"
#include "../GXDateTime.h"

using namespace std;

class CGXDLMSObjectCollection;

class CGXDLMSObject : public IGXDLMSBase
{
	friend class CGXDLMS;
	friend class CGXDLMSObjectCollection;
	friend class CGXDLMSAssociationLogicalName;
	friend class CGXDLMSAssociationShortName;

	CGXAttributeCollection m_Attributes;
	CGXAttributeCollection m_MethodAttributes;
	void Initialize(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>* pLogicalName);
	basic_string<char> m_Description;	
	OBJECT_TYPE m_ObjectType;
	char m_AttributeIndex;	
	unsigned short m_DataIndex;	
	unsigned short m_Version;		
protected:
	map<int, time_t> m_ReadTimes;
	CGXDLMSObjectCollection* m_Parent;
	unsigned short m_SN;
	unsigned char m_LN[6];

	/*
     * Is attribute read. This can be used with static attributes to make 
     * meter reading faster.
     */    
    bool IsRead(int index);
    bool CanRead(int index);
public:	
	

	CGXDLMSObject(void);
	CGXDLMSObject(OBJECT_TYPE type);

	//SN Constructor.
	CGXDLMSObject(OBJECT_TYPE type, unsigned short sn);

	//LN Constructor.
	CGXDLMSObject(OBJECT_TYPE type, basic_string<char> ln);
	CGXDLMSObject(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>& ln);
	
	~CGXDLMSObject(void);	

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
	void GetLogicalName(string& ln);
	
	//Set Object's Logical Name.
	int SetLogicalName(basic_string<char> value);
		
	void SetVersion(unsigned short value);
	unsigned short GetVersion();

	CGXAttributeCollection& GetAttributes();
	CGXAttributeCollection& GetMethodAttributes();
	virtual int SetDataType(int index, DLMS_DATA_TYPE type);
	virtual int GetDataType(int index, DLMS_DATA_TYPE& type);
	
	virtual int GetUIDataType(int index, DLMS_DATA_TYPE& type);
	void SetUIDataType(int index, DLMS_DATA_TYPE type);

	ACCESSMODE GetAccess(int index);
	void SetAccess(int index, ACCESSMODE access);
	METHOD_ACCESSMODE GetMethodAccess(int index);
	void SetMethodAccess(int index, METHOD_ACCESSMODE access);


	//Get description of the object.
	basic_string<char> GetDescription();
	
	//Set description of the object.
	void SetDescription(basic_string<char> value);

	CGXDLMSObjectCollection* GetParent()
	{
		return m_Parent;
	}

	//Get values as string.
	virtual void GetValues(vector<string>& values)
	{
		assert(0);		
	}

	virtual void GetAttributeIndexToRead(vector<int>& attributes)
	{
		assert(0);		
	}

	// Returns amount of attributes.
	virtual int GetAttributeCount()
	{
		assert(0);
		return 0;
	}

    // Returns amount of methods.
	virtual int GetMethodCount()
	{
		assert(0);
		return 0;
	}

	// Returns value of given attribute.
	virtual int GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
    {		
		return ERROR_CODES_INVALID_PARAMETER;
    }

	// Set value of given attribute.
	virtual int SetValue(int index, CGXDLMSVariant& value)
    {
		return ERROR_CODES_INVALID_PARAMETER;		
    }

	// Set value of given attribute.
	virtual int Invoke(int index, CGXDLMSVariant& parameters)
    {
		return ERROR_CODES_INVALID_PARAMETER;		
    }
};

class CGXDLMSCustomObject : public CGXDLMSObject
{
public:
	CGXDLMSCustomObject(OBJECT_TYPE type) : CGXDLMSObject(type)
	{
	}
};
