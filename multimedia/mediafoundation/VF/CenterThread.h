#pragma once
#include "CenterWnd.h"


// CCenterThread

class CCenterThread : public CWinThread
{
	DECLARE_DYNCREATE(CCenterThread)

protected:
	CCenterThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCenterThread();
public:
	

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


