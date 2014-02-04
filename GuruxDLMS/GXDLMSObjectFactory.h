#pragma once

#include "Objects/GXDLMSObject.h"

class CGXDLMSObjectFactory
{
public:
	static CGXDLMSObject* CreateObject(OBJECT_TYPE type);
};
