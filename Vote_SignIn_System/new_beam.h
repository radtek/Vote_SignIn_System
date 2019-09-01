
// new_beam.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


#include "structtype.h"
#include <set>


// CNewBeamApp:
// 有关此类的实现，请参阅 new_beam.cpp
//

class CNewBeamApp : public CWinApp
{
public:
	CNewBeamApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
};

extern CNewBeamApp theApp;
extern CONF config;
extern std::set<unsigned int> device_ids;
