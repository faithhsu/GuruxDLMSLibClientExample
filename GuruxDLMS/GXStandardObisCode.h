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
#include <string>
#include <vector>
using namespace std;

class CGXStandardObisCode
{
    vector< basic_string<char> > m_OBIS;
    basic_string<char> m_DataType;        
    basic_string<char> m_Interfaces;        
    basic_string<char> m_Description;
public:	
	// Constructor.
    CGXStandardObisCode()
	{
	}

    // Constructor.
    CGXStandardObisCode(vector< basic_string<char> > obis, basic_string<char>& desc, 
            basic_string<char>& interfaces, basic_string<char>& dataType);
    // OBIS code.
    vector< basic_string<char> >& GetOBIS();
	
	void SetOBIS(vector< basic_string<char> >& value);

	// OBIS code description.
    basic_string<char>& GetDescription();
    
    void SetDescription(basic_string<char> value);

	// Interfaces that are using this m_OBIS code.
    basic_string<char>& GetInterfaces();
    void SetInterfaces(basic_string<char> value);

    // Standard data types.
    basic_string<char>& GetDataType();
    void SetDataType(basic_string<char> value);
};
