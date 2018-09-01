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
        deleteAllChildren();
        
        InitBarsDrawArea();
        CalculateOneBarPixel();
        CalculateLinesDrawPoints();
        InitBars();
    
        addAndMakeVisible(m_lineAxisX);
        addAndMakeVisible(m_lineAxisY);
        
        InitHistogramsLines();
        CalculateHistogramLinesDrawPoints();
    
        InitHistogramsShowArrows();
        CalculateShowHistogramArrow();
        
        InitHistogramsWight();
        CalculateHistograms();
        
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
        CalculateOneBarPixel();
        InitBarsDrawArea();
        
        CalculateLinesDrawPoints();
        CalculateHistogramLinesDrawPoints();
        CalculateShowHistogramArrow();
        SetHightAndWidthForBars();
        CalculateHistograms();
       
        repaint();
    }
}

//==============================================================================
void BarAndLine::InitBarsDrawArea()
//==============================================================================
{
    Rectangle<float> area = getLocalBounds().toFloat();
    area.reduce(15.0f, 0.0f);
    float reduce = (area.getHeight() * 0.5f);
    area.setBottom(area.getBottom() - reduce);
    
    m_areaForBars = area;
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
void BarAndLine::InitHistogramsLines()
//==============================================================================
{
    m_vLineOfHistogramAxisX.clear();
    m_vLineOfHistogramAxisY.clear();
    m_vborderPath.clear();
    
    for (int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        m_vLineOfHistogramAxisX.push_back(std::make_shared<LinesDraw>(m_pMainCompenent));
        m_vLineOfHistogramAxisY.push_back(std::make_shared<LinesDraw>(m_pMainCompenent));
        
        m_vLineOfHistogramAxisX[i]->SetDirection(LineDraw::eHorizontal);
        m_vLineOfHistogramAxisX[i]->SetColor(ColorsForHistograms[i]);
        
        m_vLineOfHistogramAxisY[i]->SetDirection(LineDraw::eVertical);
        m_vLineOfHistogramAxisY[i]->SetColor(ColorsForHistograms[i]);
        
        addAndMakeVisible(*m_vLineOfHistogramAxisX[i]);
        addAndMakeVisible(*m_vLineOfHistogramAxisY[i]);
        
        m_vborderPath.push_back(Path());
    }
}

//==============================================================================
void BarAndLine::InitHistogramsWight()
//==============================================================================
{
    if (0 != m_numOfBars)
    {
        m_vHistogram.clear();
        m_vHistogram.resize(eNumberOfHistogramColors);
        
        for (int j = 0; j < eNumberOfHistogramColors; ++j)
        {
            m_vHistogram[j].resize(m_numOfBars);
            
            for (int i = 0; i < m_vBars.size(); ++i)
            {
                m_vHistogram[j][i] = std::make_shared<HistogramsDraw>(m_pMainCompenent);
                addAndMakeVisible(*m_vHistogram[j][i]);
            }
        }
    }
}

//==============================================================================
void BarAndLine::CalculateHistograms()
//==============================================================================
{
    if (0 != m_numOfBars)
    {
        auto& vBarDescriptor = m_rcpDescriptors.GetBarDescriptor();
        for (int j = 0; j < eNumberOfHistogramColors; ++j)
        {
            for (int i = 0; i < m_vBars.size(); ++i)
            {
                int redWight = vBarDescriptor[i]->m_vHistogramWeight[j];
                
                Rectangle<float> histogramBounds;
                histogramBounds.setTop((m_vLineOfHistogramAxisX[j]->getBounds().getY() + m_vLineOfHistogramAxisX[j]->getHeight() / 2) - redWight);
                histogramBounds.setHeight(redWight);
                histogramBounds.setX((m_vLineOfHistogramAxisX[j]->getX() + m_vLineOfHistogramAxisY[j]->getWidth() / 2) + (i * m_barWidthInPixel));
                histogramBounds.setWidth(m_barWidthInPixel);
                m_vHistogram[j][i]->setBounds(histogramBounds.toNearestInt());
            }
        }
    }
}

//==============================================================================
void BarAndLine::InitHistogramsShowArrows()
//==============================================================================
{
    m_vShowHistogramOrBar.clear();
    
    for(int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        m_vShowHistogramOrBar.push_back(std::make_shared<ArrowButtonForHistogramView>(m_pMainCompenent, 0.0f, ColorsForHistograms[i]));
        m_vShowHistogramOrBar[i]->addMouseListener(this, false);
    
        addAndMakeVisible(*m_vShowHistogramOrBar[i]);
    }
}

//==============================================================================
void BarAndLine::CalculateShowHistogramArrow()
//==============================================================================
{
    Rectangle<float> area = getLocalBounds().toFloat();
    //area.reduce(15.0f, 0.0f);
    
    for(int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        area.setBottom(m_vLineOfHistogramAxisX[i]->getBottom());
        m_vShowHistogramOrBar[i]->setBounds(area.getX(), area.getBottom() - 15.0f, 20.0f, 20.0f);
    }
}

//==============================================================================
void BarAndLine::paint (Graphics& g)
//==============================================================================
{
    if (!m_vborderPath.empty())
    {
        for (int i = 0; i < eNumberOfHistogramColors; ++i)
        {
            g.setColour (Colours::red);
            g.fillPath (m_vborderPath[i]);
            g.fillPath (m_vborderPath[i]);
        }
    }
    
    
}

//==============================================================================
void BarAndLine::CalculateLinesDrawPoints()
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
void BarAndLine::CalculateHistogramLinesDrawPoints()
//==============================================================================
{
    Rectangle<float> area = getLocalBounds().toFloat();
    float areaHightForHistogram = (area.getHeight() / 2) / 4;
    area.reduce(15.0f, 15.0f);
    area.setBottom(area.getBottom());
    area.setTop(m_areaForBars.getBottom());
    
    for (int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        Rectangle<float> areaLineDrawHorizontal(area.getX(), area.getBottom() - 15.0f - areaHightForHistogram * i, area.getWidth(), 30.0f);
        m_vLineOfHistogramAxisX[i]->setBounds(areaLineDrawHorizontal.toNearestInt());
        m_vLineOfHistogramAxisX[i]->SetNumberOfSepertors(m_numOfBars);
        m_vLineOfHistogramAxisX[i]->resized();
        
        Rectangle<float> areaLineDrawVertical(area.getX(),areaLineDrawHorizontal.getBottom() - areaHightForHistogram, 30.0f, areaHightForHistogram);
        m_vLineOfHistogramAxisY[i]->setBounds(areaLineDrawVertical.toNearestInt());
        m_vLineOfHistogramAxisY[i]->SetNumberOfSepertors(m_numOfBars);
        m_vLineOfHistogramAxisY[i]->resized();
    }
    /* TODO:: Border line
    for (int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        int border = m_rcpDescriptors.GetRcpHeaderDescriptor().m_vBorderLineHistogram[i];
        Rectangle<float> borderArea = m_vLineOfHistogramAxisX[i]->getBounds().toFloat();
        m_vborderPath[i].applyTransform (m_vborderPath[i].getTransformToScaleToFit (borderArea.getX(), borderArea.getY() - border, borderArea.getWidth(), borderArea.getHeight(), true));
    }
     */
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
                curBarBounds.setY((cur * m_barHightInPixel));
                m_vBars[cur]->setBounds(curBarBounds);
                for (int j = 0; j < m_vBars[cur]->GetBarDescriptor().m_vWhichBarAfterMe.size(); ++j)
                {
                    int barAfterMe = m_vBars[cur]->GetBarDescriptor().m_vWhichBarAfterMe[j];
                    float newAxisX = m_vBars[cur]->getBounds().getX() + m_vBars[cur]->GetBarDescriptor().m_barLength * m_barWidthInPixel;
                    Rectangle<float> newBarBounds = m_vBars[barAfterMe]->getBounds().toFloat();
                    newBarBounds.setX(newAxisX);
                    m_vBars[barAfterMe]->setBounds(newBarBounds.toNearestInt());
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
    Rectangle<int> area;
    Point<int> curPosition = getMouseXYRelative();
    Point<int> deltaDrag = (m_lastMouseLocation - curPosition);
    
    // Moves this Component according to the mouse drag event and applies our constraints to it
    if(e.eventComponent != this)
    {
        BarComponent* pBarComponent = dynamic_cast<BarComponent*>(e.eventComponent);
        
        if (nullptr != pBarComponent)
        {
            area = pBarComponent->getBounds();
       
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
    }
    
    for (int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        if(e.eventComponent == &(*m_vShowHistogramOrBar[i]))
        {
            area = e.eventComponent->getBounds();
            Rectangle<int> drawArea = getLocalBounds();
            drawArea.reduce(10, 10);
            Rectangle<int> newArea(area.getX(), area.getY() - deltaDrag.getY(), area.getWidth(), area.getHeight());
            if (newArea.getY() < drawArea.getHeight() && newArea.getY() > drawArea.getY())
            {
                m_arrowDistance = area.getY() - deltaDrag.getY();
                e.eventComponent->setBounds(newArea.getX(), m_arrowDistance, newArea.getWidth(), newArea.getHeight());
            }
        }
    }
    m_lastMouseLocation = getMouseXYRelative();
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

