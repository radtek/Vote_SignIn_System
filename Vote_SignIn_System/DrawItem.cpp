

#include"pch.h"
#include"DrawItem.h"



//virtual base DrawItem


#define BUFSIZ 512



DrawItem::DrawItem() {
	bk_path = "./res/bk.jpg";
	bk_img.Load(bk_path);
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	screen_height = GetSystemMetrics(SM_CYSCREEN);
}


void DrawItem::DrawBackImg(CDC& pdc) {
	
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


void DrawVoteModular::DrawForeText(std::vector<CString>& names, std::vector<unsigned int> votes, int beam_width, int mem_nums) {
	int size = names.size();
	CFont* old_font = m_pdc->GetCurrentFont();
	LOGFONT lf;
	old_font->GetLogFont(&lf);
	//old_font->CreatePointFontIndirect(&lf, m_pdc);
	int font_height = lf.lfHeight;
	int font_width = lf.lfWidth;

	int width = screen_width / (size + 1);
	beam_width = beam_width > width ? width : beam_width;
	int height = screen_height / (mem_nums + 10);
	int bottom = height * (mem_nums + 5);
	int string_start_x = width / 2;
	for (int i = 0; i < size; ++i) {
		int len = names[i].GetLength();
		m_pdc->TextOutW(string_start_x - names[i].GetLength() / 2 * font_width, bottom, names[i]);
		
		CRect fillRect;
		fillRect.top = bottom - height * votes[i];
		fillRect.left = string_start_x - beam_width / 2;
		fillRect.bottom = bottom;
		fillRect.right = string_start_x + beam_width / 2;
		m_pdc->FillRect(&fillRect, m_pbrush);
	}
	
	
}



//DrawSignInModular

void DrawSignInModular::Init() {

}


void DrawSignInModular::DrawForeText(std::vector<CString>& types, std::vector<unsigned int> signin_mems, int beam_width, int mem_nums) {
	int size = types.size();
	CFont* old_font = m_pdc->GetCurrentFont();
	LOGFONT lf;
	old_font->CreatePointFontIndirect(&lf);
	

	int heigth = screen_height / (types.size() + 5);

	int font_height = lf.lfHeight > heigth ? heigth : lf.lfHeight;
	int font_width = lf.lfWidth;
	
	int string_start_x = screen_width / 2;
	

	int string_start_y = heigth * 4;

	for (int i = 0; i < size; ++i) {
		m_pdc->TextOutW(string_start_x - types[i].GetLength() * font_width / 2, string_start_y, types[i]);
		m_pdc->TextOutW(string_start_x, screen_width / 2, L":");
		char c[BUFSIZ];
		sprintf_s(c, "%d", signin_mems[i]);
		m_pdc->TextOutW(string_start_x + font_width * 10, string_start_y, CString(c));
		string_start_y += font_height;
	}



	
}