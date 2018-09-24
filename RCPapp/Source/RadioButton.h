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
class RadioButtonText  : public TextButton
{
public:
    RadioButtonText();
    RadioButtonText(const String in_buttonName, const int in_index)
    : TextButton(in_buttonName)
    {
        m_index = in_index;
    }
    virtual ~RadioButtonText(){;}
    void SetRadioButtonIndex(const int in_index) {m_index = in_index;}
    void SetButtonText (String& in_buttonName) { setButtonText (in_buttonName);}
    int GetCurrentIndex() { return m_index; }

private:
    int m_index = 0;
};


//==============================================================================
class RadioButtons  : public Button
{
public:
    RadioButtons(const int in_numberOfButtons, const int in_groupNumber);
    virtual ~RadioButtons(){;}
    void UpdateToggleState (Button* button, int in_index);
    void SetButtonText (const int in_index, String in_buttonName);
    int GetCurrentIndex() { return m_currentIndex; }
    void AddListener(Listener* in);
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
    void resized() override;
    
    OwnedArray<RadioButtonText> m_radioButtons;
    int m_currentIndex = 0;
};


#endif /* __RadioButton_h__ */
