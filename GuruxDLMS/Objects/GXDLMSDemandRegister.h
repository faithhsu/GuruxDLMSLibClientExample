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

#include <cmath>
#include "GXDLMSObject.h"

class CGXDLMSDemandRegister : public CGXDLMSObject
{
	CGXDLMSVariant m_CurrentAvarageValue;    
    CGXDLMSVariant m_LastAvarageValue;    
    char m_Scaler;
	unsigned char m_Unit;
    CGXDLMSVariant m_Status;
    CGXDateTime m_CaptureTime;
    CGXDateTime m_StartTimeCurrent;
    int m_NumberOfPeriods;
    unsigned long m_Period;

protected:
	bool IsRead(int index);

public:
    /**  
     Constructor.
    */
	CGXDLMSDemandRegister();

    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSDemandRegister(basic_string<char> ln);

    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSDemandRegister(int sn);
    
    /** 
     Current avarage value of COSEM Data object.
    */
    CGXDLMSVariant GetCurrentAvarageValue();
	void SetCurrentAvarageValue(CGXDLMSVariant value);

    /** 
     Last avarage value of COSEM Data object.
    */
    CGXDLMSVariant GetLastAvarageValue();
    void SetLastAvarageValue(CGXDLMSVariant value);

    /** 
     Scaler of COSEM Register object.
    */
    double GetScaler();
    void SetScaler(double value);

	// Unit of COSEM Register object.    
    int GetUnit();
	void SetUnit(unsigned char value);

	/** 
     Scaler of COSEM Register object.
    */
    CGXDLMSVariant GetStatus();
    void SetStatus(CGXDLMSVariant value);

    /** 
     Capture time of COSEM Register object.
    */
    CGXDateTime GetCaptureTime();
    void SetCaptureTime(CGXDateTime value);

    /** 
     Current start time of COSEM Register object.
    */
    CGXDateTime GetStartTimeCurrent();
    void SetStartTimeCurrent(CGXDateTime value);

    unsigned long GetPeriod();
    void SetPeriod(unsigned long value);
    
    int GetNumberOfPeriods();
    void SetNumberOfPeriods(int value);

    /*
     * Reset value.
     */
    void Reset();
    
    /*
     * Next period.
     */
    void NextPeriod();
    
	//Get attribute values of object.
	void GetValues(vector<string>& values);

	void GetAttributeIndexToRead(vector<int>& attributes);
    
	// Returns amount of attributes.
	int GetAttributeCount();

	// Returns amount of methods.
	int GetMethodCount();

	int Invoke(int index, CGXDLMSVariant& value);

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);
    
    int SetValue(int index, CGXDLMSVariant& value);
};