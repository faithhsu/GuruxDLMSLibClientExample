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

#include "GXDLMSObject.h"
#include "../GXHelpers.h"

//SN Constructor.
CGXDLMSObject::CGXDLMSObject(OBJECT_TYPE type, unsigned short sn)
{
	Initialize(sn, type, 0, NULL);
}

//LN Constructor.
CGXDLMSObject::CGXDLMSObject(OBJECT_TYPE type, basic_string<char> ln)
{
	Initialize(0, type, 0, NULL);
	SetLogicalName(ln);
}

CGXDLMSObject::CGXDLMSObject()
{
	Initialize(0, OBJECT_TYPE_NONE, 0, NULL);
}

CGXDLMSObject::CGXDLMSObject(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>& ln)
{	
	Initialize(sn, class_id, version, &ln);
}

CGXDLMSObject::CGXDLMSObject(OBJECT_TYPE type)
{
	Initialize(0, type, 0, NULL);	
}

void CGXDLMSObject::Initialize(short sn, unsigned short class_id, unsigned char version, vector<unsigned char>* pLogicalName)
{
	m_Parent = NULL;
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

CGXDLMSObject::~CGXDLMSObject(void)
{
	m_Attributes.clear();
	m_MethodAttributes.clear();
}

CGXDLMSVariant CGXDLMSObject::GetName()
{	
	if (m_SN != 0)
	{
		return CGXDLMSVariant(m_SN);
	}
	CGXDLMSVariant ln(m_LN, 6, DLMS_DATA_TYPE_OCTET_STRING);
	return ln;
}

int CGXDLMSObject::SetName(CGXDLMSVariant value)
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

OBJECT_TYPE CGXDLMSObject::GetObjectType()
{
	return m_ObjectType;
}

int CGXDLMSObject::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index < 1)
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	for(vector<CGXDLMSAttribute>::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{		
		if ((*it).GetIndex() == index)
		{
			type = (*it).GetDataType();
			return ERROR_CODES_OK;
		}
	}
	type = DLMS_DATA_TYPE_NONE;
	return ERROR_CODES_OK;
}

int CGXDLMSObject::SetDataType(int index, DLMS_DATA_TYPE type)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			(*it).SetDataType(type);
			return ERROR_CODES_OK;
		}
	}
	CGXDLMSAttribute att(index);
	att.SetDataType(type);
	m_Attributes.push_back(att);
	return ERROR_CODES_OK;
}

ACCESSMODE CGXDLMSObject::GetAccess(int index)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			return (*it).GetAccess();
		}
	}
    //LN is read only.
    if (index == 1)
    {
		return ACCESSMODE_READ;
    }
	return ACCESSMODE_READWRITE;
}

// Set attribute access.
void CGXDLMSObject::SetAccess(int index, ACCESSMODE access)
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

METHOD_ACCESSMODE CGXDLMSObject::GetMethodAccess(int index)
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

void CGXDLMSObject::SetMethodAccess(int index, METHOD_ACCESSMODE access)
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

int CGXDLMSObject::GetUIDataType(int index, DLMS_DATA_TYPE& type)
{
	for(CGXAttributeCollection::iterator it = m_Attributes.begin(); it != m_Attributes.end(); ++it)
	{
		if ((*it).GetIndex() == index)
		{
			type = (*it).GetUIDataType();
			return ERROR_CODES_OK;
		}
	}
	type = DLMS_DATA_TYPE_NONE;
	return ERROR_CODES_OK;
}

void CGXDLMSObject::SetUIDataType(int index, DLMS_DATA_TYPE type)
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

unsigned short CGXDLMSObject::GetShortName()
{
	return m_SN;
}

void CGXDLMSObject::SetShortName(unsigned short value)
{
	m_SN = value;
}


void CGXDLMSObject::GetLogicalName(string& ln)
{	
	CGXOBISTemplate::GetLogicalName(m_LN, ln);
}

int CGXDLMSObject::SetLogicalName(basic_string<char> value)
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
		
void CGXDLMSObject::SetVersion(unsigned short value)
{
	m_Version = value;
}

unsigned short CGXDLMSObject::GetVersion()
{
	return m_Version;
}

CGXAttributeCollection& CGXDLMSObject::GetAttributes()
{
	return m_Attributes;
}

CGXAttributeCollection& CGXDLMSObject::GetMethodAttributes()
{
	return m_MethodAttributes;
}
/*TODO:
//Get Object's attribute index.
char CGXDLMSObject::GetAttributeIndex()
{
	return m_AttributeIndex;
}

//Set Object's attribute index.
void CGXDLMSObject::SetAttributeIndex(char value)
{
	m_AttributeIndex = value;
}

//Get Object's data index.
unsigned short CGXDLMSObject::GetDataIndex()
{
	return m_DataIndex;
}

//Set Object's data index.
void CGXDLMSObject::SetDataIndex(unsigned short value)
{
	m_DataIndex = value;
}
*/

//Get Object's Logical Name.
basic_string<char> CGXDLMSObject::GetDescription()
{
	return m_Description;
}

//Set Object's Logical Name.
void CGXDLMSObject::SetDescription(basic_string<char> value)
{
	m_Description = value;
}

bool CGXDLMSObject::IsRead(int index)
{            
    if (!CanRead(index))
    {
        return true;
    }        
    return m_ReadTimes.find(index) != m_ReadTimes.end();
}        

bool CGXDLMSObject::CanRead(int index)
{
	return GetAccess(index) != ACCESSMODE_NONE;
}