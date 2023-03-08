
// kaanadalilar_Adalilar_Kaan_HW6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "kaanadalilar_Adalilar_Kaan_HW6.h"
#include "kaanadalilar_Adalilar_Kaan_HW6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// Ckaanadalilar_Adalilar_Kaan_HW6Dlg dialog



Ckaanadalilar_Adalilar_Kaan_HW6Dlg::Ckaanadalilar_Adalilar_Kaan_HW6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ckaanadalilar_Adalilar_Kaan_HW6Dlg::IDD, pParent)
	, andButton(0)
	, orButton(0)
	, xorButton(0)
	, button1(0)
	, button2(0)
	, operGroup(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_CHECK1, check1);
	DDX_Control(pDX, IDC_EDIT4, edit4);
	DDX_Control(pDX, IDC_LIST1, list1);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_CHECK1, check1);
	DDX_Control(pDX, IDC_EDIT4, edit4);
	DDX_Control(pDX, IDC_LIST1, list1);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Radio(pDX, IDC_RADIO1, operGroup);
}

BEGIN_MESSAGE_MAP(Ckaanadalilar_Adalilar_Kaan_HW6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, &Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnBnClickedRadio1)
	ON_EN_CHANGE(IDC_EDIT4, &Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_CHECK1, &Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Ckaanadalilar_Adalilar_Kaan_HW6Dlg message handlers

BOOL Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	combo1.SetCurSel(0);
	operGroup = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
}


void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if(check1.GetCheck()){
		combo1.EnableWindow(true);
		edit4.EnableWindow(true);
	}
	else{
		combo1.EnableWindow(false);
		edit4.EnableWindow(false);
	}
}

int maxSize = 0;

void Ckaanadalilar_Adalilar_Kaan_HW6Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	CString operand1, operand2, result, shiftDirection, shiftSize, myOperator;
	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(GetFont());
	CSize cz;

	edit1.GetWindowTextW(operand1);
	edit2.GetWindowTextW(operand2);
	edit4.GetWindowTextW(shiftSize);
	
	if(operand1.IsEmpty() || operand2.IsEmpty()){
		result = "At least one operand was not entered.";
		list1.AddString(result);
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize){
			maxSize = cz.cx;
		}
	}
	else{
		if(check1.GetCheck()){
			if(shiftSize.IsEmpty()){
				result = "Specify how many bits you want to shift";
				list1.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize){
					maxSize = cz.cx;
				}
			}
			else{
				unsigned int oper1, oper2, sizeOfShift, newResult1, newResult2;
				combo1.GetWindowTextW(shiftDirection);
				if(shiftDirection == _T("Left")){
					edit4.GetWindowTextW(shiftSize);
					oper1 = _tcstoul(operand1, nullptr, 10);
					oper2 = _tcstoul(operand2, nullptr, 10);
					sizeOfShift = _tcstoul(shiftSize, nullptr, 10);
					newResult1 = oper1 << sizeOfShift;
					newResult2 = oper2 << sizeOfShift;
				}
				else if(shiftDirection == _T("Right")){
					edit4.GetWindowTextW(shiftSize);
					oper1 = _tcstoul(operand1, nullptr, 10);
					oper2 = _tcstoul(operand2, nullptr, 10);
					sizeOfShift = _tcstoul(shiftSize, nullptr, 10);
					newResult1 = oper1 >> sizeOfShift;
					newResult2 = oper2 >> sizeOfShift;
				}
				UpdateData(TRUE);
				if(operGroup == 0){
					unsigned int calculatedVers = newResult1 & newResult2;
					CString strResult;
					strResult.Format(_T("%u"), calculatedVers);
					CString strOperand1;
					strOperand1.Format(_T("%u"), newResult1);
					CString strOperand2;
					strOperand2.Format(_T("%u"), newResult2);
					result = strOperand1 + " AND " + strOperand2 + " = " + strResult;
					list1.AddString(result);
				}
				else if(operGroup == 1){
					unsigned int calculatedVers = newResult1 | newResult2;
					CString strResult;
					strResult.Format(_T("%u"), calculatedVers);
					CString strOperand1;
					strOperand1.Format(_T("%u"), newResult1);
					CString strOperand2;
					strOperand2.Format(_T("%u"), newResult2);
					result = strOperand1 + " OR " + strOperand2 + " = " + strResult;
					list1.AddString(result);
				}
				else if(operGroup == 2){
					unsigned int calculatedVers = newResult1 ^ newResult2;
					CString strResult;
					strResult.Format(_T("%u"), calculatedVers);
					CString strOperand1;
					strOperand1.Format(_T("%u"), newResult1);
					CString strOperand2;
					strOperand2.Format(_T("%u"), newResult2);
					result = strOperand1 + " XOR " + strOperand2 + " = " + strResult;
					list1.AddString(result);
				}
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize){
					maxSize = cz.cx;
				}
			}
		}
		else{
			unsigned int oper1, oper2, newResult;
			oper1 = _tcstoul(operand1, nullptr, 10);
			oper2 = _tcstoul(operand2, nullptr, 10);
			UpdateData(TRUE);
			if(operGroup == 0){
				newResult = oper1 & oper2;
				CString strResult;
				strResult.Format(_T("%u"), newResult);
				result = operand1 + " AND " + operand2 + " = " + strResult;
				list1.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize){
					maxSize = cz.cx;
				}
			}
			else if(operGroup == 1){
				newResult = oper1 | oper2;
				CString strResult;
				strResult.Format(_T("%u"), newResult);
				result = operand1 + " OR " + operand2 + " = " + strResult;
				list1.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize){
					maxSize = cz.cx;
				}
			}
			else if(operGroup == 2){
				newResult = oper1 ^ oper2;
				CString strResult;
				strResult.Format(_T("%u"), newResult);
				result = operand1 + " XOR " + operand2 + " = " + strResult;
				list1.AddString(result);
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize){
					maxSize = cz.cx;
				}
			}
		}
	}
	list1.SetHorizontalExtent(maxSize);
}