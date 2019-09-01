
#pragma once
#include "mscomm.h"


typedef BOOL PortInputMode;

#define INPUTLEN 1024

class PortOperator {
public:
	PortOperator(CMscomm& com, CWnd* pParentWnd = nullptr);
	void OpenPort();
	void SelPort(unsigned int com);
	void InitPort(CString baud_rate, CString setting, PortInputMode mode = 1,
		unsigned int InputLen = INPUTLEN, int RThreshold = 1, BOOL RTSEnable = TRUE);
	void SendData(CString);
	void RecvData(char* recv_data, unsigned int buf_len);
	void ClosePort();
	BOOL GetPortStatus();

protected:
	CMscomm& mscomm;
};




