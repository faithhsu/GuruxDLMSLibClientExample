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
#include <assert.h>
#include <vector>
using namespace std;
#include "Enums.h"
#include "ErrorCodes.h"
#include "GXHelpers.h"
#include "GXApplicationContextName.h"
#include "GXUserInformation.h"
#include "GXOBISTemplate.h"

const char AARQTag = 0x60;
const char AARETag = 0x61;

const unsigned char LLCSendBytes[3] = {0xE6, 0xE6, 0x00};
const unsigned char LLCReplyBytes[3] = {0xE6, 0xE7, 0x00};

enum GXDLMS_ASSOCIATION_RESULT
{
	GXDLMS_ASSOCIATION_RESULT_ACCEPTED = 0,
	GXDLMS_ASSOCIATION_RESULT_REJECTED_PERMAMENT = 1,
	GXDLMS_ASSOCIATION_RESULT_REJECTED_TRANSIENT = 2
};

enum GXDLMS_SOURCE_DIAGNOSTIC
{
	GXDLMS_SOURCE_DIAGNOSTIC_NULL = 0,
	GXDLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN = 1,
	GXDLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED = 2,
	GXDLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_NOT_RECOGNISED = 11,
	GXDLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_REQUIRED = 12,
	GXDLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE =13,
	GXDLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED =14
};

enum DLMS_FRAME_TYPE
{
		//////////////////////////////////////////////////////////
		// This command is used to set the secondary station in connected mode and reset
		// its sequence number variables.
		DLMS_FRAME_TYPE_SNRM		= 0x93, // Set Normal Response Mode (SNRM)
		//////////////////////////////////////////////////////////
		// This response is used to confirm that the secondary received and acted on an SNRM or DISC command.
		DLMS_FRAME_TYPE_UA			= 0x73, // Unnumbered Acknowledge (UA)
		//////////////////////////////////////////////////////////
		// This command and response is used to transfer a block of data together with its sequence number. 
		// The command also includes the sequence number of the next frame the transmitting station expects to see. 
		// This way, it works as an RR. Like RR, it enables transmission of I frames from the opposite side.
		DLMS_FRAME_TYPE_INFORMATION = 0x10, // Information (I)
		//////////////////////////////////////////////////////////
		// This response is used to indicate an error condition. The two most likely error conditions are:
		// Invalid command or Sequence number problem.
		DLMS_FRAME_TYPE_REJECTED = 0x97,  // Frame Reject 
		//////////////////////////////////////////////////////////
		// This command is used to terminate the connection.
		DLMS_FRAME_TYPE_DISCONNECT = 0x53,
		//////////////////////////////////////////////////////////
		// This response is used to inform the primary station that the secondary is disconnected.
		DLMS_FRAME_TYPE_DISCONNECT_MODE = 0x1F // Disconnected Mode
};

class GXAPDU
{
	basic_string<char> m_Password;
	GXDLMS_AUTHENTICATION m_Authentication;
	CGXApplicationContextNamePdu m_ApplicationContextName;
	unsigned long ResultValue, ResultDiagnosticValue;	
public:
	CGXUserInformation UserInformation;
	GXAPDU() : m_Authentication(GXDLMS_AUTHENTICATION_NONE), 
				ResultValue(0), ResultDiagnosticValue(0)
	{
	}

	~GXAPDU()
	{
	}

	void UseLN(bool bVal)
	{
		m_ApplicationContextName.UseLN = bVal;
	}

	bool UseLN()
	{
		return m_ApplicationContextName.UseLN;
	}

	GXDLMS_ASSOCIATION_RESULT GetResultComponent()
	{
		return (GXDLMS_ASSOCIATION_RESULT) ResultValue;
	}
	
	GXDLMS_SOURCE_DIAGNOSTIC GetResultDiagnosticValue()
	{
		return (GXDLMS_SOURCE_DIAGNOSTIC) ResultDiagnosticValue;
	}

	void SetAuthentication(GXDLMS_AUTHENTICATION val, const char* pw)
	{
		m_Authentication = val;
		if (pw != NULL)
		{
			m_Password = pw;
		}
	}

	basic_string<char> GetPassword()
	{
		return m_Password;
	}

	GXDLMS_AUTHENTICATION GetAuthentication()
	{
		return m_Authentication;
	}

	int GetAuthenticationString(std::vector<unsigned char>& buff)
	{
		//If authentication is not used.
		if (m_Authentication == GXDLMS_AUTHENTICATION_NONE)
		{
			return ERROR_CODES_OK;
		}
		//Add sender ACSE-requirenents field component.
		buff.push_back(0x8A);
        buff.push_back(2);
		unsigned short value = 0x0780;
		GXHelpers::ChangeByteOrder(buff, &value, 2);
		buff.push_back(0x8B);
		buff.push_back(0x7);
		unsigned char data[7] = {0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x0};
		data[6] = m_Authentication;
		GXHelpers::AddRange(buff, data, 7);
		int pwLen = m_Password.size();
		//Add Calling authentication information.		
		buff.push_back(0xAC);
		buff.push_back(2 + pwLen);
		//Add authentication information.		
		buff.push_back(0x80);		
		buff.push_back(pwLen);
		GXHelpers::AddRange(buff, m_Password.c_str(), pwLen);
		return ERROR_CODES_OK;
	}

	//Code data.
	int CodeData(std::vector<unsigned char>& buff, GXDLMS_INTERFACETYPE InterfaceType)
	{
		//AARQ APDU Tag
		buff.push_back(AARQTag);		
		unsigned char LenPos = buff.size();
		//Lenght is updated later.
		buff.push_back(0x00);
		///////////////////////////////////////////
		// Add Application context name.
		int ret;
		if ((ret = m_ApplicationContextName.CodeData(buff)) != 0 ||
			(ret = GetAuthenticationString(buff)) != 0 ||
			(ret = UserInformation.CodeData(buff)) != 0)
		{
			return ret;
		}		
		buff[LenPos] = (char) (buff.size() - LenPos - 1);
		return ret;
	}

	//Encode data.
	int EncodeData(unsigned char* pBuff, int& size)
	{
		// Get AARE tag and length
		int tag = *pBuff++ & 0xFF;
		--size;
		if (tag != 0x60 && tag != 0x61)
		{
			return ERROR_CODES_INVALID_TAG;
		}
		int len = *pBuff++;
		--size;
		if (len > size)
		{
			return ERROR_CODES_OUTOFMEMORY;
		}
		int ret = ERROR_CODES_OK;
		while(size > 0)
		{
			tag = pBuff[0] & 0xFF;
			len = pBuff[1] & 0xFF;
			if (tag == 0xA1)
			{
				if ((ret = m_ApplicationContextName.EncodeData(pBuff, size)) != 0)
				{
					return ret;
				}
			}
			else if (tag == 0xBE)
			{
				if ((ret = UserInformation.EncodeData(pBuff, size)) != 0)
				{
					return ret;
				}
			}
			else if (tag == 0xA2) //Result 
			{
				//Get tag
				tag = *pBuff++ & 0xFF;
				--size;
				//Get length.
				len = *pBuff++ & 0xFF;
				--size;
				//Choice for result (INTEGER, universal)
				tag = *pBuff++ & 0xFF;
				--size;
				//Get length.
				len = *pBuff++ & 0xFF;
				--size;
				ResultValue = *pBuff++ & 0xFF;
				--size;
			}
			else if (tag == 0xA3) //SourceDiagnostic 
			{
				tag = *pBuff++ & 0xFF;
				--size;
				len = *pBuff++ & 0xFF;
				--size;
				size -= len;
				// ACSE service user tag.
				tag = *pBuff++ & 0xFF;
				len = *pBuff++ & 0xFF;
				// Result source diagnostic component.
				tag = *pBuff++ & 0xFF;
				len = *pBuff++ & 0xFF;
				ResultDiagnosticValue = *pBuff++ & 0xFF;
			}
			 else if (tag == 0x8A || tag == 0x88) //Authentication.
            {
                tag = *pBuff++ & 0xFF;
				--size;
                //Get sender ACSE-requirenents field component.
                if (*pBuff++ != 2)
                {
                    return ERROR_CODES_INVALID_TAG;
                }                
				--size;
				short val = CGXOBISTemplate::GetInt16(pBuff);
				size -= 2;
                if (val != 0x0780 && val != 0x0680)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
            }               
            else if (tag == 0xAA) //Server Challenge.                
            {
				tag = *pBuff++ & 0xFF;
				--size;
				len = *pBuff++ & 0xFF;
				--size;
                ++pBuff;
				--size;
                len = *pBuff++ & 0xFF;
				--size;
            }
            else if (tag == 0x8B || tag == 0x89) //Authentication.
            {
                tag = *pBuff++ & 0xFF;
				--size;
                len = *pBuff++ & 0xFF;
				--size;
                bool IsAuthenticationTag = len > 7;
                if (*pBuff++ != 0x60)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
				--size;
                if ((*pBuff++ & 0xFF) != 0x85)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
				--size;
                if (*pBuff++ != 0x74)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
				--size;
                if (*pBuff++ != 0x05)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
				--size;
                if (*pBuff++ != 0x08)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
				--size;
                if (*pBuff++ != 0x02)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
				--size;
                int tmp = *pBuff++;
				--size;
                if (tmp < 0 || tmp > 5)
                {
                    return ERROR_CODES_INVALID_TAG;
                }
                if (IsAuthenticationTag)
                {
                    m_Authentication = (GXDLMS_AUTHENTICATION) tmp;
                    int tag2 = (*pBuff++ & 0xFF);
					--size;
                    if (tag2 != 0xAC && tag2 != 0xAA)
                    {
                        return ERROR_CODES_INVALID_TAG;
                    }
                    len = *pBuff++;
					--size;
                    //Get authentication information.
                    if ((*pBuff++ & 0xFF) != 0x80)
                    {
                        return ERROR_CODES_INVALID_TAG;
                    }
					--size;
                    len = *pBuff++ & 0xFF;
					--size;
					m_Password.append(*pBuff, len);
					size -= len;
                }
                else
                {
					m_Authentication = GXDLMS_AUTHENTICATION_NONE;                    
                }
            }
			//Unknown tags.
			else 
			{
				tag = *pBuff++ & 0xFF;
				--size;
				len = *pBuff++ & 0xFF;
				--size;
				pBuff +=len;
				size -= len;
			}
		}
		return ERROR_CODES_OK;
	}

    void GenerateAARE(std::vector<unsigned char>& data, unsigned short maxReceivePDUSize, unsigned char* pConformanceBlock, GXDLMS_ASSOCIATION_RESULT result, GXDLMS_SOURCE_DIAGNOSTIC diagnostic)
    {
        // Set AARE tag and length
		data.push_back(0x61);
        m_ApplicationContextName.CodeData(data);
        //Result
        data.push_back(0xA2);
        data.push_back(3); //len
        data.push_back(2); //Tag
        //Choice for result (INTEGER, universal)
        data.push_back(1); //Len
        data.push_back(result); //ResultValue            
        //SourceDiagnostic
        data.push_back(0xA3);
        data.push_back(5); //len
        data.push_back(0xA1); //Tag
        data.push_back(3); //len
        data.push_back(2); //Tag
        //Choice for result (INTEGER, universal)
        data.push_back(1); //Len
        data.push_back(diagnostic); //diagnostic            
        //Add User Information
        data.push_back(0xBE); //Tag        
        data.push_back(0x10); //Length for AARQ user field
        data.push_back(0x04); //Coding the choice for user-information (Octet STRING, universal)        
        data.push_back(0xE); //Length
        data.push_back(InitialResponce); // Tag for xDLMS-Initiate response
        data.push_back(0x00); // Usage field for the response allowed component � not used
        data.push_back(6); // DLMSVersioNumber
        data.push_back(0x5F);
        data.push_back(0x1F);
        data.push_back(0x04);// length of the conformance block
        data.push_back(0x00);// encoding the number of unused bits in the bit string            
		GXHelpers::AddRange(data, pConformanceBlock, 3);
        GXHelpers::SetUInt16(maxReceivePDUSize, data);
        //VAA Name VAA name (0x0007 for LN referencing and 0xFA00 for SN)
		if (UseLN())
        {
            GXHelpers::SetUInt16(0x0007, data);
        }
        else
        {
            GXHelpers::SetUInt16(0xFA00, data);
        }            
		data.insert(data.begin() + 1, data.size() - 1);
    }
};
