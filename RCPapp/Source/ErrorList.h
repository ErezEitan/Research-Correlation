
/* Copy to include:
#include "ErrorList.h"
*/

typedef int32_t	UTErr;
const UTErr eNoErr = 0;

// General errors
const UTErr eGenericErr = -1;
const UTErr eUserCanceled = -2;
const UTErr eUnknownErr = -3;
const UTErr eExceptionErr = -4;
const UTErr eEndianError = -5;
const UTErr eThreadSafeError = -6;
const UTErr eSomeThingNotInitailzed = -7;
const UTErr eWrongObjectState = -8; //!< object was not in an acceptable state
const UTErr eUninitalized = -9;
const UTErr eDeprecated = -10;
const UTErr eCommandLineParameter = -11;
const UTErr eNotANumber = -12; //!< expected a number but none was found
const UTErr eNotJustANumber = -13; //!< expected a number and found one but also other stuff (e.g. "123XYZ")
const UTErr eNegativeNumber = -14; //!< expected a positive number and found a negative
const UTErr eTimeOut = -15; //!< something timed out
const UTErr eSomeThingInitailzedTwice = -17;
const UTErr eGenerateHelpInfo = -18;
const UTErr eOutOfRangeNumber = -19;
const UTErr eMacOnlyCode = -20;
const UTErr eWinOnlyCode = -21;
const UTErr eAppLaunchFailed = -22; //!< failed to launch an application
const UTErr eAppTerminateFailed = -23; //!< failed to terminate an application
const UTErr eAppReturnedError = -24; //!< Non zero exit code from application
const UTErr eNotImplemented = -25; //!< Function is not implemented
const UTErr eNotEmpty = -26; //!< Something was expected to be empty but is not
const UTErr eSessionTemplatesNotFound = -27; //!< Session template folder is empty.
const UTErr eValueNotFound = -29;
const UTErr eValueWrongSize = -30;
const UTErr eOperatingSystemNotSupported = -31;
const UTErr eInvalidValue = -32;

// File Manager errors
const UTErr eFMNoSuchVolume = -1001;
const UTErr eFMFileNotFound = -1002;
const UTErr eFMFileAllreadyExists = -1003;
const UTErr eFMAllreadyOpenWithWritePerm = -1004;
const UTErr eFMEndOfFile = -1005;
const UTErr eFMPermissionErr = -1006;
const UTErr eFMBusyErr = -1007;
const UTErr eFMOpenFailed = -1008;
const UTErr eFMTranslateFileNameFailed = -1009;
const UTErr eFMWTPathRefCreationFailed = -1010;
const UTErr eFMReadFailed = -1011;
const UTErr eFMIllegalPathRef = -1012;
const UTErr eFMFileNotOpened = -1013;
const UTErr eFMFileSizeTooBig = -1014;
const UTErr eFMNoSuchDomain = -1015;
const UTErr eFMNoSuchSystemFolder = -1016;
const UTErr eFMWrongParameters = -1017;
const UTErr eFMIsNotAFolder = -1018;
const UTErr eFMIsAFolder = -1019;
const UTErr eFMIsNotAFile = -1020;
const UTErr eFMIsAFile = -1021;
const UTErr eFMDeleteFailed = -1022;
const UTErr eFMCreateFailed = -1023;
const UTErr eFMPathTooLong = -1024;
const UTErr eFMIOError = -1025;
const UTErr eFMIllegalOpenFileRef = -1026;
const UTErr eFMDiskFull = -1027;
const UTErr eFMFileNotEmpty = -1028;
const UTErr eFMEndOfFolder = -1029;
const UTErr eFMSamePath = -1030;
const UTErr eFMPathTooShort = -1031;
const UTErr eFMIncompletePath = -1032;
const UTErr eFMIsNoAFileSystemLink = -1033;
const UTErr eFMSymlinkBroken = -1034;
const UTErr eFMMoveFailed = -1035;
const UTErr eFMWriteFailed = -1036;
const UTErr eFMTooManyOpenFiles = -1037;
const UTErr eFMTooManySymlinks = -1038;
const UTErr eFMFileIsEmpty = -1039;

// System errors
const UTErr eGenericSystemError = -2000;
const UTErr eSysNoEnvironmentVariable = -2001;
const UTErr eDLLLoadingFailed = -2002;
const UTErr eFuncPointerNotFound = -2003;
const UTErr eDLLNotFound = -2004;
const UTErr eInvalideDate = -2009;
const UTErr eNoNetDevice = -2010;
const UTErr eNotAValidApplication = -2012;

// Resource Manager errors
const UTErr eRMResNotFound = -3000;
const UTErr eRMResExists = -3001; //!< a resource exist even though it's not expected to
const UTErr eRMContainerNotFound = -3002; //!< The container was not found in the list of containers
const UTErr eRMResRefNotFound = -3003; //!< The resRef was not found in container's resource list
const UTErr eRMInvalidResRef = -3004;
const UTErr eRMInvalidResContainer = -3005;
const UTErr eRMInvalidNativeResContainer = -3006;
const UTErr eRMAttachResContainerFailed = -3007;
const UTErr eRMInvalidResID = -3008;
const UTErr eRMResUpdateFailed = -3009;

// Graphic Manager & GUI errors
const UTErr eGMIsNotInitailzed = -3500;
const UTErr eGMInvalidImage = -3501;
const UTErr eGMGenericErr = -3502;
const UTErr eGMNoCurrentContext = -3503;
const UTErr eGUISkinNotFound = -3504;
const UTErr eGMNoVertices = -3505;
const UTErr eGMNoColors = -3506;
const UTErr eGMNoTexture = -3507;
const UTErr eGMIncompatibleOGLVersion = -3508;
const UTErr eGMNoDeviceContext = -3509;
const UTErr eGMNoPixelFormat = -3510;
const UTErr eGMNoOGLContext = -3511;
const UTErr eGMNoOGLContextSharing = -3512;
const UTErr eGMUnsupportedImageFormat = -3513;
const UTErr eGMUninitializedContext = -3514;
const UTErr eControlOutOfRange = -3515;
const UTErr eGMUninitializedFont = -3516;
const UTErr eGMInvalidFontDrawMethod = -3517;
const UTErr eGMUnreleasedTextures = -3518;
const UTErr eGMWrongThread = -3519;
const UTErr eGMDontCommitDraw = -3520;


// Memory errors
const UTErr eMemNewFailed = -4001; //!< Something = new CSomething, returned null
const UTErr eMemNewTPtrFailed = -4002; //!< NewTPtr or NewTPtrClear failed
const UTErr eMemNullPointer = -4003; //!< a null pointer was encountered where it should not
const UTErr eMemObjNotInitialized = -4004;
const UTErr eMemBuffTooShort = -4005; //!< the buffer in question did not have enough space for the operation
const UTErr eInstanciationFailed = -4006;
const UTErr eMemAddressSpaceError = -4007; //!< memory falls outside the legal address space
const UTErr eMemBadPointer = -4008;
const UTErr eMemOutOfMemory = -4009;

// XML Errors
const UTErr eXMLParserFailed = -6001;
const UTErr eXMLTreeNotValid = -6002;
const UTErr eXMLTreeEmpty = -6003;
const UTErr eXMLElementMissing = -6004;
const UTErr eXMLElementUninitalized = -6005; //!< element was default constructed it has not element name, etc..
const UTErr eXMLElementIncomplete = -6006;     //!< XML parser did not complete building the element
const UTErr eXMLAttribMissing = -6007;

#define UTIsError(theErrorCode) (eNoErr != (theErrorCode))
#define UTNoError(theErrorCode) (eNoErr == (theErrorCode))

#define UTThrowError(theErrorCode) {if(WUIsError(theErrorCode))throw (theErrorCode);}
#define UTThrowErrorIfNil(thePtr , theErrorCode) {if (0 == thePtr )throw (theErrorCode);}
#define UTThrowErrorIfFalse(theBool , theErrorCode) {if (!(theBool))throw (theErrorCode);}
#define UTThrowErrorCodeIfError(err,theErrorCode) {if(WUIsError(err))throw (theErrorCode);}
