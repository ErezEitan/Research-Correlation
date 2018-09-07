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
BarAndLine::BarAndLine(MainComponent* in_mainComponent)
    : BaseComponentControl(in_mainComponent)
    , m_lineAxisX(in_mainComponent)
    , m_lineAxisY(in_mainComponent)
//==============================================================================
{
    m_controlName = "BarAndLine";
    
    m_lineAxisX.SetDirection(LineDraw::eHorizontal);
    m_lineAxisY.SetDirection(LineDraw::eVertical);
}

//==============================================================================
void BarAndLine::Callback(const String in_msg, void* /*in_data*/)
//==============================================================================
{
    if(UTNoError(m_rcpDescriptors.OpenFilePathAndPharse(in_msg)))
    {
        m_vBars.clear();
       // m_vHistogram.clear();
        m_vLineOfHistogramAxisX.clear();
        m_vLineOfHistogramAxisY.clear();
        removeAllChildren();
        
        InitBarsDrawArea();
        CalculateOneBarPixel();
        CalculateLinesBarsDrawPoints();
        InitBars();
    
        addAndMakeVisible(m_lineAxisX);
        addAndMakeVisible(m_lineAxisY);
    
        InitHistogramDraw();
        CalculateHistogramDraw();
        
        InitHistogramsShowArrows();
        CalculateShowHistogramArrow();
        
        repaint();
    }
}

//==============================================================================
void BarAndLine::CalculateOneBarPixel()
//==============================================================================
{
    m_numOfBars = m_rcpDescriptors.GetRcpHeaderDescriptor().m_numOfBars;
    
    m_barWidthInPixel = m_areaForBars.getWidth() / m_numOfBars;
    m_barHightInPixel = m_areaForBars.getHeight() / m_numOfBars;
}

//==============================================================================
void BarAndLine::resized()
//==============================================================================
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    if(m_rcpDescriptors.IsFileOpen())
    {
        CalculateBarsDrawArea();
        CalculateOneBarPixel();
        CalculateLinesBarsDrawPoints();
        SetHightAndWidthForBars();
        m_histogramsDraw->setBounds(m_areaForHistograms.toNearestInt());
        repaint();
    }
}

//==============================================================================
void BarAndLine::InitBarsDrawArea()
//==============================================================================
{
    Rectangle<float> area = getLocalBounds().toFloat();
    area.reduce(15.0f, 0.0f);
    m_areaForHistograms = area;
    
    float reduce = (area.getHeight() * 0.5f);
    area.setBottom(area.getBottom() - reduce - m_factor);
    m_areaForHistograms.setTop(area.getBottom());
   

    m_areaForBars = area;
    area = m_areaForBars;
}

//==============================================================================
void BarAndLine::InitBars()
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
            
            Rectangle<float> barBounds(m_lineAxisY.getX() * 2.0f, (i * m_barHightInPixel), m_barWidthInPixel * vBarDescriptor[i]->m_barLength, m_barHightInPixel);
            m_vBars[i]->setBounds(barBounds.toNearestInt());
            m_vBars[i]->SetBarDescriptor(*vBarDescriptor[i]);
        }
        
        SetHightAndWidthForBars();
    }
}

//==============================================================================
void BarAndLine::InitHistogramsShowArrows()
//==============================================================================
{
    m_showHistogramOrBar = std::make_shared<ArrowButtonForHistogramView>(m_pMainCompenent, 0.0f, Colours::aquamarine);
    m_showHistogramOrBar->addMouseListener(this, false);
    
    addAndMakeVisible(*m_showHistogramOrBar);
    
}

//==============================================================================
void BarAndLine::InitHistogramDraw()
//==============================================================================
{
    m_histogramsDraw = std::make_shared<HistogramsDraw>(m_pMainCompenent, m_rcpDescriptors.GetBarDescriptor());
    m_histogramsDraw->setBounds(m_areaForHistograms.toNearestInt());
    m_histogramsDraw->InitHistogramDraw();
    addAndMakeVisible(*m_histogramsDraw);
}

//==============================================================================
void BarAndLine::CalculateBarsDrawArea()
//==============================================================================
{
    Rectangle<float> area = getLocalBounds().toFloat();
    area.reduce(15.0f, 0.0f);
    
    m_areaForBars.setWidth(area.getWidth());
    m_areaForBars.setBottom(m_areaForBars.getBottom() - m_factor);
    
    m_areaForHistograms.setWidth(area.getWidth());
    m_areaForHistograms.setBottom(area.getBottom());
    m_areaForHistograms.setTop(m_areaForBars.getBottom());
}

//==============================================================================
void BarAndLine::CalculateShowHistogramArrow()
//==============================================================================
{
    Rectangle<float> area = getLocalBounds().toFloat();
    //area.reduce(15.0f, 0.0f);
    
    area.setBottom(m_lineAxisX.getBounds().getBottom());
    m_showHistogramOrBar->setBounds(area.getX(), area.getBottom() - 15.0f, 20.0f, 20.0f);
}

//==============================================================================
void BarAndLine::CalculateLinesBarsDrawPoints()
//==============================================================================
{
    Rectangle<float> areaLineDrawHorizontal(m_areaForBars.getX(), m_areaForBars.getBottom() - 15.0f, m_areaForBars.getWidth(), 30.0f);
    m_lineAxisX.setBounds(areaLineDrawHorizontal.toNearestInt());
    m_lineAxisX.SetNumberOfSepertors(m_numOfBars);
    m_lineAxisX.resized();
    
    Rectangle<float> areaLineDrawVertical(m_areaForBars.getX(), m_areaForBars.getTopLeft().getY(), 30.0f, m_areaForBars.getHeight());
    m_lineAxisY.setBounds(areaLineDrawVertical.toNearestInt());
    m_lineAxisY.SetNumberOfSepertors(m_numOfBars);
    m_lineAxisY.resized();
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
                Rectangle<float> curBarBounds = m_vBars[cur]->getBounds().toFloat();
                curBarBounds.setY((cur * m_barHightInPixel));
                m_vBars[cur]->setBounds(curBarBounds.toNearestInt());
                for (int j = 0; j < m_vBars[cur]->GetBarDescriptor().m_vWhichBarAfterMe.size(); ++j)
                {
                    int barAfterMe = m_vBars[cur]->GetBarDescriptor().m_vWhichBarAfterMe[j];
                    float newAxisX = m_vBars[cur]->getBounds().toFloat().getX() + m_vBars[cur]->GetBarDescriptor().m_barLength * m_barWidthInPixel;
                    Rectangle<float> newBarBounds = m_vBars[barAfterMe]->getBounds().toFloat();
                    newBarBounds.setX(newAxisX);
                    m_vBars[barAfterMe]->setBounds(newBarBounds.toNearestInt());
                }
            }
        }
    }
}

//==============================================================================
void BarAndLine::CalculateHistogramDraw()
//==============================================================================
{
    m_histogramsDraw->setBounds(m_areaForHistograms.toNearestInt());
}

//==============================================================================
void BarAndLine::paint (Graphics& g)
//==============================================================================
{
    if (!m_vborderPath.empty())
    {
        float pixelOfHistogram = (m_vLineOfHistogramAxisY[0]->getBounds().toFloat().getHeight() / m_vBars.size());
         
        for (int i = 0; i < eNumberOfHistogramColors; ++i)
        {
            int border = m_rcpDescriptors.GetRcpHeaderDescriptor().m_vBorderLineHistogram[i];
            Rectangle<float> histogramLineArea = m_vLineOfHistogramAxisX[i]->getBounds().toFloat();
            
            Rectangle<float> borderArea;

            borderArea.setY((histogramLineArea.getY() + (histogramLineArea.getHeight() / 2)) - border * pixelOfHistogram);
            borderArea.setX(histogramLineArea.getX());
            borderArea.setWidth(histogramLineArea.getWidth());
            borderArea.setHeight(10);
            
            g.drawLine(borderArea.getX(), borderArea.getY(), borderArea.getWidth(), borderArea.getY());
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
    Rectangle<float> area;
    Point<int> curPosition = getMouseXYRelative();
    Point<int> deltaDrag = (m_lastMouseLocation - curPosition);
    
    // Moves this Component according to the mouse drag event and applies our constraints to it
    if(e.eventComponent != this)
    {
        BarComponent* pBarComponent = dynamic_cast<BarComponent*>(e.eventComponent);
        
        if (nullptr != pBarComponent)
        {
            area = pBarComponent->getBounds().toFloat();
       
            if (0 != deltaDrag.getX())
            {
                BarDescriptorStruct barDescriptor = pBarComponent->GetBarDescriptor();
                Rectangle<float> areaBarBeforeMe = GetTheAreaLimiterFromBarsBeforeMe(barDescriptor.m_vWhichBarBeforeMe);
                Rectangle<float> areaBarAfterMe = GetTheAreaLimiterFromBarsAfterMe(barDescriptor.m_vWhichBarAfterMe);
                
                if((area.getX() - deltaDrag.getX()) > areaBarBeforeMe.getRight())
                {
                    area.setX(area.getX() - deltaDrag.getX());
                    e.eventComponent->setBounds(area.toNearestInt());
                }
            }
        }
    }
    
  
        if(e.eventComponent == &(*m_showHistogramOrBar))
        {
            m_factor = deltaDrag.getY();
            resized();
        }
    
    m_lastMouseLocation = getMouseXYRelative();
}

//=================================================================================================
Rectangle<float> BarAndLine::GetTheAreaLimiterFromBarsBeforeMe(const std::vector<int32_t>& in_vWhichBarBeforeMe)
//==================================================================================================
{
    Rectangle<float> areaRetVal(0.0f,0.0f,0.0f,0.0f);
    for(int i = 0; i < in_vWhichBarBeforeMe.size(); ++i)
    {
        Rectangle<float> areaBarBeforeMe = m_vBars[in_vWhichBarBeforeMe[i]]->getBounds().toFloat();
        if(areaRetVal.getRight() < areaBarBeforeMe.getX())
        {
            areaRetVal = areaBarBeforeMe;
        }
    }
    
    return areaRetVal;
}

//=================================================================================================
Rectangle<float> BarAndLine::GetTheAreaLimiterFromBarsAfterMe(const std::vector<int32_t>& in_vWhichBarAfterMe)
//==================================================================================================
{
    Rectangle<float> areaRetVal(0.0f,0.0f,0.0f,0.0f);
    for(int i = 0; i < in_vWhichBarAfterMe.size(); ++i)
    {
        Rectangle<float> areaBarAfterMe = m_vBars[in_vWhichBarAfterMe[i]]->getBounds().toFloat();
        if(areaRetVal.getX() < areaBarAfterMe.getRight())
        {
            areaRetVal = areaBarAfterMe;
        }
    }
    
    return areaRetVal;
}

