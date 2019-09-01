#pragma once

#include <vector>
#include "DrawItem.h"
#include"new_beamDlg.h"


#include "structtype.h"
#include "PortOperate.h"
#include "mscomm.h"

// MainDialog 对话框




class MainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MainDialog)

public:
	MainDialog(CWnd* pParent = nullptr);   // 标准构造函数

	
	virtual ~MainDialog();
	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_BEAM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();

	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

	CMscomm mscomm;

	//签到函数

	afx_msg LRESULT SignIn(WPARAM wParam, LPARAM lParam);

	//投票函数

	afx_msg LRESULT Vote(WPARAM wParam, LPARAM lParam);

	//端口通信


	//打开、关闭端口

	afx_msg LRESULT OperatePort(WPARAM wParam, LPARAM lParam);


	//投票导出

	afx_msg LRESULT ExportVotesToExcel(WPARAM wParam, LPARAM lParam);

	//签到导出

	afx_msg LRESULT ExportSignInToExcel(WPARAM wParam, LPARAM lParam);


	void Init();
	
	

protected:
	std::vector<DrawItem*> vDI;

	BOOL sign_in_flag;
	BOOL vote_flag;

	unsigned char func_idx;
	

private:
	
	void ShowConfigDialog();


	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()

	void OnCommMscomm();
};


extern std::vector<CString> baud_rate;
extern std::vector<CString> beam_color;


