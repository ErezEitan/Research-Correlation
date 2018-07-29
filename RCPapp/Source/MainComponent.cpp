/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <string>


//==============================================================================
MainComponent::MainComponent()
//==============================================================================
{
	setSize(620, 620);
    
    addAndMakeVisible(m_barsAndLInes);
	addAndMakeVisible(m_toolBar);

    m_toolBar.AddListner(static_cast<ComponentCallbackListenerAbs*>(&m_barsAndLInes));
}

//==============================================================================
MainComponent::~MainComponent()
//==============================================================================
{
}

//==============================================================================
void MainComponent::resized()
//==============================================================================
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    m_toolBar.setSize(getWidth(), m_toolBar.getHeight());
    m_barsAndLInes.setBounds(30, m_toolBar.getHeight(), getWidth() - 30, getHeight() - m_toolBar.getHeight());
}
