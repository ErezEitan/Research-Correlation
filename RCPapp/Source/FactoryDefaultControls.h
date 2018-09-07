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
#include "BaseComponentControl.h"

class MainComponent;

std::shared_ptr<BaseComponentControl> CreateDefaultControls(const String& in_ControlName, MainComponent* in_StandardGUI);
//td::shared_ptr<Component> CreateToolBarControls(const String& in_ControlName, MainComponent* /*in_StandardGUI*/);

#endif /* FactoryDefaultControls_h */
