#pragma once

enum EKeyboardEvent
{
	NoneKey,
	KeyDown,
	KeyUp,
	KeyChar,
};

namespace INPUTS
{
	class KeyBoard
	{
	public:
		KeyBoard();
		virtual ~KeyBoard() {}

		void SetEvent(EKeyboardEvent eKeyEvent);
		BOOL IsKeyDown(int iKey);
		BOOL OnKeyPass(int iKey, BOOL bKeydown);
		BOOL OnKeyChar(WPARAM wParam);
		EKeyboardEvent GetEvent() { return m_eEvent; }
		int GetKey() { return m_iKeyPass; }
		char GetChar() { return m_cKey[0]; }
		char *GetWord() { return m_cKey; }
	private:
		EKeyboardEvent m_eEvent = (EKeyboardEvent)-1;
		int m_iKeyPass = 0;
		BOOL m_bKeydown[256];
		char m_cKey[3] = { 0 };
	};
}
