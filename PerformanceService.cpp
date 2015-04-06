// PerformanceService.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "PerformanceService.h"
using namespace JITComVCTK_BOCLib;

double atof(const char *nptr);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

/*// This is an example of an exported variable
PERFORMANCESERVICE_API int nPerformanceService=0;

// This is an example of an exported function.
PERFORMANCESERVICE_API int fnPerformanceService(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see PerformanceService.h for the class definition
CPerformanceService::CPerformanceService()
{ 
	return; 
}*/


typedef long (*funInitServerConnectEx)(HANDLE*, const char*, const long);
typedef long (*funFinalizeServerConnectEx)(HANDLE*);
typedef long (*funSetServerUriEx)(HANDLE, const char*);
typedef long (*funSetCertAliasEx)(HANDLE, const char*);
typedef long (*funGetCertInfoEx)(HANDLE, const char*, const long, const char*, char*, long *);
typedef long (*funGetDataEx)(HANDLE, unsigned char*, long *);
typedef long (*funGetErrorCodeEx)(HANDLE);
typedef long (*funGetErrorMessageEx)(HANDLE, const long, char*, long *);
typedef long (*funGetFileEx)(HANDLE, const char*);
typedef long (*funEncryptSignedEnvelopEx)(HANDLE, const char*, const char*, const unsigned char*, const long, char*, long *);
typedef long (*funDecryptSignedEnvelopEx)(HANDLE, const char*, unsigned char*, long *);

void PF_NetGatewaySignedEnvelopSign(const char* lpszSrcData, const char *pszServerIP, int usPort, const char *pszUri, const char *pszSignAlias, const char *pszEncAlias, const char *pszLibName, unsigned char *pDataBuf, long lDataBufLen)
{
    HINSTANCE hinstance = NULL;
    HANDLE handle = NULL; /*����VSTK����*/
    const char *pszHashAlg = "SHA1"; /*������Ĭ��ֵ*/
    const char *pszEncAlg = "RSA"; /*������Ĭ��ֵ*/
    //long lDataBufLen = 0;
    long lError = 0;

    hinstance = LoadLibrary(pszLibName);
    if (hinstance != NULL)
    {
        printf("dl open ok\n");
        funEncryptSignedEnvelopEx pfunEncryptSignedEnvelopEx;
        funDecryptSignedEnvelopEx pfunDecryptSignedEnvelopEx;

        funFinalizeServerConnectEx pfunFinalizeServerConnectEx;
        funGetCertInfoEx pfunGetCertInfoEx;
        funGetDataEx pfunGetDataEx;
        funGetErrorCodeEx pfunGetErrorCodeEx;
        funGetErrorMessageEx pfunGetErrorMessageEx;
        funInitServerConnectEx pfunInitServerConnectEx;
        funSetCertAliasEx pfunSetCertAliasEx;
        funSetServerUriEx pfunSetServerUriEx;

        pfunEncryptSignedEnvelopEx = (funEncryptSignedEnvelopEx)GetProcAddress(hinstance, "EncryptSignedEnvelopEx");

        pfunFinalizeServerConnectEx = (funFinalizeServerConnectEx)GetProcAddress(hinstance, "FinalizeServerConnectEx");

        pfunGetCertInfoEx = (funGetCertInfoEx)GetProcAddress(hinstance, "GetCertInfoEx");

        pfunGetDataEx = (funGetDataEx)GetProcAddress(hinstance, "GetDataEx");

        pfunGetErrorCodeEx = (funGetErrorCodeEx)GetProcAddress(hinstance, "GetErrorCodeEx");

        pfunGetErrorMessageEx = (funGetErrorMessageEx)GetProcAddress(hinstance, "GetErrorMessageEx");

        pfunInitServerConnectEx = (funInitServerConnectEx)GetProcAddress(hinstance, "InitServerConnectEx");

        pfunSetCertAliasEx = (funSetCertAliasEx)GetProcAddress(hinstance, "SetCertAliasEx");

        pfunSetServerUriEx = (funSetServerUriEx)GetProcAddress(hinstance, "SetServerUriEx");

        pfunDecryptSignedEnvelopEx = (funDecryptSignedEnvelopEx)GetProcAddress(hinstance, "DecryptSignedEnvelopEx");

        lError = pfunInitServerConnectEx(&handle, pszServerIP, usPort); /*����ǩ��������*/
        if (lError == 0)
        {
            lError = pfunSetServerUriEx(handle, pszUri); /*����ͨѶUri*/
            /*������Ҫʹ�ã�Ĭ�Ͽ��Բ�������*/
            /*lError = pfunSetAlgorithmEx(handle, pszHashAlg, pszEncAlg);*/
            lError = pfunEncryptSignedEnvelopEx(handle, pszSignAlias, pszEncAlias, (const unsigned char*)(lpszSrcData), strlen(lpszSrcData), NULL, NULL);
            if (lError == 0)
            {
                printf("VSTK �����ŷ�ɹ�\n");

                lError = pfunGetDataEx(handle, pDataBuf, &lDataBufLen);
                if (lError == 0 && lDataBufLen != 0)
                {
                    /*pDataBuf = (unsigned char*)malloc(lDataBufLen + 1);
                    memset(pDataBuf, 0, lDataBufLen + 1);
                    lError = pfunGetDataEx(handle, pDataBuf, &lDataBufLen);
                    if (lError == 0)
                    {
                        lError = pfunDecryptSignedEnvelopEx(handle, (const char*)pDataBuf, NULL, NULL);
                        if (lError == 0)
                        {
                            printf("VSTK �����ŷ�ɹ�\n");

                            lError = pfunGetDataEx(handle, NULL, &lDataBufLen);
                            if (lError == 0 && lDataBufLen != 0)
                            {
                                unsigned char *pSrcData = (unsigned char*)malloc(lDataBufLen + 1);
                                memset(pSrcData, 0, lDataBufLen + 1);
                                lError = pfunGetDataEx(handle, pSrcData, &lDataBufLen);
                                if (lError == 0)
                                {
                                    printf("ԭ�ģ�%s\n", (const char*)pSrcData);
                                }
                                free(pSrcData);

                                lError = pfunGetCertInfoEx(handle, "VS", 0, NULL, NULL, &lDataBufLen); ȡ��֤���������Ϣ
	                            if (lError == 0 && lDataBufLen != 0)
	                            {
	                                char *pCertDN = (char*)malloc(lDataBufLen + 1);
	                                memset(pCertDN, 0, lDataBufLen + 1);
	                                lError = pfunGetCertInfoEx(handle, "VS", 0, NULL, pCertDN, &lDataBufLen); ȡ��֤���������Ϣ
	                                if (lError == 0)
	                                {
	                                    printf("֤������(%d)��%s\n", lDataBufLen, pCertDN);
	                                }
	                                free(pCertDN);
	                            }
	
	                            lError = pfunGetCertInfoEx(handle, "VS", 1, NULL, NULL, &lDataBufLen); ȡ��֤��İ䷢����Ϣ
	                            if (lError == 0 && lDataBufLen != 0)
	                            {
	                                char *pCertIssuerDN = (char*)malloc(lDataBufLen + 1);
	                                memset(pCertIssuerDN, 0, lDataBufLen + 1);
	                                lError = pfunGetCertInfoEx(handle, "VS", 1, NULL, pCertIssuerDN, &lDataBufLen); ȡ��֤��İ䷢����Ϣ
	                                if (lError == 0)
	                                {
	                                    printf("֤�����кţ�%s\n", pCertIssuerDN);
	                                }
	                                free(pCertIssuerDN);
	                            }
	
	                            lError = pfunGetCertInfoEx(handle, "VS", 2, NULL, NULL, &lDataBufLen); ȡ��֤������к���Ϣ
	                            if (lError == 0 && lDataBufLen != 0)
	                            {
	                                char *pCertSN = (char*)malloc(lDataBufLen + 1);
	                                memset(pCertSN, 0, lDataBufLen + 1);
	                                lError = pfunGetCertInfoEx(handle, "VS", 2, NULL, pCertSN, &lDataBufLen); ȡ��֤������к���Ϣ
	                                if (lError == 0)
	                                {
	                                    printf("֤��䷢�����⣺%s\n", pCertSN);
	                                }
	                                free(pCertSN);
	                            }
                            }
                        }
                        else
                        {
                            lError = pfunGetErrorMessageEx(handle, pfunGetErrorCodeEx(handle), NULL, &lDataBufLen);
                            if (lError == 0 && lDataBufLen != 0)
                            {
                                char *pErrorMsg = (char*)malloc(lDataBufLen + 1);
                                memset(pErrorMsg, 0, lDataBufLen + 1);
                                lError = pfunGetErrorMessageEx(handle, pfunGetErrorCodeEx(handle), pErrorMsg, &lDataBufLen);
                                if (lError == 0)
                                {
                                    printf("VSTK �����ŷ�ʧ��(%s)\n", pErrorMsg); ��ʾ��������
                                }
                                free(pErrorMsg);
                            }
                        }
                    }
                    free(pDataBuf);*/
                }
            }
            else
            {
                lError = pfunGetErrorMessageEx(handle, pfunGetErrorCodeEx(handle), NULL, &lDataBufLen);
                if (lError == 0 && lDataBufLen != 0)
                {
                    char *pErrorMsg = (char*)malloc(lDataBufLen + 1);
                    memset(pErrorMsg, 0, lDataBufLen + 1);
                    lError = pfunGetErrorMessageEx(handle, pfunGetErrorCodeEx(handle), pErrorMsg, &lDataBufLen);
                    if (lError == 0)
                    {
						//return -1;

                        printf("VSTK �����ŷ�ʧ��(%s)\n", pErrorMsg); /*��ʾ��������*/
                    }
                    free(pErrorMsg);
                }
            }
        }
        else
        {
            lError = pfunGetErrorMessageEx(handle, pfunGetErrorCodeEx(handle), NULL, &lDataBufLen);
            if (lError == 0 && lDataBufLen != 0)
            {
                char *pErrorMsg = (char*)malloc(lDataBufLen + 1);
                memset(pErrorMsg, 0, lDataBufLen + 1);
                lError = pfunGetErrorMessageEx(handle, pfunGetErrorCodeEx(handle), pErrorMsg, &lDataBufLen);
                if (lError == 0)
                {
					//return -1;
                    printf("VSTK ����ǩ��������ʧ��(%s)\n", pErrorMsg); /*��ʾ��������*/
                }
                free(pErrorMsg);
            }
        }
        pfunFinalizeServerConnectEx(&handle);
        FreeLibrary(hinstance);
    }
    else
    {
		//return -1;
        printf("dllopen error\n%d\n", GetLastError());
    }

	//return 0;
}

//365 0:59:1.721000000
const  char *SubStr(char*strDest,char*strSource,int iStartPos,int iNum) 
{
	int i = 0;
	for(i;i<iNum;i++)
	{
	   strDest[i]=strSource[i]; 
	}

    strDest[iNum]='\0';

	return strDest;
}

const char *SubString(char *tempStr,int length,int iNum)
{
	char result[100];
	char *surStr = (char *)malloc(length+1); 
	char dststr[100];

	memset(result,0x00,100);
	memset(dststr,0x00,100);

	if(tempStr != NULL && strlen(tempStr) >= length)
	{

		SubStr(surStr,tempStr,0,length);

        strncpy(dststr,strrev(strdup(surStr)),iNum);
        strcpy(result,strrev(strdup(dststr)));
	}
	else
	{
		return "��ȡ�ĳ��ȴ����ַ�������!";
	}

	return result;
}

const char *PF_SubString(char *tempStr,int length,int iNum)
{
	char result[100];
	char *surStr = (char *)malloc(length+1); 
	char dststr[100];

	memset(result,0x00,100);
	memset(dststr,0x00,100);

	if(tempStr != NULL && strlen(tempStr) >= length)
	{

		SubStr(surStr,tempStr,0,length);

        strncpy(dststr,strrev(strdup(surStr)),iNum);
        strcpy(result,strrev(strdup(dststr)));
	}
	else
	{
		return "��ȡ�ĳ��ȴ����ַ�������!";
	}

	return result;
}

const char *PF_TimeDiffStr(char *timeStr)
{
	int day = 0,hour = 0,min = 0;
	double sec = 0.000,timeDiff = 0.000;
	char resTime[100];
	char resTimeDiff[100];

	memset(resTime,0x00,100);
	memset(resTimeDiff,0x00,100);

	day = atoi(SubString(timeStr,3,3));
	hour = atoi(SubString(timeStr,5,2));
	min = atoi(SubString(timeStr,8,2));
    sprintf(resTime,"%s",SubString(timeStr,20,11));

	sec = atof(resTime);

    timeDiff = day * 24 * 3600 + hour * 3600 + min * 60 + sec;

	sprintf(resTimeDiff, "%lf", timeDiff);

	return resTimeDiff;
}


#define NON_NUM '0'

int hex2num(char c)
{
    if (c>='0' && c<='9') return c - '0';
    if (c>='a' && c<='z') return c - 'a' + 10;//����+10��ԭ����:����16���Ƶ�aֵΪ10
    if (c>='A' && c<='Z') return c - 'A' + 10;
    
    printf("unexpected char: %c", c);
    return NON_NUM;
}

/**
 * @brief URLDecode ���ַ���URL����,����������
 *
 * @param str ԭ�ַ���
 * @param strSize ԭ�ַ�����С������������\0��
 * @param result ����ַ���������
 * @param resultSize �����ַ�Ļ�������С(��������\0)
 *
 * @return: >0 result ��ʵ����Ч���ַ�������
 *            0 ����ʧ��
 */

int PF_URLDecode(const char* str, const int strSize, char* result, const int resultSize)
{
    char ch,ch1,ch2;
    int i;
    int j = 0;//record result index

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize) && (j<resultSize); ++i) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;
            case '%':
                if (i+2<strSize) {
                    ch1 = hex2num(str[i+1]);//��4λ
                    ch2 = hex2num(str[i+2]);//��4λ
                    if ((ch1!=NON_NUM) && (ch2!=NON_NUM))
                        result[j++] = (char)((ch1<<4) | ch2);
                    i += 2;
                    break;
                } else {
                    break;
                }
            default:
                result[j++] = ch;
                break;
        }
    }
    
    result[j] = 0;
    return j;
}

/**
 * @brief URLEncode ���ַ���URL����
 *
 * @param str ԭ�ַ���
 * @param strSize ԭ�ַ�������(����������\0)
 * @param result ����������ĵ�ַ
 * @param resultSize ����������Ĵ�С(��������\0)
 *
 * @return: >0:resultstring ��ʵ����Ч�ĳ���
 *            0: ����ʧ��.
 */


int PF_URLEncode(const char* str, const int strSize, char* result, const int resultSize)
{
    int i;
    int j = 0;//for result index
    char ch;

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize)&&(j<resultSize); ++i) {
        ch = str[i];
        if (((ch>='A') && (ch<='Z')) ||
            ((ch>='a') && (ch<='z')) ||
            ((ch>='0') && (ch<='9'))) {
            result[j++] = ch;
        } else if (ch == ' ') {
            result[j++] = '%';
			result[j++] = '2';
			result[j++] = '0';
        } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
            //result[j++] = ch;
			if(ch == '.')
			{
				result[j++] = '%';
				result[j++] = '2';
				result[j++] = 'E';
			}
			if(ch == '-')
			{
				result[j++] = '%';
				result[j++] = '2';
				result[j++] = 'D';
			}
			if(ch == '_')
			{
				result[j++] = '%';
				result[j++] = '5';
				result[j++] = 'F';
			}
			if(ch == '*')
			{
				result[j++] = '%';
				result[j++] = '2';
				result[j++] = 'A';
			}
        } else {
            if (j+3 < resultSize) {
                sprintf(result+j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}

int PF_DateTimeURLEncode(const char* str, const int strSize, char* result, const int resultSize)
{
    int i;
    int j = 0;//for result index
    char ch;

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize)&&(j<resultSize); ++i) {
        ch = str[i];
        if (((ch>='A') && (ch<='Z')) ||
            ((ch>='a') && (ch<='z')) ||
            ((ch>='0') && (ch<='9'))) {
            result[j++] = ch;
        } else if (ch == ' ') {
            result[j++] = '%';
			result[j++] = '2';
			result[j++] = '0';
        } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
            //result[j++] = ch;
			if(ch == '.')
			{
				result[j++] = '.';
			}
			if(ch == '-')
			{
				result[j++] = '-';
			}
			if(ch == '_')
			{
				result[j++] = '%';
				result[j++] = '5';
				result[j++] = 'F';
			}
			if(ch == '*')
			{
				result[j++] = '%';
				result[j++] = '2';
				result[j++] = 'A';
			}
        } else {
            if (j+3 < resultSize) {
                sprintf(result+j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}

const char *PF_JITPerformanceSign2(const char *certInfo,  const char *srcStr)
{
	_bstr_t bstrCertInfo(_T(certInfo)); 
	_bstr_t bstrSrcSign(_T(srcStr)); 
	_bstr_t bstrResult;
	char result[2048];
	TCHAR szFinal[2048]={0};

	memset(result,0x00,2048);

	CoInitialize(NULL);
	JITComVCTK_BOCLib::IJITVCTK_BOCPtr pJITDetachPtr;
	HRESULT hRes = pJITDetachPtr.CreateInstance(__uuidof(JITComVCTK_BOCLib::JITVCTK_BOC));
	if(hRes == S_OK)
	{
		bstrResult = pJITDetachPtr ->AttachSignStr(bstrCertInfo,bstrSrcSign);
        _stprintf(szFinal, _T("%s"), (LPCTSTR)bstrResult);
		int iLen = _tcslen(szFinal); 
        char* chRtn = new char[iLen+1] ;
        _tcscpy(chRtn,szFinal);
		sprintf(result,"%s",chRtn);
	}
	CoUninitialize();

	return result;
}

const char *PF_JITPerformanceSign(const char *certInfo,  const char *srcStr)
{
	_bstr_t bstrCertInfo(_T(certInfo)); 
	_bstr_t bstrSrcSign(_T(srcStr)); 
	_bstr_t bstrResult;
	char result[2048];
	TCHAR szFinal[2048]={0};

	memset(result,0x00,2048);

	CoInitialize(NULL);
	JITComVCTK_BOCLib::IJITVCTK_BOCPtr pJITDetachPtr;
	HRESULT hRes = pJITDetachPtr.CreateInstance(__uuidof(JITComVCTK_BOCLib::JITVCTK_BOC));
	if(hRes == S_OK)
	{
		bstrResult = pJITDetachPtr ->DetachSignStr(bstrCertInfo,bstrSrcSign);
        _stprintf(szFinal, _T("%s"), (LPCTSTR)bstrResult);
		int iLen = _tcslen(szFinal); 
        char* chRtn = new char[iLen+1] ;
        _tcscpy(chRtn,szFinal);
		sprintf(result,"%s",chRtn);
	}
	CoUninitialize();

	return result;
}