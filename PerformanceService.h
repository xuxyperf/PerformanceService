
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PERFORMANCESERVICE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PERFORMANCESERVICE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//double atof(const char *string); 
/*#ifdef PERFORMANCESERVICE_EXPORTS
#define PERFORMANCESERVICE_API __declspec(dllexport)
#else
#define PERFORMANCESERVICE_API __declspec(dllimport)
#endif

// This class is exported from the PerformanceService.dll
class PERFORMANCESERVICE_API CPerformanceService {
public:
	CPerformanceService(void);
	// TODO: add your methods here.
};

extern PERFORMANCESERVICE_API int nPerformanceService;

PERFORMANCESERVICE_API int fnPerformanceService(void);*/

extern "C" __declspec(dllexport) void PF_NetGatewaySignedEnvelopSign(const char* lpszSrcData, const char *pszServerIP, int usPort, const char *pszUri, const char *pszSignAlias, const char *pszEncAlias, const char *pszLibName, unsigned char *pDataBuf, long lDataBufLen);
extern "C" __declspec(dllexport) int PF_URLEncode(const char* str, const int strSize, char* result, const int resultSize);
extern "C" __declspec(dllexport) int PF_DateTimeURLEncode(const char* str, const int strSize, char* result, const int resultSize);
extern "C" __declspec(dllexport) int PF_URLDecode(const char* str, const int strSize, char* result, const int resultSize);
extern "C" __declspec(dllexport) const char *PF_TimeDiffStr(char *timeStr);
extern "C" __declspec(dllexport) const char *PF_SubString(char *tempStr,int length,int iNum);
extern "C" __declspec(dllexport) const char *PF_JITPerformanceSign2(const char *certInfo,  const char *srcStr);
extern "C" __declspec(dllexport) const char *PF_JITPerformanceSign(const char *certInfo,  const char *srcStr);