

#include "pch.h"
#include "PortOperate.h"

#include "resource.h"






PortOperator::PortOperator(CMscomm& com, CWnd* pParentWnd): mscomm(com) {
	CRect rect(0, 0, 0, 0);
	mscomm.Create(NULL, WS_VISIBLE, rect, pParentWnd, IDC_MSCOMM);


}


/*
	������		��	OpenPort
	����			��	None
	����			��	������Ӧ�Ķ˿�
	����			��	zxc
	ʱ��			��	2019-9-20 

*/


void PortOperator::OpenPort() {

	if (GetPortStatus()) {
		ClosePort();
	}
	mscomm.put_PortOpen(true);
}





/*
	������		��	SelPort
	����			��	unsigned int	com		�˿ں�
	����			��	ѡ��˿�
	����			��	zxc
	ʱ��			��	2019-9-20

*/
void PortOperator::SelPort(unsigned int com) {
	if (com == 0) {
		MessageBox(NULL, L"�˿�Ϊ0, ���ö˿�ʧ��", L"tips:", MB_OK);
		return;
	}
	mscomm.put_CommPort(com);
}



/*
	������		��	InitPort
	����			��	
		CString baud_rate,		������
		CString setting,		����
		PortInputMode mode,		ģʽ
		unsigned int InputLen,	���볤��
		int RThreshold,			������
		BOOL RTSEnable			����
	����			��	��ʼ���˿�����
	����			��	zxc
	ʱ��			��	2019-9-20

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
	������		��	SendData
	����			��	CString send_data	��Ҫ���͵�����
	����			��	��������
	����			��	zxc
	ʱ��			��	2019-9-20

*/
void PortOperator::SendData(CString send_data) {
	mscomm.put_Output(COleVariant(send_data));
}





/*
	������		��	RecvData
	����			��	
		char* recv_data,		�������ݵ�buf 
		unsigned int buf_len	����
	����			��	��������
	����			��	zxc
	ʱ��			��	2019-9-20

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
	������		��	ClosePort
	����			��	None
	����			��	�ر���Ӧ�Ķ˿�
	����			��	zxc
	ʱ��			��	2019-9-20

*/
void PortOperator::ClosePort() {
	mscomm.put_PortOpen(false);
}





/*
	������		��	GetPortStatus
	����			��	None
	����			��	��ȡ�˿�״̬
	����			��	zxc
	ʱ��			��	2019-9-20

*/
BOOL PortOperator::GetPortStatus() {
	return mscomm.get_PortOpen();
}
