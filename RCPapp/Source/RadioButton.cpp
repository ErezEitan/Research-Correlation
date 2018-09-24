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
        auto* b = m_radioButtons.add (new RadioButtonText ("Button " + String (i + 1), i));
        
        addAndMakeVisible (b);
        b->setRadioGroupId (in_groupNumber);
        b->setClickingTogglesState (true);
        b->onClick = [this, i, b] { UpdateToggleState( (Button*)b, i); };
        int setConncected = Button::ConnectedOnRight;
        setConncected += (i * Button::ConnectedOnRight);
        b->setConnectedEdges (setConncected);
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
    auto state = button->getToggleState();
    if(state)
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
void RadioButtons::AddListener(Listener* in)
//===========================
{
    for(auto& r : m_radioButtons)
    {
        r->addListener(in);
    }
}

//===========================
void RadioButtons::resized()
//===========================
{
    Rectangle<int>  area(-40,0,40,15);
    auto row = area;
    
    for (auto* b : m_radioButtons)
    {
        row.setX(row.getX() + 40);
        b->setBounds (row);
    }
    
}
