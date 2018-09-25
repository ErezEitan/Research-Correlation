//
//  BaseComponentControl.h
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#ifndef __BaseComponentControl_h__
#define __BaseComponentControl_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>
#include "Listener.h"
#include "MainComponent.h"
#include "PharseRCPFileToDescriptors.h"

class BaseComponentControl  : public Component ,public Listener
{
public:
    //==============================================================================
    BaseComponentControl(MainComponent* in_pMainCompenent);
    ~BaseComponentControl();
    
    //==============================================================================
    void resized() override;
    virtual void AddListner(std::shared_ptr<ComponentCallbackListenerAbs> in_pListener){;}
    virtual void Callback(const String in_msg, void* /*in_data*/) override {;}
    
protected:
   
    MainComponent* m_pMainCompenent = nullptr;
    String m_controlName = "ComponentControls";
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaseComponentControl)
};

#endif /* __BaseComponentControl_h__ */
