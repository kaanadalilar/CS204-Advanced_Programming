
// kaanadalilar_Adalilar_Kaan_HW6Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Ckaanadalilar_Adalilar_Kaan_HW6Dlg dialog
class Ckaanadalilar_Adalilar_Kaan_HW6Dlg : public CDialogEx
{
// Construction
public:
	Ckaanadalilar_Adalilar_Kaan_HW6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KAANADALILAR_ADALILAR_KAAN_HW6_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeEdit4();
	CEdit operand1;
	CEdit operand2;
	int andButton;
	int orButton;
	int xorButton;
	CButton shiftButton;
	CEdit bitsToShift;
	CListBox resultList;
	afx_msg void OnBnClickedCheck1();
	CEdit edit1;
	CEdit edit2;
	int button1;
	int button2;
	CButton check1;
	CEdit edit4;
	CListBox list1;
	CComboBox combo1;
	afx_msg void OnBnClickedButton1();
	CButton operatorGiven;
	int operGroup;
};
