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

struct IGXDLMSBase
{
public:
    // Returns amount of attributes.
    virtual int GetAttributeCount() = 0;

    // Returns amount of methods.
    virtual int GetMethodCount() = 0;

    // Returns value of given attribute.
    virtual int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value) = 0;
    
    // Set value of given attribute.
    virtual int SetValue(int index, CGXDLMSVariant& value) = 0;

    // Invokes method.
    virtual int Invoke(int index, CGXDLMSVariant& parameters) = 0;

//	virtual DLMS_DATA_TYPE GetUIDataType(int index) = 0;
};