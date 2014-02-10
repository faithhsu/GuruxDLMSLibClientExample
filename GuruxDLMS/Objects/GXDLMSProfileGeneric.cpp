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
#include "GXDLMSProfileGeneric.h"
#include "../GXDLMSObjectFactory.h"

void CGXDLMSProfileGeneric::Init()
{
	m_SortObjectAttributeIndex = 0;
	m_SortObjectDataIndex = 0;
	m_SortObject = NULL;
	m_CapturePeriod = 3600;
	m_ProfileEntries = 1;
	m_SortMethod = GX_SORT_METHOD_FIFO;
}

int CGXDLMSProfileGeneric::GetColumns(vector<unsigned char>& data)
{
    int cnt = m_CaptureObjects.size();        
    data.push_back(DLMS_DATA_TYPE_ARRAY);
    //Add count
	CGXOBISTemplate::SetObjectCount(cnt, data);            		
	string ln;
	for (std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >::iterator it = m_CaptureObjects.begin(); it != m_CaptureObjects.end(); ++it)                    
    {
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        data.push_back(4); //Count
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*it).first->GetObjectType()); //ClassID
		(*it).first->GetLogicalName(ln);
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, ln); //LN
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_INT8, (*it).second->GetAttributeIndex()); //Attribute Index
        CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, (*it).second->GetDataIndex()); //Data Index
    }
	return ERROR_CODES_OK;
}

int CGXDLMSProfileGeneric::GetData(vector< vector<CGXDLMSVariant> > table, vector<unsigned char>& data) 
{
    data.push_back(DLMS_DATA_TYPE_ARRAY);        
    CGXOBISTemplate::SetObjectCount(table.size(), data);
    vector<DLMS_DATA_TYPE> types;        
	DLMS_DATA_TYPE type;
	int ret;
	for (std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >::iterator it = m_CaptureObjects.begin(); 
						it != m_CaptureObjects.end(); ++it)                           
    {
		if ((ret = (*it).first->GetDataType((*it).second->GetAttributeIndex(), type)) != 0)
		{
			return ret;
		}
        types.push_back(type);
    }
	for (vector< vector<CGXDLMSVariant> >::iterator row = table.begin(); row != table.end(); ++row)                           
    {
        data.push_back(DLMS_DATA_TYPE_STRUCTURE);
        CGXOBISTemplate::SetObjectCount((*row).size(), data);
        int pos = -1;
		for (vector<CGXDLMSVariant>::iterator value = (*row).begin(); value != (*row).end(); ++value)                           
        {
            DLMS_DATA_TYPE tp = types[++pos];
            if (tp == DLMS_DATA_TYPE_NONE)
            {
				//TODO:
                //tp = GXCommon.GetValueType(value);
                //types[pos] = tp;  
            }
            CGXOBISTemplate::SetData(data, tp, *value);
        }
    }        
	return ERROR_CODES_OK;        
}  

 /*
 * Add new capture object (column) to the profile generic.
 */
int CGXDLMSProfileGeneric::AddCaptureObject(CGXDLMSObject* pObj, int attributeIndex, int dataIndex)
{
    if (pObj == NULL)            
    {
        //Invalid Object
		return ERROR_CODES_INVALID_PARAMETER;
    }
    if (attributeIndex < 1)
    {
        //Invalid attribute index
		return ERROR_CODES_INVALID_PARAMETER;
    }
    if (dataIndex < 0)
    {
        //Invalid data index
		return ERROR_CODES_INVALID_PARAMETER;
    }
    CGXDLMSCaptureObject* pCO = new CGXDLMSCaptureObject(attributeIndex, dataIndex);
	//std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >
    m_CaptureObjects.push_back(std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*>(pObj, pCO));        
	return ERROR_CODES_OK;        
}

int CGXDLMSProfileGeneric::GetAccessSelector(unsigned char* data, int Length, int& Selector, CGXDLMSVariant& start, CGXDLMSVariant& to)
{
    Selector = data[0];
    //Start index
	int ret;
    if (Selector == 1) //Read by range
    {
        if (data[1] != DLMS_DATA_TYPE_STRUCTURE || data[2] != 4 || 
			data[3] != DLMS_DATA_TYPE_STRUCTURE || data[4] != 4)
        {
            return ERROR_CODES_INVALID_PARAMETER;
        }			
        CGXDLMSVariant classId, ln, attributeIndex, version, tmp;
		data += 5;
		Length -= 5;
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, classId)) != 0)
		{
			return ret;
		}
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, ln)) != 0)
		{
			return ret;
		}
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, attributeIndex)) != 0)
		{
			return ret;
		}
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, version)) != 0)
		{
			return ret;
		}
		//TODO:
		/*

		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, tmp)) != 0 ||
			(ret = GXDLMSClient::ChangeType(tmp, DLMS_DATA_TYPE_DATETIME, start)) != 0)
		{
			return ret;
		}          

		tmp.Clear();
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, tmp)) != 0 ||
			(ret = GXDLMSClient::ChangeType(tmp, DLMS_DATA_TYPE_DATETIME, to)) != 0)
		{
			return ret;
		} 
		*/
    }
    else if (Selector == 2) //Read by entry.
    {
        if (data[1] != DLMS_DATA_TYPE_STRUCTURE || data[2] != 4)
        {
			return ERROR_CODES_INVALID_PARAMETER;
        }
        data += 3;
		Length -= 3;
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, start)) != 0)
		{
			return ret;
		}
		if ((ret = CGXOBISTemplate::GetData(data, Length, DLMS_DATA_TYPE_NONE, to)) != 0)
		{
			return ret;
		}
        if (start.ToInteger() > to.ToInteger())
        {
            return ERROR_CODES_INVALID_PARAMETER;
        }
    }
    else
    {
        return ERROR_CODES_INVALID_PARAMETER;
    }
	return ERROR_CODES_OK;
}

int CGXDLMSProfileGeneric::GetProfileGenericData(unsigned char* parameters, int length, vector<unsigned char>& reply)
{        
    int selector = 0;
	CGXDLMSVariant from, to;
    //If all data is readed.
    if (length == 0)
    {
        return GetData(GetBuffer(), reply);            
    }
    GetAccessSelector(parameters, length, selector, from, to);
    vector< vector<CGXDLMSVariant> >& table = GetBuffer();
    vector< vector<CGXDLMSVariant> > items;
    //TODO: Lock synchronized (this)
    {
        if (selector == 1) //Read by range
        {	
			struct tm tmp = from.dateTime.GetValue();
			time_t start = mktime(&tmp);
			tmp = to.dateTime.GetValue();
			time_t end = mktime(&tmp);				 
			for (vector< vector<CGXDLMSVariant> >::iterator row = table.begin(); row != table.end(); ++row)                           
            {
				tmp = (*row)[0].dateTime.GetValue();
                time_t tm = mktime(&tmp);
                if (tm >= start && tm <= end)
                {
                    items.push_back(*row);
                }
            }			
        }
        else if (selector == 2) //Read by entry.
        {
            int start = from.ToInteger();
            int count = to.ToInteger();
            for (int pos = 0; pos < count; ++pos)
            {
                if ((unsigned int) (pos + start) == table.size())
                {
                    break;
                }
                items.push_back(table[start + pos]);
            }
        }
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
    }
    return GetData(items, reply);       
}

/**  
 Constructor.
*/
CGXDLMSProfileGeneric::CGXDLMSProfileGeneric() : CGXDLMSObject(OBJECT_TYPE_PROFILE_GENERIC)
{
	Init();
}

//SN Constructor.
CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_PROFILE_GENERIC, sn)
{
	Init();
}

//SN Constructor.
CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(unsigned short sn, CGXDLMSVariant value) : CGXDLMSObject(OBJECT_TYPE_PROFILE_GENERIC, sn)
{
	Init();
}

/**  
 Constructor.

 @param ln Logican Name of the object.
*/
CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_PROFILE_GENERIC, ln)
{
	Init();
}     

/** 
 Data of profile generic.
*/
vector< vector<CGXDLMSVariant> >& CGXDLMSProfileGeneric::GetBuffer()
{
    return m_Buffer;
}

/** 
 Captured Objects.
*/
std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >& CGXDLMSProfileGeneric::GetCaptureObjects()
{
    return m_CaptureObjects;
}

/** 
 How often values are captured.
*/
int CGXDLMSProfileGeneric::GetCapturePeriod()
{
    return m_CapturePeriod;
}
void CGXDLMSProfileGeneric::SetCapturePeriod(int value)
{
    m_CapturePeriod = value;
}

/** 
 How columns are sorted.
*/
GX_SORT_METHOD CGXDLMSProfileGeneric::GetSortMethod()
{
    return m_SortMethod;
}
void CGXDLMSProfileGeneric::SetSortMethod(GX_SORT_METHOD value)
{
    m_SortMethod = value;
}

/** 
 Column that is used for sorting.
*/
CGXDLMSObject* CGXDLMSProfileGeneric::GetSortObject()
{
    return m_SortObject;
}
void CGXDLMSProfileGeneric::SetSortObject(CGXDLMSObject* value)
{
    m_SortObject = value;
}

/** 
 Entries (rows) in Use.
*/
char CGXDLMSProfileGeneric::GetEntriesInUse()
{
    return m_Buffer.size();
}

/** 
 Maximum Entries (rows) count.
*/
char CGXDLMSProfileGeneric::GetProfileEntries()
{
    return m_ProfileEntries;
}
void CGXDLMSProfileGeneric::SetProfileEntries(char value)
{
    m_ProfileEntries = value;
}

 /** 
 Attribute index of sort object.
*/
int CGXDLMSProfileGeneric::GetSortObjectAttributeIndex()
{
    return m_SortObjectAttributeIndex;
}
void CGXDLMSProfileGeneric::SetSortObjectAttributeIndex(int value)
{
    m_SortObjectAttributeIndex = value;
}

/** 
 Data index of sort object.
*/
int CGXDLMSProfileGeneric::GetSortObjectDataIndex()
{
    return m_SortObjectDataIndex;
}
void CGXDLMSProfileGeneric::SetSortObject(int value)
{
    m_SortObjectDataIndex = value;
}    

/** 
 Clears the buffer.
*/
void CGXDLMSProfileGeneric::Reset()
{
	//TODO:
}

/** 
 Copies the values of the objects to capture 
 into the buffer by reading capture objects.
*/
void CGXDLMSProfileGeneric::Capture()
{
	//TODO:
}

void CGXDLMSProfileGeneric::GetAttributeIndexToRead(vector<int>& attributes)
{
    //LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //Buffer
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //CaptureObjects
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //CapturePeriod
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //SortMethod
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //SortObject
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    //EntriesInUse
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    //ProfileEntries
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }        
}

//Returns amount of attributes.     
int CGXDLMSProfileGeneric::GetAttributeCount()
{
    return 8;
}       

//Returns amount of methods.     
int CGXDLMSProfileGeneric::GetMethodCount()
{
    return 1;
}

int CGXDLMSProfileGeneric::GetDataType(int index, DLMS_DATA_TYPE& type)
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
    if (index == 3)
    {
		type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
		type = DLMS_DATA_TYPE_INT8;
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {            
		type = DLMS_DATA_TYPE_INT8;
		return ERROR_CODES_OK;
    }        
    if (index == 6)
    {
		type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    }
    if (index == 7)
    {
		type = DLMS_DATA_TYPE_UINT32;
		return ERROR_CODES_OK;
    }
    if (index == 8)
    {
		type = DLMS_DATA_TYPE_UINT32;
		return ERROR_CODES_OK;
    }  	
	return ERROR_CODES_INVALID_PARAMETER;
}

 /*
 * Returns value of given attribute.
 */    
int CGXDLMSProfileGeneric::GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value)   
{
    if (index == 1)
    {
        GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {			
        return GetProfileGenericData(parameters, length, value.byteArr);          
    }        
    if (index == 3)
    {
		vector<unsigned char> data;
        return GetColumns(data);
    }
    if (index == 4)
    {
        value = GetCapturePeriod();
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {            
        value = GetSortMethod();
		return ERROR_CODES_OK;
    }
    if (index == 7)
    {
        value = GetEntriesInUse();
		return ERROR_CODES_OK;
    }
    if (index == 8)
    {
        value = GetProfileEntries();
		return ERROR_CODES_OK;
    }
    return ERROR_CODES_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSProfileGeneric::SetValue(int index, CGXDLMSVariant& value)
{
	int ret;
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
        if (m_CaptureObjects.size() == 0)
        {
			//Read capture objects first.
			return ERROR_CODES_INVALID_PARAMETER;                
        }
        m_Buffer.clear();
		if (value.vt != DLMS_DATA_TYPE_NONE)
        {
            vector<DLMS_DATA_TYPE> types;
            int pos = -1;  
			DLMS_DATA_TYPE type;
			for (std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >::iterator it = m_CaptureObjects.begin(); it != m_CaptureObjects.end(); ++it)                    
            {
				if ((ret = (*it).first->GetUIDataType((*it).second->GetAttributeIndex(), type)) != 0)
				{
					return ret;
				}
                types.push_back(type);
            } 
			for (std::vector<CGXDLMSVariant >::iterator row = value.Arr.begin(); row != value.Arr.end(); ++row)                    
            //for(Object row : (Object[]) value)
            {
                if ((*row).Arr.size() != m_CaptureObjects.size())
                {
                    //Number of columns do not match.
					return ERROR_CODES_INVALID_PARAMETER;
                }
                for(unsigned int a = 0; a < (*row).Arr.size(); ++a)
                {
                    CGXDLMSVariant data = (*row).Arr[a];
                    DLMS_DATA_TYPE type = types[a];
                    if (type != DLMS_DATA_TYPE_NONE && data.vt == DLMS_DATA_TYPE_ARRAY)
                    {
						unsigned char* pBuff = &data.byteArr[0];
						int size = data.byteArr.size();
                        if ((ret = CGXOBISTemplate::GetData(pBuff, size, type, (*row).Arr[a])) != 0)
						{
							return ret;
						}
                    }
					std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> item = m_CaptureObjects[pos];
                    //AbstractMap.SimpleEntry<GXDLMSObject, GXDLMSCaptureObject> item = m_CaptureObjects.get(pos);
					if (item.first->GetObjectType() == OBJECT_TYPE_REGISTER && item.second->GetAttributeIndex() == 2)
                    {
                        double scaler = ((CGXDLMSRegister*) item.first)->GetScaler();
                        if (scaler != 1)
                        {
							//TODO: tarkista jos ei double.
                            row[a] = data.dblVal * scaler;                                    
                        }
                    }   
                }
                //TODO: m_Buffer.push_back(row);
            }  
        }            
    }
    else if (index == 3)
    {
        m_CaptureObjects.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {
			for (std::vector<CGXDLMSVariant >::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
            {                    
                if ((*it).Arr.size() != 4)
                {
					//Invalid structure format.
					return ERROR_CODES_INVALID_PARAMETER;                        
                }
                OBJECT_TYPE type = (OBJECT_TYPE) (*it).Arr[0].ToInteger();
				string ln;
				CGXOBISTemplate::GetLogicalName(&(*it).Arr[1].byteArr[0], ln);
                CGXDLMSObject* pObj = GetParent()->FindByLN(type, ln);
                if(pObj == NULL)
                {                        
                    pObj = CGXDLMSObjectFactory::CreateObject(type);
                    pObj->SetLogicalName(ln);
                }                    
                AddCaptureObject(pObj, (*it).Arr[2].ToInteger(), (*it).Arr[3].ToInteger());
            }
        }
    }
    else if (index == 4)
    {
        m_CapturePeriod = value.ToInteger();
    }
    else if (index == 5)
    {
        m_SortMethod = (GX_SORT_METHOD) value.ToInteger();          
    }
    else if (index == 6)
    {
        if (value.vt == DLMS_DATA_TYPE_NONE)
        {
            m_SortObject = NULL;
        }
        else
        {                
            if (value.Arr.size() != 4)
            {
                //Invalid structure format.
				return ERROR_CODES_INVALID_PARAMETER;
            }
            OBJECT_TYPE type = (OBJECT_TYPE) value.Arr[0].ToInteger();
			string ln;
			CGXOBISTemplate::GetLogicalName(&value.Arr[1].byteArr[0], ln);                
            int attributeIndex = value.Arr[2].ToInteger();
            int dataIndex = value.Arr[3].ToInteger();
            m_SortObject = GetParent()->FindByLN(type, ln);                   
            if(m_SortObject == NULL)
            {                        					
                m_SortObject = CGXDLMSObjectFactory::CreateObject(type);
                m_SortObject->SetLogicalName(ln);                    
            }                                                    
            m_SortObjectAttributeIndex = attributeIndex;
            m_SortObjectDataIndex = dataIndex;
        }                        
    }
    else if (index == 7)
    {                
        //Client can't set row count.
        //TODO: throw new IllegalArgumentException("SetValue failed. Invalid attribute index.");
    }
    else if (index == 8)
    {
		m_ProfileEntries = value.ToInteger();                                    
    }
    else
    {
        return ERROR_CODES_INVALID_PARAMETER;
    }		
	return ERROR_CODES_OK;
}
