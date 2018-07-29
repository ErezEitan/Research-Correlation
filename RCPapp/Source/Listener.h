//
//  Listener.h
//  RCPapp
//
//  Created by Erez Eitan on 7/18/18.
//
//

#ifndef __Listener_h__
#define __Listener_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core/system/juce_PlatformDefs.h"

class ComponentCallbackListenerAbs : public ComponentListener
{
public:
    ComponentCallbackListenerAbs() {;}
    virtual ~ComponentCallbackListenerAbs() {;}
    virtual void Callback(const String in_msg) = 0;
};

class Listener : public ComponentCallbackListenerAbs
{
public:
    Listener() {;}
    virtual ~Listener() {;}
    void AddListener(ComponentCallbackListenerAbs* in_pListner) {m_pCallbackListener = in_pListner;}
    virtual void Callback(const String in_msg) override;
    
private:
    ComponentCallbackListenerAbs* m_pCallbackListener = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Listener);
};



#endif /* __Listener_h__ */
