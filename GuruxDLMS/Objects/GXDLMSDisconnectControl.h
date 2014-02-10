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

#include "GXDLMSObject.h"

enum CONTROLSTATE 
{
    /*
     * The output_state is set to false and the consumer is disconnected.
     */
    CONTROLSTATE_DISCONNECTED,
    /*
     * The output_state is set to true and the consumer is connected.
     */
    CONTROLSTATE_CONNECTED,
    /*
     * The output_state is set to false and the consumer is disconnected.
     */
    CONTROLSTATE_READY_FOR_RECONNECTION
};


/*
 * Configures the behaviour of the disconnect control object for all
triggers, i.e. the possible state transitions.
 */
enum CONTROLMODE 
{
    /*
     * The disconnect control object is always in 'connected' state,
     */
    CONTROLMODE_NONE,
    /*
     * Disconnection: Remote (b, c), manual (f), local (g) 
     * Reconnection: Remote (d), manual (e).
     */
    CONTROLMODE_MODE_1,
    /*
     * Disconnection: Remote (b, c), manual (f), local (g) 
     * Reconnection: Remote (a), manual (e).
     */
    CONTROLMODE_MODE_2,
    /*
     * Disconnection: Remote (b, c), manual (-), local (g) 
     * Reconnection: Remote (d), manual (e).
     */
    CONTROLMODE_MODE_3,
    /*
     * Disconnection: Remote (b, c), manual (-), local (g) 
     * Reconnection: Remote (a), manual (e)
     */
    CONTROLMODE_MODE_4,
    /*
     * Disconnection: Remote (b, c), manual (f), local (g) 
     * Reconnection: Remote (d), manual (e), local (h),
     */
    CONTROLMODE_MODE_5,
    /*
     * Disconnection: Remote (b, c), manual (-), local (g) 
     * Reconnection: Remote (d), manual (e), local (h)
     */
    CONTROLMODE_MODE_6,
};

class CGXDLMSDisconnectControl : public CGXDLMSObject
{
	bool m_OutputState;
    CONTROLSTATE m_ControlState;        
    CONTROLMODE m_ControlMode;

public:	
	//Constructor.
	CGXDLMSDisconnectControl();

	//SN Constructor.
	CGXDLMSDisconnectControl(unsigned short sn);

	//LN Constructor.
	CGXDLMSDisconnectControl(basic_string<char> ln);
	
	/** 
     Output state of COSEM Disconnect Control object.
    */
    bool GetOutputState();
    void SetOutputState(bool value);

    /** 
     Control state of COSEM Disconnect Control object.
    */
    CONTROLSTATE GetControlState();
    void SetControlState(CONTROLSTATE value);
    
     /** 
     Control mode of COSEM Disconnect Control object.
    */
    CONTROLMODE GetControlMode();
    void SetControlMode(CONTROLMODE value);

    // Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	void GetAttributeIndexToRead(vector<int>& attributes);

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
