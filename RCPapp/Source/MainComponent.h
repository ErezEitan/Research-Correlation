
#ifndef __MainComponent_h__
#define __MainComponent_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include "BarsAndLines.h"
#include <iostream>
#include <cstdlib>


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class MainComponent  : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    
    //==============================================================================
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    ToolBar m_toolBar;
    BarAndLine m_barsAndLInes;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
 

#endif

