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
#include "GuruxDLMS/GXDLMSConverter.h"

static void WriteValue(string line)
{
	printf(line.c_str());
	GXHelpers::Write("LogFile.txt", line);
}

#if defined(_WIN32) || defined(_WIN64)//Windows
int _tmain(int argc, _TCHAR* argv[])
#else
int main( int argc, char* argv[] )
#endif
{
	{
	//Use user locale settings.
	std::locale::global(std::locale(""));
#if defined(_WIN32) || defined(_WIN64)//Windows
	WSADATA wsaData; 	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// Tell the user that we could not find a usable WinSock DLL.
		return 1;
	}
#endif	
	int ret;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TODO: Client and Server ID's are manufacturer dependence. They should be standard values but they are not.
	//Below are some example values. Ask correct values from your meter manufacturer or http://www.gurux.org.
/*
	//Iskra Serial port settings.
	CGXDLMSClient cl(true, (unsigned char) 0xC9, (unsigned short) 0x0223, GXDLMS_AUTHENTICATION_LOW, "12345678");
	//Landis+Gyr settings.
	CGXDLMSClient cl(false);
	//Actaris settings.
	CGXDLMSClient cl(true, (unsigned char) 3, (unsigned int) 0x00020023, GXDLMS_AUTHENTICATION_LOW, "ABCDEFGH");	
	//Iskra TCP/IP settings.
	CGXDLMSClient cl(true, (unsigned short) 100, (unsigned short) 1, GXDLMS_AUTHENTICATION_LOW, "12345678", GXDLMS_INTERFACETYPE_NET);	
	//ZIV settings.
	CGXDLMSClient cl(true, (unsigned short) 1, (unsigned short)1, GXDLMS_AUTHENTICATION_NONE, NULL, GXDLMS_INTERFACETYPE_NET);
*/
	bool trace = false;
//	CGXDLMSClient cl(true, (unsigned short) 1, (unsigned short)1, GXDLMS_AUTHENTICATION_NONE, NULL, GXDLMS_INTERFACETYPE_NET);

	//Iskra Serial port settings.
	CGXDLMSClient cl(true, (unsigned short) 0x1, (unsigned short) 0x1, GXDLMS_AUTHENTICATION_LOW, "31323334", GXDLMS_INTERFACETYPE_NET);
	//Remove trace file if exists.
	remove("trace.txt");
	remove("LogFile.txt");

	GXClient comm(&cl, 1500, trace);
	/*
	if ((ret = comm.Open("COM3", true)) != 0)
	{
		TRACE("Connect failed %S.\r\n", CGXDLMSConverter::GetErrorMessage(ret));
		return 1;
	}
	*/	
	if ((ret = comm.Connect("localhost", 4059)) != 0)
	{
		TRACE("Connect failed %s.\r\n", CGXDLMSConverter::GetErrorMessage(ret));
		return 1;
	}	

	if ((ret = comm.InitializeConnection()) != 0)
	{
		TRACE("InitializeConnection failed %s.\r\n", CGXDLMSConverter::GetErrorMessage(ret));
		return 1;
	}
	CGXDLMSObjectCollection Objects;
	if ((ret = comm.GetObjects(Objects)) != 0)
	{
		TRACE("InitializeConnection failed %s.\r\n", CGXDLMSConverter::GetErrorMessage(ret));
		return 1;
	}
	string str;
	//Read columns.
	CGXDLMSVariant value;
	CGXDLMSObjectCollection profileGenerics;
	Objects.GetObjects(OBJECT_TYPE_PROFILE_GENERIC, profileGenerics);
	string ln;
	for(vector<CGXDLMSObject*>::iterator it = profileGenerics.begin(); it != profileGenerics.end(); ++it)
	{
		//Read Profile Generic columns first.
		CGXDLMSProfileGeneric* pg = (CGXDLMSProfileGeneric*) *it;
		if ((ret = comm.Read(pg, 3, value)) != 0)
		{
			TRACE("Err! Failed to read columns: %s", CGXDLMSConverter::GetErrorMessage(ret));
            //Continue reading.
			continue;
		}

        //Read and update columns scalers.
		for(std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >::iterator it2 = pg->GetCaptureObjects().begin(); it2 != pg->GetCaptureObjects().end(); ++it2)
        {			
			OBJECT_TYPE ot = (*it2).first->GetObjectType();
			if (ot == OBJECT_TYPE_REGISTER)
            {
				(*it2).first->GetLogicalName(ln);
				TRACE("%s\r\n", ln.c_str());
                if ((ret = comm.Read((*it2).first, 3, value)) != 0)
				{
					TRACE("Err! Failed to read register: %s", CGXDLMSConverter::GetErrorMessage(ret));
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
					TRACE("Err! Failed to read demand register: %s", CGXDLMSConverter::GetErrorMessage(ret));
					//Continue reading.
					continue;
				}
            }
        }
		WriteValue("Profile Generic " + (*it)->GetName().ToString() + " Columns:\r\n");
		string str;
		for(std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >::iterator it2 = pg->GetCaptureObjects().begin(); it2 != pg->GetCaptureObjects().end(); ++it2)
        {
			if (str.size() != 0)
			{
				str.append(" | ");
			}			
			str.append((*it2).first->GetName().ToString());
			str.append(" ");
			str.append((*it2).first->GetDescription());
		}
		str.append("\r\n");
        WriteValue(str);
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
          //Example manufacturer specific interface.
          printf("Unknown Interface: %d\r\n", (*it)->GetObjectType());
          continue;
		}		
		char buff[200];
#if _MSC_VER > 1000
	sprintf_s(buff, 200, "-------- Reading %s %s %s\r\n", CGXDLMSClient::ObjectTypeToString((*it)->GetObjectType()).c_str(), (*it)->GetName().ToString().c_str(), (*it)->GetDescription().c_str());
#else
	sprintf(buff, "-------- Reading %s %s %s\r\n", CGXDLMSClient::ObjectTypeToString((*it)->GetObjectType()).c_str(), (*it)->GetName().ToString().c_str(), (*it)->GetDescription().c_str());
#endif
		WriteValue(buff);
		vector<int> attributes;
		(*it)->GetAttributeIndexToRead(attributes);
		for(vector<int>::iterator pos = attributes.begin(); pos != attributes.end(); ++pos)
		{			
			if ((ret = comm.Read(*it, *pos, value)) != ERROR_CODES_OK)
			{
#if _MSC_VER > 1000
				sprintf_s(buff, 100, "Error! Index: %d %s\r\n", *pos, CGXDLMSConverter::GetErrorMessage(ret));				
#else
				sprintf(buff, "Error! Index: %d read failed: %s\r\n", *pos, CGXDLMSConverter::GetErrorMessage(ret));				
#endif			
				WriteValue(buff);
				//Continue reading.
			}
			else
			{
#if _MSC_VER > 1000
				sprintf_s(buff, 100, "Index: %d Value: ", *pos);
#else
				sprintf(buff, "Index: %d Value: ", *pos);
#endif				
				WriteValue(buff);
				WriteValue(value.ToString().c_str());
				WriteValue("\r\n");
			}						
		}
	}

	//Find profile generics and read them.                
	CGXDLMSObjectCollection pgs;
	Objects.GetObjects(OBJECT_TYPE_PROFILE_GENERIC, pgs);
	for(vector<CGXDLMSObject*>::iterator it = pgs.begin(); it != pgs.end(); ++it)
    {
		char buff[200];
#if _MSC_VER > 1000
	sprintf_s(buff, 200, "-------- Reading %s %s %s\r\n", CGXDLMSClient::ObjectTypeToString((*it)->GetObjectType()).c_str(), (*it)->GetName().ToString().c_str(), (*it)->GetDescription().c_str());
#else
	sprintf(buff, "-------- Reading %s %s %s\r\n", CGXDLMSClient::ObjectTypeToString((*it)->GetObjectType()).c_str(), (*it)->GetName().ToString().c_str(), (*it)->GetDescription().c_str());
#endif
		WriteValue(buff);

		if ((ret = comm.Read(*it, 7, value)) != ERROR_CODES_OK)
		{
#if _MSC_VER > 1000
			sprintf_s(buff, 100, "Error! Index: %d: %s\r\n", 7, CGXDLMSConverter::GetErrorMessage(ret));				
#else
			sprintf(buff, "Error! Index: %d: %s\r\n", 7, CGXDLMSConverter::GetErrorMessage(ret));				
#endif			
			WriteValue(buff);
			//Continue reading.
		}
				
        int entriesInUse = value.ToInteger();
		if ((ret = comm.Read(*it, 8, value)) != ERROR_CODES_OK)
		{
#if _MSC_VER > 1000
			sprintf_s(buff, 100, "Error! Index: %d: %s\r\n", 8, CGXDLMSConverter::GetErrorMessage(ret));				
#else
			sprintf(buff, "Error! Index: %d: %s\r\n", 8, CGXDLMSConverter::GetErrorMessage(ret));				
#endif			
			WriteValue(buff);
			//Continue reading.
		}
		int entries = value.ToInteger();
        str = "Entries: ";
		str += CGXDLMSVariant(entriesInUse).ToString();
		str += "/";
		str += CGXDLMSVariant(entries).ToString();
		str += "\r\n";
		WriteValue(str);
        //If there are no columns or rows.
		if (entriesInUse == 0 || ((CGXDLMSProfileGeneric*) *it)->GetCaptureObjects().size() == 0)
        {
            continue;
        }
        //Read first row from Profile Generic.
        CGXDLMSVariant rows;
		if ((ret = comm.ReadRowsByEntry(*it, 1, 1, rows)) != 0)
		{
			str = "Error! Failed to read first row:";
			str += CGXDLMSConverter::GetErrorMessage(ret);
			str += "\r\n";
			WriteValue(str);
            //Continue reading.
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////////
			//Show rows.			
			WriteValue(rows.ToString());			
		}
		if ((ret = comm.ReadRowsByRange((*it), &CGXDateTime::Now().GetValue(), &CGXDateTime::Now().GetValue(), rows)) != 0)
		{
            str = "Error! Failed to read last day:";
			str += CGXDLMSConverter::GetErrorMessage(ret);
			str += "\r\n";
			WriteValue(str);
            //Continue reading.
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////////
			//Show rows.
			WriteValue(rows.ToString());			
        }
    }      
	//Close connection.
	comm.Close();
	}
#if _MSC_VER > 1400
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

