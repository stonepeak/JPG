
// JPGDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JPG.h"
#include "JPGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJPGDlg 对话框




CJPGDlg::CJPGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJPGDlg::IDD, pParent)
	, wenjian1(_T(""))
	, wenjian2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJPGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, wenjian1);
	DDX_Text(pDX, IDC_EDIT2, wenjian2);
}

BEGIN_MESSAGE_MAP(CJPGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(file, &CJPGDlg::OnBnClickedfile)
	ON_BN_CLICKED(filee, &CJPGDlg::OnBnClickedfilee)
	ON_BN_CLICKED(file3, &CJPGDlg::OnBnClickedfile3)
	ON_EN_CHANGE(IDC_EDIT1, &CJPGDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CJPGDlg 消息处理程序

BOOL CJPGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJPGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJPGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJPGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJPGDlg::OnBnClickedfile()
{
	TCHAR szFilter[]=_T("jpg(*.jpg)|*.jpg||");//设置过滤器
	CFileDialog fileDlg(TRUE,_T("jpg"),NULL,0,szFilter,this);//构造文件打开对话框
	if(IDOK==fileDlg.DoModal())//如果点击了文件对话框上的“打开文件”，则选择的文件路径显示到编辑框里
	{
		wenjian1=fileDlg.GetPathName();
		UpdateData(false);//更新地址显示到编辑框
		
    CFile wenjian(wenjian1,CFile::modeRead );
     //获取文件长度
    DWORD m_filelen = wenjian.GetLength(); 
     //在堆上分配空间
    HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE,m_filelen);
    LPVOID pvdata = NULL;
    //锁定堆空间,获取指向堆空间的指针
    pvdata = GlobalLock(m_hglobal);
    //将文件数据读区到堆中
    wenjian.Read(pvdata,m_filelen);
    IStream*  m_stream;
    GlobalUnlock(m_hglobal);
    //在堆中创建流对象
    CreateStreamOnHGlobal(m_hglobal,TRUE,&m_stream);
    //利用流加载图像
    OleLoadPicture(m_stream,m_filelen,TRUE,IID_IPicture,(LPVOID*)&m_picture);
    m_picture->get_Width(&m_width);
    m_picture->get_Height(&m_height);    
    CDC* dc = GetDC();//上下全文
    CRect rect;
    GetClientRect(rect);
    SetScrollRange(SB_VERT,0,(int)(m_height/100)-rect.Height());//数字越大，图片越小
    SetScrollRange(SB_HORZ,0,(int)(m_width/100)-rect.Width());
    m_picture->Render(*dc,50,50,(int)(m_width/100),(int)(m_height/100),0,m_height,m_width,-m_height,NULL);
   
	};// TODO: 在此添加控件通知处理程序代码
}


void CJPGDlg::OnBnClickedfilee()
{
	TCHAR szFilter[]=_T("jpg(*.jpg)|*.jpg||");//设置过滤器
	CFileDialog fileDlg(TRUE,_T("jpg"),NULL,0,szFilter,this);//构造文件打开对话框
	if(IDOK==fileDlg.DoModal())//如果点击了文件对话框上的“打开文件”，则选择的文件路径显示到编辑框里
	{
		wenjian2=fileDlg.GetPathName();//显示完整的，文件路径名，和扩展名
		UpdateData(false);//更新地址显示到编辑框
		IPicture *m_picture;
    OLE_XSIZE_HIMETRIC m_width;
    OLE_YSIZE_HIMETRIC m_height;
    CFile wenjian(wenjian2,CFile::modeRead );
     //获取文件长度
    DWORD m_filelen = wenjian.GetLength(); 
     //在堆上分配空间
    HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE,m_filelen);
    LPVOID pvdata = NULL;
    //锁定堆空间,获取指向堆空间的指针
    pvdata = GlobalLock(m_hglobal);
    //将文件数据读区到堆中
    wenjian.Read(pvdata,m_filelen);
    IStream*  m_stream;
    GlobalUnlock(m_hglobal);
    //在堆中创建流对象
    CreateStreamOnHGlobal(m_hglobal,TRUE,&m_stream);
    //利用流加载图像
    OleLoadPicture(m_stream,m_filelen,TRUE,IID_IPicture,(LPVOID*)&m_picture);
    m_picture->get_Width(&m_width);
    m_picture->get_Height(&m_height);    
    CDC* dc = GetDC();//上下全文
    CRect rect;
    GetClientRect(rect);
    SetScrollRange(SB_VERT,0,(int)(m_height/100)-rect.Height());//数字越大，图片越小
    SetScrollRange(SB_HORZ,0,(int)(m_width/100)-rect.Width());
    m_picture->Render(*dc,320,50,(int)(m_width/100),(int)(m_height/100),0,m_height,m_width,-m_height,NULL);
	//调整（*dc，左右，上下）位置
   
	};// TODO: 在此添加控件通知处理程序代码
}


void CJPGDlg::OnBnClickedfile3()
{  
    CDC* dc = GetDC();//上下全文
	dc->BitBlt(750,50,260,250,dc,188,50,SRCCOPY);
    /*
	CRect rect;
    GetClientRect(rect);
    SetScrollRange(SB_VERT,0,(int)(m_height/100)-rect.Height());//数字越大，图片越小
    SetScrollRange(SB_HORZ,0,(int)(m_width/100)-rect.Width());
    m_picture->Render(*dc,450,50,(int)(m_width/100),(int)(m_height/100),0,m_height,m_width,-m_height,NULL);// TODO: 在此添加控件通知处理程序代码
	*/
}


void CJPGDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
