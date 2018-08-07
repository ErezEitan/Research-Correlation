//
//  CompenentControls.hpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#ifndef __CompenentControls_h__
#define __CompenentControls_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>
#include "Listener.h"

class MainComponent;

class CompenentControls  : public Component ,public Listener
{
public:
    //==============================================================================
    CompenentControls(MainComponent* in_pMainCompenent);
    ~CompenentControls();
    
    //==============================================================================
    void resized() override;
    virtual void AddListner(std::shared_ptr<ComponentCallbackListenerAbs> in_pListener){;}
    
    MainComponent* m_pMainCompenent = nullptr;
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    //std::shared_ptr<CompenentControls> m_toolBar;
    //std::shared_ptr<CompenentControls> m_barsAndLines;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompenentControls)
};

#endif /* __CompenentControls_h__ */
