//
//  ArrowButtonForHistogramView.h
//  RCPapp
//
//  Created by Erez Eitan on 8/26/18.
//
//

#ifndef __ArrowButtonForHistogramView_h__
#define __ArrowButtonForHistogramView_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>
#include "BaseComponentControl.h"


//==============================================================================
class RadioButtons  : public Component
{
public:
    RadioButtons(const int in_numberOfButtons, const int in_groupNumber)
    {
        for (int i = 0; i < in_numberOfButtons; ++i)
        {
            auto* b = m_radioButtons.add (new TextButton ("Button " + String (i + 1)));
            
            addAndMakeVisible (b);
            b->setRadioGroupId (in_groupNumber);
            b->setClickingTogglesState (true);
            b->onClick = [this, i, b] { UpdateToggleState( (Button*)b, i); };
            int setConncected = Button::ConnectedOnRight;
            setConncected += (i * Button::ConnectedOnRight);
            b->setConnectedEdges (setConncected);
        }
    }
    
    void UpdateToggleState (Button* button, int in_index)
    {
        auto state = button->getToggleState();
        if(state)
        {
            m_currentIndex = in_index;
        }
    }
    
    void SetButtonText (const int in_index, String in_buttonName)
    {
        if(in_index < m_radioButtons.size())
        {
            m_radioButtons[in_index]->setButtonText(in_buttonName);
        }
    }
    
    int GetCurrentIndex() { return m_currentIndex; }
    
    void resized() override
    {
        Rectangle<int>  area(-40,0,40,15);
        auto row = area;

        for (auto* b : m_radioButtons)
        {
            row.setX(row.getX() + 40);
            b->setBounds (row);
        }
        
    }

    OwnedArray<TextButton> m_radioButtons;
    int m_currentIndex = 0;
};

class ArrowButtonForHistogramView : public BaseComponentControl
{
public:
    ArrowButtonForHistogramView(MainComponent* in_mainComponent, float arrowDirectionInRadians, Colour arrowColour);
    ~ArrowButtonForHistogramView() {};
    void paint (Graphics& g) override;
    
private:
    Path m_arrowPath;
    Colour m_colour;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArrowButtonForHistogramView)
};


#endif /* __ArrowButtonForHistogramView_h__ */
