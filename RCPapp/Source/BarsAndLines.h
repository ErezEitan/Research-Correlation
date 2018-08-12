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
#include "BaseComponentControl.h"
#include "LoadFile.h"
#include "PharseRCPFileToDescriptors.h"

//==============================================================================
/** This will be the source of our balls and can be dragged around. */
class BarComponent : public BaseComponentControl
{
public:
    BarComponent(MainComponent* in_mainComponent)
    : BaseComponentControl(in_mainComponent)
    {
        m_controlName = "BarCompenent";
    }
    ~BarComponent() {};
    
    void paint(Graphics& g) override
    {
        g.setColour(Colours::orange);
        auto area = getLocalBounds().reduced(2);
        g.drawRoundedRectangle(area.toFloat(), 2.0f, 2.0f);
        g.fillRect(area);
        g.setColour(findColour(TextButton::textColourOffId));
        g.drawFittedText(m_barName, area, Justification::centredLeft, 1);
    }
    
    void SetBarDescriptor(const BarDescriptorStruct& in_barDescriptor)
    {
        m_barDescriptor = in_barDescriptor;
    }
    
    const BarDescriptorStruct& GetBarDescriptor()
    {
        return m_barDescriptor;
    }
    
    void mouseDown(const MouseEvent& e) override
    {
        // Prepares our dragger to drag this Component
        //dragger.startDraggingComponent(this, e);
    }
    
    void SetBarIndex(const int in_index)
    {
        m_barIndex = in_index;
        
        m_barName = "Bar: " + std::to_string(m_barIndex);
    }
    
private:
    int m_sizeOfBarInPixel = 0;
    int m_barIndex = -1;
    std::string m_barName;
    Rectangle<int> m_barRectangle;
    BarDescriptorStruct m_barDescriptor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BarComponent)
};


class BarAndLine  : public BaseComponentControl
{
public:
    //==============================================================================
    BarAndLine(MainComponent* in_mainComponent)
    : BaseComponentControl(in_mainComponent)
    {
        m_controlName = "BarAndLine";
    }
    ~BarAndLine(){};
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e) override;
    virtual void Callback(const String in_msg, void* /*in_data*/) override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    PharseRCPFileToDescriptors m_rcpDescriptors;
    std::vector<std::shared_ptr<BarComponent>> m_vBars;
    Point<int> m_lastMouseLocation = {0,0};
    
    Line<float> m_lineGraphHorizontal;
    Line<float> m_lineGraphVertical;
    int m_numOfBars = 0;
    float m_barWidthInPixel = 0.0f;
    float m_barHightInPixel = 0.0f;
    
    // Members function
    void CalculateLinesDrawPoints();
    void CalculateAndSetBarsSize();
    void SetHightAndWidthForBars();
    Rectangle<int> GetTheAreaLimiterFromBarsBeforeMe(const std::vector<int32_t>& in_vWhichBarBeforeMe);
    Rectangle<int> GetTheAreaLimiterFromBarsAfterMe(const std::vector<int32_t>& in_vWhichBarAfterMe);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarAndLine)
};


#endif /* __BarsAndLines_h__ */
