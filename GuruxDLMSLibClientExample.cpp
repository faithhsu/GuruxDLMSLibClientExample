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

// GuruxDLMSLibClientExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GuruxDLMS/GXDLMSClient.h"
#include "GXClient.h"
#include "GuruxDLMS/Objects/GXDLMSProfileGeneric.h"

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main( int argc, char* argv[] )
#endif
{
	{
#if _MSC_VER > 1000
	WSADATA wsaData; 	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// Tell the user that we could not find a usable WinSock DLL.
		return 1;
	}
#endif
	int ret;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TODO: Client and Server ID's are manufacturer debency. They should be standard values but they are not.
	//Below are some example values. Ask correct values from your meter manufacturer or http://www.gurux.org.
/*
	//Iskra Serial port settings.
	CGXDLMSClient cl(true, (unsigned char) 0x49, (unsigned short) 0x111, GXDLMS_AUTHENTICATION_LOW, "12345678");
	//Landis+Gyr settings.
	CGXDLMSClient cl(false);
	//Actaris settings.
	CGXDLMSClient cl(true, (unsigned char) 3, (unsigned int) 0x00020023, GXDLMS_AUTHENTICATION_LOW, "ABCDEFGH");	
	//Iskra TCP/IP settings.
	CGXDLMSClient cl(true, (unsigned short) 100, (unsigned short) 1, GXDLMS_AUTHENTICATION_LOW, "12345678", GXDLMS_INTERFACETYPE_NET);	
	//ZIV settings.
	CGXDLMSClient cl(true, (unsigned short) 1, (unsigned short)1, GXDLMS_AUTHENTICATION_NONE, NULL, GXDLMS_INTERFACETYPE_NET);
*/
	bool UseLogicalNameReferencing = true;
	bool trace = true;
	CGXDLMSClient cl(true, (unsigned short) 1, (unsigned short)1, GXDLMS_AUTHENTICATION_NONE, NULL, GXDLMS_INTERFACETYPE_NET);

	GXClient comm(&cl, trace);		
	if ((ret = comm.Connect("localhost", 4063)) != 0)
	{
		TRACE("Connect failed %d.\r\n", ret);
		return 1;
	}	

	//Remove trace file if exists.
	remove("trace.txt");

	if ((ret = comm.InitializeConnection()) != 0)
	{
		TRACE("InitializeConnection failed %d.\r\n", ret);
		return 1;
	}
	
	CGXDLMSObjectCollection Objects;
	if ((ret = comm.GetObjects(Objects)) != 0)
	{
		TRACE("InitializeConnection failed %d.\r\n", ret);
		return 1;
	}	
	//Read columns.
	CGXDLMSVariant value;
	CGXDLMSObjectCollection profileGenerics;
	Objects.GetObjects(OBJECT_TYPE_PROFILE_GENERIC, profileGenerics);
	string ln;
	for(vector<CGXDLMSObject*>::iterator it = profileGenerics.begin(); it != profileGenerics.end(); ++it)
	{
		(*it)->GetLogicalName(ln);
		TRACE("%s\r\n", ln.c_str());
		CGXDLMSProfileGeneric* pg = (CGXDLMSProfileGeneric*) *it;
		if ((ret = comm.Read(pg, 3, value)) != 0)
		{
			TRACE("Err! Failed to read columns: %d", ret);
            //Continue reading.
			continue;
		}

        //Read and update columns scalers.
		for(std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >::iterator it2 = pg->GetCaptureObjects().begin(); it2 != pg->GetCaptureObjects().end(); ++it2)
        {			
			OBJECT_TYPE ot = (*it2).first->GetObjectType();
			if (ot == OBJECT_TYPE_REGISTER || ot == OBJECT_TYPE_EXTENDED_REGISTER)
            {
				(*it2).first->GetLogicalName(ln);
				TRACE("%s\r\n", ln.c_str());
                if ((ret = comm.Read((*it2).first, 3, value)) != 0)
				{
					TRACE("Err! Failed to read register: %d", ret);
					//Continue reading.
					continue;
				}
            }
			if ((*it2).first->GetObjectType() == OBJECT_TYPE_DEMAND_REGISTER)
            {
				(*it2).first->GetLogicalName(ln);
				TRACE("%s\r\n", ln.c_str());                
				if ((ret = comm.Read((*it2).first, 4, value)) != 0)
				{
					TRACE("Err! Failed to read demand register: %d", ret);
					//Continue reading.
					continue;
				}
            }
        }		
	}

	for(vector<CGXDLMSObject*>::iterator it = Objects.begin(); it != Objects.end(); ++it)
	{		
		// Profile generics are read later because they are special cases.
		// (There might be so lots of data and we so not want waste time to read all the data.)
		if ((*it)->GetObjectType() == OBJECT_TYPE_PROFILE_GENERIC)
		{
			continue;
		}

		if (dynamic_cast<CGXDLMSCustomObject*>((*it)) != NULL)
		{
          //If interface is not implemented.
          //Example manufacturer spesific interface.
          printf("Unknown Interface: %d\r\n", (*it)->GetObjectType());
          continue;
		}
		
		printf("-------- Reading %s %s\r\n", (*it)->GetName().ToString().c_str(), (*it)->GetDescription().c_str());
		vector<int> attributes;
		(*it)->GetAttributeIndexToRead(attributes);
		for(vector<int>::iterator pos = attributes.begin(); pos != attributes.end(); ++pos)
		{			
			if ((ret = comm.Read(*it, *pos, value)) != ERROR_CODES_OK)
			{
				printf("Error! %d: read failed: %d\r\n", *pos, ret);
				//Continue reading.
			}
			else
			{
				printf("Index: %d Value: %s\r\n", *pos, value.ToString().c_str());
			}			
		}
	}	
	comm.Close();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

