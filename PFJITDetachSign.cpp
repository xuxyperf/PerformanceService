#include "stdafx.h"
#include "PerformanceService.h"
using namespace JITComVCTKLib;

int  PF_DetachSign(_bstr_t  certInfo,  _bstr_t  srcStr)
{
	CoInitialize(NULL);
	JITComVCTKLib::IJITDSignPtr pJITDetachPtr;

	HRESULT hRes = pJITDetachPtr.CreateInstance(__uuidof(JITComVCTKLib::IJITDSign));
	if(hRes == S_OK)
	{
		pJITDetachPtr ->DetachSign(certInfo,srcStr);
	}

	CoUninitialize;

	return 0;
}