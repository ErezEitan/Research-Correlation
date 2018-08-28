//
//  ArrowButtonForHistogramView.c
//  RCPapp
//
//  Created by Erez Eitan on 8/26/18.
//
//

#include "ArrowButtonForHistogramView.h"

//==============================================================================================================
ArrowButtonForHistogramView::ArrowButtonForHistogramView (MainComponent* in_mainComponent, float arrowDirectionInRadians, Colour arrowColour)
    : BaseComponentControl(in_mainComponent)
    , m_colour(arrowColour)
//==============================================================================================================
{
    m_controlName = "ArrowButtonForHistogramView";
    m_arrowPath.addTriangle (0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f);
    m_arrowPath.applyTransform (AffineTransform::rotation (MathConstants<float>::twoPi * arrowDirectionInRadians, 0.5f, 0.5f));
}

//==============================================================================================================
void ArrowButtonForHistogramView::paint(Graphics& g)
//==============================================================================================================
{
    Path p (m_arrowPath);
    
    p.applyTransform (m_arrowPath.getTransformToScaleToFit (0.0f, 0.0f, getWidth() - 3.0f, getHeight() - 3.0f, false));
    
    DropShadow (Colours::black.withAlpha (0.3f), 4, Point<int>()).drawForPath (g, p);
    
    g.setColour (m_colour);
    g.fillPath (p);
}
