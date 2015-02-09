
// balance_robot_0Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "balance_robot_0.h"
#include "balance_robot_0Dlg.h"
#include "afxdialogex.h"
#include "Joystick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CJoystick joystick;

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


// Cbalance_robot_0Dlg dialog




Cbalance_robot_0Dlg::Cbalance_robot_0Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cbalance_robot_0Dlg::IDD, pParent)
	, m_bCxn(false)
	, m_div(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_port = 0;
}

void Cbalance_robot_0Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Text(pDX, IDC_EDIT_CXN, m_port);
	DDV_MinMaxInt(pDX, m_port, 0, 255);
}

BEGIN_MESSAGE_MAP(Cbalance_robot_0Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CXN, &Cbalance_robot_0Dlg::OnClickedBtnCxn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cbalance_robot_0Dlg message handlers

BOOL Cbalance_robot_0Dlg::OnInitDialog()
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
	joystick.m_hWnd = m_hWnd;
	if (!joystick.Initialise()) {
		OnCancel();
		return FALSE;
	}
	SetTimer(1, 20, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cbalance_robot_0Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cbalance_robot_0Dlg::OnPaint()
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
HCURSOR Cbalance_robot_0Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cbalance_robot_0Dlg::OnClickedBtnCxn()
{
	// TODO: Add your control notification handler code here
	int port;

	if (m_bCxn == true) {
		m_comm.disconnect();
		GetDlgItem(IDC_BTN_CXN)->SetWindowTextW(_T("Connect"));
		m_bCxn = false;
	} else {
		UpdateData(true);
		port = m_port;
		UpdateData(false);
		m_comm.initialize(&m_mscomm);
		m_comm.connect(port);
		GetDlgItem(IDC_BTN_CXN)->SetWindowTextW(_T("Disconnect"));
		m_bCxn = true;
		m_div = 0;
	}
}


void Cbalance_robot_0Dlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);

	CDialogEx::OnCancel();
}


void Cbalance_robot_0Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if FAILED(joystick.PollDevice()) {
		KillTimer(1);
		MessageBox(
			_T("get device state error\r\n"),
			_T("DirectInput example\r\n"),
			MB_ICONERROR | MB_OK
		);
	}
	if (m_bCxn == true) {
		m_comm.tx(48, joystick.m_diJs.lRx);
		m_comm.tx(49, joystick.m_diJs.lRy);
		//m_comm.tx(48, joystick.m_diJs.lX);///
		//m_comm.tx(49, joystick.m_diJs.lY);///
	}

	CDialogEx::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(Cbalance_robot_0Dlg, CDialogEx)
	ON_EVENT(Cbalance_robot_0Dlg, IDC_MSCOMM1, 1, Cbalance_robot_0Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void Cbalance_robot_0Dlg::OnCommMscomm1()
{
	// TODO: Add your message handler code here
	int x[6];

	if (m_mscomm.get_CommEvent() == 2) {
		m_comm.rx(x);
	}
}
