//
//  ArrowButtonForHistogramView.h
//  RCPapp
//
//  Created by Erez Eitan on 8/26/18.
//
//

#ifndef __RadioButton_h__
#define __RadioButton_h__

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>
#include "BaseComponentControl.h"


//==============================================================================
class RadioButtons  : public BaseComponentControl
{
public:
    RadioButtons(MainComponent* in_mainComponent, const int in_numberOfButtons, const int in_groupNumber);
    
    void UpdateToggleState (Button* button, int in_index);
    void SetButtonText (const int in_index, String in_buttonName);
    int GetCurrentIndex() { return m_currentIndex; }
    
    void resized() override;
    
    OwnedArray<TextButton> m_radioButtons;
    int m_currentIndex = 0;
};


#endif /* __RadioButton_h__ */
