//
//  BarsAndLines.cpp
//  RCPapp
//
//  Created by Erez Eitan on 7/29/18.
//
//

#include "BarsAndLines.h"
#include "MainComponent.h"

const int32_t offsetReducedFromMainArea = 30;

//==============================================================================
BarAndLine::BarAndLine()
//==============================================================================
{
}

//==============================================================================
BarAndLine::~BarAndLine()
//==============================================================================
{
}

//==============================================================================
void BarAndLine::paint (Graphics& g)
//==============================================================================
{
    if(m_rcpDescriptors.IsFileOpen())
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g.setColour (Colours::white);
        
        g.drawLine(m_lineGraphHorizontal);
        g.drawLine(m_lineGraphVertical);
        
        int32_t numOfBars = m_rcpDescriptors.GetRcpDescriptor().m_numOfBars;
        int32_t barSizeWidthInPixel = m_lineGraphVertical.getLength() / numOfBars;
        Rectangle<int> area;
        
        for (int32_t i = 0; i < numOfBars; ++i)
        {
            Line<float> seperatelinesVertical(i * barSizeWidthInPixel + 30, m_lineGraphVertical.getEnd().getY() + 10, i * barSizeWidthInPixel + 30, m_lineGraphVertical.getEnd().getY() - 10);
            g.drawLine(seperatelinesVertical);
            area.setBounds(seperatelinesVertical.getStart().getX(), seperatelinesVertical.getEnd().getY() + 10, 20, 20);
            g.setFont(10.0f);
            g.drawFittedText(std::to_string(i).c_str(), area, Justification::centredLeft, 5.f);
            
            Line<float> lineBarsHorizontal(15, i * (m_lineGraphHorizontal.getLength() / numOfBars) + 30, 40,i* (m_lineGraphHorizontal.getLength() / numOfBars) + 30);
            g.drawLine(lineBarsHorizontal);
            area.setBounds(lineBarsHorizontal.getStart().getX(), lineBarsHorizontal.getEndY(), 20, 20);
            g.setFont(10.0f);
            g.drawFittedText(std::to_string(i).c_str(), area, Justification::centredLeft, 5.f);
        }
    }
}

//==============================================================================
void BarAndLine::resized()
//==============================================================================
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    Rectangle<int> area = getLocalBounds();
    area.reduce(30, 30);
    
    m_lineGraphHorizontal.setStart(area.getTopLeft().x, area.getTopLeft().y);
    m_lineGraphHorizontal.setEnd(area.getTopLeft().x, area.getBottomLeft().y);

    m_lineGraphVertical.setStart(area.getBottomLeft().x, area.getBottomLeft().y);
    m_lineGraphVertical.setEnd(area.getBottomRight().x, area.getBottomLeft().y);

    CalculateAndSetBarsSize();
}

 //==============================================================================
 void BarAndLine::Callback(const String in_msg)
 //==============================================================================
 {
     if(UTNoError(m_rcpDescriptors.OpenFilePathAndPharse(in_msg)))
     {
         CalculateAndSetBarsSize();
         repaint();
     }
 }
 
//==============================================================================
void BarAndLine::CalculateAndSetBarsSize()
//==============================================================================
{
    m_vBars.clear();
    if(m_rcpDescriptors.IsFileOpen())
    {
        int32_t numOfBars = m_rcpDescriptors.GetRcpDescriptor().m_numOfBars;
        if (0 != numOfBars)
        {
            m_vBars.clear();
            m_vBars.resize(numOfBars);
            auto& vBarDescriptor = m_rcpDescriptors.GetBarDescriptor();
            
            int32_t sizeOfBarWidthInPixel = m_lineGraphVertical.getLength() / numOfBars;
             int32_t sizeOfBarHightInPixel = m_lineGraphHorizontal.getLength() / numOfBars;
            
            for (int32_t i = 0; i< m_vBars.size(); ++i)
            {
                m_vBars[i] = std::make_shared<BarComponent>();
                m_vBars[i]->SetBarIndex(i);
                m_vBars[i]->addMouseListener(this, false);
                addAndMakeVisible(*m_vBars[i]);
                Rectangle<int> barBounds(30, (i * sizeOfBarHightInPixel) + 30, sizeOfBarWidthInPixel * vBarDescriptor[i]->m_barLength, sizeOfBarHightInPixel);
                m_vBars[i]->setBounds(barBounds);
                m_vBars[i]->SetBarDescriptor(*vBarDescriptor[i]);
            }
            
            for (int32_t cur = 0; cur < m_vBars.size(); ++cur)
            {
                for (int32_t j = 0; j < vBarDescriptor[cur]->m_vWhichBarAfterMe.size(); ++j)
                {
                    int32_t barAfterMe = vBarDescriptor[cur]->m_vWhichBarAfterMe[j];
                    int newAxisX = m_vBars[cur]->getBounds().getX() + vBarDescriptor[cur]->m_barLength * sizeOfBarWidthInPixel;
                    Rectangle<int> newBarBounds = m_vBars[barAfterMe]->getBounds();
                    newBarBounds.setX(newAxisX);
                    m_vBars[barAfterMe]->setBounds(newBarBounds);
                    
                }
            }
        }
    }
}

//==============================================================================
void BarAndLine::mouseDown(const MouseEvent& e)
//==============================================================================
{
    // Moves this Component according to the mouse drag event and applies our constraints to it
    if (e.eventComponent != this)
    {
        m_lastMouseLocation = getMouseXYRelative();
    }
}

//=============================================================================
void BarAndLine::mouseDrag(const MouseEvent& e)
//==============================================================================
{
    // Moves this Component according to the mouse drag event and applies our constraints to it
    Rectangle<int> area = e.eventComponent->getBounds();
    Point<int> curPosition = getMouseXYRelative();
    Point<int> deltaDrag = (m_lastMouseLocation - curPosition);
    
    if (0 != deltaDrag.getX() && e.eventComponent != this)
    {
        area.setX(area.getX() - deltaDrag.getX());
        e.eventComponent->setBounds(area);
    }
    
    m_lastMouseLocation = getMouseXYRelative();
}
