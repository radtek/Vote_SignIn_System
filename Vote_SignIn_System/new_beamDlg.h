

// new_beamDlg.h: 头文件
//

#pragma once
#include <vector>

#include "structtype.h"
#include "EditNames.h"
#include "PortOperate.h"



// CnewbeamDlg 对话框
class CnewbeamDlg : public CDialogEx
{
// 构造
public:
	CnewbeamDlg(CWnd* pParent = nullptr);	// 标准构造函数


	void Show();
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONF_DIALOG};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



//public:
protected:

	CComboBox m_combox_select_com;
	CComboBox m_combox_baud_rate;
	CComboBox m_combox_beam_color;

	CEdit m_edit_beam_nums;
	CEdit m_edit_beam_width;
	CEdit m_edit_recv_data;
	CEdit m_edit_send_data;
	CEdit m_edit_terminal_nums;
	CEdit m_edit_signin_total_nums;

	CButton m_btn_com_open;
	CButton m_btn_edit_name;
	CButton m_btn_signin_cap;
	CButton m_btn_export_score;
	CButton m_btn_signin_export_data;
	


	CString m_old_port;
	CString m_old_baud_rate;

	

	int screen_width;
	int screen_height;


private:

	std::vector<int> votes;
	std::vector<CString> m_port;
	std::vector<CString> m_baud_rate;
	std::vector<CString> m_color;
	std::vector<COLORREF> m_colorref;


	EditNames* _m_edit_names;





// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBtnClickedButtonComOpen();
	afx_msg void OnBtnClickedButtonEditNames();
	afx_msg void OnBtnClickedButtonSignInCap();
	afx_msg void OnBtnClickedButtonExportScore();
	afx_msg void OnBtnClickedButtonSignInExportData();
	afx_msg void OnSysCommand(UINT, LPARAM);
	afx_msg void OnBtnClickedButtonApply();

	DECLARE_EVENTSINK_MAP()

	


private:
	int _GetValue(CEdit&);
};

extern PortOperator* opt_mscomm;

