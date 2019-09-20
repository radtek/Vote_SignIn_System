#pragma once




/*


	����		��	���ڻ���ͶƱ��ǩ������ֵı���ͼƬ��ǰ����
	����		��	zxc
	���ʱ��	��	2019-09-20



*/


#include"stdafx.h"
#include<vector>

#include "structtype.h"
#include <set>

//extern CONF config;



/*
	����		��	
	����		��
	ʱ��		��


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

	����		��	���ڻ��Ʊ���ͼƬ
	����		��	zxc
	ʱ��		��	2019-09-20


*/

class DrawBkModular : public DrawItem {
public:

	virtual void Init();
	virtual void DrawForeText(CDC& pdc);
};




/*
	����		��	���ڻ���ͶƱ��ǰ�����֣����Զ���Ӧ���ڴ�С������
	����		��	zxc
	ʱ��		��	2019-09-20
	˵��		��	�ù�����δ����


*/


class DrawVoteModular : public DrawItem {

public:

	virtual void Init();
	virtual void DrawForeText(CDC& pdc);

};





/*
	����		��	����ǩ����ǰ��������ʾ�����Զ�����
	����		��	zxc
	ʱ��		��	2019-09-20


*/

class DrawSignInModular : public DrawItem {

public:

	virtual void Init();
	virtual void DrawForeText(CDC& pdc);

};

extern std::set<unsigned int> device_ids;
extern std::vector<COLORREF> m_colorref;;