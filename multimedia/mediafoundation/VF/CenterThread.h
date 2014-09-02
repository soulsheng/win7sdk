#pragma once
#include "CenterWnd.h"


// CCenterThread

class CCenterThread : public CWinThread
{
	DECLARE_DYNCREATE(CCenterThread)

protected:
	CCenterThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CCenterThread();
public:
	

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


