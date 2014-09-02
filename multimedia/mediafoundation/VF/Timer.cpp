// Timer.cpp : 实现文件
//

#include "stdafx.h"
#include "VF.h"
#include "Timer.h"


// CTimer
void TimeProc(IUnknown *pContext);

CTimer::CTimer(HWND hEvent)
{
	m_nRefCount=1;
	m_hwndEvent=hEvent;
}

CTimer::~CTimer()
{
}
HRESULT CTimer::QueryInterface(REFIID riid, void** ppv)
{
    static const QITAB qit[] = 
    {
        QITABENT(CTimer, IMFAsyncCallback),
        { 0 }
    };
    return QISearch(this, qit, riid, ppv);
}

ULONG CTimer::AddRef()
{
    return InterlockedIncrement(&m_nRefCount);
}

ULONG CTimer::Release()
{
    ULONG uCount = InterlockedDecrement(&m_nRefCount);
    if (uCount == 0)
    {
        delete this;
    }
    return uCount;

}
HRESULT CTimer::CreateInstance(HWND hEvent, CTimer **ppTimer)  
{
    if (ppTimer == NULL)
    {
        return E_POINTER;
    }

    CTimer *pTimer = new (std::nothrow) CTimer(hEvent);
    if (pTimer == NULL)
    {
        return E_OUTOFMEMORY;
    }
	HRESULT hr=S_OK;
        *ppTimer = pTimer;
    return hr;
}
HRESULT CTimer::Invoke(IMFAsyncResult *pResult)
{
	HRESULT hr=S_OK;
	pkey=NULL;
	mfcallback=TimeProc;
	hr=MFAddPeriodicCallback(mfcallback,NULL,pkey);
	if(FAILED(hr))
	{
		AfxMessageBox(L"TimeProc Filed");
	}
	     return hr;
}

void TimeProc(IUnknown *pContext)
{

}