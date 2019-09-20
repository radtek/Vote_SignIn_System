

#include"pch.h"
#include"DrawItem.h"



//virtual base DrawItem


#define BUFSIZ 512


extern CONF config;
DrawItem::DrawItem() {
	bk_path = "./res/bk.jpg";
	bk_img.Load(bk_path);

}




/*
	
	������	��	DrawBackImg
	����		��	���ڻ��Ʊ���ͼƬ
	����		��	CDC pdc		����˫�ػ����CDC��𻷾�
	����		��
	ʱ��		��


*/

void DrawItem::DrawBackImg(CDC& pdc) {
	
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	bk_img.Draw(pdc, 0, 0, screen_width, screen_height);

}



/*
	������	��	SetBrush
	����		��	CBrush* brush ����CBrush������ʾ��������ɫ
	����		��	���ڸ�����������ɫ�ĵĻ�ˢ�豸����
	����		��	zxc
	ʱ��		��	2019-9-20


*/


void DrawItem::SetBrush(CBrush* brush) {
	m_pbrush = brush;
}




/*
	������	��	SetPaintDC
	����		��	CDC	�������ô����PaintDC�豸����
	����		��	����˫�ػ����е�CDC�豸����	
	����		��	zxc
	ʱ��		��	2019-9-20


*/


void DrawItem::SetPaintDC(CDC* dc) {
	m_pdc = dc;
}


//DrawBkModular


/*
	������	��	Init
	����		��	
	����		��	��ʼ�����Ʊ�������ز���
	����		��	zxc
	ʱ��		��	2019-9-20


*/


void DrawBkModular::Init() {

}





/*
	������	��	DrawForeText
	����		��	CDC	�ڻ��Ʊ���������;
	����		��	������ֻΪʵ�ֽӿڻ����еĻ���ǰ���ַ������ã��ڻ��Ʊ��������κ�����
	����		��	zxc
	ʱ��		��	2019-9-20


*/
void DrawBkModular::DrawForeText(CDC& pdc) {

}


//DrawVoteModular



/*
	������	��	Init
	����		��
	����		��	��ʼ������ͶƱ����ز���
	����		��	zxc
	ʱ��		��	2019-9-20


*/


void DrawVoteModular::Init() {

}



/*
	-------------�ù��ܸ���δ����---------------
	
	������	��	DrawForeText
	����		��	����ʵ��ͶƱ�е�����Ӧ��Ļ
	����		��	CDC���ڴ���˫�ػ����е��豸����
	����		��	zxc
	ʱ��		��	2019-9-20 


*/


void DrawVoteModular::DrawForeText(CDC & pdc) {
	

	TEXTMETRIC tm;


	pdc.GetTextMetrics(&tm);

	int font_height = tm.tmHeight;
	int font_width = tm.tmWeight;
	
	
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	int beam_start_x, beam_start_y, names_start_x, names_start_y;

	int height_delta, width_delta;


	height_delta = screen_height / 10;
	width_delta = screen_width / config.names.size();


	beam_start_y = height_delta * 9;

	names_start_y = beam_start_y + font_height * 1.5;
	beam_start_x = width_delta / 2;


	CBrush brush;
	
	brush.CreateSolidBrush(m_colorref[config.color_index]);
	CBrush* old_brush = pdc.SelectObject(&brush);

	for (int i = 0; i < config.names.size(); ++i) {
		int string_start_x = beam_start_x * (i + 1) - pdc.GetTextExtent(config.names[i]).cx / 2;
		pdc.TextOutW(string_start_x, names_start_y, config.names[i]);

		int beam_start_x = beam_start_y * (i + 1) - config.beam_width / 2;
		CRect rect(beam_start_x, beam_start_y - config.votes[i] * height_delta, beam_start_x + config.beam_width, beam_start_y);
		pdc.FillRect(&rect, m_pbrush);
	}
	
	pdc.SelectObject(old_brush);
}


//DrawSignInModular




/*
	
	������	��	Init
	����		��	��ʼ��ǩ���е��豸����
	����		��	None
	����		��	zxc
	ʱ��		��	2019-9-20


*/


void DrawSignInModular::Init() {

}




/*
	
	������	��		DrawForeText
	����		��		���ڻ���ǩ����ǰ����ʾ����
	����		��		CDC	���ڴ���˫�ػ�����豸����
	����		��		zxc
	ʱ��		��		2019-9-20


*/


void DrawSignInModular::DrawForeText(CDC& pdc) {
	int size = config.sign_in_nums;
	
	//CFont* old_font = pdc.GetCurrentFont();
	//LOGFONT lf;
	
	TEXTMETRIC tm;
	//old_font->CreateFontIndirectW(&lf);
	
	pdc.GetTextMetrics(&tm);

	int font_height = tm.tmHeight;
	int font_width = tm.tmAveCharWidth;

	
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	
	int string_start_y = screen_height / 7;


	std::vector<CString> vcs;
	CString tmp;
	vcs.push_back(CString(config.sign_in_caption));

	tmp.Format(L"%s:%d", L"Ӧ������", config.sign_in_nums);
	vcs.push_back(tmp);

	tmp.Format(L"%s:%d", L"ʵ������", device_ids.size());
	vcs.push_back(tmp);

	tmp.Format(L"%s:%d", L"δ������", config.sign_in_nums - device_ids.size());
	vcs.push_back(tmp);

	tmp.Format(L"%s:%.2f%%", L"������", device_ids.size() / (float)config.sign_in_nums * 100);
	vcs.push_back(tmp);

	int max_len = 0;
	
	
	
	for (int i = 0; i < vcs.size(); ++i) {


		//int string_start_x = screen_width / 2 - max_len * font_width / 2;
		//pdc.TextOutW(string_start_x, string_start_y * (i + 1), vcs[i]);
		int string_start_x = screen_width / 2 - pdc.GetTextExtent(vcs[i]).cx / 2;
		pdc.TextOutW(string_start_x, string_start_y * (i + 1), vcs[i]);
		
	}


	
}