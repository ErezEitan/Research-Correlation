/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "FactoryDefaultControls.h"
#include <string>


//==============================================================================
MainComponent::MainComponent()
//==============================================================================
{
	setSize(620, 620);
    
    m_vControls.push_back(CreateDefaultControls("ToolBar", this));
    m_vControls.push_back(CreateDefaultControls("BarAndLine", this));
    m_vControls[0]->AddListner(m_vControls[1]);
    for (auto controls : m_vControls)
    {
        addAndMakeVisible(*controls);
    }
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
    if (!m_vControls.empty()) {
        m_vControls[0]->setSize(getWidth(), 50);
        m_vControls[1]->setBounds(30, m_vControls[0]->getHeight(), getWidth() - 30, getHeight() - m_vControls[0]->getHeight());
    }
}
