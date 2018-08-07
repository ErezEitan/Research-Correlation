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
        int lineIndex = 0;
        
        while (inputStream.getPosition() < fileSize)
        {
            String lineRead = inputStream.readNextLine();
            
            if (eBarsDescriptor > lineIndex)
            {
                PharseFileRCPDescriptorsHeader(lineRead, lineIndex);
            }
            else
            {
                PharseFileToDescriptors(lineRead, lineIndex - eBarsDescriptor);
            }
            
            ++lineIndex;
        }
    }
    
    return eRetVal;
}

//================================================================================================================
void PharseRCPFileToDescriptors::PharseFileRCPDescriptorsHeader(const String& in_string, const int in_lineIndex)
//================================================================================================================
{
    std::string sSubTypes(in_string.toStdString());
    std::string sDelimiter(" ");
    std::string sSubType;
    size_t pos = 0;
    int numInColumn = 0;
    
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
            
            ++numInColumn;
        }
        sSubTypes.erase(0, pos + sDelimiter.length());
    } while (std::string::npos != pos);
    
    for(int i = 0; i < m_rcpDescriptor.m_numOfBars; ++i)
    {
         m_vBarDescriptor.push_back(std::make_shared<BarDescriptorStruct>());
    }
}

//================================================================================================================
void PharseRCPFileToDescriptors::PharseFileToDescriptors(const String& in_string, const int in_lineIndex)
//================================================================================================================
{
    std::string sSubTypes(in_string.toStdString());
    std::string sDelimiter(" ");
    std::string sSubType;
    size_t pos = 0;
    int numInColumn = 0;
    
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
           
            m_vBarDescriptor[in_lineIndex]->m_headerDescriptor = eBarsDescriptor;
            if (eBarLength == numInColumn)
            {
                m_vBarDescriptor[in_lineIndex]->m_barLength = std::atoi(sSubType.c_str());
            }
            else if ((eHistogramWeight * m_rcpDescriptor.m_numOfHistogram) > numInColumn)
            {
                m_vBarDescriptor[in_lineIndex]->m_vHistogramWeight.push_back(std::atoi(sSubType.c_str()));
            }
            else if ((eHistogramWeight * m_rcpDescriptor.m_numOfHistogram) + 1 < numInColumn)
            {
                m_vBarDescriptor[in_lineIndex]->m_vWhichBarAfterMe.push_back(std::atoi(sSubType.c_str()) - 1);
                m_vBarDescriptor[std::atoi(sSubType.c_str()) - 1]->m_vWhichBarBeforeMe.push_back(in_lineIndex);
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
