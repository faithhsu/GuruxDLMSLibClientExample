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

#include "../GXDLMSVariant.h"
#include "../GXDLMSClient.h"
#include "GXDLMSSapAssignment.h"
#include <sstream> 

/**  
 Constructor.
*/
CGXDLMSSapAssignment::CGXDLMSSapAssignment() : CGXDLMSObject(OBJECT_TYPE_SAP_ASSIGNMENT, "0.0.41.0.0.255")
{
}

/**  
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSSapAssignment::CGXDLMSSapAssignment(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_SAP_ASSIGNMENT, ln)
{
}

/**  
 Constructor.
 @param sn Short Name of the object.
*/
CGXDLMSSapAssignment::CGXDLMSSapAssignment(int sn) : CGXDLMSObject(OBJECT_TYPE_SAP_ASSIGNMENT, sn)
{

}

std::map<int, basic_string<char> >& CGXDLMSSapAssignment::GetSapAssignmentList()
{
    return m_SapAssignmentList;
}
void CGXDLMSSapAssignment::SetSapAssignmentList(std::map<int, basic_string<char> >& value)
{
    m_SapAssignmentList = value;
}

// Returns amount of attributes.
int CGXDLMSSapAssignment::GetAttributeCount()
{
	return 2;
}

// Returns amount of methods.
int CGXDLMSSapAssignment::GetMethodCount()
{
	return 1;
}

void CGXDLMSSapAssignment::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);
	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(std::map<int, basic_string<char> >::iterator it = m_SapAssignmentList.begin(); it != m_SapAssignmentList.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;
		string str = CGXDLMSVariant((it->first)).ToString();
		sb.write(str.c_str(), str.size());
		sb << ", ";		
		sb.write(it->second.c_str(), it->second.size());
	}
	sb << ']';
	values.push_back(sb.str());
}

void CGXDLMSSapAssignment::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//SapAssignmentList
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSSapAssignment::GetDataType(int index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK; 
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK; 
    }    
    return ERROR_CODES_INVALID_PARAMETER;
}


// Returns value of given attribute.
int CGXDLMSSapAssignment::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
    if (index == 1)
    {
        GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {            
        int cnt = m_SapAssignmentList.size();
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        //Add count            
        CGXOBISTemplate::SetObjectCount(cnt, data);
		int ret;
        if (cnt != 0)
        {
			for (std::map<int, basic_string<char> >::iterator it = m_SapAssignmentList.begin();
				it != m_SapAssignmentList.end(); ++it)                                
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(2); //Count
				if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*it).first)) != 0 ||
					(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).second)) != 0)
				{
					return ret;
				}
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
int CGXDLMSSapAssignment::SetValue(int index, CGXDLMSVariant& value)
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
			m_SapAssignmentList[(*item).Arr[0].ToInteger()] = str;
        }                    
		return ERROR_CODES_OK;
    }
    return ERROR_CODES_INVALID_PARAMETER;
}