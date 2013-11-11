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
#include "ErrorCodes.h"
#include "Enums.h"
#include "GXStandardObisCode.h"
#include "GXHelpers.h"

/////////////////////////////////////////////////////////////////////////////
// Obis Code Collection is used to save all default OBIS Codes.
/////////////////////////////////////////////////////////////////////////////
class CGXStandardObisCodeCollection : public std::vector<CGXStandardObisCode>
{
	//Convert logican name string to bytes.
    static int GetBytes(basic_string<char> ln, unsigned char* bytes);
    
    // Check is interface included to standard.    
    bool EqualsInterface(CGXStandardObisCode item, int ic);

    // Check OBIS codes.
    static bool EqualsMask(basic_string<char> obis, int ic);
    
	// Check OBIS code.    
    static bool EqualsObisCode(vector< basic_string<char> >& obisMask, unsigned char* ic);

    // Get description.    
    basic_string<char> GetDescription(basic_string<char>& str);

public:
    bool Find(basic_string<char> ln, OBJECT_TYPE objectType, CGXStandardObisCode& item);

    static bool EqualsMask(basic_string<char> obisMask, basic_string<char> ln);

	// Find Standard OBIS Code description.    
    bool Find(unsigned char* pObisCode, int IC, CGXStandardObisCode& tmp);
};
