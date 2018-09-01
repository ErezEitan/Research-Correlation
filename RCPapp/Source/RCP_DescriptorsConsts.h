#ifndef __RCP_DescriptorsConsts_h__
#define __RCP_DescriptorsConsts_h__

#include "../JuceLibraryCode/JuceHeader.h"


enum HistogramColor
{
    eRed,
    eBlue,
    eGreen,
    eYellow,
    eNumberOfHistogramColors
};

const Colour ColorsForHistograms[eNumberOfHistogramColors] = {
    Colours::red,
    Colours::blue,
    Colours::green,
    Colours::yellow
};

enum eRCP_Descriptor
{
	eNumOfBars,
	eNumOfHistogram,
	eNumOfRCP_Descriptor
};

enum eHeaderDescriptor
{
	eRCP_Descriptor_lineDescriptor,
	eHistogramDescriptor,
	eBarsDescriptor,
	eNumOfHeaderDescriptor,
};

enum eBarDescriptor
{
	eBarLength,
	eHistogramWeight,
	eDummy,
	eWhichBarAfterMe,
    eWhichBarBeforeMe,
	eNumOf_BarDescriptor
};

struct RCPHeaderDescriptor
{
    int m_numOfBars = -1;
    int m_numOfHistogram = -1;
    std::vector<int> m_vBorderLineHistogram;
};

struct BarDescriptorStruct
{
	int m_barLength = -1;
	std::vector<int> m_vHistogramWeight;
	int m_dummy = -1;
    std::vector<int> m_vWhichBarBeforeMe;
	std::vector<int> m_vWhichBarAfterMe;
	eHeaderDescriptor m_headerDescriptor = eNumOfHeaderDescriptor;
};

#endif //__RCP_DescriptorsConsts_h__
