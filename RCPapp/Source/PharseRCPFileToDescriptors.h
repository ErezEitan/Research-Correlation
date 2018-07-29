
#ifndef __PharseRCPFileDescriptors_h__
#define __PharseRCPFileDescriptors_h__

#include "RCP_DescriptorsConsts.h"
#include "ErrorList.h"

//==============================================================================
// #include "PharseRCPFileToDescriptors.h"
//==============================================================================



//==============================================================================
class PharseRCPFileToDescriptors
{
public:
	PharseRCPFileToDescriptors();
	~PharseRCPFileToDescriptors();

	UTErr OpenFilePathAndPharse(const String& in_string);
	std::vector<std::shared_ptr<BarDescriptorStruct>>& GetBarDescriptor() { return m_vBarDescriptor; }
	RCPHeaderDescriptor& GetRcpDescriptor() { return m_rcpDescriptor; }
    bool IsFileOpen() {return m_bIsFileOpen; }
    
private:
	// Private Members
    bool m_bIsFileOpen = false;
    RCPHeaderDescriptor m_rcpDescriptor;
	std::vector<std::shared_ptr<BarDescriptorStruct>> m_vBarDescriptor;

	// Private Functions
	void PharseFileToDescriptors(const String& in_string, const int32_t in_lineIndex);
	void ResetAllDescriptors();


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PharseRCPFileToDescriptors)
};

#endif //__PharseRCPFileDescriptors_h__
