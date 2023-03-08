
// kaanadalilar_Adalilar_Kaan_HW6.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ckaanadalilar_Adalilar_Kaan_HW6App:
// See kaanadalilar_Adalilar_Kaan_HW6.cpp for the implementation of this class
//

class Ckaanadalilar_Adalilar_Kaan_HW6App : public CWinApp
{
public:
	Ckaanadalilar_Adalilar_Kaan_HW6App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ckaanadalilar_Adalilar_Kaan_HW6App theApp;