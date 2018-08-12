//
//  BarsAndLines.cpp
//  RCPapp
//
//  Created by Erez Eitan on 7/29/18.
//
//

#include "BarsAndLines.h"
#include "MainComponent.h"

//const int kOffsetReducedFromMainArea = 30;


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

        Rectangle<int> area;
        
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
    }
}
/*
//==============================================================================
Line<float>& BarAndLine::CalculateSeperetorsVerticalsLines (Graphics& g)
//==============================================================================
{
}
*/
//==============================================================================
void BarAndLine::resized()
//==============================================================================
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    if(m_rcpDescriptors.IsFileOpen())
    {
        CalculateLinesDrawPoints();
        SetHightAndWidthForBars();
        repaint();
    }
}

//==============================================================================
void BarAndLine::CalculateLinesDrawPoints()
//==============================================================================
{
   
    Rectangle<int> area = getLocalBounds();
    area.reduce(30, 30);
    
    m_lineGraphHorizontal.setStart(area.getTopLeft().x, area.getTopLeft().y);
    m_lineGraphHorizontal.setEnd(area.getTopLeft().x, area.getBottomLeft().y);
    
    m_lineGraphVertical.setStart(area.getBottomLeft().x, area.getBottomLeft().y);
    m_lineGraphVertical.setEnd(area.getBottomRight().x, area.getBottomLeft().y);
    
    m_numOfBars = m_rcpDescriptors.GetRcpDescriptor().m_numOfBars;
    m_barWidthInPixel = m_lineGraphVertical.getLength() / m_numOfBars;
    m_barHightInPixel = m_lineGraphHorizontal.getLength() / m_numOfBars;
    
}

//==============================================================================
void BarAndLine::Callback(const String in_msg, void* /*in_data*/)
//==============================================================================
{
    if(UTNoError(m_rcpDescriptors.OpenFilePathAndPharse(in_msg)))
    {
        CalculateLinesDrawPoints();
        CalculateAndSetBarsSize();
        repaint();
    }
}

//==============================================================================
void BarAndLine::CalculateAndSetBarsSize()
//==============================================================================
{
    m_vBars.clear();
    
    if (0 != m_numOfBars)
    {
        m_vBars.resize(m_numOfBars);
        auto& vBarDescriptor = m_rcpDescriptors.GetBarDescriptor();
        
        for (int i = 0; i < m_vBars.size(); ++i)
        {
            m_vBars[i] = std::make_shared<BarComponent>(m_pMainCompenent);
            m_vBars[i]->SetBarIndex(i);
            m_vBars[i]->addMouseListener(this, false);
            addAndMakeVisible(*m_vBars[i]);
            
            Rectangle<int> barBounds(30, (i * m_barHightInPixel) + 30, m_barWidthInPixel * vBarDescriptor[i]->m_barLength, m_barHightInPixel);
            m_vBars[i]->setBounds(barBounds);
            m_vBars[i]->SetBarDescriptor(*vBarDescriptor[i]);
        }
        
        for (int cur = 0; cur < m_vBars.size(); ++cur)
        {
            for (int j = 0; j < vBarDescriptor[cur]->m_vWhichBarAfterMe.size(); ++j)
            {
                int barAfterMe = vBarDescriptor[cur]->m_vWhichBarAfterMe[j];
                int newAxisX = m_vBars[cur]->getBounds().getX() + vBarDescriptor[cur]->m_barLength * m_barWidthInPixel;
                Rectangle<int> newBarBounds = m_vBars[barAfterMe]->getBounds();
                newBarBounds.setX(newAxisX);
                m_vBars[barAfterMe]->setBounds(newBarBounds);
            }
        }
    }
}

//==============================================================================
void BarAndLine::SetHightAndWidthForBars()
//==============================================================================
{
   
    if(m_rcpDescriptors.IsFileOpen())
    {
        if (0 != m_numOfBars)
        {
            for (int i = 0; i < m_vBars.size(); ++i)
            {
                m_vBars[i]->setSize(m_vBars[i]->GetBarDescriptor().m_barLength * m_barWidthInPixel, m_barHightInPixel);
            }
            
            for (int cur = 0; cur < m_vBars.size(); ++cur)
            {
                Rectangle<int> curBarBounds = m_vBars[cur]->getBounds();
                curBarBounds.setY((cur * m_barHightInPixel) + 30);
                m_vBars[cur]->setBounds(curBarBounds);
                for (int j = 0; j < m_vBars[cur]->GetBarDescriptor().m_vWhichBarAfterMe.size(); ++j)
                {
                    int barAfterMe = m_vBars[cur]->GetBarDescriptor().m_vWhichBarAfterMe[j];
                    int newAxisX = m_vBars[cur]->getBounds().getX() + m_vBars[cur]->GetBarDescriptor().m_barLength * m_barWidthInPixel;
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
    if(e.eventComponent != this)
    {
        BarComponent* pBarComponent = dynamic_cast<BarComponent*>(e.eventComponent);
        
        if (nullptr != pBarComponent)
        {
            Rectangle<int> area = pBarComponent->getBounds();
            Point<int> curPosition = getMouseXYRelative();
            Point<int> deltaDrag = (m_lastMouseLocation - curPosition);
            
            if (0 != deltaDrag.getX())
            {
                BarDescriptorStruct barDescriptor = pBarComponent->GetBarDescriptor();
                Rectangle<int> areaBarBeforeMe = GetTheAreaLimiterFromBarsBeforeMe(barDescriptor.m_vWhichBarBeforeMe);
                Rectangle<int> areaBarAfterMe = GetTheAreaLimiterFromBarsAfterMe(barDescriptor.m_vWhichBarAfterMe);
                
                if((area.getX() - deltaDrag.getX()) > areaBarBeforeMe.getRight())
                {
                    area.setX(area.getX() - deltaDrag.getX());
                    e.eventComponent->setBounds(area);
                }
            }
        }

        m_lastMouseLocation = getMouseXYRelative();
    }
}

//=================================================================================================
Rectangle<int> BarAndLine::GetTheAreaLimiterFromBarsBeforeMe(const std::vector<int32_t>& in_vWhichBarBeforeMe)
//==================================================================================================
{
    Rectangle<int> areaRetVal(0,0,0,0);
    for(int i = 0; i < in_vWhichBarBeforeMe.size(); ++i)
    {
        Rectangle<int> areaBarBeforeMe = m_vBars[in_vWhichBarBeforeMe[i]]->getBounds();
        if(areaRetVal.getRight() < areaBarBeforeMe.getX())
        {
            areaRetVal = areaBarBeforeMe;
        }
    }
    
    return areaRetVal;
}

//=================================================================================================
Rectangle<int> BarAndLine::GetTheAreaLimiterFromBarsAfterMe(const std::vector<int32_t>& in_vWhichBarAfterMe)
//==================================================================================================
{
    Rectangle<int> areaRetVal(0,0,0,0);
    for(int i = 0; i < in_vWhichBarAfterMe.size(); ++i)
    {
        Rectangle<int> areaBarAfterMe = m_vBars[in_vWhichBarAfterMe[i]]->getBounds();
        if(areaRetVal.getX() < areaBarAfterMe.getRight())
        {
            areaRetVal = areaBarAfterMe;
        }
    }
    
    return areaRetVal;
}
