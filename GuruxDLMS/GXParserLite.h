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
#include <iostream>
#include <vector>
using namespace std;


struct valuenode
{
	basic_string<char> name;
	basic_string<char> value;
};

typedef vector< valuenode > NodeVector;

class CGXParserLite
{
	void Clear();
	int GetTag(const char*& pData, basic_string<char>& tag);
	int GetValue(const char*& pData, basic_string<char>& value);
	// parses XML data
public:
	NodeVector m_nodes;

	//Constructor.
	CGXParserLite(void)
	{

	}

	//Destructor
	virtual ~CGXParserLite(void)
	{

	}
	// parses XML data
	int Parse(const char* pData);
};
