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
#include "GXDLMSVariant.h"

class GXDLMSLimits
{
	CGXDLMSVariant m_MaxInfoTX, m_MaxInfoRX, m_WindowSizeRX, m_WindowSizeTX;
public:
	//Constructor.
	GXDLMSLimits();

    // The maximum information field length in transmit.    
    // DefaultValue is 128.
    CGXDLMSVariant GetMaxInfoTX()
    {
		return m_MaxInfoTX;
    }

	void SetMaxInfoTX(CGXDLMSVariant value)
    {
		m_MaxInfoTX = value;
    }
    
    /// The maximum information field length in receive.        
    /// DefaultValue is 62.    
    CGXDLMSVariant GetMaxInfoRX()
    {
		return m_MaxInfoRX;
    }

	void SetMaxInfoRX(CGXDLMSVariant value)
    {
		m_MaxInfoRX = value;
    }

    /// The window size in transmit.
    /// DefaultValue is 1.
    CGXDLMSVariant GetWindowSizeTX()
    {
		return m_WindowSizeRX;
    }

	void SetWindowSizeTX(CGXDLMSVariant value)
    {
		m_WindowSizeRX = value;
    }

    /// The window size in receive.      
    /// DefaultValue is 1.    
    CGXDLMSVariant GetWindowSizeRX()
    {
		return m_WindowSizeTX;
    }

	void SetWindowSizeRX(CGXDLMSVariant value)
    {
		m_WindowSizeTX = value;
    }
};
