
// JPGDlg.h : ͷ�ļ�
//

#pragma once


// CJPGDlg �Ի���
class CJPGDlg : public CDialogEx
{
// ����
public:
	CJPGDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JPG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
