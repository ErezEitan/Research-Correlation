//
//  HistogramsDraw.hpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//

#ifndef __HistogramsDraw_h__
#define __HistogramsDraw_h__

//////////////////////////
//include "Histograms.h"
/////////////////////////

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseComponentControl.h"
#include "LinesAndSeperator.h"
#include "RadioButton.h"

class HistogramsBar  : public BaseComponentControl
{
public:
    //==============================================================================
    HistogramsBar(MainComponent* in_mainComponent)
    : BaseComponentControl(in_mainComponent)
    {
        m_controlName = "HistogramsBar";
    }
    ~HistogramsBar(){;}
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistogramsBar)
};



class HistogramsDraw  : public BaseComponentControl , public Button::Listener
{
public:
    //==============================================================================
    HistogramsDraw(MainComponent* in_mainComponent, std::vector<std::shared_ptr<BarDescriptorStruct>>& in_barDesriptors, RCPHeaderDescriptor& in_rcpHeaderDescriptor)
    : BaseComponentControl(in_mainComponent)
    , m_vBarDescriptors(in_barDesriptors)
    , m_rcpHeaderDescriptor(in_rcpHeaderDescriptor)
    , m_selectedHistogramRadioButton(5, 42)
    {
        m_controlName = "HistogramsDraw";
    }
    ~HistogramsDraw(){;}
    
    void InitHistogramDraw();
    void InitHistogramsLines();
    void InitHistogramsWight();
    void InitHistogramsShowRadioButton();
    
    void CalculateHistogramLinesDrawPoints();
    void CalculateHistogramWidthAndHight();
    void CalculateHistogramBars();
    
    //==============================================================================
    void resized() override;
    void paint (Graphics& g) override;
    void buttonClicked (Button*) override;
    
private:

    size_t m_numOfBars = 0;
    float m_histogramBarWidthInPixel = 0.0f;
    float m_histogramBarHightInPixel = 0.0f;
    float m_areaHistogramDevided = 4.0f;
    float m_histogramsMultiple = 1.0f;
    //==============================================================================
    // Your private member variables go here...
    std::vector<std::vector<std::shared_ptr<HistogramsBar>>> m_vHistogramBars;
    std::vector<std::shared_ptr<LinesDraw>> m_vLineOfHistogramAxisX;
    std::vector<std::shared_ptr<LinesDraw>> m_vLineOfHistogramAxisY;
    std::vector<Path> m_vborderPath;
    
    std::vector<std::shared_ptr<BarDescriptorStruct>>& m_vBarDescriptors;
    RCPHeaderDescriptor& m_rcpHeaderDescriptor;

    RadioButtons m_selectedHistogramRadioButton;
    ColorsForHistograms m_histogramColors;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistogramsDraw)
};



#endif /* __HistogramsDraw_h__ */
