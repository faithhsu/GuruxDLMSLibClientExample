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

#include <math.h>
#include "GXDLMSObject.h"

class CGXDLMSRegister : public CGXDLMSObject
{
	void Init();
protected:
	CGXDLMSVariant m_Value;
	unsigned char m_Scaler;
	unsigned char m_Unit;

	//SN Constructor.
	CGXDLMSRegister(OBJECT_TYPE type, unsigned short sn);
	
	//LN Constructor.
	CGXDLMSRegister(OBJECT_TYPE type, basic_string<char> ln);
	
	bool IsRead(int index);
    
public:
	//Constructor.
	CGXDLMSRegister(void);
	
	//SN Constructor.
	CGXDLMSRegister(unsigned short sn);
	
	//SN Constructor.
	CGXDLMSRegister(unsigned short sn, double scaler, int unit, CGXDLMSVariant value);
	
	//LN Constructor.
	CGXDLMSRegister(basic_string<char> ln);
	
	//LN Constructor.
	CGXDLMSRegister(basic_string<char> ln, double scaler, int unit, CGXDLMSVariant value);
	
	/// <summary>
    /// Get value of COSEM Data object.
    /// </summary>        
    CGXDLMSVariant GetValue();
    
	/// <summary>
    /// Set value of COSEM Data object.
    /// </summary>        
    void SetValue(CGXDLMSVariant& value);
    
	// Scaler of COSEM Register object.    
    double GetScaler();
    
    void SetScaler(double value);
    
    // Unit of COSEM Register object.    
    int GetUnit();
    
	void SetUnit(unsigned char value);
    
	/*
     * Reset value.
     */
    void Reset();
    
	// Returns amount of attributes.
	int GetAttributeCount();
	
    // Returns amount of methods.
	int GetMethodCount();
	
	int Invoke(int index, CGXDLMSVariant& value);
	
	void GetAttributeIndexToRead(vector<int>& attributes);	

	int GetDataType(int index, DLMS_DATA_TYPE& type);
    
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);
	
	int SetValue(int index, CGXDLMSVariant& value);	
};
