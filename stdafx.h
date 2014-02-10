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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"

#include <stdio.h>

#define TRACEUL(text, ul) printf("%s %x%x%x%x\r\n", text, (unsigned char) (ul >> 24) & 0xFF, (unsigned char)(ul >> 16) & 0xFF, (unsigned char) (ul >> 8) & 0xFF, (unsigned char) ul & 0xFF)

#define TRACE1(var) printf(var)
#define TRACE(var, fmt) printf(var, fmt)


#if defined(_WIN32) || defined(_WIN64)//Windows includes
#if _MSC_VER > 1500
	#define _CRTDBG_MAP_ALLOC 
	#define CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif
	#include <tchar.h>
    #include <Winsock.h> //Add support for sockets
	#include <time.h>
#else //Linux includes.
	#define closesocket close
	#include <sys/types.h>
	#include <sys/socket.h> //Add support for sockets
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <string.h>
	#include <sys/time.h>
	#include <errno.h>
#endif


// TODO: reference additional headers your program requires here
