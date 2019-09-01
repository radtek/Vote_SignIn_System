#pragma once


// EditDlg 对话框

class EditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditDlg)

public:
	EditDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~EditDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EIDT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


protected:
	afx_msg void OnButtonClickedOk();
	afx_msg void OnButtonClickedCancle();


protected:
	CStatic m_static_edit;
	CEdit m_edit_item;
	CButton m_btn_ok;
	CButton m_btn_cancle;
	
	CString m_str_item;

};
