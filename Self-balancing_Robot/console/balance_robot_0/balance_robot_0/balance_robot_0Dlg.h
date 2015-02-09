
// balance_robot_0Dlg.h : header file
//

#pragma once
#include "mscomm1.h"
#include "usercomm.h"


// Cbalance_robot_0Dlg dialog
class Cbalance_robot_0Dlg : public CDialogEx
{
// Construction
public:
	Cbalance_robot_0Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BALANCE_ROBOT_0_DIALOG };

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
private:
	CMscomm1 m_mscomm;
public:
	afx_msg void OnClickedBtnCxn();
	int m_port;
private:
	bool m_bCxn;
	CUserComm m_comm;
	virtual void OnCancel();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_div;
public:
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
};
