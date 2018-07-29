//
//  BarsAndLines.hpp
//  RCPapp
//
//  Created by Erez Eitan on 7/29/18.
//
//
/////////////////////////////
// #include "BarsAndLines.h"
////////////////////////////

#ifndef __BarsAndLines_h__
#define __BarsAndLines_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>
#include "LoadFile.h"
#include "PharseRCPFileToDescriptors.h"

//==============================================================================
/** This will be the source of our balls and can be dragged around. */
class BarComponent : public Component
{
public:
    BarComponent(){}
    
    void paint(Graphics& g) override
    {
        g.setColour(Colours::orange);
        auto area = getLocalBounds().reduced(2);
        g.drawRoundedRectangle(area.toFloat(), 2.0f, 2.0f);
        
        g.setColour(findColour(TextButton::textColourOffId));
        g.drawFittedText(m_barName, area, Justification::centredLeft, 1);
    }
    
    void SetBarDescriptor(const BarDescriptorStruct& in_barDescriptor)
    {
        m_barDescriptor = in_barDescriptor;
    }
    
    void resized() override
    {
        // Just set the limits of our constrainer so that we don't drag ourselves off the screen
        m_constrainer.setMinimumOnscreenAmounts(getHeight(), getWidth(),
                                                getHeight(), getWidth());
    }
    
    void mouseDown(const MouseEvent& e) override
    {
        // Prepares our dragger to drag this Component
        //dragger.startDraggingComponent(this, e);
    }
    
    void SetBarIndex(const int32_t in_index)
    {
        m_barIndex = in_index;
        
        m_barName = "Bar: " + std::to_string(m_barIndex);
    }
    friend class MainComponent;
    
private:
    int32_t m_sizeOfBarInPixel = 0;
    int32_t m_barIndex = -1;
    std::string m_barName;
    Rectangle<int> m_barRectangle;
    ComponentBoundsConstrainer m_constrainer;
    ComponentDragger dragger;
    BarDescriptorStruct m_barDescriptor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarComponent)
};


class BarAndLine  : public Component ,public Listener
{
public:
    //==============================================================================
    BarAndLine();
    ~BarAndLine();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e) override;
    virtual void Callback(const String in_msg) override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    ToolBar m_toolBar;
    PharseRCPFileToDescriptors m_rcpDescriptors;
    std::vector<std::shared_ptr<BarComponent>> m_vBars;
    Line<float> m_lineGraphHorizontal;
    Line<float> m_lineGraphVertical;
    Point<int> m_lastMouseLocation = {0,0};
    
    // Members function
    void CalculateAndSetBarsSize();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarAndLine)
};


#endif /* __BarsAndLines_h__ */
