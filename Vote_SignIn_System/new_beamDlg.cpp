// new_beamDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "new_beam.h"
#include "new_beamDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SelfDefine.h"
#include "EditDlg.h"
#include "EditNames.h"
#include "structtype.h"

#include <set>
#include <vector>






CONF config;
std::vector<COLORREF> m_colorref;

std::vector<CString> baud_rate = { _T("300"), _T("600"), _T("1200"), _T("2400"), _T("4800"), _T("9600"),
	_T("19200"), _T("38400"), _T("43000"), _T("56000"), _T("57600"), _T("115200") };

std::vector<CString> beam_color = { _T("红色"), _T("绿色"), _T("蓝色") };


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnewbeamDlg 对话框



CnewbeamDlg::CnewbeamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}





void CnewbeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT_COM, m_combox_select_com);
	DDX_Control(pDX, IDCOM_BAUD_RATE, m_combox_baud_rate);
	DDX_Control(pDX, IDC_BEAM_SELECT_COLOR, m_combox_beam_color);

	DDX_Control(pDX, IDC_EDIT_BEAM_NUMS, m_edit_beam_nums);
	DDX_Control(pDX, IDC_EDIT_BEAM_WIDTH, m_edit_beam_width);
	DDX_Control(pDX, IDC_EDIT_TERMINAL_NUMS, m_edit_terminal_nums);
	DDX_Control(pDX, IDC_EDIT_TOTAL_NUMS, m_edit_signin_total_nums);
	DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_edit_send_data);
	DDX_Control(pDX, IDC_EDIT_RECV_DATA, m_edit_recv_data);

}

BEGIN_MESSAGE_MAP(CnewbeamDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTN_FONT_STYLE, &CnewbeamDlg::OnBtnClickedButtonSetFontStyle)
	ON_BN_CLICKED(IDC_SIGNIN_EXPORT_DATA, &CnewbeamDlg::OnBtnClickedButtonSignInExportData)
	ON_BN_CLICKED(IDC_EXPORT_SCORE, &CnewbeamDlg::OnBtnClickedButtonExportScore)
	ON_BN_CLICKED(IDC_IDC_SIGNIN_CAP, &CnewbeamDlg::OnBtnClickedButtonSignInCap)
	ON_BN_CLICKED(IDC_BTN_EDIT_NAME, &CnewbeamDlg::OnBtnClickedButtonEditNames)
	ON_BN_CLICKED(IDC_BTN_COM_OPEN, &CnewbeamDlg::OnBtnClickedButtonComOpen)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CnewbeamDlg::OnBtnClickedButtonApply)
END_MESSAGE_MAP()


// CnewbeamDlg 消息处理程序

BOOL CnewbeamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
	screen_height = GetSystemMetrics(SM_CYFULLSCREEN);


	//com port
	m_port.push_back(TEXT("COM1"));
	m_port.push_back(TEXT("COM2"));
	for (int i = 0; i < m_port.size(); ++i) {
		m_combox_select_com.AddString(m_port[i]);
	}
	m_combox_select_com.SetCurSel(0);

	// baud rate

	m_baud_rate = baud_rate;

	for (int i = 0; i < baud_rate.size(); ++i) {
		m_combox_baud_rate.AddString(baud_rate[i]);
	}
	
	m_combox_baud_rate.SetCurSel(0);


	//color
	
	m_colorref.push_back(RGB(255, 0, 0));
	m_colorref.push_back(RGB(0, 255, 0));
	m_colorref.push_back(RGB(0, 0, 255));

	m_color = beam_color;
	for (int i = 0; i < beam_color.size(); ++i) {
		m_combox_beam_color.AddString(beam_color[i]);
	}
	m_combox_beam_color.SetCurSel(0);



	m_combox_select_com.SetCurSel(config.com_index);
	m_combox_baud_rate.SetCurSel(config.baud_rate_index);
	m_combox_beam_color.SetCurSel(config.color_index);

	m_edit_beam_nums.SetWindowTextW(CString(_variant_t(config.beam_total_nums)));
	m_edit_beam_width.SetWindowTextW(CString(_variant_t(config.beam_width)));
	m_edit_terminal_nums.SetWindowTextW(CString(_variant_t(config.terminal_ids)));
	m_edit_signin_total_nums.SetWindowTextW(CString(_variant_t(config.sign_in_nums)));
	/*
	if (opt_mscomm == nullptr || !opt_mscomm->GetPortStatus())
		m_btn_com_open.SetWindowTextW(L"打开串口");
	else
		m_btn_com_open.SetWindowTextW(L"关闭串口");

		*/
	//baud rate


	_m_edit_names = new EditNames();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CnewbeamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CnewbeamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/*
	函数名		：	OnBtnClickedButtonSetFontStyle
	参数			：	None
	描述			：	用于设置前景显示字体的相关属性
	作者			：	zxc
	时间			：	2019-9-20

*/

void CnewbeamDlg::OnBtnClickedButtonSetFontStyle() {
	
	CFontDialog fontDlg;
	



	if (fontDlg.DoModal()) {
		if (config.new_font.m_hObject) {
			config.new_font.DeleteObject();
		}
		config.new_font.CreateFontIndirectW(fontDlg.m_cf.lpLogFont);
		//config.new_font = fontDlg.GetFont();
		config.font_color = fontDlg.GetColor();

	}	
}




/*
	函数名		：	OnBtnClickedButtonComOpen
	参数			：	None
	描述			：	用于打开或者关闭端口
	作者			：	zxc
	时间			：	2019-9-20

*/
void CnewbeamDlg::OnBtnClickedButtonComOpen() {
	SendMessageA(this->GetParent()->GetSafeHwnd(), WM_OPEN_COM, 0, 0);
	if (opt_mscomm == nullptr || !opt_mscomm->GetPortStatus())
		GetDlgItem(IDC_BTN_COM_OPEN)->SetWindowTextW(L"打开端口");
		
	else GetDlgItem(IDC_BTN_COM_OPEN)->SetWindowTextW(L"关闭端口");
	
}




/*
	函数名		：	OnBtnClickedButtonEditNames
	参数			：	None
	描述			：	用于显示添加参赛人员的对话框
	作者			：	zxc
	时间			：	2019-9-20

*/

void CnewbeamDlg::OnBtnClickedButtonEditNames() {

	EditNames dlg;
	dlg.DoModal();
	
}



/*
	函数名		：	OnBtnClickedButtonExportScore
	参数			：	None
	描述			：	将打分导出消息传送至该处理函数
	作者			：	zxc
	时间			：	2019-9-20

*/
void CnewbeamDlg::OnBtnClickedButtonExportScore() {
	

	
	//this->GetParent()->SendMessage(WM_EXPORT_SCORE, 0, 0);
	SendMessageA(this->GetParent()->GetSafeHwnd(), WM_EXPORT_SCORE, 0, 0);
}




/*
	函数名		：	OnBtnClickedButtonSignInCap
	参数			：	None
	描述			：	签到标题的对话框显示
	作者			：	zxc
	时间			：	2019-9-20

*/
void CnewbeamDlg::OnBtnClickedButtonSignInCap() {
	EditDlg dlg;
	dlg.DoModal();
}




/*
	函数名		：	OnBtnClickedButtonSignInExportData
	参数			：	None
	描述			：	签到数据导出发送给响应的函数进行处理
	作者			：	zxc
	时间			：	2019-9-20

*/
void CnewbeamDlg::OnBtnClickedButtonSignInExportData() {
	
	SendMessageA(this->GetParent()->GetSafeHwnd(), WM_EXPORT_SIGNIN_DATA, 0, 0);
}




/*
	函数名		：	OnSysCommand
	参数			：	None
	描述			：	系统消息
	作者			：	zxc
	时间			：	2019-9-20

*/
void CnewbeamDlg::OnSysCommand(UINT nID, LPARAM lParam) {

	if (nID == WM_RECV) {
		m_edit_recv_data.SetWindowTextW((LPCTSTR)lParam);
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


BEGIN_EVENTSINK_MAP(CnewbeamDlg, CDialogEx)
//ON_EVENT(CnewbeamDlg, IDC_MSCOMM, 1, CnewbeamDlg::OnCommMscomm, VTS_NONE)
	//ON_EVENT(CnewbeamDlg, IDC_MSCOMM, 1, CnewbeamDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()






/*
	函数名		：	_GetValue
	参数			：	CEdit&	edit
	描述			：	
	作者			：	zxc
	时间			：	2019-9-20

*/
int CnewbeamDlg::_GetValue(CEdit& edit) {
	CString tmp;
	CStringA transform;
	edit.GetWindowTextW(tmp);
	transform = tmp;
	int ret;
	sscanf_s(transform.GetBuffer(), "%d", &ret);
	return ret;
}





/*
	函数名		：	OnBtnClickedButtonApply
	参数			：	None
	描述			：	将所有设置进行应用
	作者			：	zxc
	时间			：	2019-9-20

*/
void CnewbeamDlg::OnBtnClickedButtonApply() {
	CString tmp;
	CStringA tranform;

	//光柱数量
	config.beam_total_nums = _GetValue(m_edit_beam_nums);
	
	//光柱颜色idx
	config.color_index = m_combox_beam_color.GetCurSel();


	//光柱宽度
	config.beam_width = _GetValue(m_edit_beam_width);

	//终端ID数量
	config.terminal_ids = _GetValue(m_edit_terminal_nums);


	for (int i = vote_flag.size(); i < config.terminal_ids; ++i) {
		vote_flag.push_back(false);
	}


	//签到总人数
	config.sign_in_nums = _GetValue(m_edit_signin_total_nums);

	//端口ID idx
	config.com_index = m_combox_select_com.GetCurSel();

	//波特率idx
	config.baud_rate_index = m_combox_baud_rate.GetCurSel();

	GetParent()->Invalidate(false);
	GetParent()->UpdateWindow();

}


