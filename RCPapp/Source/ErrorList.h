
/* Copy to include:
#include "ErrorList.h"
*/

typedef int32_t	UTErr;
const UTErr eNoErr = 0;

// General errors
const UTErr eGenericErr = -1;

// File Manager errors
const UTErr eFMOpenFailed = -1000;

// XML Errors
const UTErr eXMLParserFailed = -6000;

#define UTIsError(theErrorCode) (eNoErr != (theErrorCode))
#define UTNoError(theErrorCode) (eNoErr == (theErrorCode))

#define UTThrowError(theErrorCode) {if(WUIsError(theErrorCode))throw (theErrorCode);}
#define UTThrowErrorIfNil(thePtr , theErrorCode) {if (0 == thePtr )throw (theErrorCode);}
#define UTThrowErrorIfFalse(theBool , theErrorCode) {if (!(theBool))throw (theErrorCode);}
#define UTThrowErrorCodeIfError(err,theErrorCode) {if(WUIsError(err))throw (theErrorCode);}
