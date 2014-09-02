#pragma once

// CTimer ÃüÁîÄ¿±ê
#include  "Mfidl.h"
#include "Mfapi.h"
#pragma comment(lib,"Mfuuid.lib")
#pragma comment(lib,"Mfplat.lib")
class CTimer :  public IMFAsyncCallback
{
public:
	static HRESULT CreateInstance(HWND hEvent, CTimer **ppTimer);

	CTimer(HWND hEvent);
	virtual ~CTimer();
protected:
	long                    m_nRefCount;        // Reference count.
	HWND                    m_hwndEvent;        // App window to receive events.
	DWORD *pkey;
	MFPERIODICCALLBACK mfcallback;
public:
	 STDMETHODIMP QueryInterface(REFIID iid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IMFAsyncCallback methods
    STDMETHODIMP  GetParameters(DWORD*, DWORD*)
    {
        // Implementation of this method is optional.
        return E_NOTIMPL;
    }
    STDMETHODIMP  Invoke(IMFAsyncResult* pAsyncResult);

};


