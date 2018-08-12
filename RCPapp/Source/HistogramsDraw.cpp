//
//  HistogramsDraw.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#include "HistogramsDraw.h"


#include "BarsAndLines.h"
#include "MainComponent.h"


//==============================================================================
void HistogramsDraw::paint (Graphics& g)
//==============================================================================
{

    Rectangle<int> area = getLocalBounds();
    area.reduce(30, 30);
    
    m_lineGraphHorizontal.setStart(area.getTopLeft().x, area.getTopLeft().y);
    m_lineGraphHorizontal.setEnd(area.getTopLeft().x, area.getBottomLeft().y);
}

//==============================================================================
void HistogramsDraw::resized()
//==============================================================================
{

}


//==============================================================================
void HistogramsDraw::CalculateLinesDrawPoints()
//==============================================================================
{
    Rectangle<int> area = getLocalBounds();
    area.reduce(30, 30);
    
    m_lineGraphHorizontal.setStart(area.getTopLeft().x, area.getTopLeft().y);
    m_lineGraphHorizontal.setEnd(area.getTopLeft().x, area.getBottomLeft().y);
    
    m_lineGraphVertical.setStart(area.getBottomLeft().x, area.getBottomLeft().y);
    m_lineGraphVertical.setEnd(area.getBottomRight().x, area.getBottomLeft().y);
    
}
