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
