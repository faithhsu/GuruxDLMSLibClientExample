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
