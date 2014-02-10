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

//Mikko #include "GXDLMSObjectCollection.h"
#include "GXDLMSCaptureObject.h"
#include "GXDLMSRegister.h"

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

class CGXDLMSProfileGeneric : public CGXDLMSObject
{
private:
    vector< vector<CGXDLMSVariant> > m_Buffer;
	std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> > m_CaptureObjects;
    int m_CapturePeriod;
    GX_SORT_METHOD m_SortMethod;
    CGXDLMSObject* m_SortObject;
    char m_ProfileEntries;

    int m_SortObjectAttributeIndex;
    int m_SortObjectDataIndex;


	void Init();

	int GetColumns(vector<unsigned char>& data);
	int GetData(vector< vector<CGXDLMSVariant> > table, vector<unsigned char>& data);    

	 /*
     * Add new capture object (column) to the profile generic.
     */
    int AddCaptureObject(CGXDLMSObject* pObj, int attributeIndex, int dataIndex);
    
	int GetAccessSelector(unsigned char* data, int Length, int& Selector, CGXDLMSVariant& start, CGXDLMSVariant& to);

	int GetProfileGenericData(unsigned char* parameters, int length, vector<unsigned char>& reply);    

public:	
	/**  
     Constructor.
    */
	CGXDLMSProfileGeneric();
	
	//SN Constructor.
	CGXDLMSProfileGeneric(unsigned short sn);
	
	//SN Constructor.
	CGXDLMSProfileGeneric(unsigned short sn, CGXDLMSVariant value);
	
	/**  
     Constructor.

     @param ln Logican Name of the object.
    */
	CGXDLMSProfileGeneric(basic_string<char> ln);
	
    /** 
     Data of profile generic.
    */
    vector< vector<CGXDLMSVariant> >& GetBuffer();
    
    /** 
     Captured Objects.
    */
    std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >& GetCaptureObjects();
    
    /** 
     How often values are captured.
    */
    int GetCapturePeriod();
    void SetCapturePeriod(int value);
    
    /** 
     How columns are sorted.
    */
    GX_SORT_METHOD GetSortMethod();
    void SetSortMethod(GX_SORT_METHOD value);

    /** 
     Column that is used for sorting.
    */
    CGXDLMSObject* GetSortObject();    
	void SetSortObject(CGXDLMSObject* value);

    /** 
     Entries (rows) in Use.
    */
    char GetEntriesInUse();
    
    /** 
     Maximum Entries (rows) count.
    */
    char GetProfileEntries();   
	void SetProfileEntries(char value);
	 /** 
     Attribute index of sort object.
    */
    int GetSortObjectAttributeIndex();
    void SetSortObjectAttributeIndex(int value);
    
    /** 
     Data index of sort object.
    */
    int GetSortObjectDataIndex();    
	void SetSortObject(int value);
    
	/** 
	 Clears the buffer.
	*/
	void Reset();

	/** 
	 Copies the values of the objects to capture 
	 into the buffer by reading capture objects.
	*/
	void Capture();
    
	void GetAttributeIndexToRead(vector<int>& attributes);

	//Returns amount of attributes.     
	int GetAttributeCount();
    
	//Returns amount of methods.     
    int GetMethodCount();
    
	int GetDataType(int index, DLMS_DATA_TYPE& type);
    
     /*
     * Returns value of given attribute.
     */    
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

    /*
     * Set value of given attribute.
     */
    int SetValue(int index, CGXDLMSVariant& value);   
};
