
// PropertyGrdExampleDlg.h : header file
//

#pragma once


// CPropertyGrdExampleDlg dialog
class CPropertyGrdExampleDlg : public CDialogEx
{
// Construction
public:
	CPropertyGrdExampleDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPERTYGRDEXAMPLE_DIALOG };
#endif

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
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedDelbtn();
	afx_msg void OnBnClickedSavebtn();
	CListBox m_listBox;
	int nSel;
	CString ItemSelected;
	std::string sItemSelected;
	std::map<std::string, std::vector<int>> registers;
	CComboBox comboGender;
	CMFCPropertyGridCtrl propertyGrid;
	CMFCPropertyGridProperty* pProp0;
	CMFCPropertyGridProperty* pProp1;
	CMFCPropertyGridProperty* pProp2;
	CMFCPropertyGridProperty* pProp3;
	CMFCPropertyGridProperty* pProp4;
	afx_msg void OnBnClickedExpbtn();
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam);
	void changeGrid();
};
