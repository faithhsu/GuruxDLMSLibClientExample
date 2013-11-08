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
#include "GXDLMSVariant.h"

class GXDLMSLimits
{
	CGXDLMSVariant m_MaxInfoTX, m_MaxInfoRX, m_WindowSizeRX, m_WindowSizeTX;
public:
	//Constructor.
	GXDLMSLimits()
    {
        m_MaxInfoTX = (unsigned char)128;
        m_MaxInfoRX = (unsigned char)62;
		m_WindowSizeRX = m_WindowSizeTX = (unsigned long) 1;            
    }

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
