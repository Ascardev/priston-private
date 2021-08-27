#include "StdAfx.h"
#include "InputKeyboard.h"

namespace INPUTS
{
	KeyBoard::KeyBoard()
	{
		for (int i = 0; i < 256; i++)
			m_bKeydown[i] = FALSE;
	}
	void KeyBoard::SetEvent(EKeyboardEvent eKeyEvent)
	{
		m_eEvent = eKeyEvent;
	}
	BOOL KeyBoard::IsKeyDown(int iKey)
	{
		if (iKey >= 0 && iKey < 256)
			return m_bKeydown[iKey];

		return FALSE;
	}
	BOOL KeyBoard::OnKeyPass(int iKey, BOOL bKeydown)
	{
		if (GAMECOREHANDLE->IsInit())
		{
			if (bKeydown)
				SetEvent(KeyDown);
			else
				SetEvent(KeyUp);

			if (iKey >= 0 && iKey < sizeof(m_bKeydown))
			{
				if (bKeydown)
					m_bKeydown[iKey] = TRUE;
				else
					m_bKeydown[iKey] = FALSE;

				m_iKeyPass = iKey;
			}

			return GAME->OnKeyPress(this);
		}

		return FALSE;
	}
	BOOL KeyBoard::OnKeyChar(WPARAM wParam)
	{
		if (GAMECOREHANDLE->IsInit())
		{
			SetEvent(KeyChar);

			ZeroMemory(m_cKey, sizeof(m_cKey));

			if (wParam & 0x80)
			{
				m_cKey[0] = wParam >> 8;
				m_cKey[1] = wParam;
			}
			else
				m_cKey[0] = (char)wParam;

			return GAME->OnKeyChar(this);
		}

		return FALSE;
	}
}