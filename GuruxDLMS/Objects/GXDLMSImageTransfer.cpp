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

#include "GXDLMSImageTransfer.h"
#include "../GXDLMSClient.h"
#include <sstream> 

//Constructor.
CGXDLMSImageTransfer::CGXDLMSImageTransfer() : CGXDLMSObject(OBJECT_TYPE_IMAGE_TRANSFER)
{
}

//SN Constructor.
CGXDLMSImageTransfer::CGXDLMSImageTransfer(unsigned short sn) : CGXDLMSObject(OBJECT_TYPE_IMAGE_TRANSFER, sn)
{

}

//LN Constructor.
CGXDLMSImageTransfer::CGXDLMSImageTransfer(basic_string<char> ln) : CGXDLMSObject(OBJECT_TYPE_IMAGE_TRANSFER, ln)
{

}
/** 
 Holds the ImageBlockSize, expressed in octets, 
 * which can be handled by the server
*/
long CGXDLMSImageTransfer::GetImageBlockSize()
{
    return m_ImageBlockSize;
}
void CGXDLMSImageTransfer::SetImageBlockSize(long value)
{
    m_ImageBlockSize = value;
}

/** 
 * Provides information about the transfer status of each
 * ImageBlock. Each bit in the bit-string provides information about
 * one individual ImageBlock.
*/
string& CGXDLMSImageTransfer::GetImageTransferredBlocksStatus()
{
    return m_ImageTransferredBlocksStatus;
}
void CGXDLMSImageTransfer::SetImageTransferredBlocksStatus(string value)
{
	m_ImageTransferredBlocksStatus = value;
}

/** 
 Provides the ImageBlockNumber of the first ImageBlock not transferred.
 * NOTE If the Image is complete, the value returned should be above the
 * number of blocks calculated from the Image size and the ImageBlockSize
*/
long CGXDLMSImageTransfer::GetImageFirstNotTransferredBlockNumber()
{
    return m_ImageFirstNotTransferredBlockNumber;
}
void CGXDLMSImageTransfer::SetImageFirstNotTransferredBlockNumber(long value)
{
    m_ImageFirstNotTransferredBlockNumber = value;
}

/**      
 * Controls enabling the Image transfer process. The method can
 * be invoked successfully only if the value of this attribute is true.
 */
bool CGXDLMSImageTransfer::GetImageTransferEnabled()
{
    return m_ImageTransferEnabled;
}
void CGXDLMSImageTransfer::SetImageTransferEnabled(bool value)
{
    m_ImageTransferEnabled = value;
}

/**
 * Holds the status of the Image transfer process.     
 */
IMAGE_TRANSFER_STATUS CGXDLMSImageTransfer::GetImageTransferStatus()
{
    return m_ImageTransferStatus;
}
void CGXDLMSImageTransfer::SetImageTransferStatus(IMAGE_TRANSFER_STATUS value)
{
	m_ImageTransferStatus = value;
}

vector<CGXDLMSImageActivateInfo>& CGXDLMSImageTransfer::GetImageActivateInfo()
{
    return m_ImageActivateInfo;
}

// Returns amount of attributes.
int CGXDLMSImageTransfer::GetAttributeCount()
{
	return 7;
}

// Returns amount of methods.
int CGXDLMSImageTransfer::GetMethodCount()
{
	return 4;
}

void CGXDLMSImageTransfer::GetValues(vector<string>& values)
{
	values.clear();
	string ln;
	GetLogicalName(ln);
	values.push_back(ln);	
	values.push_back(CGXDLMSVariant(m_ImageBlockSize).ToString());
	values.push_back(CGXDLMSVariant(m_ImageTransferredBlocksStatus).ToString());
	values.push_back(CGXDLMSVariant(m_ImageFirstNotTransferredBlockNumber).ToString());
	values.push_back(CGXDLMSVariant(m_ImageTransferEnabled).ToString());
	values.push_back(CGXDLMSVariant(m_ImageTransferStatus).ToString());
	std::stringstream sb;
	sb << '[';
	bool empty = true;
	for(vector<CGXDLMSImageActivateInfo>::iterator it = m_ImageActivateInfo.begin(); it != m_ImageActivateInfo.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;	
		string str = it->ToString();
		sb.write(str.c_str(), str.size());
	}
	sb << ']';
	values.push_back(sb.str());		
}

void CGXDLMSImageTransfer::GetAttributeIndexToRead(vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXOBISTemplate::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
	//ImageBlockSize
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }        
    //ImageTransferredBlocksStatus
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //ImageFirstNotTransferredBlockNumber
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //ImageTransferEnabled
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //ImageTransferStatus
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    //ImageActivateInfo
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
}

int CGXDLMSImageTransfer::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_UINT32;
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_BIT_STRING;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT32;
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
		return ERROR_CODES_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_ENUM;
		return ERROR_CODES_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_ARRAY;
		return ERROR_CODES_OK;
    } 
	return ERROR_CODES_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSImageTransfer::GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value)
{
	if (index == 1)
	{
		GXHelpers::AddRange(value.byteArr, m_LN, 6);
		value.vt = DLMS_DATA_TYPE_OCTET_STRING;
		return ERROR_CODES_OK;
	}
    if (index == 2)
    {   
        value = GetImageBlockSize();
		return ERROR_CODES_OK;
    }
    if (index == 3)
    {
        value = m_ImageTransferredBlocksStatus;
		return ERROR_CODES_OK;
    }
    if (index == 4)
    {
        value = m_ImageFirstNotTransferredBlockNumber;
		return ERROR_CODES_OK;
    }
    if (index == 5)
    {
        value = m_ImageTransferEnabled;
		return ERROR_CODES_OK;

    }
    if (index == 6)
    {
        value = m_ImageTransferStatus;
		return ERROR_CODES_OK;
    }
    if (index == 7)
    {
        vector<unsigned char> data;
        data.push_back(DLMS_DATA_TYPE_ARRAY);
        data.push_back(m_ImageActivateInfo.size()); //Count  
		int ret;
		for (vector<CGXDLMSImageActivateInfo>::iterator it = m_ImageActivateInfo.begin(); it != m_ImageActivateInfo.end(); ++it)           
        {
            data.push_back(DLMS_DATA_TYPE_STRUCTURE);                    
            data.push_back(3);//Item count.
            if ((ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT32, (*it).GetSize())) != 0 ||
				(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).GetIdentification())) != 0 ||
				(ret = CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, (*it).GetSignature())) != 0)
			{
				return ret;
			}
        }
        value = data;
    }
	return ERROR_CODES_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSImageTransfer::SetValue(int index, CGXDLMSVariant& value)
{
	if (index == 1)
	{			
		if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
		{
			return ERROR_CODES_INVALID_PARAMETER;
		}
		memcpy(m_LN, &value.byteArr[0], 6);		
	}
     else if (index == 2)
    {
		m_ImageBlockSize = value.ToInteger();            
    }
    else if (index == 3)
    {
		m_ImageTransferredBlocksStatus = value.ToString();    
    }
    else if (index == 4)
    {
        m_ImageFirstNotTransferredBlockNumber = value.ToInteger();
    }
    else if (index == 5)
    {
		m_ImageTransferEnabled = value.boolVal;
    }
    else if (index == 6)
    {
		m_ImageTransferStatus = (IMAGE_TRANSFER_STATUS) value.ToInteger();            
    }
    else if (index == 7)
    {
        m_ImageActivateInfo.clear();
        if (value.vt == DLMS_DATA_TYPE_ARRAY)
        {     
			CGXDLMSVariant tmp;
			for (vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)           
            {                    
                CGXDLMSImageActivateInfo item;
				item.SetSize((*it).Arr[0].ToInteger());
				CGXDLMSClient::ChangeType((*it).Arr[1].byteArr, DLMS_DATA_TYPE_STRING, tmp);
				item.SetIdentification(tmp.ToString());
				CGXDLMSClient::ChangeType((*it).Arr[2].byteArr, DLMS_DATA_TYPE_STRING, tmp);
                item.SetSignature(tmp.ToString());
                m_ImageActivateInfo.push_back(item);
            }
        }
    }
	else
	{
		return ERROR_CODES_INVALID_PARAMETER;
	}
	return ERROR_CODES_OK;
}
