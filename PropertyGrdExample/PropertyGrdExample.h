
// PropertyGrdExample.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <iostream>
#include <unordered_map>
#include <vector>
// CPropertyGrdExample:
// See PropertyGrdExample.cpp for the implementation of this class
//

class CPropertyGrdExample : public CWinApp
{
public:
	CPropertyGrdExample();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPropertyGrdExample theApp;
