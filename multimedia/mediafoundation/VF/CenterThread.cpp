// CenterThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VF.h"
#include "CenterThread.h"
#include "CenterWnd.h"

// CCenterThread

IMPLEMENT_DYNCREATE(CCenterThread, CWinThread)

CCenterThread::CCenterThread()
{
}

CCenterThread::~CCenterThread()
{
}

BOOL CCenterThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	 CCenterWnd *cw=new CCenterWnd;
	RECT rc;
	rc.left=0;
	rc.top=0;
	rc.bottom=50;
	rc.right=480;
	
	cw->CreateEx(0,L"CenterWnd",L"CEN",WS_POPUP ,rc,AfxGetApp()->m_pMainWnd,0,0);
	this->m_pMainWnd=cw;
	return TRUE;
}

int CCenterThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCenterThread, CWinThread)
END_MESSAGE_MAP()


// CCenterThread ��Ϣ�������
