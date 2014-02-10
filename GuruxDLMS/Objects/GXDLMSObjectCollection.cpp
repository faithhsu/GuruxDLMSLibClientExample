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

#include "GXDLMSObjectCollection.h"

CGXDLMSObjectCollection::~CGXDLMSObjectCollection()
{
	clear();
}

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(OBJECT_TYPE type, basic_string<char> ln)
{
	const char* pLn = ln.c_str();
	string ln2;
	for (CGXDLMSObjectCollection::iterator it = this->begin(); it != end(); ++it)
    {			
		if ((type == OBJECT_TYPE_ALL || (*it)->GetObjectType() == type))
        {
			(*it)->GetLogicalName(ln2);
			if (strcmp(ln2.c_str(), pLn) == 0)
			{
				return *it;
			}
        }
    }
    return NULL;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(OBJECT_TYPE type, vector<unsigned char> ln)
{
	if (ln.size() != 6)
	{
		return NULL;
	}	
	
	string ln2;
	for (CGXDLMSObjectCollection::iterator it = this->begin(); it != end(); ++it)
    {			
		if (type == OBJECT_TYPE_ALL || (*it)->GetObjectType() == type)
        {
			(*it)->GetLogicalName(ln2);
			if (memcmp(ln2.c_str(), &ln[0], 6) == 0)
			{
				return *it;
			}
		}
    }
    return NULL;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindBySN(unsigned short sn)
{
    for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
    {
        if ((*it)->GetShortName() == sn)
        {
            return *it;
        }
    }
    return NULL;
}

void CGXDLMSObjectCollection::GetObjects(OBJECT_TYPE type, CGXDLMSObjectCollection& items)
{        
    for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
    {
        if ((*it)->GetObjectType() == type)
        {
			items.push_back(*it);
        }
    }
}

void CGXDLMSObjectCollection::push_back(CGXDLMSObject* item)
{
	if (item->m_Parent == NULL)
	{
		item->m_Parent = this;
	}
	std::vector<CGXDLMSObject*>::push_back(item);
}

void CGXDLMSObjectCollection::clear()
{
	for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
	{
		if ((*it)->m_Parent == this)
		{				
			delete (*it);
		}
	}
	std::vector<CGXDLMSObject*>::clear();
}