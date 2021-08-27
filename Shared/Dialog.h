#pragma once

class CDialog
{
protected:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	USHORT m_iResourceID;
protected:
	BOOL MakeDialog();
	static INT_PTR CALLBACK StaticDlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	virtual INT_PTR DlgProc(UINT uMsg,WPARAM wParam,LPARAM lParam) = 0;
	void RemoveDialog();
public:
	CDialog(USHORT _IResourceID);
	virtual ~CDialog();
	virtual BOOL Init() = 0;
	virtual void Shutdown() = 0;
	HINSTANCE GetProcessInstance() {return m_hInstance;}
	HWND GetWindowHandle(){return m_hWnd;}
};