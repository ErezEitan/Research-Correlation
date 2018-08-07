//
//  CompenentControls.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#include "CompenentControls.h"


//==============================================================================
CompenentControls::CompenentControls(MainComponent* in_mainComponent)
    : m_pMainCompenent(in_mainComponent)
//==============================================================================
{
    
    setSize(getParentWidth(), getParentHeight());
    /*
    m_toolBar = std::make_shared<ToolBar>();
    m_barsAndLines = std::make_shared<BarAndLine>();
    
    addAndMakeVisible(*m_barsAndLines);
    addAndMakeVisible(*m_toolBar);
    
    m_toolBar->AddListner(static_cast<std::shared_ptr<ComponentCallbackListenerAbs>>(m_barsAndLines));
     */
}

//==============================================================================
CompenentControls::~CompenentControls()
//==============================================================================
{
}

//==============================================================================
void CompenentControls::resized()
//==============================================================================
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
   // m_toolBar.setSize(getWidth(), 50);
   // m_barsAndLInes.setBounds(30, m_toolBar.getHeight(), getWidth() - 30, getHeight() - m_toolBar.getHeight());
}
