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

#include "GXSendDestinationAndMethod.h"

GXDLMS_SERVICE_TYPE CGXSendDestinationAndMethod::GetService()
{
    return m_Service;
}
void CGXSendDestinationAndMethod::SetService(GXDLMS_SERVICE_TYPE value)
{
    m_Service = value;
}

string CGXSendDestinationAndMethod::GetDestination()
{
    return m_Destination;
}
void CGXSendDestinationAndMethod::SetDestination(string value)
{
    m_Destination = value;
}

GXDLMS_MESSAGE_TYPE CGXSendDestinationAndMethod::GetMessage()
{
    return m_Message;
}
void CGXSendDestinationAndMethod::SetMessage(GXDLMS_MESSAGE_TYPE value)
{
    m_Message = value;
}