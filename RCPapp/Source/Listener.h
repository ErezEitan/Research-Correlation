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
    virtual void Callback(const String in_msg, void* in_data = 0) = 0;
};

class Listener : public ComponentCallbackListenerAbs
{
public:
    Listener() {;}
    virtual ~Listener() {;}
    void AddListener(std::shared_ptr<ComponentCallbackListenerAbs> in_pListner) {m_pCallbackListener = in_pListner;}
    virtual void Callback(const String in_msg, void* in_data = 0) override;
    
private:
    std::shared_ptr<ComponentCallbackListenerAbs> m_pCallbackListener = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Listener);
};



#endif /* __Listener_h__ */
