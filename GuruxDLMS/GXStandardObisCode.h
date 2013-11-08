//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL:  $
//
// Version:         $Revision:  $,
//                  $Date:  $
//                  $Author: $
//
// Copyright (c) Gurux Ltd
//
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
