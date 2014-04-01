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
#include <vector>
using namespace std;

class CGXxDLMSContextType
{
private:
	string m_Conformance;
    int m_MaxReceivePduSize;
    int m_MaxSendPpuSize;
    int m_DlmsVersionNumber;
    int m_QualityOfService;
    vector<unsigned char> m_CypheringInfo;
    
public:
    string GetConformance();
    void SetConformance(string value);

	int GetMaxReceivePduSize();
    void SetMaxReceivePduSize(int value);

    int GetMaxSendPpuSize();
    void SetMaxSendPpuSize(int value);

    int GetDlmsVersionNumber();
    void SetDlmsVersionNumber(int value);

	int GetQualityOfService();
    void SetQualityOfService(int value);
    
    vector<unsigned char>& GetCypheringInfo();
	void SetCypheringInfo(vector<unsigned char>& value);
       
    string ToString();
};
