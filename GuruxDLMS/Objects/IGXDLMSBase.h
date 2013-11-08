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

struct IGXDLMSBase
{
public:
    // Returns amount of attributes.
    virtual int GetAttributeCount() = 0;

    // Returns amount of methods.
    virtual int GetMethodCount() = 0;

    // Returns value of given attribute.
    virtual int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type) = 0;
    
    // Set value of given attribute.
    virtual int SetValue(int index, CGXDLMSVariant& value) = 0;

    // Invokes method.
    virtual int Invoke(int index, CGXDLMSVariant& parameters) = 0;

//	virtual DLMS_DATA_TYPE GetUIDataType(int index) = 0;
};