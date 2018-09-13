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
class LookAndFeelDemoComponent  : public Component
{
public:
    LookAndFeelDemoComponent()
    {
        for (int i = 0; i < 5; ++i)
        {
            auto* b = radioButtons.add (new TextButton ("Button " + String (i + 1)));
            
            addAndMakeVisible (b);
            b->setRadioGroupId (42);
            b->setClickingTogglesState (true);
            b->onClick = [this, i, b] { updateToggleState( (Button*)b, i); };
            switch (i)
            {
                case 0:     b->setConnectedEdges (Button::ConnectedOnRight);                            break;
                case 1:     b->setConnectedEdges (Button::ConnectedOnRight + Button::ConnectedOnLeft);  break;
                case 2:     b->setConnectedEdges (Button::ConnectedOnRight + Button::ConnectedOnLeft + Button::ConnectedOnRight);  break;
                case 3:     b->setConnectedEdges (Button::ConnectedOnRight + Button::ConnectedOnLeft + Button::ConnectedOnLeft);  break;
                case 4:     b->setConnectedEdges (Button::ConnectedOnLeft);                             break;
                default:    break;
            }
          
        }
        
      
    }
    
    void updateToggleState (Button* button, int in_index)
    {
        auto state = button->getToggleState();
        if(state)
        {
            m_currentIndex = in_index;
        }
    }
    
    int GetCurrentIndex() { return m_currentIndex; }
    
    void resized() override
    {
        Rectangle<int>  area(-40,0,40,15);
        auto row = area;

        for (auto* b : radioButtons)
        {
            row.setX(row.getX() + 40);
            b->setBounds (row);
        }
        
    }

    OwnedArray<TextButton> radioButtons;
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
