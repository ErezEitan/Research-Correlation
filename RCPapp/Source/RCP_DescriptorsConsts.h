#ifndef __RCP_DescriptorsConsts_h__
#define __RCP_DescriptorsConsts_h__

#include "../JuceLibraryCode/JuceHeader.h"

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
	eNumOf_BarDescriptor
};

struct RCPHeaderDescriptor
{
    int32_t m_numOfBars = -1;
    int32_t m_numOfHistogram = -1;
    std::vector<int32_t> m_vBorderLineHistogram;
};

struct BarDescriptorStruct
{
	int32_t m_barLength = -1;
	std::vector<int32_t> m_vHistogramWeight;
	int32_t m_dummy = -1;
	std::vector<int32_t> m_vWhichBarAfterMe;
	eHeaderDescriptor m_headerDescriptor = eNumOfHeaderDescriptor;
};

#endif //__RCP_DescriptorsConsts_h__
