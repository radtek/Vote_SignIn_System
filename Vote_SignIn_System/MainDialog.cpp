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

#define _PRIVATE_API

#define VOTE_IDX	1
#define SIGNIN_IDX	2



//签到 id
std::set<unsigned int> device_ids;
std::vector<BOOL> vote_flag;


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
	

	//device_ids的签到测试导出excel

}





void MainDialog::Init() {
	vDI.push_back(new DrawBkModular());
	vDI.push_back(new DrawVoteModular());
	vDI.push_back(new DrawSignInModular());	
	func_idx = 0;

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
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
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
	//dc->SelectObject(&config.new_font);
	bitmap.CreateCompatibleBitmap(dc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));


	pDc.CreateCompatibleDC(dc);
	
	pDc.SelectObject(&bitmap);

	pDc.SetBkMode(TRANSPARENT);
	vDI[func_idx]->DrawBackImg(pDc);
	pDc.TextOutW(GetSystemMetrics(SM_CXSCREEN) - 400, GetSystemMetrics(SM_CYSCREEN) - 100, L"hello world");
	unsigned int i = 2;	
	
	pDc.SelectObject(&(config.new_font));
	pDc.SetTextColor(config.font_color);
	
	vDI[func_idx]->DrawForeText(pDc);
	
	dc->BitBlt(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), &pDc, 0, 0, SRCCOPY);
	
	ReleaseDC(dc);
	
	CDialogEx::OnPaint();
	//
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

			//pf = (LRESULT(*)(MainDialog*,WPARAM,LPARAM))(&MainDialog::SignIn);
			MessageBox(L"在点击确认按钮后开始进入签到模式");
			//SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_SIGNIN, (LPARAM)(vDI[0]));
			break;
		case 203:
			sign_in_flag = false;
			MessageBox(L"在点击确认按钮后终止签到模式");
			//SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_END_SIGNIN, (LPARAM)nullptr);
			break;
		case 204:
			vote_flag = true;
			MessageBox(L"在点击确认按钮后开始进入投票模式");
			//pf = (LRESULT(*)(WPARAM, LPARAM))(&MainDialog::Vote);

			//SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_VOTE, (LPARAM)(vDI[0]));
			break;
		case 205:
			vote_flag = false;
			MessageBox(L"在点击确认按钮后终止投票模式");
			//SendMessageA(this->GetSafeHwnd(), WM_SYSCOMMAND, WM_END_VOTE, (LPARAM)nullptr);
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

	//device_ids.insert();
	if (device_ids.find((unsigned int)wParam) != device_ids.end()) return 0;
	device_ids.insert((unsigned int)wParam);

	Invalidate(false);

	UpdateWindow();

	return 0;
}

//投票函数



_PRIVATE_API float _translate_data(const unsigned char* data) {
	float ret = 0;
	int idx = 1;
	int flag = false;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			unsigned char tmp = (data[i] >> (4 * (1 - j))) & 0xf;
			switch (tmp)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				ret = ret * 10 + tmp * idx;
				if (flag) idx *= 0.1;
				break;
			case 0xd:
				idx *= 0.1;
				flag = true;
				break;
			case 0xf:
				return ret;
				break;

			}
		}
	}
	return ret;

}

LRESULT MainDialog::Vote(WPARAM wParam, LPARAM lParam) {
	if (!vote_flag) return 0;

	float ret = _translate_data((unsigned char*)wParam);
	
	
	Invalidate(false);
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
	MessageBox(L"export vote is successful");
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

	_excel.ExcelSetVal(0, 4, L"出勤率");
	_excel.ExcelSetVal(1, 4, rate);


	_excel.ExcelSave();
	_excel.ExcelClose();
	MessageBox(L"export sign in successful");
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
		//MessageBox(L"0xa1");
		break;
	case 0xa2:
		func_idx = VOTE_IDX;
		for (int i = 0; i < packge_len; ++i) {
			Vote((WPARAM)data[i], 0);
		}
		break;
	case 0xa3:
		func_idx = SIGNIN_IDX;
		for (int i = 0; i < packge_len - 2; ++i) {
			SignIn((WPARAM)data[i], 0);
		}
		//MessageBox(L"0xa3");
		break;

		

	}

	

	

}
