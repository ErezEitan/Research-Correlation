#include "PharseRCPFileToDescriptors.h"

//============================================================================================
PharseRCPFileToDescriptors::PharseRCPFileToDescriptors()
//============================================================================================
{
}

//============================================================================================
PharseRCPFileToDescriptors::~PharseRCPFileToDescriptors()
//============================================================================================
{
	ResetAllDescriptors();
}

//============================================================================================
UTErr PharseRCPFileToDescriptors::OpenFilePathAndPharse(const String& in_string)
//============================================================================================
{

	ResetAllDescriptors();

	File f(in_string);
	juce::FileInputStream inputStream(f);

	UTErr eRetVal = !inputStream.failedToOpen() ? eNoErr : eFMOpenFailed;

	if (UTNoError(eRetVal))
	{
        m_bIsFileOpen = true;
		int64 fileSize = inputStream.getTotalLength();
		int32_t lineIndex = 0;
		while (inputStream.getPosition() < fileSize)
		{
			String num = inputStream.readNextLine();
			PharseFileToDescriptors(num, lineIndex);
			++lineIndex;
		}
	}
	
	return eRetVal;
}

//================================================================================================================
void PharseRCPFileToDescriptors::PharseFileToDescriptors(const String& in_string, const int32_t in_lineIndex)
//================================================================================================================
{
	std::string sSubTypes(in_string.toStdString());
	std::string sDelimiter(" ");
	std::string sSubType;
	size_t pos = 0;
	int32_t numInColumn = 0;
    
    if (in_lineIndex >= eBarsDescriptor)
    {
        m_vBarDescriptor.push_back(std::make_shared<BarDescriptorStruct>());
    }
    int32_t vIndex = m_vBarDescriptor.size() - 1;
    
	do
	{
		pos = sSubTypes.find(sDelimiter);
		if (std::string::npos == pos)
		{
			sSubType = sSubTypes;
		}
		else if (pos > 0)
		{
			sSubType = sSubTypes.substr(0, pos);
			if (eRCP_Descriptor_lineDescriptor == in_lineIndex)
			{
				if (eNumOfBars == numInColumn)
				{
					m_rcpDescriptor.m_numOfBars = std::atoi(sSubType.c_str());
				}
				else if (eNumOfHistogram == numInColumn)
				{
					m_rcpDescriptor.m_numOfHistogram = std::atoi(sSubType.c_str());
				}
			}
			else if (eHistogramDescriptor == in_lineIndex)
			{
				m_rcpDescriptor.m_vBorderLineHistogram.push_back(std::atoi(sSubType.c_str()));
			}
			else if (in_lineIndex >= eBarsDescriptor)
			{
				m_vBarDescriptor[vIndex]->m_headerDescriptor = eBarsDescriptor;
				if (eBarLength == numInColumn)
				{
					m_vBarDescriptor[vIndex]->m_barLength = std::atoi(sSubType.c_str());
				}
				else if ((eHistogramWeight * m_rcpDescriptor.m_numOfHistogram) > numInColumn)
				{
					m_vBarDescriptor[vIndex]->m_vHistogramWeight.push_back(std::atoi(sSubType.c_str()));
				}
				else if ((eHistogramWeight * m_rcpDescriptor.m_numOfHistogram) + 1 < numInColumn)
				{
					m_vBarDescriptor[vIndex]->m_vWhichBarAfterMe.push_back(std::atoi(sSubType.c_str()) - 1);
				}
			}
			++numInColumn;
		}
		sSubTypes.erase(0, pos + sDelimiter.length());
	} while (std::string::npos != pos);
}

//==================================================
void PharseRCPFileToDescriptors::ResetAllDescriptors()
//==================================================
{
    m_vBarDescriptor.clear();
	m_rcpDescriptor = RCPHeaderDescriptor();
}
