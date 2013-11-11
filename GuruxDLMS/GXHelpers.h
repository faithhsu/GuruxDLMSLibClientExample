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

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#include "ErrorCodes.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <string.h>

class GXHelpers
{
public:

#define TRACEUL(text, ul) printf("%s %x%x%x%x\r\n", text, (unsigned char) (ul >> 24) & 0xFF, (unsigned char)(ul >> 16) & 0xFF, (unsigned char) (ul >> 8) & 0xFF, (unsigned char) ul & 0xFF)

#define TRACE1(var) printf(var)
#define TRACE(var, fmt) printf(var, fmt)

static inline void SetBits(unsigned char& byte, unsigned char BitMask, bool val)
{
	unsigned char Mask = 0xFF ^ BitMask;
	byte &= Mask;
	if (val != false)
	{
		byte |= BitMask;
	}
}

static std::vector< basic_string<char> > Split(basic_string<char>& s, char separator)
{	
	std::vector< basic_string<char> > items;	
	int last = 0;
	int pos = -1;
	while((pos = s.find(separator, pos + 1)) != -1)
	{
		basic_string<char> str;
		str.append(s, last, pos - last);
		items.push_back(str);
		last = pos + 1;
	}
	int len = s.length();
	if (last == 0 || last != len)
	{
		basic_string<char> str;
		str.append(s, last, pos);
		items.push_back(str);
	}	
	return items;
}

static std::vector< basic_string<char> > Split(basic_string<char>& s, basic_string<char> separators, bool ignoreEmpty)
{	
	std::vector< basic_string<char> > items;	
	int last = 0;
	int pos = -1;
	while((pos = s.find_first_of(separators, pos + 1)) != -1)
	{
		if (!ignoreEmpty || pos - last != 0)
		{
			basic_string<char> str;
			str.append(s, last, pos - last);
			items.push_back(str);
		}
		last = pos + 1;
	}
	int len = s.length();
	//if (last != len)
	{
		if (!ignoreEmpty || len - last != 0)
		{
			basic_string<char> str;
			str.append(s, last, len - last);
			items.push_back(str);
		}
	}	
	return items;
}

static void Replace(basic_string<char>& str, basic_string<char> oldString, basic_string<char> newString)
{
	int index;
	int len = oldString.length();
	while ((index = str.rfind(oldString)) != -1)
	{
		str.replace(index, len, newString);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Trim from start.
/////////////////////////////////////////////////////////////////////////////
static inline std::string &ltrim(std::string& s) 
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
		std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


/////////////////////////////////////////////////////////////////////////////
// Trim from end.
/////////////////////////////////////////////////////////////////////////////
static inline std::string &rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), 
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

/////////////////////////////////////////////////////////////////////////////
// Trim from both ends
/////////////////////////////////////////////////////////////////////////////
static inline std::string &trim(std::string& s) 
{
	return ltrim(rtrim(s));
}

static inline basic_string<char> bytesToHex(unsigned char* pBytes, int count) 
{
    const char hexArray[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	basic_string<char> hexChars(3 * count, 0);		
    int tmp;
    for (int pos = 0; pos != count; ++pos) 
    {
        tmp = pBytes[pos] & 0xFF;
        hexChars[pos * 3] = hexArray[tmp >> 4];
        hexChars[pos * 3 + 1] = hexArray[tmp & 0x0F];
        hexChars[pos * 3 + 2] = ' ';
    }
    return hexChars;
}

static inline bool GetBits(unsigned char& tmp, unsigned char BitMask)
{
	return (tmp & BitMask) != 0;
}

static inline bool StringCompare(const char* c1, const char* c2)
{
	return strcmp(c1, c2) == 0;
}

static inline void SetUInt16(unsigned short value, std::vector<unsigned char>& buff)
{
#ifdef _BIG_ENDIAN
	buff.push_back(value);
	buff.push_back(value >> 8);
#else	
	buff.push_back(value >> 8);	
	buff.push_back(value & 0xFF);	
#endif
}

static inline void SetUInt32(unsigned long value, std::vector<unsigned char>& buff)
{
#ifdef _BIG_ENDIAN
	buff.push_back((unsigned char) value);
	buff.push_back((unsigned char) (value >> 8));
	buff.push_back((unsigned char) (value >> 16));
	buff.push_back(value >> 24);
#else	
	buff.push_back((unsigned char) (value >> 24));	
	buff.push_back((unsigned char) (value >> 16));	
	buff.push_back((unsigned char) (value >> 8));	
	buff.push_back((unsigned char) (value & 0xFF));	
#endif
}

static int GetLogicalName(basic_string<char> value, unsigned char ln[6])
{
	int count = 0;	
	int size = value.size();
	char *pBuff = new char[size + 1];
	char *pOriginalBuff = pBuff;
	memcpy(pBuff, value.c_str(), size);
	pBuff[value.size()] = 0;
	char* ch;
	int val = 0;
	while((ch = strchr(pBuff, '.')) != NULL)
	{		
		*ch = '\0';
#if _MSC_VER > 1000
		if (sscanf_s(pBuff, "%d", &val) == 1)
#else
		if (sscanf(pBuff, "%d", &val) == 1)
#endif
		
		{
			ln[count] = (unsigned char)val;
			pBuff = ch + sizeof(char);		
			++count;
		}
	}
	if (count == 5)
	{
#if _MSC_VER > 1000
		if (sscanf_s(pBuff, "%d", &val) == 1)
#else
		if (sscanf(pBuff, "%d", &val) == 1)
#endif		
		{
			ln[count] = (unsigned char) val;
			pBuff = ch + sizeof(char);		
			++count;
		}
	}
	delete pOriginalBuff;
	if (count != 6)
	{
		memset(&ln, 0, 6);
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}

static inline void AddRange(vector<char>& buff, const char* pStr, int index = 0, int count = -1)
{
	if (count == -1)
	{
		count = strlen(pStr) - index;
	}
	for(int pos = 0; pos != count; ++pos)
	{
		buff.push_back(pStr[index + pos]);
	}
}

static inline void AddRange(std::vector<char>& buff, std::vector<char>& data, int index = 0, int count = -1)
{
	if (count == -1)
	{
		count = data.size() - index;
	}
	for(int pos = 0; pos != count; ++pos)
	{
		buff.push_back(data[index + pos]);
	}	
}


static inline void AddRange(std::vector<unsigned char>& buff, std::vector<unsigned char>& data, int index = 0, int count = -1)
{
	if (count == -1)
	{
		count = data.size() - index;
	}
	for(int pos = 0; pos != count; ++pos)
	{
		buff.push_back(data[index + pos]);
	}
}

static inline void AddRange(std::vector<unsigned char>& buff, const void* pSource, int count)
{
	for(int pos = 0; pos != count; ++pos)
	{
		buff.push_back(((char*)pSource)[pos]);
	}
}

static inline void ChangeByteOrder(std::vector<unsigned char>& Target, void* pSource, int nSize)
{
#ifdef _BIG_ENDIAN
	for(int pos = 0; pos != nSize; ++pos)
	{
		Target.push_back(pSource[pos]);
	}	
#else
	for(int pos = 0; pos != nSize; ++pos)
	{			
		Target.push_back(((char*) pSource)[nSize - pos - 1]);
	}
#endif
}

static inline void ChangeByteOrder(void* pTarget, void* pSource, int nSize)
{
#ifdef _BIG_ENDIAN
	memcpy(pTarget, pSource, nSize);
#else
	char* pTargetBuff = (char*)pTarget;
	char* pSourceBuff = (char*)pSource;
	if (nSize == 1)
	{
		*pTargetBuff = *pSourceBuff;
	}
	else
	{
		char tmp;
		long lastItem = nSize;		
		for (int firstItem = 0; firstItem < nSize / 2; firstItem++)
		{	
			--lastItem;
			tmp = pSourceBuff[firstItem];
			pTargetBuff[firstItem] = pSourceBuff[lastItem];
			pTargetBuff[lastItem] = tmp;
		}
	}
#endif
}	
};
