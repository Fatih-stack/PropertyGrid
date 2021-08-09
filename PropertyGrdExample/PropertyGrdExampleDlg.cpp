
// PropertyGrdExampleDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PropertyGrdExample.h"
#include "PropertyGrdExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CPropertyGrdExampleDlg dialog


CPropertyGrdExampleDlg::CPropertyGrdExampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROPERTYGRDEXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPropertyGrdExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Control(pDX, IDC_Gender, comboGender);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID1, propertyGrid);
}

BEGIN_MESSAGE_MAP(CPropertyGrdExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CPropertyGrdExampleDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_DelBTN, &CPropertyGrdExampleDlg::OnBnClickedDelbtn)
	ON_BN_CLICKED(IDC_SaveBTN, &CPropertyGrdExampleDlg::OnBnClickedSavebtn)
	ON_STN_CLICKED(IDC_MFCPROPERTYGRID1, &CPropertyGrdExampleDlg::OnStnClickedMfcpropertygrid1)
	ON_STN_ENABLE(IDC_MFCPROPERTYGRID1, &CPropertyGrdExampleDlg::OnStnEnableMfcpropertygrid1)
	ON_STN_DBLCLK(IDC_MFCPROPERTYGRID1, &CPropertyGrdExampleDlg::OnStnDblclickMfcpropertygrid1)
	ON_BN_CLICKED(IDC_ExpBTN, &CPropertyGrdExampleDlg::OnBnClickedExpbtn)
END_MESSAGE_MAP()


// CPropertyGrdExampleDlg message handlers

BOOL CPropertyGrdExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPropertyGrdExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPropertyGrdExampleDlg::OnPaint()
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
HCURSOR CPropertyGrdExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPropertyGrdExampleDlg::OnLbnSelchangeList1()
{
	CListBox* pList1 = (CListBox*)GetDlgItem(IDC_LIST1);
	propertyGrid.RemoveAll();
	nSel = pList1->GetCurSel();
	if (nSel != LB_ERR)
	{
		pList1->GetText(nSel, ItemSelected);
		CT2CA st(ItemSelected);
		std::string s(st);
		sItemSelected = s;
		CString gender = _T("Female");
		CString str;
		str.Format(L"%d", registers.find(s)->second[0]);
		if(registers.find(s)->second[3] == 1) gender = _T("Male");
		CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(_T("NAME"), ItemSelected);
		propertyGrid.AddProperty(pProp3);
		pProp3 = new CMFCPropertyGridProperty(_T("Height"), str);
		propertyGrid.AddProperty(pProp3);
		str.Format(L"%d", registers.find(s)->second[1]);
		pProp3 = new CMFCPropertyGridProperty(_T("Weight"), str);
		propertyGrid.AddProperty(pProp3);
		str.Format(L"%d", registers.find(s)->second[2]);
		pProp3 = new CMFCPropertyGridProperty(_T("Age"), str);
		propertyGrid.AddProperty(pProp3);
		pProp3 = new CMFCPropertyGridProperty(_T("Gender"), gender);
		propertyGrid.AddProperty(pProp3);

	}
}


void CPropertyGrdExampleDlg::OnBnClickedDelbtn()
{
	if (MessageBox(NULL, _T("Are you sure to want to delete?") + ItemSelected, MB_YESNO) == IDYES) {
		CT2CA st(ItemSelected);
		std::string s(st);
		m_listBox.DeleteString(nSel);
		auto it = registers.find(s);
		registers.erase(it);
	}
}


void CPropertyGrdExampleDlg::OnBnClickedSavebtn()
{
	wchar_t name[25],  height[4],  weight[4], age[4];
	GetDlgItemText(IDC_Name, name, 16);
	CString NAME = name;
	CT2CA st(NAME);
	std::string s(st);
	GetDlgItemText(IDC_Height, height, 16);
	int hgt = _wtoi(height);
	GetDlgItemText(IDC_Weight, weight, 16);
	int wgt = _wtoi(weight);
	GetDlgItemText(IDC_Age, age, 16);
	int Age = _wtoi(age);
	int gender = comboGender.GetCurSel();
	std::vector<int> values;
	registers.insert(std::make_pair(s, std::vector<int>{hgt, wgt, Age, gender}));
	m_listBox.AddString(NAME);
	//clear all edit lists
	SetDlgItemText(IDC_Name, L"");
	SetDlgItemText(IDC_Height, L"");
	SetDlgItemText(IDC_Weight, L"");
	SetDlgItemText(IDC_Age, L"");
}


void CPropertyGrdExampleDlg::OnStnClickedMfcpropertygrid1()
{

}


void CPropertyGrdExampleDlg::OnStnEnableMfcpropertygrid1()
{
	CMFCPropertyGridProperty* pProperty;//Define a pointer to the child
	pProperty = propertyGrid.GetCurSel();
	const COleVariant& strValue = pProperty->GetValue();
	CString strTmp = (CString)strValue;
}


void CPropertyGrdExampleDlg::OnStnDblclickMfcpropertygrid1()
{
	CMFCPropertyGridProperty* pProperty;//Define a pointer to the child
	pProperty = propertyGrid.GetCurSel();
	CString str = pProperty->GetName();
	COleVariant strValue = pProperty->GetValue();
	CString strTmp = (CString)strValue;
	if (str == "NAME") {
		std::vector<int> vals{ registers[sItemSelected] };
		registers.erase(sItemSelected);
		ItemSelected = strTmp;
		CT2CA st(ItemSelected);
		std::string s(st);
		sItemSelected = s;
		registers[sItemSelected] = vals;
	}
	else {
		if (str == "Height") {
			registers.find(sItemSelected)->second[0] = _wtoi(strTmp);
		}
		else if (str == "Weight") {
			registers.find(sItemSelected)->second[1] = _wtoi(strTmp);
		}
		else if (str == "Age") {
			registers.find(sItemSelected)->second[2] = _wtoi(strTmp);
		}
	}
}


void CPropertyGrdExampleDlg::OnBnClickedExpbtn()
{
	// TODO: Add your control notification handler code here
	CFile FileObj;
	FileObj.Open(L"ArchiveText.txt", CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CString height, weight, age, gender;
	height.Format(L"%d", registers.find(sItemSelected)->second[0]);
	weight.Format(L"%d", registers.find(sItemSelected)->second[1]);
	age.Format(L"%d", registers.find(sItemSelected)->second[2]);
	if (registers.find(sItemSelected)->second[3] == 1) gender = "Male";
	else gender = "Female";
	CString str = _T("") + ItemSelected + _T(";") + height + _T(";") + weight + _T(";") + 
		age + _T(";") + gender + _T("\r\n");
	FileObj.SeekToEnd();
	int size = sizeof(str);
	int len = str.GetLength();
	FileObj.Write(str.GetString(),len*2);
	FileObj.Flush();
	FileObj.Close();
	propertyGrid.UpdateData();
	propertyGrid.RemoveAll();
	MessageBox(L"Register is saved to txt file");
}
