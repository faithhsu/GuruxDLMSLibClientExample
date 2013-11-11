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
#include <vector>
using namespace std;

#include "Enums.h"
#include "GXDLMSVariant.h"

class CGXOBISTemplate
{
public:
	//Get object count. If first char > 0x80 it will tell chars count.
	static int GetObjectCount(unsigned char* pBuff, int &pos);
	static void SetObjectCount(unsigned int Count, vector<unsigned char>& buff);
	static int GetDataType(unsigned char*& pBuff, int& buffSize, DLMS_DATA_TYPE& Type);
	static int GetData(unsigned char*& pBuff, int& buffSize, DLMS_DATA_TYPE pType, CGXDLMSVariant& value, int* pTotalCnt = NULL, int* pReadCnt = NULL, int* pLastSize = NULL);
	//static int SetData(vector<unsigned char>& buff, DLMS_DATA_TYPE Type, void* Data, int DataLen);
	static int SetData(std::vector<unsigned char>& buff, DLMS_DATA_TYPE type, CGXDLMSVariant value);
	static char GetInt8(unsigned char* pBuff);
	static short GetInt16(unsigned char* pBuff);
	static int GetInt32(unsigned char* pBuff);	
	static long long GetInt64(unsigned char* pBuff);
	static unsigned char GetUInt8(unsigned char* pBuff);
	static unsigned short GetUInt16(unsigned char* pBuff);
	static unsigned int GetUInt32(unsigned char* pBuff);	
	static unsigned long long GetUInt64(unsigned char* pBuff);
	static void GetOctetString(unsigned char* pBuff, unsigned char* value, int len);
	static int GetDateTime(unsigned char* pBuff, int buffLen, char* value);
	static const char* GetUnitAsString(int unit);
};
