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

#include "GXDLMSScriptTable.h"

//Constructor.
CGXDLMSScriptTable::CGXDLMSScriptTable() : CGXDLMSObject(OBJECT_TYPE_SCRIPT_TABLE)
{
}

//SN Constructor.
CGXDLMSScriptTable::CGXDLMSScriptTable(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_SCRIPT_TABLE, sn)
{

}

//LN Constructor.
CGXDLMSScriptTable::CGXDLMSScriptTable(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_SCRIPT_TABLE, ln)
{

}

vector<pair<int, CGXDLMSScriptAction> >& CGXDLMSScriptTable::GetScripts()
{
    return m_Scripts;
}

// Returns amount of attributes.
int CGXDLMSScriptTable::GetAttributeCount()
{
	return 2;
}

// Returns amount of methods.
int CGXDLMSScriptTable::GetMethodCount()
{
	return 1;
}

void CGXDLMSScriptTable::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//Scripts
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSScriptTable::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
	//Scripts
    if (index == 2)
	{		
		type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSScriptTable::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
	{
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        //Add count            
        CGXOBISTemplate::SetObjectCount(m_Scripts.size(), data);
		for(vector<pair<int, CGXDLMSScriptAction> >::iterator it = m_Scripts.begin(); it != m_Scripts.end(); ++it)
        {
            data.push_back(DLMS_DATA_TYPE_STRUCTURE);
            data.push_back(2); //Count
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, it->first); //Script_identifier:
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            data.push_back(5); //Count
			CGXDLMSScriptAction tmp = it->second;
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_ENUM, tmp.GetType()); //service_id
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, tmp.GetObjectType()); //class_id
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, tmp.GetLogicalName()); //logical_name
            CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, tmp.GetIndex()); //index
            CGXOBISTemplate::SetData(data, tmp.GetParameterType(), tmp.GetObjectType()); //parameter
        }
        value = data;
		return ERROR_CODES_OK;
	}
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSScriptTable::SetValue(int index, CGXDLMSVariant& value)
{
	if (index == 1)
	{			
		if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		memcpy(m_LN, &value.byteArr[0], 6);		
	}
    else if (index == 2)
	{
		m_Scripts.clear();
        //Fix Xemex bug here.
        //Xemex meters do not return array as they shoul be according standard.
        if (value.Arr.size()  != 0)
        {				
            if (value.Arr[0].vt == DLMS_DATA_TYPE_ARRAY)
            {
				for(vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)                    
                { 
					int script_identifier = (*item).Arr[0].ToInteger();
					for(vector<CGXDLMSVariant>::iterator arr = (*item).Arr[1].Arr.begin(); item != (*item).Arr[0].Arr.end(); ++arr)                    
                    { 
                        CGXDLMSScriptAction it;
						SCRIPT_ACTION_TYPE type = (SCRIPT_ACTION_TYPE) (*arr).Arr[0].ToInteger();
                        it.SetType(type);                
                        OBJECT_TYPE ot = (OBJECT_TYPE) (*arr).Arr[0].ToInteger();
                        it.SetObjectType(ot);
                        string ln;							
						CGXOBISTemplate::GetLogicalName((*arr).Arr[2].byteArr, ln);
                        it.SetLogicalName(ln);
                        it.SetIndex((*arr).Arr[3].ToInteger());
                        it.SetParameter((*arr).Arr[4].ToInteger(), DLMS_DATA_TYPE_NONE);
                        m_Scripts.push_back(pair<int, CGXDLMSScriptAction>(script_identifier, it));
                    }                    
                }               
            }
            else //Read Xemex meter here.
            {
                int script_identifier = value.Arr[0].ToInteger();                    
                CGXDLMSScriptAction it;
                SCRIPT_ACTION_TYPE type = (SCRIPT_ACTION_TYPE) value.Arr[1].Arr[0].ToInteger();
                it.SetType(type);
                OBJECT_TYPE ot = (OBJECT_TYPE) value.Arr[1].Arr[1].ToInteger();
                it.SetObjectType(ot);
				string ln;							
				CGXOBISTemplate::GetLogicalName(value.Arr[1].Arr[2].byteArr, ln);
                it.SetLogicalName(ln);
				it.SetIndex(value.Arr[1].Arr[3].ToInteger());
                it.SetParameter(value.Arr[1].Arr[4], DLMS_DATA_TYPE_NONE);
				m_Scripts.push_back(pair<int, CGXDLMSScriptAction>(script_identifier, it));
            }
        }	
	}	
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}