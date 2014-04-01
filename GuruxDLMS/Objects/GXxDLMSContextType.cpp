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

#include "GXxDLMSContextType.h"
#include "../GXDLMSVariant.h"
#include "../GXHelpers.h"
#include <sstream> 

string CGXxDLMSContextType::GetConformance()
{
    return m_Conformance;
}
void CGXxDLMSContextType::SetConformance(string value)
{
    m_Conformance = value;
}

int CGXxDLMSContextType::GetMaxReceivePduSize()
{
    return m_MaxReceivePduSize;
}
void CGXxDLMSContextType::SetMaxReceivePduSize(int value)
{
    m_MaxReceivePduSize = value;
}

int CGXxDLMSContextType::GetMaxSendPpuSize()
{
    return m_MaxSendPpuSize;
}
void CGXxDLMSContextType::SetMaxSendPpuSize(int value)
{
    m_MaxSendPpuSize = value;
}

int CGXxDLMSContextType::GetDlmsVersionNumber()
{
    return m_DlmsVersionNumber;
}
void CGXxDLMSContextType::SetDlmsVersionNumber(int value)
{
    m_DlmsVersionNumber = value;
}
int CGXxDLMSContextType::GetQualityOfService()
{
    return m_QualityOfService;
}
void CGXxDLMSContextType::SetQualityOfService(int value)
{
    m_QualityOfService = value;
}

vector<unsigned char>& CGXxDLMSContextType::GetCypheringInfo()
{
    return m_CypheringInfo;
}

void CGXxDLMSContextType::SetCypheringInfo(vector<unsigned char>& value)
{
    m_CypheringInfo = value;
}

string CGXxDLMSContextType::ToString()
{
	std::stringstream sb;
	sb << CGXDLMSVariant(m_Conformance).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_MaxReceivePduSize).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_MaxSendPpuSize).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_DlmsVersionNumber).ToString().c_str();
	sb << " ";
	sb << CGXDLMSVariant(m_QualityOfService).ToString().c_str();
	sb << " ";
	if (!m_CypheringInfo.empty())
	{
		sb << GXHelpers::bytesToHex(&m_CypheringInfo[0], m_CypheringInfo.size()).c_str();
	}
	return sb.str();
}