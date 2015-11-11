
// JPGDlg.h : 头文件
//

#pragma once


// CJPGDlg 对话框
class CJPGDlg : public CDialogEx
{
// 构造
public:
	CJPGDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JPG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString wenjian1;
	CString wenjian2;
	IPicture *m_picture;
    OLE_XSIZE_HIMETRIC m_width;
    OLE_YSIZE_HIMETRIC m_height;
	afx_msg void OnBnClickedfile();
	afx_msg void OnBnClickedfilee();
	afx_msg void OnBnClickedfile3();
	afx_msg void OnEnChangeEdit1();
};
