

#include"pch.h"
#include"DrawItem.h"



//virtual base DrawItem


#define BUFSIZ 512


extern CONF config;
DrawItem::DrawItem() {
	bk_path = "./res/bk.jpg";
	bk_img.Load(bk_path);

}


void DrawItem::DrawBackImg(CDC& pdc) {
	
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	bk_img.Draw(pdc, 0, 0, screen_width, screen_height);

}


void DrawItem::SetBrush(CBrush* brush) {
	m_pbrush = brush;
}

void DrawItem::SetPaintDC(CDC* dc) {
	m_pdc = dc;
}


//DrawVoteModular





void DrawVoteModular::Init() {

}


void DrawVoteModular::DrawForeText(CDC & pdc) {
	
	
	
}


//DrawSignInModular

void DrawSignInModular::Init() {

}


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

	tmp.Format(L"%s:%d", L"应到人数", config.sign_in_nums);
	vcs.push_back(tmp);

	tmp.Format(L"%s:%d", L"实到人数", device_ids.size());
	vcs.push_back(tmp);

	tmp.Format(L"%s:%d", L"未到人数", config.sign_in_nums - device_ids.size());
	vcs.push_back(tmp);

	tmp.Format(L"%s:%.2f%%", L"出勤率", device_ids.size() / (float)config.sign_in_nums * 100);
	vcs.push_back(tmp);

	int max_len = 0;
	
	
	
	for (int i = 0; i < vcs.size(); ++i) {


		//int string_start_x = screen_width / 2 - max_len * font_width / 2;
		//pdc.TextOutW(string_start_x, string_start_y * (i + 1), vcs[i]);
		int string_start_x = screen_width / 2 - pdc.GetTextExtent(vcs[i]).cx / 2;
		pdc.TextOutW(string_start_x, string_start_y * (i + 1), vcs[i]);
		
	}


	
}