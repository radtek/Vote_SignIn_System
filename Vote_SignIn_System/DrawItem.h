#pragma once




/*


	描述		：	用于绘制投票，签到，打分的背景图片和前景字
	作者		：	zxc
	完成时间	：	2019-09-20



*/


#include"stdafx.h"
#include<vector>

#include "structtype.h"
#include <set>

//extern CONF config;



/*
	功能		：	
	作者		：
	时间		：


*/

class DrawItem {

public:
	DrawItem();
	virtual void Init() = 0;
	
	virtual void DrawBackImg(CDC& pdc);
	virtual void DrawForeText(CDC& pdc) = 0;
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





/*

	功能		：	用于绘制背景图片
	作者		：	zxc
	时间		：	2019-09-20


*/

class DrawBkModular : public DrawItem {
public:

	virtual void Init();
	virtual void DrawForeText(CDC& pdc);
};




/*
	功能		：	用于绘制投票的前景文字，并自动适应窗口大小并居中
	作者		：	zxc
	时间		：	2019-09-20
	说明		：	该功能尚未完善


*/


class DrawVoteModular : public DrawItem {

public:

	virtual void Init();
	virtual void DrawForeText(CDC& pdc);

};





/*
	功能		：	用于签到的前景文字显示，并自动居中
	作者		：	zxc
	时间		：	2019-09-20


*/

class DrawSignInModular : public DrawItem {

public:

	virtual void Init();
	virtual void DrawForeText(CDC& pdc);

};

extern std::set<unsigned int> device_ids;
extern std::vector<COLORREF> m_colorref;;