//
//  BaseComponentControl.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#include "BaseComponentControl.h"


//==============================================================================
BaseComponentControl::BaseComponentControl(MainComponent* in_mainComponent)
    : m_pMainCompenent(in_mainComponent)
//==============================================================================
{
    
    setSize(getParentWidth(), getParentHeight());
}

//==============================================================================
BaseComponentControl::~BaseComponentControl()
//==============================================================================
{
}

//==============================================================================
void BaseComponentControl::resized()
//==============================================================================
{

}
