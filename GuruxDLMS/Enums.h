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

#if _MSC_VER > 12
#define _CRTDBG_MAP_ALLOC 
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

const unsigned char HDLCFrameStartEnd = 0x7E;

/**
 *
 * Defines the baud rates.
 */
enum BAUDRATE 
{
	/** 
    Baudrate is 300.
    */
    BAUDRATE_300 = 0,
    /** 
     Baudrate is 600.
    */
    BAUDRATE_600,
    /** 
     Baudrate is 1200.
    */
    BAUDRATE_1200,
    /** 
     Baudrate is 2400.
    */
    BAUDRATE_2400,
    /** 
     Baudrate is 4800.
    */
    BAUDRATE_4800,
    /** 
     Baudrate is 9600.
    */
    BAUDRATE_9600,
    /** 
     Baudrate is 19200.
    */
    BAUDRATE_19200,
    /** 
     Baudrate is 38400.
    */
    BAUDRATE_38400,    
    /** 
     Baudrate is 57600.
    */
    BAUDRATE_57600,
    /** 
     Baudrate is 115200.
    */
    BAUDRATE_115200
};

enum GXDLMS_AUTHENTICATION
{
	GXDLMS_AUTHENTICATION_NONE = 0,
	GXDLMS_AUTHENTICATION_LOW = 0x1,
	GXDLMS_AUTHENTICATION_HIGH = 0x2
};

//Interface type that is used.
enum GXDLMS_INTERFACETYPE
{
	//General
	GXDLMS_INTERFACETYPE_GENERAL = 0,
	// IEC 62056-47 COSEM transport layers for IPv4 networks
	GXDLMS_INTERFACETYPE_NET = 0x1
};

enum GXDLMS_DATA_REQUEST_TYPES
{
	GXDLMS_DATA_REQUEST_TYPES_NONE = 0x0,
	GXDLMS_DATA_REQUEST_TYPES_FRAME = 0x1,
	GXDLMS_DATA_REQUEST_TYPES_BLOCK = 0x2	
};

enum OBJECT_TYPE
{
	OBJECT_TYPE_ALL = -1,
	OBJECT_TYPE_NONE = 0,
	OBJECT_TYPE_DATA = 1,
	OBJECT_TYPE_REGISTER = 3,
	OBJECT_TYPE_EXTENDED_REGISTER = 4,
	OBJECT_TYPE_DEMAND_REGISTER = 5,
	OBJECT_TYPE_REGISTER_ACTIVATION = 6,
	OBJECT_TYPE_PROFILE_GENERIC = 7,
	OBJECT_TYPE_CLOCK = 8,
	OBJECT_TYPE_SCRIPT_TABLE = 9,
	OBJECT_TYPE_SCHEDULE = 10,
	OBJECT_TYPE_SPECIAL_DAYS_TABLE = 11,
	OBJECT_TYPE_ASSOCIATION_SHORT_NAME = 12,
	OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME = 15,
	OBJECT_TYPE_SAP_ASSIGNMENT = 17,
	OBJECT_TYPE_IMAGE_TRANSFER = 18,
	OBJECT_TYPE_IEC_LOCAL_PORT_SETUP = 19,
	OBJECT_TYPE_ACTIVITY_CALENDAR = 20,
	OBJECT_TYPE_REGISTER_MONITOR = 21,
	OBJECT_TYPE_ACTION_SCHEDULE = 22,
	OBJECT_TYPE_IEC_HDLC_SETUP = 23,
	OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP = 24,
	OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP = 25,
	OBJECT_TYPE_UTILITY_TABLES = 26,
	OBJECT_TYPE_MODEM_CONFIGURATION = 27,
	OBJECT_TYPE_AUTO_ANSWER = 28,
	OBJECT_TYPE_AUTO_CONNECT = 29,
	OBJECT_TYPE_TCP_UDP_SETUP = 41,
	OBJECT_TYPE_IP4_SETUP = 42,
	OBJECT_TYPE_MAC_ADDRESS_SETUP = 43,
	OBJECT_TYPE_PPP_SETUP = 44,
	OBJECT_TYPE_GPRS_SETUP = 45,
	OBJECT_TYPE_SMTP_SETUP = 46,
	OBJECT_TYPE_REGISTER_TABLE = 61,
	OBJECT_TYPE_STATUS_MAPPING = 63,
	OBJECT_TYPE_SECURITY_SETUP = 64,
	OBJECT_TYPE_DISCONNECT_CONTROL = 70,
	OBJECT_TYPE_LIMITER = 71,
	OBJECT_TYPE_MBUS_CLIENT = 72,
	OBJECT_TYPE_EVENT = 100,
	OBJECT_TYPE_REMOTE_DIGITAL_CONTROL = 101,
	OBJECT_TYPE_REMOTE_ANALOGUE_CONTROL = 102,
	OBJECT_TYPE_TUNNEL = 103
};

enum DLMS_COMMAND
{
    DLMS_COMMAND_NONE,
    DLMS_COMMAND_READ_REQUEST = 0x5,
    DLMS_COMMAND_READ_RESPONSE = 0xC,
    DLMS_COMMAND_WRITE_REQUEST = 0x6,        
    DLMS_COMMAND_WRITE_RESPONSE = 0xD,
    DLMS_COMMAND_GET_REQUEST = 0xC0,
    DLMS_COMMAND_GET_RESPONSE = 0xC4,
    DLMS_COMMAND_SET_REQUEST = 0xC1,
    DLMS_COMMAND_SET_RESPONSE = 0xC5,
    DLMS_COMMAND_METHOD_REQUEST = 0xC3,
    DLMS_COMMAND_METHOD_RESPONSE = 0xC7,	
    DLMS_COMMAND_REJECTED = 0x97,
	DLMS_COMMAND_SNRM = 0x93,
	DLMS_COMMAND_AARQ = 0x60,
	DLMS_COMMAND_DISCONNECT_REQUEST = 0x62,
	DLMS_COMMAND_DISCONNECT_RESPONSE = 0x63,
	DLMS_COMMAND_ACTION = 0x40,
	//Glo messages
    DLMS_COMMAND_GLO_GET_REQUEST = 0xC8,
    DLMS_COMMAND_GLO_GET_RESPONSE = 0xCC,
    DLMS_COMMAND_GLO_SET_REQUEST = 0xC9,
    DLMS_COMMAND_GLO_SET_RESPONSE = 0xCD,
	DLMS_COMMAND_GLO_METHOD_REQUEST = 0xCB,
	DLMS_COMMAND_GLO_METHOD_RESPONSE = 0xCF
};

enum HDLC_INFO
{
	HDLC_INFO_MAX_INFO_TX = 0x5,
    HDLC_INFO_MAX_INFO_RX = 0x6,
    HDLC_INFO_WINDOW_SIZE_TX = 0x7,
    HDLC_INFO_WINDOW_SIZE_RX = 0x8
};

enum DLMS_DATA_TYPE
{
	DLMS_DATA_TYPE_NONE = 0,
	DLMS_DATA_TYPE_BOOLEAN  = 3,
	DLMS_DATA_TYPE_BIT_STRING = 4,
	DLMS_DATA_TYPE_INT32 = 5,
	DLMS_DATA_TYPE_UINT32 = 6,
	DLMS_DATA_TYPE_OCTET_STRING = 9,
	DLMS_DATA_TYPE_STRING = 10,
	DLMS_DATA_TYPE_BINARY_CODED_DESIMAL = 13,
	DLMS_DATA_TYPE_STRING_UTF8 = 12,
	DLMS_DATA_TYPE_INT8 = 15,
	DLMS_DATA_TYPE_INT16 = 16,
	DLMS_DATA_TYPE_UINT8 = 17,
	DLMS_DATA_TYPE_UINT16 = 18,
	DLMS_DATA_TYPE_INT64 = 20,
	DLMS_DATA_TYPE_UINT64 = 21,
	DLMS_DATA_TYPE_ENUM = 22,
	DLMS_DATA_TYPE_FLOAT32 = 23,
	DLMS_DATA_TYPE_FLOAT64 = 24,
	DLMS_DATA_TYPE_DATETIME = 25,
	DLMS_DATA_TYPE_DATE = 26,
	DLMS_DATA_TYPE_TIME = 27,
	DLMS_DATA_TYPE_ARRAY = 1,
	DLMS_DATA_TYPE_STRUCTURE = 2,
	DLMS_DATA_TYPE_COMPACT_ARRAY = 19
};

enum ACCESSMODE
{
    /// <summary>
    /// No access.
    /// </summary>
    ACCESSMODE_NONE = 0,
    /// <summary>
    /// The client is allowed only reading from the server.
    /// </summary>            
	ACCESSMODE_READ = 1,
    /// <summary>
    /// The client is allowed only writing to the server.
    /// </summary>
    ACCESSMODE_WRITE = 2,
    /// <summary>
    /// The client is allowed both reading from the server and writing to it.
    /// </summary>
    ACCESSMODE_READWRITE = 3,    
    ACCESSMODE_AUTHENTICATED_READ = 4,    
	ACCESSMODE_AUTHENTICATED_WRITE = 5,    
    ACCESSMODE_AUTHENTICATED_READW_RITE = 6
};

enum METHOD_ACCESSMODE
{
    /// <summary>
    /// No access.
    /// </summary>    
    METHOD_ACCESSMODE_NONE = 0,
    /// <summary>
    /// Access.
    /// </summary>    
    METHOD_ACCESSMODE_ACCESS = 1,
    /// <summary>
    /// Authenticated Access.
    /// </summary>    
    METHOD_ACCESSMODE_AUTHENTICATED_ACCESS = 2
};

enum ASSOCIATION_STATUS
{
    ASSOCIATION_STATUS_NON_ASSOCIATED = 0,
    ASSOCIATION_STATUS_ASSOCIATION_PENDING = 1,
    ASSOCIATION_STATUS_ASSOCIATED = 2
};
