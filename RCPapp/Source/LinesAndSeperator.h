//
//  LinesAndSeperatorDrawFunction.hpp
//  RCPapp
//
//  Created by Erez Eitan on 8/12/18.
//
//

#ifndef __LinesAndSeperatorDrawFunction_h__
#define __LinesAndSeperatorDrawFunction_h__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseComponentControl.h"

namespace LineDraw {
    
enum DirectionDrawLine
{
    eHorizontal,
    eVertical
};
    
};
class LinesDraw: public BaseComponentControl
{
public:
    LinesDraw(MainComponent* in_mainComponent): BaseComponentControl(in_mainComponent){;}
    ~LinesDraw(){;}
    //==============================================================================
    void resized() override;
    void paint (Graphics& g) override;
    void SetDirection(const LineDraw::DirectionDrawLine in_direction) {m_direction = in_direction;}
    void SetNumberOfSepertors(const int in_numberOfSepertors) {m_numberOfSepertors = in_numberOfSepertors;}
    void CalculateLinesDrawPoints();
    void SetColor(const Colour& in_color){m_color = in_color;}
    void CountBackword(const bool in_backword){m_bCountBackword = in_backword;}
    
private:
    void CalculateSpacesBetweenSeperetor();
    //==============================================================================
    // Your private member variables go here...
    Path m_lineAndSeperetorsPath;
    std::vector<Path> m_vSeperetorsPath;
    
    float m_barWidthLengthInPixel = 1.0f;
    float m_barHightLengthInPixel = 1.0f;
    int m_numberOfSepertors = 1;
    Colour m_color = Colours::white;
    
    bool m_bCountBackword = false;
    LineDraw::DirectionDrawLine m_direction = LineDraw::eHorizontal;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LinesDraw)
};


#endif /* LinesAndSeperatorDrawFunction_h */
