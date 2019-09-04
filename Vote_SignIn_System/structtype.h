


#include "pch.h"

#ifndef _STRUCT_TYPE
#define _STRUCT_TYPE


#include "stdafx.h"
#include <vector>

struct CONF {
	int com_index;
	int baud_rate_index;

	int beam_total_nums;
	int color_index;
	int beam_width;

	CFont new_font;
	CFont old_font;
	COLORREF font_color;

	std::vector<CString> names;
	std::vector<unsigned int> votes;


	CString sign_in_caption;
	
	int terminal_ids;
	int sign_in_nums;



	CString SignInTitle;

	CONF() : com_index(0), baud_rate_index(0), beam_total_nums(0),
		color_index(0), beam_width(0), terminal_ids(0),
		sign_in_nums(0), sign_in_caption(L"") {}



};




#endif // !_STRUCT_TYPE
