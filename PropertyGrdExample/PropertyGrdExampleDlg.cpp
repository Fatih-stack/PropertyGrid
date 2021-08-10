
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
	ON_BN_CLICKED(IDC_ExpBTN, &CPropertyGrdExampleDlg::OnBnClickedExpbtn)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
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
	nSel = pList1->GetCurSel();
	if (nSel != LB_ERR)
	{
		pList1->GetText(nSel, ItemSelected);	//take selected item text as CString
		CT2CA st(ItemSelected);
		std::string s(st);				//Convert Cstring to std::string
		sItemSelected = s;				//assign converted local value to class variable in order to use other func
		CString gender = _T("Female");
		CString str;
		str.Format(_T("%d"), registers.find(s)->second[0]);
		if(registers.find(s)->second[3] == 1)	//gender value is saved as 1 or 0 (male : 1, female : 0)
			gender = _T("Male");
		//Item's keys and values are added to propertyGrid
		//Item property NAME item value ItemSelected in propertyGrid
		pProp0 = new CMFCPropertyGridProperty(_T("NAME"), ItemSelected);	
		propertyGrid.AddProperty(pProp0);
		props.push_back(pProp0);
		//Item's next property Height item's value str in propertyGrid
		pProp1 = new CMFCPropertyGridProperty(_T("Height"), str);
		propertyGrid.AddProperty(pProp1);
		props.push_back(pProp1);
		//Item's next property Weight item's value str in propertyGrid, value is second element
		str.Format(_T("%d"), registers.find(s)->second[1]);
		pProp2 = new CMFCPropertyGridProperty(_T("Weight"), str);
		propertyGrid.AddProperty(pProp2);
		props.push_back(pProp2);
		//Item's next property Age item's value str in propertyGrid, value is third element
		str.Format(_T("%d"), registers.find(s)->second[2]);
		pProp3 = new CMFCPropertyGridProperty(_T("Age"), str);
		propertyGrid.AddProperty(pProp3);
		props.push_back(pProp3);
		if (registers.find(s)->second[3] == 1)
			pProp4 = new CMFCPropertyGridProperty(_T("Gender"), _T("Male"), _T("One of: Male, Female"));
		else
			pProp4 = new CMFCPropertyGridProperty(_T("Gender"), _T("Female"), _T("One of: Male, Female"));
		pProp4->AddOption(_T("Female"));
		pProp4->AddOption(_T("Male"));
		pProp4->AllowEdit(FALSE);
		propertyGrid.AddProperty(pProp4);
		props.push_back(pProp4);
		registersGrid.insert(std::make_pair(registers.find(s)->first, std::vector<int>{ registers.find(s)->second[0],
			registers.find(s)->second[1], registers.find(s)->second[2], registers.find(s)->second[3]}));
	}
}

//Remove selected item from list and map if select yes
void CPropertyGrdExampleDlg::OnBnClickedDelbtn()
{
	//if choose YES remove item from list and map
	if (MessageBox(_T("	") + ItemSelected, _T("Are you sure to want to delete?"), MB_YESNO) == IDYES) {
		CT2CA st(ItemSelected);
		std::string s(st);		//convert CString to std::string
		m_listBox.DeleteString(nSel);
		auto it = registers.find(s);
		registers.erase(it);
		auto itr = registersGrid.find(s);
		registersGrid.erase(itr);
		for (int i = 0; i < 5; i++){
			propertyGrid.DeleteProperty(props[props.size()-1]);
			props.pop_back();
		}
	}
}

//Takes values of edit controls and assign them to corresponding variables
//and insert it to map and add item's name to list
void CPropertyGrdExampleDlg::OnBnClickedSavebtn()
{
	//Variables for edit controls
	wchar_t name[25],  height[4],  weight[4], age[4];
	//Take values of edit controls and assign corresponding variables
	bool valid = true;
	GetDlgItemText(IDC_Name, name, 16);
	CString NAME = name;
	CT2CA st(NAME);
	std::string s(st);						//CString to std::string
	if(!isValidName(s)){
		MessageBox(_T("Enter a valid Name!!!"), _T("Warning!!!"));
		valid = false;
	}
	GetDlgItemText(IDC_Height, height, 16);
	int hgt = _wtoi(height);				//wchar_t to int
	if (hgt > 250 || hgt < 50) {
		MessageBox(_T("Enter a valid height!!!"), _T("Warning!!!"));
		valid = false;
	}
	GetDlgItemText(IDC_Weight, weight, 16);
	int wgt = _wtoi(weight);
	if (wgt > 170 || wgt < 3) {
		MessageBox(_T("Enter a valid wgt!!!"), _T("Warning!!!"));
		valid = false;
	}
	GetDlgItemText(IDC_Age, age, 16);
	int Age = _wtoi(age);
	if (Age > 120 || Age < 1) {
		MessageBox(_T("Enter a valid age!!!"), _T("Warning!!!"));
		valid = false;
	}
	int gender = comboGender.GetCurSel();
	if(gender == -1) {
		MessageBox(_T("Please choose gender!!!"), _T("Warning!!!"));
		valid = false;
	}
	if (!valid) return;
	std::vector<int> values;
	//insert Name as key and value as vector consist of corresponding values
	registers.insert(std::make_pair(s, std::vector<int>{hgt, wgt, Age, gender}));
	//add name to listbox
	m_listBox.AddString(NAME);
	//clear all edit controls
	SetDlgItemText(IDC_Name, _T(""));
	SetDlgItemText(IDC_Height, _T(""));
	SetDlgItemText(IDC_Weight, _T(""));
	SetDlgItemText(IDC_Age, _T(""));
}

LRESULT CPropertyGrdExampleDlg::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lParam)
{	
	changeGrid();
	return 0;
}
//If file is not exist create file and write chosen item to this file ( as Name;175;75;20;Male)
//If exist add chosen item to file
void CPropertyGrdExampleDlg::OnBnClickedExpbtn()
{
	CFile FileObj;		//Variable for file operations
	CString sFilePath;
	const TCHAR szFilter[] = _T("TXT Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		sFilePath = dlg.GetPathName();
	}
	else {
		return;
	}
	//Open existing file or it doesn't exist create and open
	FileObj.Open(sFilePath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	for each (auto item in registersGrid)
	{
		std::string name;
		CString Name, height, weight, age, gender;
		//Convert integer values to CString and assign corresponding variables
		Name = item.first.c_str();
		height.Format(_T("%d"), registersGrid.find(item.first)->second[0]);
		weight.Format(_T("%d"), registersGrid.find(item.first)->second[1]);
		age.Format(_T("%d"), registersGrid.find(item.first)->second[2]);
		//Determine gender according to value in the last(gender) index
		if (registersGrid.find(item.first)->second[3] == 1) gender = "Male";
		else gender = "Female";
		//Create CString variable according to given format to write file
		CString str = _T("") + Name + _T(";") + height + _T(";") + weight + _T(";") +
			age + _T(";") + gender + _T("\r\n");
		FileObj.SeekToEnd();
		int size = sizeof(str);
		int len = str.GetLength();
		FileObj.Write(str.GetString(), len * 2);
		FileObj.Flush();
	}
	
	FileObj.Close();
	propertyGrid.UpdateData();
	int num = props.size();
	for (int i = 0; i < num; i++) {
		propertyGrid.DeleteProperty(props[props.size() - 1]);
		props.pop_back();
	}
	MessageBox(_T("Item is saved successfully"));
}

void CPropertyGrdExampleDlg::changeGrid() {
	CMFCPropertyGridProperty* pProperty;//Define a pointer to the child
	pProperty = propertyGrid.GetCurSel();	//take selection
	if(pProperty == nullptr)
		return;
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

bool CPropertyGrdExampleDlg::isValidName(std::string s) {
	if (s.length() < 3)
		return false;
	bool break_line = false;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < 'A' || s[i] > 'z') {
			if (s[i] == ' ' && i > 2 && (s.length() - i) > 2 && !break_line) {
				break_line = true;
			}
			else return false;
		}
			
	}
	return true;
}