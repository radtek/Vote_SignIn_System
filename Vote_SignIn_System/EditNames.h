#pragma once




/*

	功能		：	用于添加、删除被投票人的名字
	作者		：	zxc
	完成时间	：	2019-09-20



*/


#include <vector>
#include "stdafx.h"
// EditNames 对话框


class EditNames : public CDialogEx
{
	DECLARE_DYNAMIC(EditNames)

public:
	EditNames(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~EditNames();
	std::vector<CString> GetListValue();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_NAMES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();



	afx_msg void OnButtonClickedContinueVotes();
	afx_msg void OnButtonClikedReVotes();
	afx_msg void OnButtonClickedAdd();
	afx_msg void OnButtonClickedDel();
	afx_msg void OnClose();


	//afx_msg void OnSysCommand(UINT, LPARAM);


	DECLARE_MESSAGE_MAP()

	


private:
	
	//CListBox m_list_names;
	unsigned int count;

	std::vector<CString> m_vc_names;

protected:
	// 向导添加变量
	CListBox m_list_names;
	CEdit m_edit_add_name;
	unsigned int _m_list_len;
};

extern CONF config;
extern std::vector<BOOL> vote_flag;

