
// Test_assignment.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestassignmentApp:
// See Test_assignment.cpp for the implementation of this class
//

class CTestassignmentApp : public CWinApp
{
public:
	CTestassignmentApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTestassignmentApp theApp;
