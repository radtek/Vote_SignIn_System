#pragma once




/*

	功能		：	封装了部分Excel的操作，实现了打开，追加，设置单元格数据，关闭，新建等部分功能
	作者		：	zxc
	完成时间	：	2019-9-20

*/

#include "CApplication.h"
#include "CRange.h"


#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include <vector>
#include <map>
#include <fstream>
#include "stdafx.h"


struct Cord {
	unsigned int x;
	unsigned int y;

	Cord() :x(0), y(0) {}

	bool operator<(const Cord c1) const{
		return x < c1.x;
	}
};




template<typename T = CString>
class IExcelOperator {
public:
	virtual ~IExcelOperator() {}

	virtual void ExcelNew(CString file_name) = 0;
	virtual void ExcelNew(CString file_base_dir, CString file_name) = 0;

	virtual void ExcelOpen(CString file_name) = 0;
	virtual void ExcelOpen(CString file_base_dir, CString file_name) = 0;


	virtual void ExcelWrite() = 0;
	virtual void ExcelSetVal(unsigned int row, unsigned int col, T val) = 0;
	virtual void ExcelSetVal(std::map<Cord, T> data) = 0;
	virtual void ExcelAppend(unsigned int row, unsigned int col, T val) = 0;
	virtual void ExcelAppend(std::map<Cord, T> data) = 0;

	virtual CString ExcelRead(unsigned int row, unsigned int col) = 0;
	virtual CString ExcelRead(Cord cord) = 0;

	virtual void ExcelClose() = 0;

	//virtual void ExcelSaveAs(CString file_name, CString file_path = GetCurrentDirectory()) = 0;
	virtual void ExcelSave() = 0;

protected:
	CString IndexToCString(Cord cord);
	CString IndexToCString(unsigned int row, unsigned int col);

protected:


	CString file_path;
	CString file_name;
	CString open_mode;

	CApplication app;
	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;


	LPDISPATCH lpDispatch;
	COleVariant vResult;
	COleVariant opt;

};



template<typename T>
CString IExcelOperator<T>::IndexToCString(Cord cord) {
	return IndexToCString(cord.x, cord.y);
}


template<typename T>
CString IExcelOperator<T>::IndexToCString(unsigned int row, unsigned int col) {
	CString tmp;
	tmp.Format(L"%c%d", 'A' + row, col);
	return tmp;
}



template<typename T = CString>
class ExcelOperator : public IExcelOperator<T> {

public:
	ExcelOperator();

	virtual void ExcelNew(CString file_name);
	virtual void ExcelNew(CString file_base_dir, CString file_name);

	virtual void ExcelOpen(CString file_name);
	virtual void ExcelOpen(CString file_base_dir, CString file_name);


	virtual void ExcelWrite();
	virtual void ExcelSetVal(unsigned int row, unsigned int col, T val);
	virtual void ExcelSetVal(std::map<Cord, T> data);
	virtual void ExcelAppend(unsigned int row, unsigned int col, T val);
	virtual void ExcelAppend(std::map<Cord, T> data);

	virtual CString ExcelRead(unsigned int row, unsigned int col);
	virtual CString ExcelRead(Cord cord);

	virtual void ExcelClose();

	virtual void ExcelSave();
	//virtual void ExcelSaveAs(CString file_name, CString file_path = CString("./"));
};



template<typename T>
void ExcelOperator<T>::ExcelNew(CString file_base_dir, CString file_name) {
	CString tmp;
	if (file_base_dir[file_base_dir.GetLength() - 1] != '/' && file_base_dir[file_base_dir.GetLength() - 1] != '\\') {
		tmp = file_base_dir + "/" + file_name;
	}
	else {
		tmp = file_base_dir + file_name;
	}
	ExcelNew(tmp);
}

template<typename T>
void ExcelOperator<T>::ExcelNew(CString file_name) {
	book = books.Add(opt);
	book.SaveAs(_variant_t(file_name), opt, opt, opt, opt, opt, 0, opt, opt, opt, opt, opt);
}

template<typename T>
void ExcelOperator<T>::ExcelWrite() {
	ExcelSave();
}


template<typename T>
void ExcelOperator<T>::ExcelAppend(std::map<Cord, T> data) {
	for (std::map<Cord, T>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		ExcelAppend(iter->first.x, iter->first.y, data[iter->first]);
	}
}


template<typename T>
void ExcelOperator<T>::ExcelAppend(unsigned int row, unsigned int col, T val) {
	range = sheet.get_UsedRange();
	unsigned int max_row = range.get_Row();
	unsigned int max_col = range.get_Column();
	ExcelSetVal(max_row + 1, max_col + 1, val);
}

template<typename T>
void ExcelOperator<T>::ExcelSetVal(unsigned int row, unsigned int col, T val) {
	range = sheet.get_Range(COleVariant(IndexToCString(row, col)), COleVariant(IndexToCString(row, col)));
	range.put_Value2(_variant_t(val));
}

template<typename T>
void ExcelOperator<T>::ExcelSetVal(std::map<Cord, T> data) {
	for (std::map<Cord, T>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		ExcelSetVal((unsigned int)iter->first.x, (unsigned int)iter->first.y, data[iter->first]);
	}
}


template<typename T>
CString ExcelOperator<T>::ExcelRead(unsigned int row, unsigned int col) {
	range = sheet.get_Range(COleVariant(IndexToCString(row, col)), COleVariant(IndexToCString(row, col)));
	COleVariant rval = range.get_Value2();
	rval.ChangeType(VT_BSTR);
	return CString(rval.bstrVal);
}



template<typename T>
CString ExcelOperator<T>::ExcelRead(Cord cord) {
	return ExcelRead((unsigned int)(cord.x), (unsigned int)(cord.y));
}

template<typename T>
ExcelOperator<T>::ExcelOperator() {

	opt = COleVariant(DISP_E_PARAMNOTFOUND, VT_ERROR);
	app.put_Visible(false);
	if (!app.CreateDispatch(L"Excel.Application", NULL)) {
		::MessageBox(NULL, L"Application create failed", L"tips:", MB_OK);

	}
	else {
		books = app.get_Workbooks();
	}

}

template<typename T>
void ExcelOperator<T>::ExcelOpen(CString file_base_dir, CString file_name) {
	CString tmp;
	if (file_base_dir[file_base_dir.GetLength() - 1] != '/' && file_base_dir[file_base_dir.GetLength() - 1] != '\\') {
		tmp = file_base_dir + "/" + file_name;
	}
	else {
		tmp = file_base_dir + file_name;
	}
	ExcelOpen(tmp);
}

template<typename T>
void ExcelOperator<T>::ExcelOpen(CString file_name) {
	CFileFind file;
	if (!file.FindFile(file_name)) {
		MessageBox(NULL, L"the file is not exist!", L"tips:", MB_OK);
		
		
		std::ofstream file(file_name);
		file.close();
		
	}
	lpDispatch = books.Open(file_name, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt);
	book.AttachDispatch(lpDispatch);
	sheets.AttachDispatch(book.get_Worksheets());
	lpDispatch = sheets.get_Item(_variant_t(1));
	sheet.AttachDispatch(lpDispatch);


}

template<typename T>
void ExcelOperator<T>::ExcelClose() {
	books.Close();
	app.Quit();

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();

}

template<typename T>
void ExcelOperator<T>::ExcelSave() {
	app.put_DisplayAlerts(false);
	book.Save();
	book.put_Saved(true);
	app.put_DisplayAlerts(true);
}



