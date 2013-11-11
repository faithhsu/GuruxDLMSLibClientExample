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
#include "GXObject.h"
#include "../GXHelpers.h"
#include "../GXDateTime.h"

class CGXDLMSSapAssignment : public CGXObject
{
	std::map<int, basic_string<char> > m_SapAssignmentList;
public:
    /**  
     Constructor.
    */
	CGXDLMSSapAssignment() : CGXObject(OBJECT_TYPE_SAP_ASSIGNMENT, "0.0.41.0.0.255")
    {
    }

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSSapAssignment(basic_string<char> ln) : CGXObject(OBJECT_TYPE_SAP_ASSIGNMENT, ln)
    {
    }

    /**  
     Constructor.
     @param sn Short Name of the object.
    */
    CGXDLMSSapAssignment(int sn) : CGXObject(OBJECT_TYPE_SAP_ASSIGNMENT, sn)
    {

    }

    std::map<int, basic_string<char> >& GetSapAssignmentList()
    {
        return m_SapAssignmentList;
    }
    void SetSapAssignmentList(std::map<int, basic_string<char> >& value)
    {
        m_SapAssignmentList = value;
    }
    
	// Returns amount of attributes.
	int GetAttributeCount()
	{
		return 2;
	}

    // Returns amount of methods.
	int GetMethodCount()
	{
		return 1;
	}

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
    {
        if (index == 1)
        {
            GXHelpers::AddRange(value.byteArr, m_LN, 6);
			type = value.vt = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }
        if (index == 2)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            int cnt = m_SapAssignmentList.size();
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            //Add count            
            CGXOBISTemplate::SetObjectCount(cnt, data);
            if (cnt != 0)
            {
				for (std::map<int, basic_string<char> >::iterator it = m_SapAssignmentList.begin();
					it != m_SapAssignmentList.end(); ++it)                                
                {
                    data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                    data.push_back(2); //Count
					CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*it).first);
					CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).second);
                }
            }
            value = data;
			return ERROR_CODES_OK;
        }    
        return ERROR_CODES_INVALID_PARAMETER;
    }
    
    /*
     * Set value of given attribute.
     */
    int SetValue(int index, CGXDLMSVariant& value)
    {
		if (index == 1)
        {
            if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
			{
				return ERROR_CODES_INVALID_PARAMETER;
			}
			memcpy(m_LN, &value.byteArr[0], 6);
			return ERROR_CODES_OK;
        }
        if (index == 2)
        {
            m_SapAssignmentList.clear();
			for (vector<CGXDLMSVariant>::iterator item = value.Arr.begin(); 
				item != value.Arr.end(); ++item)
            {
                basic_string<char> str;
                if ((*item).Arr[1].vt == DLMS_DATA_TYPE_OCTET_STRING)
                {
					CGXDLMSVariant tmp;
					CGXDLMSClient::ChangeType((*item).Arr[1].byteArr, DLMS_DATA_TYPE_STRING, tmp);
					str = tmp.strVal;
                }
                else
                {
                    str = (*item).Arr[1].ToString();
                }            
				m_SapAssignmentList[(*item).Arr[0].lVal] = str;
                //m_SapAssignmentList.put(((Number) Array.get(item, 0)).intValue(), str);
            }                    
			return ERROR_CODES_OK;
        }
        return ERROR_CODES_INVALID_PARAMETER;
    }
};
