// EditNames.cpp: 实现文件
//

#include "pch.h"
#include "new_beam.h"
#include "EditNames.h"
#include "afxdialogex.h"
#include "structtype.h"




// EditNames 对话框

IMPLEMENT_DYNAMIC(EditNames, CDialogEx)

EditNames::EditNames(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT_NAMES, pParent)
{
}

EditNames::~EditNames()
{
}


BOOL EditNames::OnInitDialog() {
	_m_list_len = 0;
	return CDialogEx::OnInitDialog();
}


void EditNames::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_EDIT_ADD_NAME, m_edit_add_name);
	//DDX_Control(pDX, IDC_LIST_NAMES, m_list_names);
	DDX_Control(pDX, IDC_LIST_NAMES, m_list_names);



	if (!config.names.empty()) {
		for (int i = 0; i < config.names.size(); ++i)
			m_list_names.AddString(config.names[i]);
	}
	
}


BEGIN_MESSAGE_MAP(EditNames, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &EditNames::OnButtonClickedAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &EditNames::OnButtonClickedDel)
	ON_BN_CLICKED(IDC_BTN_REVOTE, &EditNames::OnButtonClikedReVotes)
	ON_BN_CLICKED(IDC_BTN_CONTINUE_VOTE, &EditNames::OnButtonClickedContinueVotes)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void EditNames::OnButtonClikedReVotes() {
	if (m_list_names.GetCount() < 0) return;
	m_list_names.ResetContent();
	config.names.clear();
	config.votes.clear();

}

void EditNames::OnButtonClickedContinueVotes() {
	MessageBox(L"本功能尚未完善，如需使用请不要删除参与投票的人员");
	if (m_list_names.GetCount() == config.names.size()) return;
	CString tmp;
	for (int i = config.names.size(); i < m_list_names.GetCount(); ++i) {
		m_list_names.GetWindowTextW(tmp);
		config.names.push_back(tmp);
		config.votes.push_back(0);
	}
}


void EditNames::OnClose() {
	CString tmp;
	for (int i = 0; i < m_list_names.GetCount(); ++i) {
		m_list_names.GetText(i, tmp);
		config.names.push_back(tmp);
		config.votes.push_back(0);
	}
	CDialogEx::OnClose();
}



void EditNames::OnButtonClickedAdd() {
	CString tmp;
	m_edit_add_name.GetWindowTextW(tmp);
	CDC* pdc = GetDC();
	CSize size = pdc->GetTextExtent(tmp);
	_m_list_len = _m_list_len > size.cx ? _m_list_len : size.cx;
	m_list_names.SetHorizontalExtent(_m_list_len);
		
	if (!tmp.IsEmpty())
		m_list_names.InsertString(m_list_names.GetCount(), tmp.GetBuffer());

}


void EditNames::OnButtonClickedDel(){

	if (m_list_names.GetCurSel() < 0) return;
	
	m_list_names.DeleteString(m_list_names.GetCurSel());
}


std::vector<CString> EditNames::GetListValue() {
	return m_vc_names;
}

// EditNames 消息处理程序
