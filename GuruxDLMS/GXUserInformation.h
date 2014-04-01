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

const char InitialRequest = 0x1;
const char InitialResponce = 0x8;

//User Information field is optional.
class CGXUserInformation
{
	unsigned char m_ConformanceBlock[3];
public:
	unsigned short MaxReceivePDUSize;
	char DLMSVersioNumber;

	CGXUserInformation() : MaxReceivePDUSize(0xFFFF), DLMSVersioNumber(6)
	{
	}

	unsigned char* GetConformanceBlock()
	{	
		return m_ConformanceBlock;
	}
	
	void SetConformanceBlock(unsigned char* pBuff)
	{
		memcpy(&m_ConformanceBlock, pBuff, 3);
	}

	//User information code is special case...
	int CodeData(std::vector<unsigned char>& buff)
	{
		buff.push_back(0xBE); //Tag
		buff.push_back(0x10); //Length for AARQ user field
		buff.push_back(0x04); //Coding the choice for user-information (Octet STRING, universal)
		buff.push_back(0x0E); //Length
		buff.push_back(InitialRequest); // Tag for xDLMS-Initiate request
		buff.push_back(0x00); // Usage field for dedicated-key component not used
		buff.push_back(0x00); // Usage field for the response allowed component not used
		buff.push_back(0x00); // Usage field of the proposed-quality-of-service component not used
		buff.push_back(DLMSVersioNumber);
		// Tag for conformance block
		buff.push_back(0x5F);
		buff.push_back(0x1F);
		buff.push_back(0x04);// length of the conformance block
		buff.push_back(0x00);// encoding the number of unused bits in the bit string 
		GXHelpers::AddRange(buff, &m_ConformanceBlock, 3);
		buff.push_back(((MaxReceivePDUSize >> 8) & 0xFF));
		buff.push_back(MaxReceivePDUSize & 0xFF);
		return ERROR_CODES_OK;
	}

	int EncodeData(unsigned char*& pBuff, int& size)
	{
		unsigned char* pStart = pBuff;
		int tag = *pBuff++ & 0xFF;
		if (tag != 0xBE)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		int len = *pBuff++ & 0xFF;
		if (len > size)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		//Excoding the choice for user information
		tag = *pBuff++ & 0xFF;
		if (tag != 0x4)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		len = *pBuff++ & 0xFF;
		//Tag for xDLMS-Initate.response 
		tag = *pBuff++ & 0xFF;
		if (tag == InitialResponce)
		{
			//Optional usage field of the negotiated quality of service component
			tag = *pBuff++ & 0xFF;
			if (tag != 0)//Skip if used.
			{
				len = *pBuff++;
				pBuff += len;
			}
		}
		else if (tag == InitialRequest)
        {
			//Optional usage field of the negotiated quality of service component
			tag = *pBuff++ & 0xFF;
			if (tag != 0)//Skip if used.
			{
				len = *pBuff++;
				pBuff += len;
			}
			//Optional usage field of the negotiated quality of service component
			tag = *pBuff++ & 0xFF;
			if (tag != 0)//Skip if used.
			{
				len = *pBuff++;
				pBuff += len;
			}
			//Optional usage field of the negotiated quality of service component
			tag = *pBuff++ & 0xFF;
			if (tag != 0)//Skip if used.
			{
				len = *pBuff++;
				pBuff += len;
			}
		}
		else
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		//Get DLMS version number.
		DLMSVersioNumber = *pBuff++ & 0xFF;
		//Tag for conformance block
		tag = *pBuff++ & 0xFF;
		if (tag != 0x5F)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		//Old Way...
		tag = *pBuff & 0xFF;
		if (tag == 0x1F)
		{
			pBuff++;
		}
		len = *pBuff++ & 0xFF;
		//The number of unused bits in the bit string.
		tag = *pBuff++ & 0xFF;
		memcpy(&m_ConformanceBlock, pBuff, 3);
		pBuff += 3;
		GXHelpers::ChangeByteOrder(&MaxReceivePDUSize, pBuff, 2);
		pBuff += 2;
		//VAA Name
		tag = *pBuff++ & 0xFF;
		tag = *pBuff++ & 0xFF;		
		size -= (pBuff - pStart);
		return ERROR_CODES_OK;
	}
};