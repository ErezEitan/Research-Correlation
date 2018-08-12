//
//  LinesAndSeperatorDrawFunction.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/12/18.
//
//

#include "LinesAndSeperatorDrawFunction.h"

//================================================
void LinesDraw::DrawLineAndSeperators(Graphics& g)
//================================================
{
    g.setColour (Colours::white);
    
    g.drawLine(m_linesGraph);

    Rectangle<int> area;
   /*
    for (int i = 0; i < m_numOfBars; ++i)
    {
        Line<float> seperateLinesVertical(i * m_barWidthInPixel + 30, m_lineGraphVertical.getEnd().getY() + 10, i * m_barWidthInPixel + 30, m_lineGraphVertical.getEnd().getY() - 10);
        g.drawLine(seperateLinesVertical);
        area.setBounds(seperateLinesVertical.getStart().getX(), seperateLinesVertical.getEnd().getY() + 10, 20, 20);
        g.setFont(10.0f);
        g.drawFittedText(std::to_string(i).c_str(), area, Justification::centredLeft, 5.f);
        
        Line<float> lineBarsHorizontal(15, i * m_barHightInPixel + 30, 40,i * m_barHightInPixel + 30);
        g.drawLine(lineBarsHorizontal);
        area.setBounds(lineBarsHorizontal.getStart().getX(), lineBarsHorizontal.getEndY(), 20, 20);
        g.setFont(10.0f);
        g.drawFittedText(std::to_string(i).c_str(), area, Justification::centredLeft, 5.f);
    }
    */
}

//==========================================================================================
void LinesDraw::RotateLine(const int in_angle)
//==========================================================================================
{
   // m_linesGraph.applyTransform(<#const juce::AffineTransform &transform#>)
}

//==========================================================================================
void LinesDraw::SetBoundsAndReduced(Rectangle<int> in_newBounds, int in_reducedX, int in_reducedY)
//==========================================================================================
{
    m_rect = in_newBounds;
    m_rect.reduce(in_reducedX, in_reducedY);
    
    m_linesGraph.setStart(in_newBounds.getTopLeft().x, in_newBounds.getTopLeft().y);
    m_linesGraph.setEnd(in_newBounds.getTopLeft().x, in_newBounds.getBottomLeft().y);
    
    m_reducedX = in_reducedX;
    m_reducedY = in_reducedY;
}
