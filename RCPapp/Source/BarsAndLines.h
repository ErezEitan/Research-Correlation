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

#include "LinesAndSeperator.h"
#include "HistogramsDraw.h"
#include "RadioButton.h"

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
        auto area = getLocalBounds().reduced(1);
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
    BarAndLine(MainComponent* in_mainComponent);
    ~BarAndLine(){};
    
    void paint (Graphics&) override;
    void resized() override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e);
    virtual void Callback(const String in_msg, void* /*in_data*/) override;
    
protected:
    void InitBarsDrawArea();
    void InitBars();
    void InitHistogramDraw();
    void InitShowRadioButton();
    void ShowHandle(const int in_handle);
    
private:
    // Your private member variables go here...
    
    // Members function
    void CalculateOneBarPixel();
    void CalculateBarsDrawArea();
    void CalculateLinesBarsDrawPoints();
    void SetHightAndWidthForBars();
    
    void CalculateHistogramDraw();
    void CalculateShowRadioButton();
    
    Rectangle<float> GetTheAreaLimiterFromBarsBeforeMe(const std::vector<int32_t>& in_vWhichBarBeforeMe);
    Rectangle<float> GetTheAreaLimiterFromBarsAfterMe(const std::vector<int32_t>& in_vWhichBarAfterMe);

    PharseRCPFileToDescriptors m_rcpDescriptors;
    
    LinesDraw m_lineAxisX;
    LinesDraw m_lineAxisY;
    
    int m_showCase = 0;
    RadioButtons m_selectedBarOrHistogramRadioButton;
    
    std::shared_ptr<HistogramsDraw> m_histogramsDraw;
    std::vector<std::shared_ptr<BarComponent>> m_vBars;
    
    int m_numOfBars = 0;
    float m_barWidthInPixel = 0.0f;
    float m_barHightInPixel = 0.0f;
    float m_arrowDistance = 0;
    
    Rectangle<float> m_areaForBars;
    Rectangle<float> m_areaForHistograms;

    float m_factor = 0.0f;
    
    Point<int> m_lastMouseLocation = {0,0};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BarAndLine)
};


#endif /* __BarsAndLines_h__ */
