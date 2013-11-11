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

class CGXObjectCollection : public std::vector<CGXObject*>
{
public:	
	~CGXObjectCollection()
	{
		clear();
	}

	CGXObject* FindByLN(OBJECT_TYPE type, basic_string<char> ln)
    {
		const char* pLn = ln.c_str();
		for (CGXObjectCollection::iterator it = this->begin(); it != end(); ++it)
        {
			if ((type == OBJECT_TYPE_ALL || (*it)->GetObjectType() == type) && strcmp((*it)->GetLogicalName().c_str(), pLn) == 0)
            {
                return *it;
            }
        }
        return NULL;
    }

	CGXObject* FindByLN(OBJECT_TYPE type, vector<unsigned char> ln)
    {
		if (ln.size() != 6)
		{
			return NULL;
		}
		for (CGXObjectCollection::iterator it = this->begin(); it != end(); ++it)
        {
			if ((type == OBJECT_TYPE_ALL || (*it)->GetObjectType() == type) && 
				memcmp((*it)->m_LN, &ln[0], 6) == 0)
            {
                return *it;
            }
        }
        return NULL;
    }

    CGXObject* FindBySN(unsigned short sn)
    {
        for (CGXObjectCollection::iterator it = begin(); it != end(); ++it)
        {
            if ((*it)->GetShortName() == sn)
            {
                return *it;
            }
        }
        return NULL;
    }

    void clear()
    {
    	for (CGXObjectCollection::iterator it = begin(); it != end(); ++it)
		{
			delete (*it);
		}
    	std::vector<CGXObject*>::clear();
    }
};
