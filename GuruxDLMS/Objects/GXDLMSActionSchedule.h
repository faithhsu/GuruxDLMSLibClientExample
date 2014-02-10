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

#include "GXDLMSObject.h"

enum SINGLE_ACTION_SCHEDULE_TYPE
{
    /** 
     Size of execution_time = 1. Wildcard in date allowed.
    */
    SINGLE_ACTION_SCHEDULE_TYPE1 = 0,
    /** 
     Size of execution_time = n. 
     All time values are the same, wildcards in date not allowed.
    */
    SINGLE_ACTION_SCHEDULE_TYPE2 = 1,
    /** 
     Size of execution_time = n. 
     All time values are the same, wildcards in date are allowed,
    */
    SINGLE_ACTION_SCHEDULE_TYPE3 = 2,
    /** 
     Size of execution_time = n.
     Time values may be different, wildcards in date not allowed,
    */
    SINGLE_ACTION_SCHEDULE_TYPE4 = 3,
    /** 
     Size of execution_time = n.
     Time values may be different, wildcards in date are allowed
    */
    SINGLE_ACTION_SCHEDULE_TYPE5 = 4
};

class CGXDLMSActionSchedule : public CGXDLMSObject
{
	basic_string<char> m_ExecutedScriptLogicalName;
    int m_ExecutedScriptSelector;
    SINGLE_ACTION_SCHEDULE_TYPE m_Type;
    vector<CGXDateTime> m_ExecutionTime;
    
	void Init();
public:

    /**  
     Constructor.
    */
	CGXDLMSActionSchedule();

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSActionSchedule(basic_string<char> ln);

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSActionSchedule(int sn);
        
    basic_string<char> GetExecutedScriptLogicalName();
    void SetExecutedScriptLogicalName(basic_string<char> value);

    int GetExecutedScriptSelector();
    void SetExecutedScriptSelector(int value);

    SINGLE_ACTION_SCHEDULE_TYPE GetType();
    void SetType(SINGLE_ACTION_SCHEDULE_TYPE value);

    vector<CGXDateTime> GetExecutionTime();
    void SetExecutionTime(vector<CGXDateTime> value);

   // Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	void GetAttributeIndexToRead(vector<int>& attributes);	

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);
       
    // Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
