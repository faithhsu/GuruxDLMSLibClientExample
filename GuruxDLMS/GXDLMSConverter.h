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

#include "Enums.h"

//This class is used to convert enum and error values to string.
class CGXDLMSConverter
{
public:
	//Get Unit as String.
	static const char* GetUnitAsString(int unit);
	//Get baudrate enum balue as string.
	static const char* ToString(BAUDRATE value);
	//Get clock base enum value as string.
	static const char* ToString(CLOCKBASE value);	
	//Get clock status enum value as string.
	static const char* ToString(GXDLMS_CLOCK_STATUS value);

	//Get error message as string.
	static const char* GetErrorMessage(int error);

	//Get address state enum value as string.
	static const char* ToString(ADDRESS_STATE value);	

	//Get Disconnect control control state as a string.
	static const char* ToString(CONTROLSTATE value);	

	//Get Disconnect control control mode as a string.
	static const char* ToString(CONTROLMODE value);	

	//Get Security Setup security policy as a string.
	static const char* ToString(SECURITY_POLICY value);	

	//Get Security Setup security suite as a string.
	static const char* ToString(SECURITY_SUITE value);	
	
};
