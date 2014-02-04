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
#include "../GXDateTime.h"

enum GXDLMS_CLOCK_STATUS
{
	GXDLMS_CLOCK_STATUS_OK = 0x0,
	GXDLMS_CLOCK_STATUS_INVALID_VALUE = 0x1,
	GXDLMS_CLOCK_STATUS_DOUBTFUL_VALUE = 0x2,
	GXDLMS_CLOCK_STATUS_DIFFERENT_CLOCK_BASE = 0x4,
    GXDLMS_CLOCK_STATUS_RESERVED1 = 0x8,
	GXDLMS_CLOCK_STATUS_RESERVED2 = 0x10,
    GXDLMS_CLOCK_STATUS_RESERVED3 = 0x20,
    GXDLMS_CLOCK_STATUS_RESERVED4 = 0x40,
    GXDLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE = 0x80,
};

class CGXDLMSClock : public CGXDLMSObject
{
    char m_ClockBase;
    char m_Deviation;
    bool m_Enabled;
    CGXDateTime m_End;
    GXDLMS_CLOCK_STATUS m_Status;
    CGXDateTime m_Begin;
    unsigned short m_TimeZone;
    CGXDateTime m_Time;

	void Init();
public:
    /**  
     Constructor.
    */
	CGXDLMSClock();

    /**  
     Constructor.
     @param ln Logican Name of the object.
    */
    CGXDLMSClock(basic_string<char> ln);

    /**  
     Constructor.
     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSClock(basic_string<char> ln, int sn);

	/** 
     Time of COSEM Clock object.
    */	
    CGXDateTime GetTime();

	void SetTime(CGXDateTime& value);

    /** 
     TimeZone of COSEM Clock object.
    */
    unsigned short GetTimeZone();
    void SetTimeZone(unsigned short value);

    /** 
     Status of COSEM Clock object.
    */
    GXDLMS_CLOCK_STATUS GetStatus();
    void SetStatus(GXDLMS_CLOCK_STATUS value);

    CGXDateTime GetBegin();
    void SetBegin(CGXDateTime& value);

	CGXDateTime GetEnd();
	void SetEnd(CGXDateTime& value);

    char GetDeviation();
    void SetDeviation(char value);
    
    bool GetEnabled();
    void SetEnabled(bool value);

    /** 
     Clock base of COSEM Clock object.
    */
    char GetClockBase();
    void SetClockBase(char value);
    
	// Returns amount of attributes.
	int GetAttributeCount();
	
    // Returns amount of methods.
	int GetMethodCount();

	void GetAttributeIndexToRead(vector<int>& attributes);	

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
