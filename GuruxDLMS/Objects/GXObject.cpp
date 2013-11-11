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

#include "GXObject.h"
#include "../GXHelpers.h"

//SN Constructor.
CGXObject::CGXObject(OBJECT_TYPE type, unsigned short sn)
{
	Initialize(sn, type, 1, NULL);
}

//LN Constructor.
CGXObject::CGXObject(OBJECT_TYPE type, basic_string<char> ln)
{
	Initialize(0, type, 1, NULL);
	SetLogicalName(ln);
}

CGXObject::CGXObject()
{
	Initialize(0, OBJECT_TYPE_NONE, 1, NULL);
}

CGXObject::CGXObject(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>& ln)
{	
	Initialize(sn, class_id, version, &ln);
}

CGXObject::CGXObject(OBJECT_TYPE type)
{
	Initialize(0, type, 1, NULL);	
}

void CGXObject::Initialize(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>* pLogicalName)
{
	m_AttributeIndex = 0;	
	m_DataIndex = 0;
	m_SN = sn;
	m_ObjectType = (OBJECT_TYPE)class_id;
	m_Version = version;
	if (pLogicalName == NULL)
	{
		memset(&m_LN, 0, 6);
	}
	else
	{
		int cnt = pLogicalName->size();
		if (cnt == 6)
		{
			for(int pos = 0; pos != cnt; ++pos)
			{
				m_LN[pos] = *(pLogicalName->begin() + pos);
			}
		}
		else
		{
			assert(false);
		}
	}
	//Attribute 1 is always Logical name.
	m_Attributes.push_back(CGXDLMSAttribute(1, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_OCTET_STRING));
}

CGXObject::~CGXObject(void)
{
	m_Attributes.clear();
	m_MethodAttributes.clear();
}

CGXDLMSVariant CGXObject::GetName()
{	
	if (m_SN != 0)
	{
		return CGXDLMSVariant(m_SN);
	}
	CGXDLMSVariant ln(m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);
	return ln;
}

int CGXObject::SetName(CGXDLMSVariant value)
{	
	if (value.vt == DLMS_DATA_TYPE_UINT16)
	{
		m_SN = value.uiVal;
		return ERROR_CODES_OK;
	}
	if (value.vt == DLMS_DATA_TYPE_STRING)
	{
		SetLogicalName(value.strVal);
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

OBJECT_TYPE CGXObject::GetObjectType()
{
	return m_ObjectType;
}

DLMS_DATA_TYPE CGXObject::GetDataType(int index)
{
	for(vector<CGXDLMSAttribute>::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		int tmp = (*it).GetIndex();
		if (tmp < 1)
		{
			return DLMS_DATA_TYPE_NONE;
		}
		if ((*it).GetIndex() == index)
		{
			return (*it).GetType();
		}
	}
	return DLMS_DATA_TYPE_NONE;
}

ACCESSMODE CGXObject::GetAccess(int index)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			return (*it).GetAccess();
		}
	}
	return ACCESSMODE_READWRITE;
}

// Set attribute access.
void CGXObject::SetAccess(int index, ACCESSMODE access)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			(*it).SetAccess(access);
			return;
		}
	}
	CGXDLMSAttribute att(index);
	att.SetAccess(access);
	m_Attributes.push_back(att);
}

METHOD_ACCESSMODE CGXObject::GetMethodAccess(int index)
{
	for(CGXAttributeCollection::iterator it = m_MethodAttributes.begin(); it != m_MethodAttributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			return (*it).GetMethodAccess();
		}
	}
	return METHOD_ACCESSMODE_NONE;
}

void CGXObject::SetMethodAccess(int index, METHOD_ACCESSMODE access)
{
	for(CGXAttributeCollection::iterator it = m_MethodAttributes.begin(); it != m_MethodAttributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			(*it).SetMethodAccess(access);
			return;
		}
	}
	CGXDLMSAttribute att(index);
	att.SetMethodAccess(access);
	m_MethodAttributes.push_back(att);
}

DLMS_DATA_TYPE CGXObject::GetUIDataType(int index)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			return (*it).GetUIDataType();
		}
	}
	return DLMS_DATA_TYPE_NONE;
}

void CGXObject::SetUIDataType(int index, DLMS_DATA_TYPE type)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			return (*it).SetUIDataType(type);
		}
	}
	CGXDLMSAttribute att(index);
	att.SetUIDataType(type);
	m_Attributes.push_back(att);
}

unsigned short CGXObject::GetShortName()
{
	return m_SN;
}

void CGXObject::SetShortName(unsigned short value)
{
	m_SN = value;
}


basic_string<char> CGXObject::GetLogicalName()
{
	int dataSize;
	char buff[25];
#if _MSC_VER > 1000
	dataSize = sprintf_s(buff, 25, "%d.%d.%d.%d.%d.%d", m_LN[0], m_LN[1], m_LN[2], m_LN[3], m_LN[4], m_LN[5]) + 1;
#else
	dataSize = sprintf(buff, "%d.%d.%d.%d.%d.%d", m_LN[0], m_LN[1], m_LN[2], m_LN[3], m_LN[4], m_LN[5]) + 1;
#endif		
	if (dataSize > 25)
	{	
		assert(0);			
	}
	basic_string<char> tmp(buff);
	return tmp;
}

int CGXObject::SetLogicalName(basic_string<char> value)
{
	int count = 0;	
	int size = value.size();
	char *pBuff = new char[size + 1];
	char *pOriginalBuff = pBuff;
	memcpy(pBuff, value.c_str(), size);
	pBuff[value.size()] = 0;
	char* ch;
	int val = 0;
	while((ch = strchr(pBuff, '.')) != NULL)
	{		
		*ch = '\0';
#if _MSC_VER > 1000
		if (sscanf_s(pBuff, "%d", &val) == 1)
#else
		if (sscanf(pBuff, "%d", &val) == 1)
#endif
		{
			m_LN[count] = (unsigned char)val;
			pBuff = ch + sizeof(char);		
			++count;
		}
	}
	if (count == 5)
	{
#if _MSC_VER > 1000
		if (sscanf_s(pBuff, "%d", &val) == 1)
#else
		if (sscanf(pBuff, "%d", &val) == 1)
#endif		
		{
			m_LN[count] = (unsigned char) val;
			pBuff = ch + sizeof(char);		
			++count;
		}
	}
	delete pOriginalBuff;
	if (count != 6)
	{
		memset(&m_LN, 0, 6);
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}
		
unsigned short CGXObject::GetVersion()
{
	return m_Version;
}

CGXAttributeCollection& CGXObject::GetAttributes()
{
	return m_Attributes;
}

CGXAttributeCollection& CGXObject::GetMethodAttributes()
{
	return m_MethodAttributes;
}

//Get Object's attribute index.
char CGXObject::GetAttributeIndex()
{
	return m_AttributeIndex;
}

//Set Object's attribute index.
void CGXObject::SetAttributeIndex(char value)
{
	m_AttributeIndex = value;
}

//Get Object's data index.
unsigned short CGXObject::GetDataIndex()
{
	return m_DataIndex;
}

//Set Object's data index.
void CGXObject::SetDataIndex(unsigned short value)
{
	m_DataIndex = value;
}

//Get Object's Logical Name.
basic_string<char> CGXObject::GetDescription()
{
	return m_Description;
}

//Set Object's Logical Name.
void CGXObject::SetDescription(basic_string<char> value)
{
	m_Description = value;
}
