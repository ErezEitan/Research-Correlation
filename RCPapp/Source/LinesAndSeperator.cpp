//
//  LinesAndSeperatorDrawFunction.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/12/18.
//
//

#include "LinesAndSeperator.h"

//================================================
void LinesDraw::CalculateLinesDrawPoints()
//================================================
{
     m_vSeperetorsPath.clear();
    if (m_numberOfSepertors != m_vSeperetorsPath.size())
    {
        m_vSeperetorsPath.resize(m_numberOfSepertors);
    }
    
    Rectangle<float> areaLineAxis = getLocalBounds().toFloat();
    Rectangle<float> areaLineSeperetor = getLocalBounds().toFloat();
    float offsetLine = 0.0f;
    if (LineDraw::eVertical == m_direction)
    {
        areaLineSeperetor.setSize(areaLineAxis.getWidth(), 1);
        offsetLine = areaLineAxis.getWidth() * 0.5f;
        areaLineAxis.setX(areaLineAxis.getX() + offsetLine);
        areaLineAxis.setSize(2, areaLineAxis.getHeight());
    }
    else
    {
        areaLineSeperetor.setSize(1, areaLineAxis.getHeight());
        offsetLine = areaLineAxis.getHeight() * 0.5f;
        areaLineAxis.setX(areaLineAxis.getX() + offsetLine);
        areaLineAxis.setY(areaLineAxis.getY() + offsetLine);
        areaLineAxis.setSize(areaLineAxis.getWidth(), 2);
    }
    
    m_lineAndSeperetorsPath.clear();
    m_lineAndSeperetorsPath.addRectangle(areaLineAxis);
    
    Rectangle<float> rectangleSeperetorLines;

    for (int i = 0; i < m_numberOfSepertors; ++i)
    {
        
        if (LineDraw::eVertical == m_direction)
        {
            areaLineSeperetor.setY(i * m_barHightLengthInPixel);
        }
        else
        {
            areaLineSeperetor.setX(i * m_barWidthLengthInPixel + offsetLine);
        }
        
        m_vSeperetorsPath[i].addRectangle(areaLineSeperetor);
    }
}

//==============================================================================
void LinesDraw::paint (Graphics& g)
//==============================================================================
{
    g.setColour (m_color);
    g.strokePath (m_lineAndSeperetorsPath, PathStrokeType (2.0f));
 
    int counter = 0;
    int beginNextStep = 1;
    if (m_bCountBackword)
    {
        beginNextStep = -1;
        counter = m_numberOfSepertors - 1;
    }
    for (int i = 0; i < m_numberOfSepertors && !m_vSeperetorsPath.empty(); ++i, counter = counter + beginNextStep)
    {
        g.strokePath (m_vSeperetorsPath[i], PathStrokeType (1.0f));
        g.setFont(10.0f);
        Rectangle<float>  fontArea = m_vSeperetorsPath[i].getBounds();
        fontArea.setWidth(10.0f);
        fontArea.setHeight(10.0f);
        if (LineDraw::eHorizontal == m_direction)
        {
            fontArea.setY(m_lineAndSeperetorsPath.getBounds().getY() + m_lineAndSeperetorsPath.getBounds().getHeight());
        }
        g.drawFittedText(std::to_string(counter).c_str(), fontArea.toNearestInt(), Justification::centredBottom, 5.f);
    }
}

//==============================================================================
void LinesDraw::resized()
//==============================================================================
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    CalculateSpacesBetweenSeperetor();
    CalculateLinesDrawPoints();
    repaint();
}

//==============================================================================
void LinesDraw::CalculateSpacesBetweenSeperetor()
//==============================================================================
{
    Rectangle<float> areaLineAxis = getLocalBounds().toFloat();
    m_barHightLengthInPixel = areaLineAxis.getHeight() / m_numberOfSepertors;
    m_barWidthLengthInPixel = areaLineAxis.getWidth() / m_numberOfSepertors;
    //m_barWidthLengthInPixel -= 0.3f;
}
