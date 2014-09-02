// CenterWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "VF.h"
#include "CenterWnd.h"
////////////////////////////////////////////////
#define WM_CENTERWNDCREATE  WM_USER+1
#define WM_CSHOWWINDOW WM_USER+2
#define WM_TIMEPROC WM_USER+3
#define WM_OPENCOMMAND WM_USER+6
#define WM_DURATION WM_USER+8
#define WM_CONTROLPLAY WM_USER+9
///////////////////////////////////////////////////////
VOID CALLBACK TimerProc(PVOID lpParameter,BOOLEAN TimerOrWaitFired);
HWND hcwnd;
//////////////////////////////////////////////////////////////
// CCenterWnd

IMPLEMENT_DYNAMIC(CCenterWnd, CWnd)

CCenterWnd::CCenterWnd()
{
	m_mainWnd=NULL;
	CPlayState=0;
	open=NULL;
	pause=NULL;
	play=NULL;
	 Duration=NULL;
	 TIMELINEW=0;
	 openRgn=NULL;
	 ppRgn=NULL;
	 IsPlayOrPause=0;
	 IsOpen=0;
	////////////////////////////////
	 hTimer = NULL;
     hTimerQueue = NULL;
	 A6[0]='0';A6[1]='1';A6[2]='2';A6[3]='3';A6[4]='4';A6[5]='5';A6[6]='6';A6[7]='7';A6[8]='8';A6[9]='9';
	 A5[0]='0';A5[1]='1';A5[2]='2';A5[3]='3';A5[4]='4';A5[5]='5';
     A4[0]='0';A4[1]='1';A4[2]='2';A4[3]='3';A4[4]='4';A4[5]='5';A4[6]='6';A4[7]='7';A4[8]='8';A4[9]='9';
     A3[0]='0';A3[1]='1';A3[2]='2';A3[3]='3';A3[4]='4';A3[5]='5';
     A2[0]='0';A2[1]='1';A2[2]='2';A2[3]='3';A2[4]='4';A2[5]='5';A2[6]='6';A2[7]='7';A2[8]='8';A2[9]='9';
	 A1[0]='0';A1[1]='1';A1[2]='2';
     sinal=':';
	 a1=a2=a3=a4=a5=a6=0;
	 T1=A1[a1];T2=A2[a2];T3=A3[a3];T4=A4[a4];T5=A5[a5];T6=A6[a6];
	 rect1=this->IniRect(10,15,20,30);
	 rect2=this->IniRect(25,15,35,30);
	 this->rectS1=this->IniRect(40,15,45,30);
	 this->rect3=this->IniRect(50,15,60,30);
	 this->rect4=this->IniRect(65,15,75,30);
	 this->rectS2=this->IniRect(80,15,85,30);
	 this->rect5=this->IniRect(90,15,100,30);
	 this->rect6=this->IniRect(105,15,115,30);
	
}

CCenterWnd::~CCenterWnd()
{
}


BEGIN_MESSAGE_MAP(CCenterWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CCenterWnd 消息处理程序




void CCenterWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	HDC hdc=dc.m_hDC;
	RECT rc={0};
	this->GetClientRect(&rc);
	CBrush br(RGB(0,0,0));
	dc.FillRect(&rc,&br);
	this->ShowTime(dc.m_hDC);
	  SetBkMode(hdc,TRANSPARENT);
	  COLORREF oldcolor=SetTextColor(hdc,RGB(255,255,255));
	   DrawText(hdc,&T6,1,&rect6,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&T5,1,&rect5,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&sinal,1,&rectS1,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&T4,1,&rect4,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&T3,1,&rect3,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&sinal,1,&rectS2,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&T2,1,&rect2,DT_CENTER|DT_VCENTER);
	   DrawText(hdc,&T1,1,&rect1,DT_CENTER|DT_VCENTER);
	   SetTextColor(hdc,oldcolor);
	   SetBkMode(hdc,OPAQUE);
	 /*  Graphics g(hdc);
	  Image iopen(L"C:\\Users\\Administrator\\Desktop\\VF\\打开文件.png");
	  Image ipp(L"C:\\Users\\Administrator\\Desktop\\VF\\暂停按钮.png");
	    RectF igopen(125,15,32,32);
		 RectF igpp(160,15,32,32);
	     g.DrawImage(&iopen ,igopen);
		 g.DrawImage(&ipp,igpp);*/
	   DrawIcon(hdc,125,15,open);
	   if(CPlayState==3)
	   {
	        DrawIcon(hdc,160,15,pause);
	   }
	   else
	   {
		    DrawIcon(hdc,160,15,play);
	   }
}


void CCenterWnd::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CWnd::PostNcDestroy();
}


void CCenterWnd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	DestroyWindow();
	if(hTimerQueue&&hTimer)
	{
	     DeleteTimerQueueTimer(hTimerQueue,hTimer,NULL);
		 hTimerQueue=NULL;
		 hTimer=NULL;
	}
	DeleteObject (open);
	DeleteObject(pause);
	DeleteObject(play);
	DeleteObject(ppRgn);
	DeleteObject(openRgn);
	CWnd::OnClose();
}


void CCenterWnd::OnDestroy()
{
	CWnd::OnDestroy();
	PostQuitMessage(0);
	// TODO: 在此处添加消息处理程序代码
}


BOOL CCenterWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	return CWnd::OnEraseBkgnd(pDC);
}


void CCenterWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CWnd::OnLButtonDblClk(nFlags, point);
}


int CCenterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	openRgn=CreateRectRgn(125,15,157,47);
	ppRgn=CreateRectRgn(160,15,192,47);
	// TODO:  在此添加您专用的创建代码
	 open=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_OPEN));
	 play=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PLAYICON));
	 pause=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PAUSE));
	 bb.dwFlags = DWM_BB_ENABLE;
    bb.fEnable = true;
    bb.hRgnBlur = NULL;
	HRESULT hr = DwmEnableBlurBehindWindow(this->m_hWnd, &bb);
    if (FAILED(hr))
    {
		this->MessageBox(L"blur failed");
    }
	m_mainWnd=this->m_hWnd;
	hcwnd=this->m_hWnd;
	::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd,WM_CENTERWNDCREATE,(WPARAM)m_mainWnd,0);
	return 0;
}


void CCenterWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	///CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}


LRESULT CCenterWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(message)
	{
	case WM_CSHOWWINDOW:
		{
			if(BOOL(lParam)==TRUE)
			{
			    RECT *rc=(RECT *)wParam;
				this->SetWindowPos(&wndTop,rc->left+((rc->right-rc->left)-480)/2,rc->bottom-10-50,480,50,SWP_NOZORDER|SWP_SHOWWINDOW       );
			}
			if(BOOL(lParam)==FALSE)
			{
				this->ShowWindow(SW_HIDE);
			}
		}
		break;
	case WM_TIMEPROC:
		{
			if(CPlayState==3)
			{
			    this->TimeStart();
			}
		}
		break;
	case WM_PLAYSTATE:
		{
			if((INT)wParam==3)
			{
				if(hTimerQueue==NULL&&hTimer==NULL)
				{
				hTimerQueue = CreateTimerQueue();
				CreateTimerQueueTimer( &hTimer, hTimerQueue, 
                            (WAITORTIMERCALLBACK)TimerProc, 0 , 0, 1000, WT_EXECUTEINPERSISTENTTHREAD);
				}
				CPlayState=3;
				this->Invalidate(0);
			}
			if((INT)wParam==4)
			{
				CPlayState=4;
				this->Invalidate(0);
			}
			if(INT(wParam)==5)
			{
				CPlayState=5;
				a1=a2=a3=a4=a5=a6=0;
				 T1=A1[a1];T2=A2[a2];T3=A3[a3];T4=A4[a4];T5=A5[a5];T6=A6[a6];
				if(hTimerQueue&&hTimer)
	            {
	                    DeleteTimerQueueTimer(hTimerQueue,hTimer,NULL);
		                hTimerQueue=NULL;
		                hTimer=NULL;
	              }
				this->Invalidate();
			}
		}
		break;
	case WM_DURATION:
		{
			UINT64 *pDuration=NULL;
			pDuration=(UINT64*)wParam;
			Duration=*pDuration/10000000;
			
		}
		break;
	}
	return CWnd::WindowProc(message, wParam, lParam);
}




BOOL CCenterWnd::ShowTime(HDC hdc)
{
	 

	Graphics g(hdc);
	Pen pen(Color(255, 0, 100, 150),1 );
	Rect rect(38, 2, 404, 10);
	g.DrawRectangle(&pen,rect);
	SolidBrush solidBrush(Color(255, 20, 150, 100));
	Rect fillrect(40, 4, TIMELINEW, 6);
	g.FillRectangle(&solidBrush,fillrect);
	return 1;
}


void CCenterWnd::TimeStart(void)
{
	if(Duration)
	{
	   TIMELINEW =(((a1*10+a2)*3600+(a3*10+a4)*60+a5*10+a6)*(400/Duration));
	 
		 //TIMELINEW=400;
	 
	}
	this->InvalidateRect(CRect(40,4,400,10),0);
	a6++;
	if(a6<=9&&a6>=0)
	{
		T6=A6[a6];
		InvalidateRect(&rect6,0);
	}
	else
	{
		a6=0;T6=A6[a6];InvalidateRect(&rect6,0);
		a5++;
		if(a5>=0&&a5<=5)
		{
			T5=A5[a5];
			InvalidateRect(&rect5,0);
		}
		else
		{
			a5=0;T5=A5[a5];InvalidateRect(&rect5,0);
			a4++;
			if(a4>=0&&a4<=9)
			{
				T4=A4[a4];
			     InvalidateRect(&rect4,0);
			}
			else
			{
				a4=0;T4=A4[a4];InvalidateRect(&rect4,0);
				a3++;
				if(a3>=0&&a3<=5)
				{
					T3=A3[a3];
			         InvalidateRect(&rect3,0);
				}
				else
				{
					a3=0;T3=A3[a3];InvalidateRect(&rect3,0);
					a2++;
					if(a2>=0&&a2<=9)
					{
						T2=A2[a2];
			             InvalidateRect(&rect2,0);
					}
					else
					{
						a2=0;T2=A2[a2];InvalidateRect(&rect2,0);
						a1++;
						if(a1>=0&&a1<=2)
						{
							T1=A1[a1];
			                 InvalidateRect(&rect1,0);
						}
						else
						{
							a1=0;T1=A1[a1];InvalidateRect(&rect1,0);
						}
					}
				}
			}
		}
	}
}


RECT CCenterWnd::IniRect(int x, int y, int z, int w)
{
	RECT rect;
	rect.left=x;
	rect.top=y;
	rect.right=z;
	rect.bottom=w;
	return rect;
}
VOID CALLBACK TimerProc(PVOID lpParameter,BOOLEAN TimerOrWaitFired)
{
	::SendMessage(hcwnd,WM_TIMEPROC,0,0);
}

void CCenterWnd::OpenCommand(void)
{
	::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd,WM_OPENCOMMAND,0,0);
	a1=a2=a3=a4=a5=a6=0;
	 T1=A1[a1];T2=A2[a2];T3=A3[a3];T4=A4[a4];T5=A5[a5];T6=A6[a6];
	if(hTimerQueue&&hTimer)
	 {
	          DeleteTimerQueueTimer(hTimerQueue,hTimer,NULL);
		      hTimerQueue=NULL;
		      hTimer=NULL;
	   }
	this->ShowWindow(SW_HIDE);
	this->Invalidate();
}


void CCenterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	IsOpen=PtInRegion(openRgn,point.x,point.y);
	IsPlayOrPause=PtInRegion(ppRgn,point.x,point.y);
	CWnd::OnMouseMove(nFlags, point);
}


void CCenterWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(IsOpen==1)
	{
		this->OpenCommand();
	}
	if(IsPlayOrPause==1)
	{
		this->ControlPlay();
	}
	CWnd::OnLButtonUp(nFlags, point);
}


BOOL CCenterWnd::ControlPlay(void)
{
	::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd,WM_CONTROLPLAY,0,0);
	return 0;
}
