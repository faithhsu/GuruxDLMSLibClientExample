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

#include "GXObjectCollection.h"

enum GX_SORT_METHOD
{
    /** 
     First in first out

     When circle buffer is full first item is removed.
    */
    GX_SORT_METHOD_FIFO = 0,
    /** 
     Last in first out.

     When circle buffer is full last item is removed.
    */
    GX_SORT_METHOD_LIFO = 1,
    /** 
     Largest is first.
    */
    GX_SORT_METHOD_LARGEST = 2,
    /** 
     Smallest is first.
    */
    GX_SORT_METHOD_SMALLEST = 3,
    /** 
     Nearst to zero is first.
    */
    GX_SORT_METHOD_NEAREST_TO_ZERO = 4,
    /** 
     Farest from zero is first.
    */
    GX_SORT_METHOD_FAREST_FROM_ZERO = 5
};

class CGXProfileGenericObject : public CGXObject
{
    vector< vector<CGXDLMSVariant> > m_Buffer;
    CGXObjectCollection m_CaptureObjects;
    int m_CapturePeriod;
    GX_SORT_METHOD m_SortMethod;
    CGXObject* m_SortObject;
    char m_ProfileEntries;

	void Init()
	{
		m_SortObject = NULL;
		m_CapturePeriod = 3600;
		m_ProfileEntries = 1;
		m_SortMethod = GX_SORT_METHOD_FIFO;
	}

public:	
	/**  
     Constructor.
    */
	CGXProfileGenericObject() : CGXObject(OBJECT_TYPE_PROFILE_GENERIC)
	{
		Init();
	}

	//SN Constructor.
	CGXProfileGenericObject(unsigned short sn) : CGXObject(OBJECT_TYPE_PROFILE_GENERIC, sn)
	{
		Init();
	}

	//SN Constructor.
	CGXProfileGenericObject(unsigned short sn, CGXDLMSVariant value) : CGXObject(OBJECT_TYPE_PROFILE_GENERIC, sn)
	{
		Init();
	}

	/**  
     Constructor.

     @param ln Logican Name of the object.
    */
	CGXProfileGenericObject(basic_string<char> ln) : CGXObject(OBJECT_TYPE_PROFILE_GENERIC, ln)
	{
		Init();
	}     

    /** 
     Data of profile generic.
    */
    vector< vector<CGXDLMSVariant> > GetBuffer()
    {
        return m_Buffer;
    }
    void SetBuffer(vector< vector<CGXDLMSVariant> > value)
    {
        //m_Buffer.addAll(Arrays.asList(value));
    }

    /** 
     Captured Objects.
    */
    CGXObjectCollection& GetCaptureObjects()
    {
        return m_CaptureObjects;
    }

    /** 
     How often values are captured.
    */
    int GetCapturePeriod()
    {
        return m_CapturePeriod;
    }
    void SetCapturePeriod(int value)
    {
        m_CapturePeriod = value;
    }

    /** 
     How columns are sorted.
    */
    GX_SORT_METHOD GetSortMethod()
    {
        return m_SortMethod;
    }
    void SetSortMethod(GX_SORT_METHOD value)
    {
        m_SortMethod = value;
    }

    /** 
     Column that is used for sorting.
    */
    CGXObject* GetSortObject()
    {
        return m_SortObject;
    }
    void SetSortObject(CGXObject* value)
    {
        m_SortObject = value;
    }

    /** 
     Entries (rows) in Use.
    */
    char GetEntriesInUse()
    {
        return m_Buffer.size();
    }

    /** 
     Maximum Entries (rows) count.
    */
    char GetProfileEntries()
    {
        return m_ProfileEntries;
    }
    void SetProfileEntries(char value)
    {
        m_ProfileEntries = value;
    }

	/** 
	 Clears the buffer.
	*/
	void Reset()
	{
		//TODO:
	}

	/** 
	 Copies the values of the objects to capture 
	 into the buffer by reading capture objects.
	*/
	void Capture()
	{
		//TODO:
	}
    
     /*
     * Returns value of given attribute.
     */    
    int GetValue(int index, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
    {
        if (index == 1)
        {
            GXHelpers::AddRange(value.byteArr, m_LN, 6);
			type = value.vt = DLMS_DATA_TYPE_OCTET_STRING;
			return ERROR_CODES_OK;
        }
        //Should newer call. HandleRequest handles this.
        if (index == 2 || index == 3 || index == 6)
        {
			assert(0);
            return -1;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_INT32;
            return GetCapturePeriod();
        }
        if (index == 5)
        {            
            type = DLMS_DATA_TYPE_INT8;
            return (char) GetSortMethod();
        }
        if (index == 7)
        {
            type = DLMS_DATA_TYPE_INT8;
            return GetEntriesInUse();
        }
        if (index == 8)
        {
            type = DLMS_DATA_TYPE_INT8;
            return GetProfileEntries();
        }
        return -1;
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
        else
        {
            return -1;
        }
    }};
