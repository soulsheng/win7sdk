
// VFDlg.h : 头文件
//

#pragma once
#include "Player.h"
#include <gdiplus.h>
#include "CenterThread.h"
#include "CenterWnd.h"
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
///////////////////////////////////////////////////////////
#define WM_CENTERWNDCREATE  WM_USER+1
#define WM_CSHOWWINDOW WM_USER+2
#define WM_OPENCOMMAND WM_USER+6
#define WM_SETVIDEOSIZE WM_USER+7
#define WM_CONTROLPLAY WM_USER+9
///////////////////////////////////////////////////////////

// CVFDlg 对话框
class CVFDlg : public CDialogEx
{
// 构造
public:
	CVFDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public :
	///////////////////////////////////////////////////////////////////////
	CPlayer *vfp;
	///////////////////////////////////////////////////////////////////////////
	 TCHAR szFile[260];       // buffer for file name
	 /////////////////////////////
	 HWND hCenterWnd;
	 /////////////////////////////////////////////////
	 GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   //////////////////////////////////////////////////////
   CCenterWnd *cw;
   CCenterThread *ct;
   ///////////////////////////////////////////////
  RECT  m_mainRect;
  INT ScreenW,ScreenH;
  BOOL IsScreen;
  BOOL IsNoFrame;
  //////////////////////////
  HRGN crgn;
  HBRUSH hbr;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL GetFilePath(void);
	afx_msg void OnClose();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	BOOL RegCenterWnd(void);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void CenterWndLD(void);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
