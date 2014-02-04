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

#include "IGXDLMSBase.h"
#include "GXDLMSObject.h"
#include "../GXHelpers.h"
#include "GXDLMSSpecialDay.h"

class CGXDLMSSpecialDaysTable : public CGXDLMSObject
{
	vector<CGXDLMSSpecialDay> m_Entries;
public:	
	//Constructor.
	CGXDLMSSpecialDaysTable() : CGXDLMSObject(OBJECT_TYPE_SPECIAL_DAYS_TABLE)
	{
	}

	//SN Constructor.
	CGXDLMSSpecialDaysTable(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_SPECIAL_DAYS_TABLE, sn)
	{

	}

	//LN Constructor.
	CGXDLMSSpecialDaysTable(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_SPECIAL_DAYS_TABLE, ln)
	{

	}

    vector<CGXDLMSSpecialDay>& GetEntries()
    {
        return m_Entries;
    }

    void SetValue(vector<CGXDLMSSpecialDay>& value)
    {
        m_Entries = value;
    }

    // Returns amount of attributes.
	int GetAttributeCount()
	{
		return 2;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 0;
	}

	void GetAttributeIndexToRead(vector<int>& attributes)
	{
		//LN is static and read only once.
		if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
        {
            attributes.push_back(1);
        }
		//Entries
        if (CanRead(2))
        {
            attributes.push_back(2);
        }
	}

	int GetDataType(int index, DLMS_DATA_TYPE& type)
    {
		if (index == 1)
		{
			type = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
		}
		//Entries
        if (index == 2)
		{		
			type = DLMS_DATA_TYPE_ARRAY;
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
	}

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)
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
			CGXOBISTemplate::SetObjectCount(m_Entries.size(), data);
			for (vector<CGXDLMSSpecialDay>::iterator it = m_Entries.begin(); it != m_Entries.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(3); //Count
				CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*it).GetIndex());
				CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_DATETIME, (*it).GetDate());
				CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT8, (*it).GetDayId());
            }
			return ERROR_CODES_OK;
		}
		return ERROR_CODES_INVALID_PARAMETER;
    }

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value)
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
			m_Entries.clear();
            if (value.vt == DLMS_DATA_TYPE_ARRAY)
            {
				CGXDLMSVariant tmp;
				for (vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); item != value.Arr.end(); ++item)
                {
                    CGXDLMSSpecialDay it;                    
                    it.SetIndex((*item).Arr[0].ToInteger());
					CGXDLMSClient::ChangeType((*item).Arr[1].byteArr, DLMS_DATA_TYPE_DATE, tmp);
					it.SetDate(tmp.dateTime);
                    it.SetDayId((*item).Arr[2].ToInteger());
                    m_Entries.push_back(it);
                }
            }		
		}	
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		return ERROR_CODES_OK;
    }
};
