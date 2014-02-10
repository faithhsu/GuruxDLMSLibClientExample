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
#include "GXDLMSMonitoredValue.h"
#include "GXDLMSActionSet.h"

class CGXDLMSRegisterMonitor : public CGXDLMSObject
{
	vector<CGXDLMSActionSet> m_Actions;
    CGXDLMSMonitoredValue m_MonitoredValue;
    vector<CGXDLMSVariant> m_Thresholds;
    
public:
	/**  
     Constructor.
    */
	CGXDLMSRegisterMonitor();
    
    /**  
     Constructor.

     @param ln Logican Name of the object.
    */
    CGXDLMSRegisterMonitor(basic_string<char> ln);
    
    /**  
     Constructor.

     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
	CGXDLMSRegisterMonitor(int sn);
    
    vector<CGXDLMSVariant> GetThresholds();
    
	void SetThresholds(vector<CGXDLMSVariant>& value);
    

    CGXDLMSMonitoredValue& GetMonitoredValue();
    
	void SetMonitoredValue(CGXDLMSMonitoredValue& value);
    
    vector<CGXDLMSActionSet>& GetActions();
    
	void SetActions(vector<CGXDLMSActionSet>& value);
    
	// Returns amount of attributes.
	int GetAttributeCount();
	
    // Returns amount of methods.
	int GetMethodCount();
	
	void GetAttributeIndexToRead(vector<int>& attributes);
	    
	int GetDataType(int index, DLMS_DATA_TYPE& type);
	
    /*
     * Returns value of given attribute.
     */    
    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);	
    
    /*
     * Set value of given attribute.
     */
    int SetValue(int index, CGXDLMSVariant& value);	
};