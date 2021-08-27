#pragma once

#include "Dialog.h"

class CWindow
{
public:
	CWindow();
	virtual ~CWindow();
	virtual UINT Init() = 0;
	virtual void Shutdown() = 0;
	virtual BOOL Run() = 0;

	CApplication * GetApplication() {return m_pcApplication;}
	void SetApplication(CApplication * pcApplication) {m_pcApplication = pcApplication;}

	HWND GetHandle() {return m_hWnd;}
	void LoadWindowMessage();
	void AddDialog(CDialog *pcDialog);
	void RemoveDialog(CDialog *pcDialog);
	void Exit(BOOL b){m_bExit = b;}
	BOOL Exit(){return m_bExit;}
	void Minimized(BOOL b){m_bMinimized = b;}
	BOOL Minimized(){return m_bMinimized;}
protected:
	BOOL Register(const char *pszClassName,UINT uStyle,UINT uIncon,HBRUSH hbrBackground);
	void Unregister();
	BOOL MakeWindow(LPCSTR lpszTitle, BOOL bServer, BOOL bWindowed = FALSE, BOOL bMaximized = FALSE, int iWidth = 0, int iHeight = 0);
	BOOL PumpWindowMessage();
	void LoopWindowMessage();
	BOOL IsActive(BOOL bIncludeDialog = TRUE);
	BOOL IsDialog(HWND hWnd);
	BOOL ProcessMessage(MSG &msg);
	static LRESULT CALLBACK StaticWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	virtual LRESULT WndProc(UINT uMsg,WPARAM wParam,LPARAM lParam) = 0;

	virtual void Update(double fTime) = 0;
	static DWORD WINAPI UpdaterThread(CWindow *pThis);

	void RemoveDialogs();
	void RemoveWindow();
protected:
	CApplication * m_pcApplication;
	HWND m_hWnd;
	BOOL m_bRegisterSucess;
	char m_szClassName[256];
	std::vector<CDialog *> m_vDialogs;
	DWORD m_dwUpdateTimeInterval;
	BOOL m_bExit;
	BOOL m_bRuning;
	BOOL m_bMinimized;
};