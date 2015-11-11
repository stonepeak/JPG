
// JPGDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JPG.h"
#include "JPGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CJPGDlg �Ի���




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


// CJPGDlg ��Ϣ�������

BOOL CJPGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJPGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJPGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJPGDlg::OnBnClickedfile()
{
	TCHAR szFilter[]=_T("jpg(*.jpg)|*.jpg||");//���ù�����
	CFileDialog fileDlg(TRUE,_T("jpg"),NULL,0,szFilter,this);//�����ļ��򿪶Ի���
	if(IDOK==fileDlg.DoModal())//���������ļ��Ի����ϵġ����ļ�������ѡ����ļ�·����ʾ���༭����
	{
		wenjian1=fileDlg.GetPathName();
		UpdateData(false);//���µ�ַ��ʾ���༭��
		
    CFile wenjian(wenjian1,CFile::modeRead );
     //��ȡ�ļ�����
    DWORD m_filelen = wenjian.GetLength(); 
     //�ڶ��Ϸ���ռ�
    HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE,m_filelen);
    LPVOID pvdata = NULL;
    //�����ѿռ�,��ȡָ��ѿռ��ָ��
    pvdata = GlobalLock(m_hglobal);
    //���ļ����ݶ���������
    wenjian.Read(pvdata,m_filelen);
    IStream*  m_stream;
    GlobalUnlock(m_hglobal);
    //�ڶ��д���������
    CreateStreamOnHGlobal(m_hglobal,TRUE,&m_stream);
    //����������ͼ��
    OleLoadPicture(m_stream,m_filelen,TRUE,IID_IPicture,(LPVOID*)&m_picture);
    m_picture->get_Width(&m_width);
    m_picture->get_Height(&m_height);    
    CDC* dc = GetDC();//����ȫ��
    CRect rect;
    GetClientRect(rect);
    SetScrollRange(SB_VERT,0,(int)(m_height/100)-rect.Height());//����Խ��ͼƬԽС
    SetScrollRange(SB_HORZ,0,(int)(m_width/100)-rect.Width());
    m_picture->Render(*dc,50,50,(int)(m_width/100),(int)(m_height/100),0,m_height,m_width,-m_height,NULL);
   
	};// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CJPGDlg::OnBnClickedfilee()
{
	TCHAR szFilter[]=_T("jpg(*.jpg)|*.jpg||");//���ù�����
	CFileDialog fileDlg(TRUE,_T("jpg"),NULL,0,szFilter,this);//�����ļ��򿪶Ի���
	if(IDOK==fileDlg.DoModal())//���������ļ��Ի����ϵġ����ļ�������ѡ����ļ�·����ʾ���༭����
	{
		wenjian2=fileDlg.GetPathName();//��ʾ�����ģ��ļ�·����������չ��
		UpdateData(false);//���µ�ַ��ʾ���༭��
		IPicture *m_picture;
    OLE_XSIZE_HIMETRIC m_width;
    OLE_YSIZE_HIMETRIC m_height;
    CFile wenjian(wenjian2,CFile::modeRead );
     //��ȡ�ļ�����
    DWORD m_filelen = wenjian.GetLength(); 
     //�ڶ��Ϸ���ռ�
    HGLOBAL m_hglobal = GlobalAlloc(GMEM_MOVEABLE,m_filelen);
    LPVOID pvdata = NULL;
    //�����ѿռ�,��ȡָ��ѿռ��ָ��
    pvdata = GlobalLock(m_hglobal);
    //���ļ����ݶ���������
    wenjian.Read(pvdata,m_filelen);
    IStream*  m_stream;
    GlobalUnlock(m_hglobal);
    //�ڶ��д���������
    CreateStreamOnHGlobal(m_hglobal,TRUE,&m_stream);
    //����������ͼ��
    OleLoadPicture(m_stream,m_filelen,TRUE,IID_IPicture,(LPVOID*)&m_picture);
    m_picture->get_Width(&m_width);
    m_picture->get_Height(&m_height);    
    CDC* dc = GetDC();//����ȫ��
    CRect rect;
    GetClientRect(rect);
    SetScrollRange(SB_VERT,0,(int)(m_height/100)-rect.Height());//����Խ��ͼƬԽС
    SetScrollRange(SB_HORZ,0,(int)(m_width/100)-rect.Width());
    m_picture->Render(*dc,320,50,(int)(m_width/100),(int)(m_height/100),0,m_height,m_width,-m_height,NULL);
	//������*dc�����ң����£�λ��
   
	};// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CJPGDlg::OnBnClickedfile3()
{  
    CDC* dc = GetDC();//����ȫ��
	dc->BitBlt(750,50,260,250,dc,188,50,SRCCOPY);
    /*
	CRect rect;
    GetClientRect(rect);
    SetScrollRange(SB_VERT,0,(int)(m_height/100)-rect.Height());//����Խ��ͼƬԽС
    SetScrollRange(SB_HORZ,0,(int)(m_width/100)-rect.Width());
    m_picture->Render(*dc,450,50,(int)(m_width/100),(int)(m_height/100),0,m_height,m_width,-m_height,NULL);// TODO: �ڴ���ӿؼ�֪ͨ����������
	*/
}


void CJPGDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
