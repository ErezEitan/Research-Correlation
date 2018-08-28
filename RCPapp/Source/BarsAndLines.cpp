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
    , m_lineOfHistogramAxisX(in_mainComponent)
    , m_lineOfHistogramAxisY(in_mainComponent)
//==============================================================================
{
    m_controlName = "BarAndLine";
    
    m_lineAxisX.SetDirection(LineDraw::eHorizontal);
    m_lineAxisY.SetDirection(LineDraw::eVertical);
 
    m_lineOfHistogramAxisX.SetDirection(LineDraw::eHorizontal);
    m_lineOfHistogramAxisX.SetColor(Colours::red);
    m_lineOfHistogramAxisY.SetDirection(LineDraw::eVertical);
    m_lineOfHistogramAxisY.SetColor(Colours::red);
    
    for (int i = 0; i < eNumberOfHistogramColors; ++i)
    {
        m_vShowHistogramOrBar.push_back(std::make_shared<ArrowButtonForHistogramView>(m_pMainCompenent, 0.0f, Colours::red));
        m_vShowHistogramOrBar[i]->addMouseListener(this, false);
    }
}

//==============================================================================
void BarAndLine::paint (Graphics& g)
//==============================================================================
{

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
        CalculateLinesDrawPoints();
        CalculateHistogramLinesDrawPoints();
        SetHightAndWidthForBars();
        CalculateAndHistograms();
        
        Rectangle<float> area = getLocalBounds().toFloat();
        area.reduce(15.0f, 0.0f);
        float reduce = (area.getHeight() * 0.5f) * 0.25f;
        for(int i = 0; i < eNumberOfHistogramColors; ++i)
        {
            area.setBottom(area.getBottom() - reduce - (i * reduce));
            m_vShowHistogramOrBar[i]->setBounds(area.getX(), area.getBottom() - 15.0f, 20.0f, 20.0f);
        }
        
        repaint();
    }
}

//==============================================================================
void BarAndLine::CalculateLinesDrawPoints()
//==============================================================================
{
   
    m_numOfBars = m_rcpDescriptors.GetRcpDescriptor().m_numOfBars;
    
    Rectangle<float> area = getLocalBounds().toFloat();
    area.reduce(15.0f, 0.0f);
    float reduce = (area.getHeight() * 0.5f);
    area.setBottom(area.getBottom() - reduce);
    
    Rectangle<float> areaLineDrawHorizontal(area.getX(), area.getBottom() - 15.0f, area.getWidth(), 30.0f);
    m_lineAxisX.setBounds(areaLineDrawHorizontal.toNearestInt());
    m_lineAxisX.SetNumberOfSepertors(m_numOfBars);
    m_lineAxisX.resized();
    
    Rectangle<float> areaLineDrawVertical(area.getX(), area.getTopLeft().getY(), 30.0f, area.getHeight());
    m_lineAxisY.setBounds(areaLineDrawVertical.toNearestInt());
    m_lineAxisY.SetNumberOfSepertors(m_numOfBars);
    m_lineAxisY.resized();
    
    m_barWidthInPixel = areaLineDrawHorizontal.getWidth() / m_numOfBars;
    m_barHightInPixel = areaLineDrawVertical.getHeight() / m_numOfBars;    
}


//==============================================================================
void BarAndLine::CalculateHistogramLinesDrawPoints()
//==============================================================================
{
    
    m_numOfBars = m_rcpDescriptors.GetRcpDescriptor().m_numOfBars;
    
    Rectangle<float> area = getLocalBounds().toFloat();
    area.reduce(15.0f, 15.0f);
    area.setBottom(area.getBottom());
    area.setTop(m_lineAxisX.getBottom());
    
    Rectangle<float> areaLineDrawHorizontal(area.getX(), area.getBottom() - 15.0f, area.getWidth(), 30.0f);
    m_lineOfHistogramAxisX.setBounds(areaLineDrawHorizontal.toNearestInt());
    m_lineOfHistogramAxisX.SetNumberOfSepertors(m_numOfBars);
    m_lineOfHistogramAxisX.resized();
    
    Rectangle<float> areaLineDrawVertical(area.getX(), m_lineAxisY.getBottom() + 15.0f, 30.0f, area.getHeight());
    m_lineOfHistogramAxisY.setBounds(areaLineDrawVertical.toNearestInt());
    m_lineOfHistogramAxisY.SetNumberOfSepertors(m_numOfBars);
    m_lineOfHistogramAxisY.resized();
}

//==============================================================================
void BarAndLine::Callback(const String in_msg, void* /*in_data*/)
//==============================================================================
{
    if(UTNoError(m_rcpDescriptors.OpenFilePathAndPharse(in_msg)))
    {
        addAndMakeVisible(m_lineAxisX);
        addAndMakeVisible(m_lineAxisY);
        addAndMakeVisible(m_lineOfHistogramAxisX);
        addAndMakeVisible(m_lineOfHistogramAxisY);
  
        
        Rectangle<float> area = getLocalBounds().toFloat();
        area.reduce(15.0f, 0.0f);
        float reduce = (area.getHeight() * 0.5f) * 0.25f;
        for(int i = 0; i < eNumberOfHistogramColors; ++i)
        {
            area.setBottom(area.getBottom() - reduce - (i * reduce));
            m_vShowHistogramOrBar[i]->setBounds(area.getX(), area.getBottom() - 15.0f, 20.0f, 20.0f);
            addAndMakeVisible(*m_vShowHistogramOrBar[i]);
        }
 
        CalculateLinesDrawPoints();
        CalculateHistogramLinesDrawPoints();
        CalculateAndSetBarsSize();
        CalculateAndHistograms();
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
            
            Rectangle<float> barBounds(m_lineAxisY.getX() * 2.0f, (i * m_barHightInPixel), m_barWidthInPixel * vBarDescriptor[i]->m_barLength, m_barHightInPixel);
            m_vBars[i]->setBounds(barBounds.toNearestInt());
            m_vBars[i]->SetBarDescriptor(*vBarDescriptor[i]);
        }
        
        SetHightAndWidthForBars();
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

//==============================================================================
void BarAndLine::CalculateAndHistograms()
//==============================================================================
{
    m_vHistogram.clear();
    
    if (0 != m_numOfBars)
    {
        m_vHistogram.resize(m_numOfBars);
        auto& vBarDescriptor = m_rcpDescriptors.GetBarDescriptor();
        
        for (int i = 0; i < m_vBars.size(); ++i)
        {
            m_vHistogram[i] = std::make_shared<HistogramsDraw>(m_pMainCompenent);
            addAndMakeVisible(*m_vHistogram[i]);
            int redWight = vBarDescriptor[i]->m_vHistogramWeight[eRed];

            Rectangle<float> histogramBounds;
            histogramBounds.setTop((m_lineOfHistogramAxisX.getBounds().getY() + m_lineOfHistogramAxisX.getHeight() / 2) - redWight);
            histogramBounds.setHeight(redWight);
            histogramBounds.setX((m_lineOfHistogramAxisX.getX() + m_lineOfHistogramAxisY.getWidth() / 2) + (i * m_barWidthInPixel));
            histogramBounds.setWidth(m_barWidthInPixel);
            m_vHistogram[i]->setBounds(histogramBounds.toNearestInt());
        }
    }
}
