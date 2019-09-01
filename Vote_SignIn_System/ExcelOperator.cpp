#pragma once

#include "CApplication.h"
#include "CRange.h"


#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include <vector>
#include <utility>


struct Cord {
	unsigned int x;
	unsigned int y;

	Cord() :x(0), y(0) {}
};





class IExcelOperator {
public:
	virtual ~IExcelOperator() {}

	virtual void ExcelOpen(CString& file_name) = 0;
	virtual void ExcelOpen(CString& file_base_dir, CString& file_name) = 0;


	virtual void ExcelWrite() = 0;
	virtual void ExcelSetVal(unsigned int& row, unsigned int& col, CString& val) = 0;
	virtual void ExcelSetVal(std::vector<std::pair<Cord, CString>>& data) = 0;
	virtual void ExcelAppend(unsigned int& row, unsigned int& col, CString& val) = 0;
	virtual void ExcelAppend(std::vector<std::pair<Cord, CString>>& data) = 0;

	virtual CString ExcelRead(unsigned int& row, unsigned int& col) = 0;
	virtual CString ExcelRead(Cord& cord) = 0;

	virtual void ExcelClose() = 0;

	//virtual void ExcelSaveAs(CString file_name, CString file_path = CString("./")) = 0;
	virtual void ExcelSave() = 0;

protected:
	CString IndexToCString(Cord& cord);
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




CString IExcelOperator::IndexToCString(Cord& cord) {
	return IndexToCString(cord.x, cord.y);
}



CString IExcelOperator::IndexToCString(unsigned int row, unsigned int col) {
	return L"";
}




class ExcelOperator : public IExcelOperator {

public:
	virtual ~ExcelOperator(){}
	ExcelOperator();
	virtual void ExcelOpen(CString& file_name);
	virtual void ExcelOpen(CString& file_base_dir, CString& file_name);


	virtual void ExcelWrite();
	virtual void ExcelSetVal(unsigned int& row, unsigned int& col, CString& val);
	virtual void ExcelSetVal(std::vector<std::pair<Cord, CString>>& data);
	virtual void ExcelAppend(unsigned int& row, unsigned int& col, CString& val) = 0;
	virtual void ExcelAppend(std::vector<std::pair<Cord, CString>>& data) = 0;

	virtual CString ExcelRead(unsigned int& row, unsigned int& col);
	virtual CString ExcelRead(Cord& cord);

	virtual void ExcelClose();

	virtual void ExcelSave();
	//virtual void ExcelSaveAs(CString file_name, CString file_path = CString("./"));
};


void ExcelOperator::ExcelWrite() {
	ExcelSave();
}



void ExcelOperator::ExcelAppend(std::vector<std::pair<Cord, CString>>& data) {
	for (std::vector<std::pair<Cord, CString>>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		unsigned int row = iter->first.x;
		unsigned int col = iter->first.y;
		CString tmp = iter->second;
		this->ExcelAppend(row, col, tmp);
	}
}



void ExcelOperator::ExcelAppend(unsigned int& row, unsigned int& col, CString& val) {
	range = sheet.get_UsedRange();
	unsigned int max_row = range.get_Row();
	unsigned int max_col = range.get_Column();
	ExcelSetVal(max_row, max_col, val);
}


void ExcelOperator::ExcelSetVal(unsigned int& row, unsigned int& col, CString& val) {
	range = sheet.get_Range(COleVariant(IndexToCString(row, col)), COleVariant(IndexToCString(row, col)));
	range.put_Value2(_variant_t(val));
}


void ExcelOperator::ExcelSetVal(std::vector<std::pair<Cord, CString>>& data) {
	for (std::vector<std::pair<Cord, CString>>::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		unsigned int row = iter->first.x;
		unsigned int col = iter->first.y;
		CString tmp = iter->second;
		ExcelSetVal(row, col, tmp);
	}
}



CString ExcelOperator::ExcelRead(unsigned int& row, unsigned int& col) {
	range = sheet.get_Range(COleVariant(IndexToCString(row, col)), COleVariant(IndexToCString(row, col)));
	COleVariant rval = range.get_Value2();
	rval.ChangeType(VT_BSTR);
	return CString(rval.bstrVal);
}




CString ExcelOperator::ExcelRead(Cord& cord) {
	return ExcelRead((unsigned int&)(cord.x), (unsigned int&)(cord.y));
}


ExcelOperator::ExcelOperator() {

	opt = COleVariant(DISP_E_PARAMNOTFOUND, VT_ERROR);
	app.put_Visible(false);
	if (app.CreateDispatch(L"Excel.Application", NULL)) {
		::MessageBox(NULL, L"Application create failed", L"tips:", MB_OK);

	}
	else {
		books = app.get_Workbooks();
	}

}


void ExcelOperator::ExcelOpen(CString& file_base_dir, CString& file_name) {
	CString tmp;
	if (file_base_dir[file_base_dir.GetLength() - 1] != '/' && file_base_dir[file_base_dir.GetLength() - 1] != '\\') {
		tmp = file_base_dir + "/" + file_name;
	}
	else {
		tmp = file_base_dir + file_name;
	}
	ExcelOpen(tmp);
}


void ExcelOperator::ExcelOpen(CString& file_name) {
	CFileFind file;
	if (!file.FindFile(file_name)) {
		MessageBox(NULL, L"the file is not exist!", L"tips:", MB_OK);
		return;
	}
	lpDispatch = books.Open(file_name, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt, opt);
	book.AttachDispatch(lpDispatch);
	sheets.AttachDispatch(book.get_Worksheets());
	lpDispatch = sheets.get_Item(_variant_t(1));
	sheet.AttachDispatch(lpDispatch);


}


void ExcelOperator::ExcelClose() {
	books.Close();
	app.Quit();

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();

}


void ExcelOperator::ExcelSave() {
	app.put_DisplayAlerts(false);
	book.Save();
	book.put_Saved(true);
	app.put_DisplayAlerts(true);
}



