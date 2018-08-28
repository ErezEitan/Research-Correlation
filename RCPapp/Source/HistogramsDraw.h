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

class HistogramsDraw  : public BaseComponentControl
{
public:
    //==============================================================================
    HistogramsDraw(MainComponent* in_mainComponent)
    : BaseComponentControl(in_mainComponent)
    {
        m_controlName = "HistogramsDraw";
    }
    ~HistogramsDraw(){;}
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistogramsDraw)
};



#endif /* __HistogramsDraw_h__ */
