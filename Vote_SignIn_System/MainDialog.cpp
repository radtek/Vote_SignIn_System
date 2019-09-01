// MainDialog.cpp: 实现文件
//

#include "pch.h"
#include "new_beam.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "DrawItem.h"
#include <afxwin.h>
#include "SelfDefine.h"
#include <vector>
#include "structtype.h"
#include "ExcelOperator.h"
#include <functional>


#define VOTE_IDX	0
#define SIGNIN_IDX	1


std::set<unsigned int> device_ids;
PortOperator* opt_mscomm = nullptr;

unsigned int func_index = 0;

typedef LRESULT(*pf)(MainDialog* , WPARAM, LPARAM);
//CMscomm mscomm;



// MainDialog 对话框

IMPLEMENT_DYNAMIC(MainDialog, CDialogEx)

MainDialog::MainDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_BEAM_DIALOG, pParent)
{
	Init();

	sign_in_flag = false;
	vote_flag = false;
	
	for (int i = 0; i < 10; ++i)
		device_ids.insert(i);
}





void MainDialog::Init() {
	vDI.push_back(new DrawVoteModular());
	vDI.push_back(new DrawSignInModular());	

}




MainDialog::~MainDialog()
{
}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




BEGIN_MESSAGE_MAP(MainDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_HOTKEY()
	ON_MESSAGE(WM_OPEN_COM, MainDialog::OperatePort)
	ON_MESSAGE(WM_SIGNIN, &MainDialog::SignIn)
	ON_MESSAGE(WM_VOTE, &MainDialog::Vote)
	ON_MESSAGE(WM_EXPORT_SCORE, &MainDialog::ExportVotesToExcel)
	ON_MESSAGE(WM_EXPORT_SIGNIN_DATA, &MainDialog::ExportSignInToExcel)
	
END_MESSAGE_MAP()






// MainDialog 消息处理程序

BOOL MainDialog::OnInitDialog() {
	//SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	RegisterHotKey(GetSafeHwnd(), 200, MOD_CONTROL, VK_F11);
	RegisterHotKey(GetSafeHwnd(), 201, 0, VK_F2);
	RegisterHotKey(GetSafeHwnd(), 202, 0, VK_F3);
	RegisterHotKey(GetSafeHwnd(), 203, 0, VK_F4);
	RegisterHotKey(GetSafeHwnd(), 204, 0, VK_F5);
	RegisterHotKey(GetSafeHwnd(), 205, 0, VK_F6);


	opt_mscomm = new PortOperator(mscomm, this);

	//func_idx = 0;
	//func.push_back(&MainDialog::Vote);
	//func.push_back(&MainDialog::SignIn);

	return CDialogEx::OnInitDialog();
}



void MainDialog::ShowConfigDialog() {
	CnewbeamDlg beamDlg;
	//beamDlg.Create(IDD_CONF_DIALOG, this);
	beamDlg.DoModal();

}


void MainDialog::OnPaint() {
	
	CDC* dc = GetDC();
	CDC pDc;
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(dc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	pDc.CreateCompatibleDC(dc);
	pDc.SelectObject(&bitmap);
	pDc.SetBkMode(TRANSPARENT);
	unsigned int i = 2;	
	vDI[0]->DrawBackImg(pDc);
	
	pDc.TextOutW(GetSystemMetrics(SM_CXSCREEN)-400, GetSystemMetrics(SM_CYSCREEN)-100, L"hello world");
	dc->BitBlt(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), &pDc, 0, 0, SRCCOPY);
	
	ReleaseDC(dc);
	
	CWnd::OnPaint();
}


void MainDialog::OnHotKey(UINT nHotKeyID, UINT nKey1, UINT nKey2) {
	
	switch (nHotKeyID) {
		case 200:
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
			break;
		case 201:
			ShowConfigDialog();
			break;
		case 202:
			sign_in_flag = true;

			pf = (LRESULT(*)(MainDialog*,WPARAM,LPARAM))(&MainDialog::SignIn);
			
			SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_SIGNIN, (LPARAM)(vDI[0]));
			break;
		case 203:
			sign_in_flag = false;
			SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_END_SIGNIN, (LPARAM)nullptr);
			break;
		case 204:
			vote_flag = true;

			pf = (LRESULT(*)(WPARAM, LPARAM))(&MainDialog::Vote);

			SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_VOTE, (LPARAM)(vDI[0]));
			break;
		case 205:
			vote_flag = false;
			SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_END_VOTE, (LPARAM)nullptr);
			break;
	}
	CDialogEx::OnHotKey(nHotKeyID, nKey1, nKey2);

}




//打开、关闭端口

LRESULT MainDialog::OperatePort(WPARAM wParam, LPARAM lParam) {
	if (opt_mscomm->GetPortStatus()) {
		opt_mscomm->ClosePort();
		return 0;
	}
	CString setting;
	setting = baud_rate[config.baud_rate_index] + L",n,8,1";
	opt_mscomm->InitPort(CString(_variant_t(config.baud_rate_index + 1)), setting);
	opt_mscomm->OpenPort();
}


//签到函数

LRESULT MainDialog::SignIn(WPARAM wParam, LPARAM lParam) {

	if (!sign_in_flag) return 0;



	return 0;
}

//投票函数

LRESULT MainDialog::Vote(WPARAM wParam, LPARAM lParam) {
	if (!vote_flag) return 0;



	return 0;
}

//端口通信

//投票导出

LRESULT MainDialog::ExportVotesToExcel(WPARAM wParam, LPARAM lParam) {
	MessageBox(L"export vote to excel start!");
	ExcelOperator<CString> _excel;
	

	wchar_t path[BUFSIZ] = { 0 };
	GetCurrentDirectory(BUFSIZ, path);
	//transfor = "E:\\Desktop\\git\\New_Beam\\new_beam\\xlsx\\votes_score.xlsx"
	CString abs_file_name = path + CString("\\export_xlsx\\") + CString("votes_score.xlsx");
	CStringA transfor(abs_file_name);
	CFileFind file;
	BOOL flag = file.FindFile(abs_file_name);
	if (!flag) {

		_excel.ExcelNew(abs_file_name);
	}

	_excel.ExcelOpen(abs_file_name);
	
	
	for (int i = 0; i < config.names.size(); ++i) {
		_excel.ExcelSetVal(0, i+1, config.names[i]);
		_excel.ExcelSetVal(1, i+1, CString(_variant_t(config.votes[i])));
	}
	_excel.ExcelSave();
	_excel.ExcelClose();
	return 0;
}

//签到导出

LRESULT MainDialog::ExportSignInToExcel(WPARAM wParam, LPARAM lParam) {
	MessageBox(L"export sign in to excel start!");

	ExcelOperator<CString> _excel;


	wchar_t path[BUFSIZ] = { 0 };
	GetCurrentDirectory(BUFSIZ, path);
	//transfor = "E:\\Desktop\\git\\New_Beam\\new_beam\\xlsx\\votes_score.xlsx"
	CString abs_file_name = path + CString("\\export_xlsx\\") + CString("SignInResult.xlsx");
	CStringA transfor(abs_file_name);
	CFileFind file;
	BOOL flag = file.FindFile(abs_file_name);
	if (!flag) {

		_excel.ExcelNew(abs_file_name);
	}

	_excel.ExcelOpen(abs_file_name);


	//应到人数
	//实到人数
	//未到人数
	//到勤率

	CString rate;
	rate.Format(L"%f%%", device_ids.size()/(float)config.sign_in_nums*100);

	_excel.ExcelSetVal(0, 1, L"应到人数");
	_excel.ExcelSetVal(1, 1, CString(_variant_t(config.sign_in_nums)));

	_excel.ExcelSetVal(0, 2, L"实到人数");
	_excel.ExcelSetVal(1, 2, CString(_variant_t(device_ids.size())));

	_excel.ExcelSetVal(0, 3, L"未到人数");
	_excel.ExcelSetVal(1, 3, CString(_variant_t(config.sign_in_nums - device_ids.size())));

	_excel.ExcelSetVal(0, 4, L"到勤率");
	_excel.ExcelSetVal(1, 4, rate);


	_excel.ExcelSave();
	_excel.ExcelClose();
	return 0;
}

BEGIN_EVENTSINK_MAP(MainDialog, CDialogEx)
//	ON_EVENT(MainDialog, IDC_MSCOMM, 1, MainDialog::OnCommMscomm, VTS_NONE)
ON_EVENT(MainDialog, IDC_MSCOMM, 1, MainDialog::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()




void MainDialog::OnCommMscomm()
{
	// TODO: 在此处添加消息处理程序代码
	char buf[BUFSIZ] = { 0 };
	if (mscomm.get_CommEvent() == 2) {
		opt_mscomm->RecvData(buf, BUFSIZ);
	}

	unsigned char packge_len = buf[1];
	unsigned char command = buf[2];
	unsigned char data[BUFSIZ] = { 0 };
	for (int i = 0; i < packge_len; ++i) {
		data[i] = buf[i + 3];
	}


	switch (command)
	{

	case 0xa1:
		MessageBox(L"0xa1");
		break;
	case 0xa2:
		MessageBox(L"0xa2");
		break;
	case 0xa3:
		MessageBox(L"0xa2");
		break;

	}

	

	

}
