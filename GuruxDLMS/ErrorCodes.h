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

enum ERROR_CODE
{
	ERROR_CODES_FALSE = -1,
	ERROR_CODES_OK = 0,
	ERROR_CODES_INVALID_PARAMETER = 1,
	//Server is not initialized.
	ERROR_CODES_NOT_INITIALIZED,
	//Not enough memory available.
	ERROR_CODES_OUTOFMEMORY,
	//Packet is not a reply for a send packet.
	ERROR_CODES_NOT_REPLY,
	//Meter rejects send packet.
	ERROR_CODES_FRAME_REJECTED,
	//Invalid Logical Name
	ERROR_CODES_INVALID_LOGICAL_NAME,
	//Client HDLC Address is not set.
	ERROR_CODES_INVALID_CLIENT_ADDRESS,
	//Server HDLC Address is not set.
	ERROR_CODES_INVALID_SERVER_ADDRESS,
	//Not a HDLC frame.
	ERROR_CODES_INVALID_DATA_FORMAT,
	//Invalid DLMS version number.
	ERROR_CODES_INVALID_VERSION_NUMBER,
	//Client addresses do not match
	ERROR_CODES_CLIENT_ADDRESS_NO_NOT_MATCH,
	//Server addresses do not match
	ERROR_CODES_SERVER_ADDRESS_NO_NOT_MATCH,
	//CRC do not match.
	ERROR_CODES_WRONG_CRC,
	//Invalid response
	ERROR_CODES_INVALID_RESPONSE,
	//Invalid Tag.
	ERROR_CODES_INVALID_TAG,
	//Encoding failed. Not enough data.
	ERROR_CODES_ENCODING_FAILED,
	ERROR_CODES_REJECTED_PERMAMENT,
	ERROR_CODES_REJECTED_TRANSIENT,
	ERROR_CODES_NO_REASON_GIVEN,
	ERROR_CODES_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED,
	ERROR_CODES_AUTHENTICATION_MECHANISM_NAME_NOT_RECOGNISED,
	ERROR_CODES_AUTHENTICATION_MECHANISM_NAME_REQUIRED,
	ERROR_CODES_AUTHENTICATION_FAILURE,
	ERROR_CODES_AUTHENTICATION_REQUIRED,
	//Access Error : Device reports a hardware fault
	ERROR_CODES_HW_FAULT,		
	//Access Error : Device reports a temporary failure
	ERROR_CODES_TEMP_FAIL,		
	// Access Error : Device reports Read-Write denied
	ERROR_CODES_WRITE_DENIED,		
	// Access Error : Device reports a undefined object
	ERROR_CODES_UNDEFINED_OBJ,		
	// Access Error : Device reports a inconsistent Class or Object
	ERROR_CODES_INCONSISTENT_OBJ,
	// Access Error : Device reports a unavailable object
	ERROR_CODES_UNAVAILABLE_OBJ,		
	// Access Error : Device reports a unmatched type
	ERROR_CODES_UNMATCH_TYPE,		
	// Access Error : Device reports scope of access violated
	ERROR_CODES_VIOLATED,		
	//Unknown error.
	ERROR_CODES_UNKNOWN,
	//Data send failed.
	ERROR_CODES_SEND_FAILED,
	//Data receive failed.
	ERROR_CODES_RECEIVE_FAILED,
	ERROR_CODES_NOT_IMPLEMENTED
};
