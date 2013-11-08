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


#ifdef WIN32 //Windows includes
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
