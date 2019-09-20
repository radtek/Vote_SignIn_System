// EditDlg.cpp: 实现文件
//

#include "pch.h"
#include "new_beam.h"
#include "EditDlg.h"
#include "afxdialogex.h"
#include "SelfDefine.h"
#include "structtype.h"


// EditDlg 对话框

IMPLEMENT_DYNAMIC(EditDlg, CDialogEx)

EditDlg::EditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EIDT_DIALOG, pParent)
{

}

EditDlg::~EditDlg()
{
}

void EditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_STATIC_EDIT, m_static_edit);
	DDX_Control(pDX, IDC_EDIT_ITEM, m_edit_item);
}


BEGIN_MESSAGE_MAP(EditDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &EditDlg::OnButtonClickedOk)
	ON_BN_CLICKED(IDC_BTN_CANCLE, &EditDlg::OnButtonClickedCancle)


END_MESSAGE_MAP()


/*
	函数名	：	OnButtonClickedOk
	参数		：	None
	描述		：	用于设置全局配置中签到标题
	作者		：	zxc
	时间		：	2019-9-20
*/

void EditDlg::OnButtonClickedOk() {
	GetDlgItemText(IDC_EDIT_ITEM, m_str_item);
	config.sign_in_caption = m_str_item;
	CDialogEx::OnOK();
}


void EditDlg::OnButtonClickedCancle() {
	CDialogEx::OnCancel();
}



// EditDlg 消息处理程序



