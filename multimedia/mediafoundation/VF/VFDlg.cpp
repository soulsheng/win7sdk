
// VFDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VF.h"
#include "VFDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVFDlg �Ի���

#define URL_WEB_CAMERA		(L"rtsp://192.168.1.11:554/user=admin&password=admin&channel=1&stream=0.sdp?")



CVFDlg::CVFDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	vfp=NULL;
	cw=NULL;
	crgn=NULL;
	ct=NULL;
	hCenterWnd=NULL;
	ScreenW=0;ScreenH=0;
	ZeroMemory(szFile,260);
	 IsScreen=0;
	 BOOL IsNoFrame=0;
	 hbr=NULL;
}

void CVFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVFDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCCALCSIZE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(12,CenterWndLD)
	ON_WM_MOVING()
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CVFDlg ��Ϣ�������

BOOL CVFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	hbr=::CreateSolidBrush(RGB(0,0,0));
	HWND hSwnd=::GetDesktopWindow();
     HDC m_hdc=::GetDC(0);
	 ScreenW=::GetDeviceCaps( m_hdc,HORZRES);
     ScreenH=::GetDeviceCaps( m_hdc,VERTRES);
	this->SetWindowPos(&wndTop,(ScreenW-500)/2,(ScreenH-400)/2,500,300,SWP_SHOWWINDOW);
	
	this->RegCenterWnd();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	this->GetWindowRect(&m_mainRect);
   
	//cw->SetWindowPos(&wndTopMost,0,0,100,100,SWP_SHOWWINDOW);
	
	/////////////////////////////////////////////////CenterThread
	CRuntimeClass* prt = RUNTIME_CLASS(CCenterThread);
	ct=(CCenterThread *)AfxBeginThread(prt);
	RECT rc={0};
	this->GetClientRect(&rc);
	crgn= CreateRectRgn((rc.right-rc.left-480)/2,rc.bottom-50,(rc.right-rc.left-480)/2+480,rc.bottom-10);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	::ReleaseDC(hSwnd, m_hdc);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVFDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (IsIconic())
	{
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if(vfp&&vfp->HasVideo())
		{
			vfp->Repaint();
		}
		else
		{
			RECT rc;
			GetClientRect(&rc);
           // FillRect(dc.m_hDC,&rc, (HBRUSH) COLOR_WINDOW);

		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CVFDlg::GetFilePath(void)
{
	   OPENFILENAME ofn;       // common dialog box structure
      
         // Initialize OPENFILENAME
          ZeroMemory(&ofn, sizeof(ofn));
          ofn.lStructSize = sizeof(ofn);
		  ofn.hwndOwner =this->m_hWnd;
          ofn.lpstrFile = szFile;
          ofn.lpstrFile[0] = '\0';
          ofn.nMaxFile = sizeof(szFile);
          ofn.lpstrFilter =L"MP4\0*.mp4\0WMV\0*.WMV\0AVI\0*.AVI\0";
          ofn.nFilterIndex = 1;
          ofn.lpstrFileTitle = NULL;
          ofn.nMaxFileTitle = 0;
          ofn.lpstrInitialDir = NULL;
          ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // Display the Open dialog box. 

            if (GetOpenFileName(&ofn)==TRUE)
             {
				 vfp->OpenURL(this->szFile);
				
			 }
			//CoTaskMemFree(this->szFile);

	      return 0;
}


void CVFDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 GdiplusShutdown(gdiplusToken);
	 if (vfp)
    {
       vfp->Shutdown();
        SafeRelease(&vfp);
    }
	 if(hCenterWnd==NULL)
	 {
		 hCenterWnd=(ct->m_pMainWnd)->m_hWnd;
		 ::SendMessage(hCenterWnd,WM_CLOSE,0,0);
	 }
	 else
	 {
		  ::SendMessage(hCenterWnd,WM_CLOSE,0,0);
	 }
	 Sleep(1000);
	 if(crgn)
	{
		DeleteObject(crgn);
	}
	 if(hbr)
	 {
		  DeleteObject (hbr);
	 }
	 CDialogEx::OnClose();
	 
}


LRESULT CVFDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(message)
	{
	case WM_SETVIDEOSIZE:
		{  
		//	HRESULT hr = vfp->HandleEvent(wParam);
			SIZE *pszMin;SIZE *pszMax;
			pszMin=(SIZE*)wParam;pszMax=(SIZE*)lParam;
			this->SetWindowPos(&wndTop,0,0,pszMin->cx,pszMax->cy,0);
			if(pszMin)
			{
				delete pszMin;pszMin=NULL;
			}
			if(pszMax)
			{
				delete pszMax;pszMax=NULL;
			}

         }
		break;
	case WM_CENTERWNDCREATE:
		{
			hCenterWnd=(HWND)wParam;
			cw=(CCenterWnd*)(ct->m_pMainWnd);
			////////////////////////////////////////////////��ʼ������ģ��
			HRESULT hr=CPlayer::CreateInstance(this->m_hWnd,hCenterWnd,&vfp);
	        if(hr!=S_OK)
	        {
		              this->MessageBox(L"����ģ���ʼ��ʧ�ܣ����򼴽��ر�",L"vfp");
		              PostMessage(WM_CLOSE,0,0);
            }

			vfp->OpenURL( URL_WEB_CAMERA );
		}
		break;
	case WM_OPENCOMMAND:
		{
			this->GetFilePath();
		}
		break;
	case WM_CONTROLPLAY:
		{
			INT state=vfp->GetState();
			switch(state)
			{
			case 3:
				{
					vfp->Pause();
				}
				break;
			case 4:
				{
					vfp->Play();
				}
				break;
			}
		}
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CVFDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(vfp&&vfp->HasVideo())
	{
	    vfp->ResizeVideo(cx,cy);
		
	}
if(cw)
	{
	   RECT rc={0};
 	   this->GetWindowRect(&rc);
	   cw->SetWindowPos(&wndNoTopMost,rc.left+((rc.right-rc.left)-480)/2,(rc.bottom-50-10),480,50,SWP_NOOWNERZORDER   );
	}
	if(crgn)
	{
		DeleteObject(crgn);
		crgn=NULL;
		RECT rc={0};
		this->GetClientRect(&rc);
		crgn=CreateRectRgn(((rc.right-rc.left)-480)/2+10,(rc.bottom-50),((rc.right-rc.left)-480)/2+480-10,rc.bottom-10);
	}
}


BOOL CVFDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CVFDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( IsScreen==0)
	{
		this->GetWindowRect(&m_mainRect);
		IsNoFrame=1;
		this->SetWindowPos(&wndTop,0,0,ScreenW,ScreenH,0);
		IsScreen=1;
	}
	else
	{
		IsNoFrame=0;
		this->SetWindowPos(&wndTop,m_mainRect.left,m_mainRect.top,m_mainRect.right-m_mainRect.left,m_mainRect.bottom-m_mainRect.top,0);
		IsScreen=0;
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CVFDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(IsNoFrame!=1)
           CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
	
}


BOOL CVFDlg::RegCenterWnd(void)
{
	WNDCLASS wc; 
 
    // Register the main window class. 
    wc.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS; 
    wc.lpfnWndProc = AfxWndProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance =AfxGetInstanceHandle(); 
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
    wc.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName = 0; 
    wc.lpszClassName = L"CenterWnd"; 
 
    if (!RegisterClass(&wc)) 
       return 0; 

	return 1;
}


void CVFDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int playstate=vfp->GetState();
	switch(playstate)
	{
	case Started:
	{
		vfp->Pause();
		Invalidate(0);
	}
	break;
	case Paused:
	{
		vfp->Play();
		Invalidate(0);
	}
	break;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CVFDlg::CenterWndLD(void)
{
	this->GetFilePath();
}


void CVFDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	if(cw)
	{
	   RECT rc={0};
 	   this->GetWindowRect(&rc);
	   //cw->SetWindowPos(&wndNoTopMost,rc.left+((rc.right-rc.left)-480)/2,(rc.bottom-50-10),480,50,SWP_NOOWNERZORDER   );
	  
		cw->MoveWindow(rc.left+((rc.right-rc.left)-480)/2,(rc.bottom-50-10),480,50,1);
	}
	// TODO: �ڴ˴������Ϣ����������
}


void CVFDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	   CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
}


void CVFDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
 lpMMI->ptMinTrackSize.x = 500; // ���ô�����С���
 lpMMI->ptMinTrackSize.y = 300; // ���ô�����С�߶�
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CVFDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BOOL bresult=PtInRegion(crgn,point.x,point.y);
	if(bresult)
	{
		RECT *rc=new RECT;
		GetWindowRect(rc);
		::SendMessage(hCenterWnd,WM_CSHOWWINDOW,(WPARAM)rc,(LPARAM)TRUE);
		if(rc)
		{
			delete rc;
			rc=NULL;
		}
	}
	else
	{
		::SendMessage(hCenterWnd,WM_CSHOWWINDOW,0,(LPARAM)FALSE);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}



HBRUSH CVFDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH htbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
