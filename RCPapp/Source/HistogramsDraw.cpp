//
//  HistogramsDraw.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#include "HistogramsDraw.h"


//==============================================================================
void HistogramsDraw::paint (Graphics& g)
//==============================================================================
{
    g.setColour(Colours::orange);
    auto area = getLocalBounds().reduced(2);
    g.fillCheckerBoard(area.toFloat(), 1.0f, 1.0f, Colours::lightgreen, Colours::lightgreen);
    g.fillRect(area);
}

//==============================================================================
void HistogramsDraw::resized()
//==============================================================================
{

}
