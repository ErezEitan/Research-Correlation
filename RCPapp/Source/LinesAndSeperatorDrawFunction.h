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

enum DirectionDrawLine
{
    eHorizontal,
    eVertical
};

class LinesDraw
{
public:
    LinesDraw(){;}
    ~LinesDraw(){;}
    //==============================================================================
    void DrawLineAndSeperators(Graphics& g);
    void SetBoundsAndReduced(Rectangle<int> in_newBounds, int in_reducedX = 0, int in_reducedY = 0);
    void SetDirection(const DirectionDrawLine in_direction) {m_direction = in_direction;}
    void SetNumberOfSepertors(const int in_numberOfSepertors) {m_numberOfSepertors = in_numberOfSepertors;}
    void SetLengthSeperetrosLines(const int in_length) { m_lengthSepertorsLine = in_length;}
    void RotateLine(const int in_angle);
private:
    //==============================================================================
    // Your private member variables go here...
    Line<float> m_linesGraph;
    Rectangle<int> m_rect;
    int m_reducedX = 0;
    int m_reducedY = 0;
    int m_numberOfSepertors = 0;
    int m_lengthSepertorsLine = 0;
    DirectionDrawLine m_direction = eHorizontal;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LinesDraw)
};


#endif /* LinesAndSeperatorDrawFunction_h */
