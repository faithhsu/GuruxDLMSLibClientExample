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

// GuruxDLMSLibClientExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GuruxDLMS/GXDLMSClient.h"
#include "GXClient.h"

#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main( int argc, char* argv[] )
#endif
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
	bool trace = false;
	CGXDLMSClient cl(UseLogicalNameReferencing);
	GXClient comm(&cl, trace);		
	if ((ret = comm.Connect("localhost", 4061)) != 0)
	{
		TRACE("Connect failed %d.\r\n", ret);
		return 1;
	}
	if ((ret = comm.InitializeConnection()) != 0)
	{
		TRACE("InitializeConnection failed %d.\r\n", ret);
		return 1;
	}	
	CGXObjectCollection Objects;
	if ((ret = comm.GetObjects(Objects)) != 0)
	{
		TRACE("InitializeConnection failed %d.\r\n", ret);
		return 1;
	}
	for(vector<CGXObject*>::iterator it = Objects.begin(); it != Objects.end(); ++it)
	{		
		CGXDLMSVariant ln, value;
		if (comm.Read(*it, 1, ln) != ERROR_CODES_OK)
		{
			//Show error.
			return ret;
		}
		//////////////////////////////////////////////////////////////////////////////
		//Data object.
		if ((*it)->GetObjectType() == OBJECT_TYPE_DATA)
		{		
			//Read value.
			if (comm.Read(*it, 2, value) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Data Object: '%s' : '%s'\r\n", ln.ToString().c_str(), value.ToString().c_str());
		}
		//////////////////////////////////////////////////////////////////////////////
		//Register object.
		else if ((*it)->GetObjectType() == OBJECT_TYPE_REGISTER)
		{
			//Read value.
			if (comm.Read(*it, 2, value) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			//Read scalar and unit.
			CGXDLMSVariant scalerUnit;
			if (comm.Read(*it, 3, scalerUnit) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			CGXDLMSVariant scaler = scalerUnit.Arr[0];
			CGXDLMSVariant unit = scalerUnit.Arr[1];
			printf("Register Object: '%s' '%s' '%s': '%s'\r\n", ln.ToString().c_str(), scaler.ToString().c_str(), unit.ToString().c_str(), value.ToString().c_str());
		}
		//////////////////////////////////////////////////////////////////////////////
		//Clock object.
		else if ((*it)->GetObjectType() == OBJECT_TYPE_CLOCK)
		{
			printf("Clock Object: '%s'\r\n", ln.ToString().c_str());
			//Read time.
			CGXDLMSVariant time;
			if (comm.Read(*it, 2, time) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Read time: '%s'\r\n", time.ToDateTime().c_str());
			CGXDLMSVariant time_zone;
			if (comm.Read(*it, 3, time_zone) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Time Zone: '%s'\r\n", time_zone.ToString().c_str());
			CGXDLMSVariant status;
			if (comm.Read(*it, 4, status) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Status: '%s'\r\n", status.ToString().c_str());
			CGXDLMSVariant daylight_savings_begin;
			if (comm.Read(*it, 5, daylight_savings_begin) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Daylight Savings Begin: '%s'\r\n", daylight_savings_begin.ToDateTime().c_str());
			CGXDLMSVariant daylight_savings_end;
			if (comm.Read(*it, 6, daylight_savings_end) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Daylight Savings End: '%s'\r\n", daylight_savings_end.ToDateTime().c_str());

			CGXDLMSVariant daylight_savings_deviation;
			if (comm.Read(*it, 7, daylight_savings_deviation) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Daylight Savings Deviation: '%s'\r\n", daylight_savings_deviation.ToString().c_str());
			CGXDLMSVariant daylight_savings_enabled;
			if (comm.Read(*it, 8, daylight_savings_enabled) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Daylight Savings Enabled: '%s'\r\n", daylight_savings_enabled.ToString().c_str());
			CGXDLMSVariant clock_base;
			if (comm.Read(*it, 9, clock_base) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			printf("Clock base: '%s'\r\n", clock_base.ToString().c_str());
		}
		//////////////////////////////////////////////////////////////////////////////
		//Profile Generic object.
		else if ((*it)->GetObjectType() == OBJECT_TYPE_PROFILE_GENERIC)
		{
			CGXDLMSVariant entries_in_use;
			if (comm.Read(*it, 7, entries_in_use) != ERROR_CODES_OK ||
				entries_in_use.ChangeType(DLMS_DATA_TYPE_INT32) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}			
			CGXDLMSVariant profile_entries;
			if (comm.Read(*it, 8, profile_entries) != ERROR_CODES_OK ||
				profile_entries.ChangeType(DLMS_DATA_TYPE_INT32) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			CGXDLMSVariant sort_method;
			if (comm.Read(*it, 5, sort_method) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}			
			CGXObjectCollection columns;
			if (comm.GetColumns(*it, &columns) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			CGXDLMSVariant capture_period;
			if (comm.Read(*it, 4, capture_period) != ERROR_CODES_OK ||
				capture_period.ChangeType(DLMS_DATA_TYPE_INT32) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			CGXObject* pSortObject = NULL;
			if (comm.GetSortObject(*it, pSortObject) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}			
			if (pSortObject != NULL)
			{
				printf("Profile Generic : '%s' period: %ld entries: %ld/%ld sorted %d by '%s'\r\n", ln.ToString().c_str(), capture_period.lVal, entries_in_use.lVal, profile_entries.lVal, sort_method.bVal, pSortObject->GetLogicalName().c_str());
				delete pSortObject;
				pSortObject = NULL;
			}
			else
			{
				printf("Profile Generic : '%s' period: %ld entries: %ld/%ld not sorted %d\r\n", ln.ToString().c_str(), capture_period.lVal, entries_in_use.lVal, profile_entries.lVal, sort_method.bVal);
			}
			//////////////////////////////////////////////////////////////////////////////
			//Show column names.
			for(vector<CGXObject*>::iterator col = columns.begin(); col != columns.end(); ++col)
			{
				if (col != columns.begin())
				{
					printf(" | ");
				}
				printf((*col)->GetLogicalName().c_str());
			}			
			printf("\r\n");
			CGXDLMSVariant rows;			
			/* TODO: Remove this if you want to read all columns.
			//////////////////////////////////////////////////////////////////////////////
			//Read all data rows.
			if (comm.Read(*it, 2, rows) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			*/

			//////////////////////////////////////////////////////////////////////////////
			// Read rows by entry.			
			//
			//Note! 
			// All meters do not support this.
			//Uncomment if needed.
			CGXDLMSVariant name = (*it)->GetName();
			if (comm.ReadRowsByEntry(name, 0, 1, rows) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}	
			//////////////////////////////////////////////////////////////////////////////
			//Read rows by range.
			time_t tm1 = time(NULL);
#if _MSC_VER > 1000
			struct tm start;
			localtime_s(&start, &tm1);
#else
			struct tm start = *localtime(&tm1);
#endif			
			start.tm_sec = start.tm_min = start.tm_hour = 0;
			struct tm end = start;
			end.tm_mday += 1;
			//If sort object is not used give first object of the column.
			if (pSortObject == NULL)
			{
				pSortObject = columns[0];
			}
			CGXDLMSVariant name2 = (*it)->GetName();
			if (comm.ReadRowsByRange(name2, pSortObject, &start, &end, rows) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
			//////////////////////////////////////////////////////////////////////////////
			//Show rows.
			for(vector<CGXDLMSVariant>::iterator row = rows.Arr.begin(); row != rows.Arr.end(); ++row)
			{
				for(vector<CGXDLMSVariant>::iterator cell = row->Arr.begin(); cell != row->Arr.end(); ++cell)
				{
					if (cell != row->Arr.begin())
					{
						printf(" | ");
					}
					printf("%s", cell->ToString().c_str());
				}
				printf("\r\n");
			}
		}
		else if ((*it)->GetObjectType() == OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME)
		{
			//Update access rights.
			if ((ret = comm.UpdateAccess(*it, Objects)) != ERROR_CODES_OK)
			{
				//Show error.
				return ret;
			}
		}
		else if ((*it)->GetObjectType() == OBJECT_TYPE_TCP_UDP_SETUP)
		{
		}
		else
		{
			printf("Unknown object type '%s' %d\r\n", ln.ToString().c_str(), (*it)->GetObjectType());
		}
	}
	comm.Close();
	return 0;
}

