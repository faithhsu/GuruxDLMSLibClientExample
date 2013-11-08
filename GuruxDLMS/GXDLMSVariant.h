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
#include "Enums.h"
#include "ErrorCodes.h"
#include "GXDateTime.h"

#define __tagVARIANT
#define __VARIANT_NAME_1
#define __VARIANT_NAME_2
#define __VARIANT_NAME_3

class CGXDLMSVariant;

struct dlmsVARIANT
    {
    union 
        {
        struct __tagVARIANT
            {
            DLMS_DATA_TYPE vt;
            union 
                {					                
                long lVal;
                unsigned char bVal;
                char cVal;
				short iVal;
				int intVal;
                float fltVal;
                double dblVal;
				bool boolVal;	
				unsigned short uiVal;
				unsigned int uintVal;
				unsigned long ulVal;
				long long llVal;
				unsigned long long ullVal;				
                } 	__VARIANT_NAME_3;
            } 	__VARIANT_NAME_2;        
        } 	__VARIANT_NAME_1;
	CGXDateTime dateTime;
    basic_string<char> strVal;
	vector<unsigned char> byteArr;
	vector<CGXDLMSVariant> Arr;
    } ;

class CGXDLMSVariant : public dlmsVARIANT
{
	static int Convert(CGXDLMSVariant* item, DLMS_DATA_TYPE type);
public:
	void Clear();
	CGXDLMSVariant();
	
	CGXDLMSVariant(float value);
	CGXDLMSVariant(double value);

	CGXDLMSVariant(unsigned long long value);
	CGXDLMSVariant(long long value);
	CGXDLMSVariant(bool value);
	CGXDLMSVariant(char value);
	CGXDLMSVariant(short value);
	CGXDLMSVariant(int value);
	CGXDLMSVariant(long value);
	CGXDLMSVariant(struct tm value);
	CGXDLMSVariant(vector<unsigned char> value);
	CGXDLMSVariant(CGXDateTime value);	
	
	CGXDLMSVariant(CGXDLMSVariant* value);
	CGXDLMSVariant(unsigned char* pValue, int size, DLMS_DATA_TYPE type);
	CGXDLMSVariant(unsigned char value);
	CGXDLMSVariant(unsigned short value);
	CGXDLMSVariant(unsigned int value);
	CGXDLMSVariant(unsigned long value);
	CGXDLMSVariant(basic_string<char> value);
	CGXDLMSVariant(const char* value);
	CGXDLMSVariant& operator=(basic_string<char> value);
	CGXDLMSVariant& operator=(const char* value);
	CGXDLMSVariant& operator=(float value);
	CGXDLMSVariant& operator=(double value);
	CGXDLMSVariant& operator=(unsigned long long value);
	CGXDLMSVariant& operator=(long long value);
	CGXDLMSVariant& operator=(bool value);
	CGXDLMSVariant& operator=(char value);
	CGXDLMSVariant& operator=(short value);
	CGXDLMSVariant& operator=(int value);
	CGXDLMSVariant& operator=(long value);
	CGXDLMSVariant& operator=(unsigned char value);
	CGXDLMSVariant& operator=(unsigned short value);
	CGXDLMSVariant& operator=(unsigned int value);
	CGXDLMSVariant& operator=(unsigned long value);
	CGXDLMSVariant& operator=(struct tm value);	
	CGXDLMSVariant& operator=(vector<unsigned char> value);		
	CGXDLMSVariant& operator=(CGXDateTime value);		
	void Add(unsigned char*, int count);
	void Add(char*, int count);
	void Add(basic_string<char>& value);
	bool Equals(CGXDLMSVariant& item);
	int ChangeType(DLMS_DATA_TYPE newType);
	//Returns bytes as Big Endian byteorder.
	void GetBytes(std::vector<unsigned char>& buff);
	//Get size in bytes.
	int GetSize();
	//Get size in bytes.
	static int GetSize(DLMS_DATA_TYPE vt);	
	basic_string<char> ToString();
	basic_string<char> ToDateTime();
	basic_string<char> ToDate();
	basic_string<char> ToTime();
};
