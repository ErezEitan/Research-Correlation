//
//  HistogramsDraw.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#include "HistogramsDraw.h"
#include "RCP_DescriptorsConsts.h"

//==============================================================================
void HistogramsDraw::InitHistogramDraw()
//==============================================================================
{
    m_vHistogramBars.clear();
    m_vLineOfHistogramAxisX.clear();
    m_vLineOfHistogramAxisY.clear();
    m_numOfBars = m_vBarDescriptors.size();
    
    InitHistogramsLines();
    CalculateHistogramLinesDrawPoints();
    
    InitHistogramsWight();
    CalculateHistogramBars();
    repaint();
}

//==============================================================================
void HistogramsDraw::InitHistogramsLines()
//==============================================================================
{
    m_vLineOfHistogramAxisX.clear();
    m_vLineOfHistogramAxisY.clear();
    m_vborderPath.clear();
    
    for (size_t i = 0; i < eNumberOfHistogramColors; ++i)
    {
        m_vLineOfHistogramAxisX.push_back(std::make_shared<LinesDraw>(m_pMainCompenent));
        m_vLineOfHistogramAxisY.push_back(std::make_shared<LinesDraw>(m_pMainCompenent));
        
        m_vLineOfHistogramAxisX[i]->SetDirection(LineDraw::eHorizontal);
        m_vLineOfHistogramAxisX[i]->SetColor(ColorsForHistograms[i]);
        
        m_vLineOfHistogramAxisY[i]->SetDirection(LineDraw::eVertical);
        m_vLineOfHistogramAxisY[i]->SetColor(ColorsForHistograms[i]);
        m_vLineOfHistogramAxisY[i]->CountBackword(true);
        
        addAndMakeVisible(*m_vLineOfHistogramAxisX[i]);
        addAndMakeVisible(*m_vLineOfHistogramAxisY[i]);
        
        m_vborderPath.push_back(Path());
    }
}

//==============================================================================
void HistogramsDraw::InitHistogramsWight()
//==============================================================================
{
    if (0 != m_numOfBars)
    {
        m_vHistogramBars.clear();
        m_vHistogramBars.resize(eNumberOfHistogramColors);
        
        for (size_t j = 0; j < eNumberOfHistogramColors; ++j)
        {
            m_vHistogramBars[j].resize(m_numOfBars);
            
            for (size_t i = 0; i < m_numOfBars; ++i)
            {
                m_vHistogramBars[j][i] = std::make_shared<HistogramsBar>(m_pMainCompenent);
                addAndMakeVisible(*m_vHistogramBars[j][i]);
            }
        }
    }
}

//==============================================================================
void HistogramsDraw::CalculateHistogramLinesDrawPoints()
//==============================================================================
{
    if(!m_vLineOfHistogramAxisX.empty())
    {
        Rectangle<float> localBounds = getLocalBounds().toFloat();
        
        float areaHightForHistogram = (localBounds.getHeight() / 4.0f);
        
        for (size_t i = 0; i < eNumberOfHistogramColors; ++i)
        {
            Rectangle<float> areaLineDrawHorizontal(localBounds.getX(), localBounds.getBottom() - areaHightForHistogram * i - 30, localBounds.getWidth(), 30.0f);
            m_vLineOfHistogramAxisX[i]->setBounds(areaLineDrawHorizontal.toNearestInt());
            m_vLineOfHistogramAxisX[i]->SetNumberOfSepertors(m_numOfBars);
            m_vLineOfHistogramAxisX[i]->resized();
            
            Rectangle<float> areaLineDrawVertical(localBounds.getX(), localBounds.getBottom() - areaHightForHistogram * i - areaHightForHistogram, 30.0f, areaHightForHistogram);
            m_vLineOfHistogramAxisY[i]->setBounds(areaLineDrawVertical.toNearestInt());
            m_vLineOfHistogramAxisY[i]->SetNumberOfSepertors(m_numOfBars);
            m_vLineOfHistogramAxisY[i]->resized();
        }
    }
}

//==============================================================================
void HistogramsDraw::CalculateHistogramBars()
//==============================================================================
{
    if (0 != m_numOfBars)
    {
        m_histogramBarWidthInPixel = getLocalBounds().toFloat().getWidth() / m_numOfBars;
        for (size_t j = 0; j < eNumberOfHistogramColors; ++j)
        {
            for (size_t i = 0; i < m_numOfBars; ++i)
            {
                Rectangle<float> lineXHistogramBounds = m_vLineOfHistogramAxisX[j]->getBounds().toFloat();
                Rectangle<float> lineYHistogramBounds = m_vLineOfHistogramAxisY[j]->getBounds().toFloat();
                float wight = m_vBarDescriptors[i]->m_vHistogramWeight[j] * (lineYHistogramBounds.getHeight() / m_numOfBars);
                
                Rectangle<float> histogramBounds;
                histogramBounds.setY(lineXHistogramBounds.getY());
                  histogramBounds.setX((lineXHistogramBounds.getX() + lineXHistogramBounds.getHeight() / 2) + (i * m_histogramBarWidthInPixel));
                
                histogramBounds.setTop((lineXHistogramBounds.getY() + lineYHistogramBounds.getWidth()  / 2) - wight);
                histogramBounds.setHeight(wight);
                histogramBounds.setWidth(m_histogramBarWidthInPixel);
                
                m_vHistogramBars[j][i]->setBounds(histogramBounds.toNearestInt());
                m_vHistogramBars[j][i]->resized();
            }
        }
    }
}

//==============================================================================
void HistogramsDraw::resized()
//==============================================================================
{
    CalculateHistogramLinesDrawPoints();
    CalculateHistogramBars();
}


//=======================================    HistogramsBar      ====================================


//==============================================================================
void HistogramsBar::paint (Graphics& g)
//==============================================================================
{
    g.setColour(Colours::orange);
    auto area = getLocalBounds().toFloat().reduced(2);
    g.fillCheckerBoard(area.toFloat(), 1.0f, 1.0f, Colours::lightgreen, Colours::lightgreen);
    g.fillRect(area);
}

//==============================================================================
void HistogramsBar::resized()
//==============================================================================
{
    repaint();
}
