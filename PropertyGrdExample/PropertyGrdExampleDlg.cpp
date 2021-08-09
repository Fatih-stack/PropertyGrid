
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

//take selected list item(NAME) and find corresponding values from map(Height,weight,age,gender)
//insert selected item's keys and values to propertyGrid 
void CPropertyGrdExampleDlg::OnLbnSelchangeList1()
{
	CListBox* pList1 = (CListBox*)GetDlgItem(IDC_LIST1);
	propertyGrid.RemoveAll();
	nSel = pList1->GetCurSel();
	if (nSel != LB_ERR)
	{
		pList1->GetText(nSel, ItemSelected);	//take selected item text as CString
		CT2CA st(ItemSelected);
		std::string s(st);				//Convert Cstring to std::string
		sItemSelected = s;				//assign converted local value to class variable in order to use other func
		CString gender = _T("Female");
		CString str;
		str.Format(L"%d", registers.find(s)->second[0]);
		if(registers.find(s)->second[3] == 1)	//gender value is saved as 1 or 0 (male : 1, female : 0)
			gender = _T("Male");
		//Item's keys and values are added to propertyGrid
		//Item property NAME item value ItemSelected in propertyGrid
		CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(_T("NAME"), ItemSelected);	
		propertyGrid.AddProperty(pProp3);
		//Item's next property Height item's value str in propertyGrid
		pProp3 = new CMFCPropertyGridProperty(_T("Height"), str);
		propertyGrid.AddProperty(pProp3);
		//Item's next property Weight item's value str in propertyGrid, value is second element
		str.Format(L"%d", registers.find(s)->second[1]);
		pProp3 = new CMFCPropertyGridProperty(_T("Weight"), str);
		propertyGrid.AddProperty(pProp3);
		//Item's next property Age item's value str in propertyGrid, value is third element
		str.Format(L"%d", registers.find(s)->second[2]);
		pProp3 = new CMFCPropertyGridProperty(_T("Age"), str);
		propertyGrid.AddProperty(pProp3);
		pProp3 = new CMFCPropertyGridProperty(_T("Gender"), gender);
		propertyGrid.AddProperty(pProp3);

	}
}

//Remove selected item from list and map if select yes
void CPropertyGrdExampleDlg::OnBnClickedDelbtn()
{
	//if choose YES remove item from list and map
	if (MessageBox(NULL, _T("Are you sure to want to delete?") + ItemSelected, MB_YESNO) == IDYES) {
		CT2CA st(ItemSelected);
		std::string s(st);		//convert CString to std::string
		m_listBox.DeleteString(nSel);
		auto it = registers.find(s);
		registers.erase(it);
	}
}

//Takes values of edit controls and assign them to corresponding variables
//and insert it to map and add item's name to list
void CPropertyGrdExampleDlg::OnBnClickedSavebtn()
{
	//Variables for edit controls
	wchar_t name[25],  height[4],  weight[4], age[4];
	//Take values of edit controls and assign corresponding variables
	GetDlgItemText(IDC_Name, name, 16);
	CString NAME = name;
	CT2CA st(NAME);
	std::string s(st);						//CString to std::string
	GetDlgItemText(IDC_Height, height, 16);
	int hgt = _wtoi(height);				//wchar_t to int
	GetDlgItemText(IDC_Weight, weight, 16);
	int wgt = _wtoi(weight);
	GetDlgItemText(IDC_Age, age, 16);
	int Age = _wtoi(age);
	int gender = comboGender.GetCurSel();
	std::vector<int> values;
	//insert Name as key and value as vector consist of corresponding values
	registers.insert(std::make_pair(s, std::vector<int>{hgt, wgt, Age, gender}));
	//add name to listbox
	m_listBox.AddString(NAME);
	//clear all edit controls
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
}

//Click edited key and take edited value and change value in the map
void CPropertyGrdExampleDlg::OnStnDblclickMfcpropertygrid1()
{
	CMFCPropertyGridProperty* pProperty;//Define a pointer to the child
	pProperty = propertyGrid.GetCurSel();	//take selection
	CString str = pProperty->GetName();		//take key
	COleVariant strValue = pProperty->GetValue();	//take value
	CString strTmp = (CString)strValue;
	//assign taken value to corresponding place according to key
	//if name is edited assign all values to new name and remove old name
	if (str == "NAME") {
		std::vector<int> vals{ registers[sItemSelected] };	//assign values of selected name to vals variable
		registers.erase(sItemSelected);		//remove selected item from map
		ItemSelected = strTmp;
		CT2CA st(ItemSelected);
		std::string s(st);
		sItemSelected = s;
		registers[sItemSelected] = vals;
	}
	else {
		//if value is changed update it from values according to value's index
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

//If file is not exist create file and write chosen item to this file ( as Name;175;75;20;Male)
//If exist add chosen item to file
void CPropertyGrdExampleDlg::OnBnClickedExpbtn()
{
	CFile FileObj;		//Variable for file operations
	//Open existing file or it doesn't exist create and open
	FileObj.Open(L"Registers.txt", CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CString height, weight, age, gender;
	//Convert integer values to CString and assign corresponding variables
	height.Format(L"%d", registers.find(sItemSelected)->second[0]);
	weight.Format(L"%d", registers.find(sItemSelected)->second[1]);
	age.Format(L"%d", registers.find(sItemSelected)->second[2]);
	//Determine gender according to value in the last(gender) index
	if (registers.find(sItemSelected)->second[3] == 1) gender = "Male";
	else gender = "Female";
	//Create CString variable according to given format to write file
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
