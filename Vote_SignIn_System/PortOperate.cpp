

#include "pch.h"
#include "PortOperate.h"

#include "resource.h"






PortOperator::PortOperator(CMscomm& com, CWnd* pParentWnd): mscomm(com) {
	CRect rect(0, 0, 0, 0);
	mscomm.Create(NULL, WS_VISIBLE, rect, pParentWnd, IDC_MSCOMM);


}


/*
	函数名		：	OpenPort
	参数			：	None
	描述			：	代开相应的端口
	作者			：	zxc
	时间			：	2019-9-20 

*/


void PortOperator::OpenPort() {

	if (GetPortStatus()) {
		ClosePort();
	}
	mscomm.put_PortOpen(true);
}





/*
	函数名		：	SelPort
	参数			：	unsigned int	com		端口号
	描述			：	选择端口
	作者			：	zxc
	时间			：	2019-9-20

*/
void PortOperator::SelPort(unsigned int com) {
	if (com == 0) {
		MessageBox(NULL, L"端口为0, 设置端口失败", L"tips:", MB_OK);
		return;
	}
	mscomm.put_CommPort(com);
}



/*
	函数名		：	InitPort
	参数			：	
		CString baud_rate,		波特率
		CString setting,		设置
		PortInputMode mode,		模式
		unsigned int InputLen,	输入长度
		int RThreshold,			。。。
		BOOL RTSEnable			。。
	描述			：	初始化端口设置
	作者			：	zxc
	时间			：	2019-9-20

*/
void PortOperator::InitPort(CString baud_rate, CString setting, PortInputMode mode,
	unsigned int InputLen, int RThreshold, BOOL RTSEnable) {
	mscomm.put_InputMode(mode);
	mscomm.put_Settings(setting);
	mscomm.put_InputLen(InputLen);
	mscomm.put_RThreshold(RThreshold);
	mscomm.put_RTSEnable(RTSEnable);
}



/*
	函数名		：	SendData
	参数			：	CString send_data	将要发送的数据
	描述			：	发送数据
	作者			：	zxc
	时间			：	2019-9-20

*/
void PortOperator::SendData(CString send_data) {
	mscomm.put_Output(COleVariant(send_data));
}





/*
	函数名		：	RecvData
	参数			：	
		char* recv_data,		接收数据的buf 
		unsigned int buf_len	长度
	描述			：	接收数据
	作者			：	zxc
	时间			：	2019-9-20

*/
void PortOperator::RecvData(char* recv_data, unsigned int buf_len) {
	COleSafeArray fs = mscomm.get_Input();
	int port_buf_len = fs.GetOneDimSize();
	if (buf_len < port_buf_len)
		recv_data = (char*)calloc(port_buf_len, sizeof(char));
	for (long i = 0; i < fs.GetOneDimSize(); ++i) {
		fs.GetElement(&i, recv_data + i);
	}
}





/*
	函数名		：	ClosePort
	参数			：	None
	描述			：	关闭相应的端口
	作者			：	zxc
	时间			：	2019-9-20

*/
void PortOperator::ClosePort() {
	mscomm.put_PortOpen(false);
}





/*
	函数名		：	GetPortStatus
	参数			：	None
	描述			：	获取端口状态
	作者			：	zxc
	时间			：	2019-9-20

*/
BOOL PortOperator::GetPortStatus() {
	return mscomm.get_PortOpen();
}
