#pragma once

#include "Dwmapi.h"
#pragma comment(lib,"Dwmapi.lib")
#include <gdiplus.h>
using namespace Gdiplus;
// CCenterWnd
#define  WM_PLAYSTATE  WM_USER+4
class CCenterWnd : public CWnd
{
	DECLARE_DYNAMIC(CCenterWnd)

public:
	CCenterWnd();
	virtual ~CCenterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	/////////////////////////////////
	 DWM_BLURBEHIND bb;
	 HWND m_mainWnd;
	///////////////////////////////////
	HANDLE hTimer ;
    HANDLE hTimerQueue ;
	int a6,a5,a4,a3,a2,a1;
    WCHAR T6,T5,T4,T3,T2,T1;
	WCHAR A6[10];
    WCHAR A5[6];
    WCHAR A4[10];
    WCHAR A3[6];
     WCHAR A2[10];
    WCHAR A1[3];
    WCHAR sinal;
	RECT rect6,rect5,rect4,rect3,rect2,rect1,rectS1,rectS2;
	 ///////////////////////////////////
	INT CPlayState;
	DOUBLE Duration;
	DOUBLE TIMELINEW;
	///////////
	HRGN openRgn;
	HRGN ppRgn;
	HICON open;
	HICON play;
	HICON pause;
	BOOL IsPlayOrPause;
	BOOL IsOpen;
public:
	afx_msg void OnPaint();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL ShowTime(HDC hdc);
	void TimeStart(void);
	RECT IniRect(int x, int y, int z, int w);
	 void OpenCommand(void);
	 afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	 afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	 BOOL ControlPlay(void);
};


