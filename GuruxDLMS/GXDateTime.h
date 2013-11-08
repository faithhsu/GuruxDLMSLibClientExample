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

#pragma once

#include <time.h> 
#include <string>
using namespace std;
// DataType enumerates skipped fields from date time.
enum DATETIME_SKIPS
{    
    // Nothing is skipped from date time.    
    DATETIME_SKIPS_NONE = 0x0,    
    // Year part of date time is skipped.
    DATETIME_SKIPS_YEAR = 0x1,
    // Month part of date time is skipped.
    DATETIME_SKIPS_MONTH = 0x2,
    // Day part is skipped.
    DATETIME_SKIPS_DAY = 0x4,
    // Day of week part of date time is skipped.
    DATETIME_SKIPS_DAYOFWEEK = 0x8,
    // Hours part of date time is skipped.
    DATETIME_SKIPS_HOUR = 0x10,
    // Minute part of date time is skipped.
    DATETIME_SKIPS_MINUTE = 0x20,
    // Seconds part of date time is skipped.
    DATETIME_SKIPS_SECOND = 0x40,
    // Hundreds of seconds part of date time is skipped.
    DATETIME_SKIPS_MS = 0x80,
};

// This class is used because in COSEM object model some fields from date time can be ignored.
// Default behavior of DateTime do not allow this.
class CGXDateTime
{
	DATETIME_SKIPS m_Skip;
	struct tm m_Value;
public:
    // Constructor.
    CGXDateTime();
	// Constructor.
    CGXDateTime(struct tm value);
    // Constructor.    
    CGXDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);

	// Used date time value.
    struct tm& GetValue();
    void SetValue(struct tm& value);
    
    // Skip selected date time fields.
    DATETIME_SKIPS GetSkip();
	void SetSkip(DATETIME_SKIPS value);
	basic_string<char> ToString();

	//Get currect time.
	static CGXDateTime Now();
};