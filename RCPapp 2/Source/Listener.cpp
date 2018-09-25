//
//  Listener.cpp
//  RCPapp
//
//  Created by Erez Eitan on 7/18/18.
//
//

#include "Listener.h"

//==============================================================================
void Listener::Callback(const String in_msg, void* in_data)
//==============================================================================
{
    if (!m_vpCallbackListener.empty())
    {
        for(auto &&inListener : m_vpCallbackListener)
        {
            inListener->Callback(in_msg, in_data);
        }
    }
}
