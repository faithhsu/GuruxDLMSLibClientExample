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
using namespace std;

class CGXDLMSImageActivateInfo
{
	long m_Size;
    string m_Identification;
    string m_Signature;
public:	
	/**
     * Constructor.
     */
    CGXDLMSImageActivateInfo();

	/**
     * Constructor.
     */
    CGXDLMSImageActivateInfo(long size, string identification, string signature);
    
	 /** 
      *  Image_size is the size of the Image(s) to be activated. 
      *  Expressed in octets;
    */
    long GetSize();
    void SetSize(long value);
    
     /** 
      * Image identification is the identification of the Image(s)
      * to be activated, and may contain information like
      * manufacturer, device type, version information, etc.
    */
    string GetIdentification();
    void SetIdentification(string value);
    
     /** 
      * Image signature is the signature of the Image(s) to be activated.
    */
    string GetSignature();
    void SetSignature(string value);

	string ToString();
};
