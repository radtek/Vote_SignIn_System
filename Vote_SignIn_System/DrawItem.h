#pragma once


#include"stdafx.h"
#include<vector>




class DrawItem {

public:
	DrawItem();
	virtual void Init() = 0;
	virtual void DrawBackImg(CDC& pdc);
	virtual void DrawForeText(std::vector<CString>& types, std::vector<unsigned int> votes, int beam_width, int mem_nums) = 0;
	void SetPaintDC(CDC* dc);
	void SetBrush(CBrush* brush);

protected:
	virtual ~DrawItem() {}

	CImage bk_img;
	CString bk_path;
	int screen_width;
	int screen_height;
	CDC* m_pdc;
	CBrush* m_pbrush;
	CString Title;
};



class DrawVoteModular : public DrawItem {

public:

	virtual void Init();
	virtual void DrawForeText(std::vector<CString>& types, std::vector<unsigned int> votes, int beam_width, int mem_nums);

};


class DrawSignInModular : public DrawItem {

public:

	virtual void Init();
	virtual void DrawForeText(std::vector<CString>& types, std::vector<unsigned int> votes, int beam_width, int mem_nums);

};

