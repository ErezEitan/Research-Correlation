//
//  FactoryDefaultControls.cpp
//  RCPapp
//
//  Created by Erez Eitan on 8/7/18.
//
//

#include "CompenentControls.h"
#include "FactoryDefaultControls.h"

#include "LoadFile.h"
#include "BarsAndLines.h"
#include "HistogramsDraw.h"

//==============================================================================================================
std::shared_ptr<CompenentControls> CreateDefaultControls(const String& in_ControlName, MainComponent* in_StandardGUI)
//==============================================================================================================
{
    std::shared_ptr<CompenentControls> retVal = 0;
    
    if( in_ControlName == "ToolBar")
    {
        retVal = std::make_shared<ToolBar>(in_StandardGUI);
    }
    else if( in_ControlName == "BarAndLine")
    {
        retVal = std::make_shared<BarAndLine>(in_StandardGUI);
    }
    
    return retVal;
}
