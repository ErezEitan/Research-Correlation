//
//  ArrowButtonForHistogramView.c
//  RCPapp
//
//  Created by Erez Eitan on 8/26/18.
//
//

#include "RadioButton.h"

//==============================================================================
RadioButtons::RadioButtons(const int in_numberOfButtons, const int in_groupNumber)
    : Button("RadioButton")
//==============================================================================
{
    for (int i = 0; i < in_numberOfButtons; ++i)
    {
        auto* button = m_radioButtons.add (new RadioButtonText ("Button " + String (i + 1), i));
        
        button->setRadioGroupId (in_groupNumber);
        button->setClickingTogglesState (true);
        button->onClick = [this, i, button] { UpdateToggleState( (Button*)button, i); };
        int setConncected = Button::ConnectedOnRight;
        setConncected += (i * Button::ConnectedOnRight);
        button->setConnectedEdges (setConncected);
        
        addAndMakeVisible (button);
    }
}

//==============================================================================
void RadioButtons::paintButton (Graphics& /*g*/, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
//==============================================================================
{
}

//==============================================================================
void RadioButtons::UpdateToggleState (Button* button, int in_index)
//==============================================================================
{
    auto bState = button->getToggleState();
    
    if(bState)
    {
        m_currentIndex = in_index;
    }
}

//==============================================================================
void RadioButtons::SetButtonText (const int in_index, String in_buttonName)
//==============================================================================
{
    if(in_index < m_radioButtons.size())
    {
        m_radioButtons[in_index]->setButtonText(in_buttonName);
    }
}

//===========================
void RadioButtons::AddListener(Listener* in_listener)
//===========================
{
    for(auto& radioButton : m_radioButtons)
    {
        radioButton->addListener(in_listener);
    }
}

//===========================
void RadioButtons::resized()
//===========================
{
    Rectangle<int>  area(-40,0,40,15);
    auto row = area;
    
    for (auto* pRadioButton : m_radioButtons)
    {
        row.setX(row.getX() + 40);
        pRadioButton->setBounds (row);
    }
    
}
