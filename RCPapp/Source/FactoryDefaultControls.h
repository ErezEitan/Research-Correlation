//
//  FactoryDefaultControls.hpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#ifndef __FactoryDefaultControls_h__
#define __FactoryDefaultControls_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include "CompenentControls.h"

class MainComponent;

std::shared_ptr<CompenentControls> CreateDefaultControls(const String& in_ControlName, MainComponent* in_StandardGUI);

#endif /* FactoryDefaultControls_h */
