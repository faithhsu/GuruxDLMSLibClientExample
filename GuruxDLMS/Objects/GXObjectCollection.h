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
