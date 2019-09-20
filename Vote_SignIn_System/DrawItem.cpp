

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
	
	函数名	：	DrawBackImg
	描述		：	用于绘制背景图片
	参数		：	CDC pdc		用于双重缓冲的CDC设别环境
	作者		：
	时间		：


*/

void DrawItem::DrawBackImg(CDC& pdc) {
	
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	bk_img.Draw(pdc, 0, 0, screen_width, screen_height);

}



/*
	函数名	：	SetBrush
	参数		：	CBrush* brush 传入CBrush设置显示柱体的填充色
	描述		：	用于更改柱体的填充色的的画刷设备环境
	作者		：	zxc
	时间		：	2019-9-20


*/


void DrawItem::SetBrush(CBrush* brush) {
	m_pbrush = brush;
}




/*
	函数名	：	SetPaintDC
	参数		：	CDC	用于设置传入的PaintDC设备环境
	描述		：	更改双重缓冲中的CDC设备环境	
	作者		：	zxc
	时间		：	2019-9-20


*/


void DrawItem::SetPaintDC(CDC* dc) {
	m_pdc = dc;
}


//DrawBkModular


/*
	函数名	：	Init
	参数		：	
	描述		：	初始化绘制背景的相关参数
	作者		：	zxc
	时间		：	2019-9-20


*/


void DrawBkModular::Init() {

}





/*
	函数名	：	DrawForeText
	参数		：	CDC	在绘制背景中无用途
	描述		：	本函数只为实现接口基类中的绘制前景字符的作用，在绘制背景中无任何作用
	作者		：	zxc
	时间		：	2019-9-20


*/
void DrawBkModular::DrawForeText(CDC& pdc) {

}


//DrawVoteModular



/*
	函数名	：	Init
	参数		：
	描述		：	初始化绘制投票的相关参数
	作者		：	zxc
	时间		：	2019-9-20


*/


void DrawVoteModular::Init() {

}



/*
	-------------该功能更尚未完善---------------
	
	函数名	：	DrawForeText
	描述		：	用于实现投票中的自适应屏幕
	参数		：	CDC用于传入双重缓冲中的设备环境
	作者		：	zxc
	时间		：	2019-9-20 


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
	
	函数名	：	Init
	描述		：	初始化签到中的设备环境
	参数		：	None
	作者		：	zxc
	时间		：	2019-9-20


*/


void DrawSignInModular::Init() {

}




/*
	
	函数名	：		DrawForeText
	描述		：		用于绘制签到的前景显示文字
	参数		：		CDC	用于传入双重缓冲的设备环境
	作者		：		zxc
	时间		：		2019-9-20


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