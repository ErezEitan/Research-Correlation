#ifndef __LoadFile_h__
#define __LoadFile_h__


#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_core/system/juce_PlatformDefs.h"
#include "Listener.h"
#include "CompenentControls.h"


enum DialogType
{
	loadChooser,
	saveChooser,
};

//==============================================================================
class ToolBar : public CompenentControls
{
public:
    ToolBar(MainComponent* in_mainComponent);
	~ToolBar() {};

	void paint(Graphics& g) override;
	void resized() override;
    void AddListner(std::shared_ptr<ComponentCallbackListenerAbs> in_pListener) override { m_listener.AddListener(in_pListener); }
    
private:
	// Private Members
	OwnedArray<TextButton> windowButtons;
	std::unique_ptr<FileChooser> fc;
    String m_rcpFilePath;
    Listener m_listener;
	// Private Functions
	void ShowWindow(Component& button, DialogType type);
    std::function<void(void*)> onClick = [&](void*){};
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToolBar)
};


#endif //__LoadFile_h__
