#include "LoadFile.h"

//================
ToolBar::ToolBar()
//================
{
	setOpaque(true);
	StringArray windowNames{ "'Load' File Browser", "'Save' File Browser" };

	for (auto windowName : windowNames)
	{
		auto* newButton = new TextButton();

		addAndMakeVisible(windowButtons.add(newButton));
		newButton->setButtonText(windowName);

		auto index = windowNames.indexOf(windowName);
		newButton->onClick = [this, index, newButton] { ShowWindow(*newButton, static_cast<DialogType> (index)); };
	}

	setSize(620, 50);
}

//===============================
void ToolBar::paint(Graphics& g)
//===============================
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.setColour(Colours::white);
}

//=======================
void ToolBar::resized()
//=======================
{
	auto area = getLocalBounds().reduced(5, 15);
	Rectangle<int> topRow;

	for (auto* b : windowButtons)
	{
		auto index = windowButtons.indexOf(b);

		if (topRow.getWidth() < 10 || index == loadChooser)
			topRow = area.removeFromTop(26);

		b->setBounds(topRow.removeFromLeft(area.getWidth() / 2).reduced(4, 2));
	}

	area.removeFromTop(15);
}

//============================================================
void ToolBar::ShowWindow(Component& button, DialogType type) 
//============================================================
{
	if (type >= loadChooser && type <= saveChooser)
	{
		if (type == loadChooser)
		{
			fc.reset(new FileChooser("Choose a file to open...", File::getCurrentWorkingDirectory(),
				"*", false));

			fc->launchAsync(FileBrowserComponent::canSelectMultipleItems | FileBrowserComponent::openMode
				| FileBrowserComponent::canSelectFiles,
				[&](const FileChooser& chooser)
			{
				m_rcpFilePath.clear();
				auto results = chooser.getURLResults();

				for (auto result : results)
					m_rcpFilePath << (result.isLocalFile() ? result.getLocalFile().getFullPathName()
						: result.toString(false));

				AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
					"File Chooser...",
					"You picked: " + m_rcpFilePath);
             
                    m_listener.Callback(m_rcpFilePath);
                
    
			});
		}
		else if (type == saveChooser)
		{
			auto fileToSave = File::createTempFile("saveChooserDemo");

			if (fileToSave.createDirectory().wasOk())
			{
				fileToSave = fileToSave.getChildFile("JUCE.png");
				fileToSave.deleteFile();

				std::unique_ptr<OutputStream> outStream(fileToSave.createOutputStream());
				//std::unique_ptr<InputStream> inStream(createAssetInputStream("juce_icon.png"));
				//outStream->writeFromInputStream(*inStream, -1);
			}

			fc.reset(new FileChooser("Choose a file to save...",
				File::getCurrentWorkingDirectory().getChildFile(fileToSave.getFileName()),
				"*", false));

			fc->launchAsync(FileBrowserComponent::saveMode | FileBrowserComponent::canSelectFiles,
				[fileToSave](const FileChooser& chooser)
			{
				auto result = chooser.getURLResult();
				auto name = result.isEmpty() ? String()
					: (result.isLocalFile() ? result.getLocalFile().getFullPathName()
						: result.toString(true));

				// Android and iOS file choosers will create placeholder files for chosen
				// paths, so we may as well write into those files.
#if JUCE_ANDROID || JUCE_IOS
				if (!result.isEmpty())
				{
					std::unique_ptr<InputStream>  wi(fileToSave.createInputStream());
					std::unique_ptr<OutputStream> wo(result.createOutputStream());

					if (wi.get() != nullptr && wo.get() != nullptr)
					{
						auto numWritten = wo->writeFromInputStream(*wi, -1);
						jassert(numWritten > 0);
						ignoreUnused(numWritten);
						wo->flush();
					}
				}
#endif

				AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
					"File Chooser...",
					"You picked: " + name);
			});
		}
	}
}
