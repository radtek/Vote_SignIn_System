DrawItem.h
    DrawItem    为虚基类，用作接口

        member function
            Init()
            DrawBackImg(CDC& pdc)
            DrawForeText(CDC& pdc)
            SetPaintDC(CDC* dc)
            SetBrush(CBrush* brush)


        member data
            CImage bk_img;
            CString bk_path;
            int screen_width;
            int screen_height;
            CDC* m_pdc;
            CBrush* m_pbrush;
            CString Title;


EditDlg.h

    用于更改签到标题


EditNames.h
    用于添加删除被投票人的名字


ExcelOperator
    封装了部分Excel的操作


new_beam.h
    app


new_beamDlg.h
    用于设置该软件的相关属性


Portoperate.h
    封装了部分端口通信的函数


SelfDefine.h
    自定义了部分消息

SignIn.h
    ...


structtype.h
    定义了一个保存设置的结构体，用于全局保存显示的属性




