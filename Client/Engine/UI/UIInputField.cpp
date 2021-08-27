#include "StdAfx.h"
#include "UIInputField.h"

namespace UI
{
	InputField::InputField(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}
	InputField::~InputField()
	{
		//Clear();
	}
	void InputField::Clear()
	{
		CLEARPTR(m_pImage);

		UI::ImageLoader::DeleteImage(m_pImage);

		m_vInputActives.clear();
		m_vBindActiveKeyboard.clear();
	}
	std::string InputField::GetText()
	{
		if (m_bIsNumber && (m_strText.length() == 0 || atoi((char *)m_strText.c_str()) == 0))
			return "0";

		if (m_bPassword)
			return UnicodeToANSI(m_strPassword);

		return UnicodeToANSI(m_strText);
	}
	void InputField::SetIsNumber(BOOL b, int iMin, int iMax)
	{
		m_bIsNumber = b;
		m_iMinNum = iMin;
		m_iMaxNum = iMax;

		SetText(FormatString("%d", iMin));
	}
	void InputField::Update(float fTime)
	{

	}
	UINT InputField::BuildFormat() const
	{
		UINT uFormat = DT_EXPANDTABS;

		switch (m_eHorizontal)
		{
		default:
		case ALIGN_Left:
			uFormat |= DT_LEFT;
			break;
		case ALIGN_Center:
			uFormat |= DT_CENTER;
			break;
		case ALIGN_Right:
			uFormat |= DT_RIGHT;
			break;
		}
		switch (m_eVerticalAlign)
		{
		default:
		case ALIGN_Top:
			uFormat |= DT_TOP;
			break;
		case ALIGN_Middle:
			uFormat |= DT_VCENTER;
			break;
		case ALIGN_Bottom:
			uFormat |= DT_BOTTOM;
			break;
		}

		return uFormat;
	}
	void InputField::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (IsOpen())
		{
			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = m_bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
			int iRenderHeight = m_bParentChild ? low(GetHeight(), iHeight - GetY()) :  GetHeight();

			UI::ImageRender::Render(m_pImage, iRenderX + iSourceX, iRenderY + iSourceY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);

			int iWidthSelectedText = m_pFont ? m_pFont->GetWidthTextW(m_strText.c_str(), m_iCurrPosition) : 0;
			int iWidthText = m_pFont ? m_pFont->GetWidthTextW(m_strText.c_str(),m_strText.length()) : 0;

			BOOL bClipText = GetWidth() - iWidthSelectedText < 0 ? TRUE : FALSE;

			RECT rRect;

			rRect.left	= bClipText ? iRenderX - 10 - (iWidthSelectedText - GetWidth()) : iRenderX;
			rRect.top	= iRenderY;
			rRect.right = rRect.left + GetWidth();
			rRect.bottom = rRect.top + GetHeight();

			if (m_eHorizontal == ALIGN_Left)
				rRect.left += 2;

			//Compute Scissor

			RECT r = { iRenderX,iRenderY,iRenderX + GetWidth(),iRenderY + GetHeight() };

			GRAPHICDEVICE->GetScissorRectInside(r);
			GRAPHICDEVICE->PushScissorRect(r);

			if (m_pFont)
				m_pFont->Draw(rRect, UnicodeToANSI(m_strText), BuildFormat() | DT_NOCLIP, m_dwColorText);

			if (m_bHover || m_bSelect)
			{
				if (m_pGroup)
				{
					if (m_pGroup->GetIndexObject() != GetID())
						m_bSelect = FALSE;

					if (m_bSelect)
					{
						if (m_dwTimeBarText < GetCurrentTime())
						{
							m_dwTimeBarText = GetCurrentTime() + m_iBarTextTime;
							m_bBarTextShow = m_bBarTextShow ? FALSE : TRUE;
						}
						else
						{
							if (m_bBarTextShow)
							{
								rRect.left += iWidthSelectedText;

								if (m_pFont)
									m_pFont->Draw(rRect, std::string("|"), BuildFormat() | DT_NOCLIP, m_dwColorText);
							}
						}

						if (m_strText.length() > 0)
						{
							//Render Selected Text
							if (m_iSelectedTextLength > 0)
							{
								int iWidthText = m_pFont ? m_pFont->GetWidthTextW(m_strText.substr(m_iSelectedTextPos, m_iSelectedTextLength).c_str(), m_iSelectedTextLength) : 0;
								LINEHANDLE->MakeLine()->Draw(Rectangle2D(iRenderX + m_sSelectedTextBox.iX, iRenderY + m_sSelectedTextBox.iY, iWidthText, 14), D3DCOLOR_ARGB(100, 255, 255, 255));
							}
							else if (m_iSelectedTextLength < 0)
							{
								int iWidthText = m_pFont ? m_pFont->GetWidthTextW(m_strText.substr(m_iSelectedTextPos - abs(m_iSelectedTextLength), m_iSelectedTextPos + 1).c_str(),abs(m_iSelectedTextLength)) : 0;
								LINEHANDLE->MakeLine()->Draw(Rectangle2D(iRenderX + m_sSelectedTextBox.iX - iWidthText + m_sSelectedTextBox.iWidth, iRenderY + m_sSelectedTextBox.iY, iWidthText, 14), D3DCOLOR_ARGB(100, 255, 255, 255));

							}
						}
					}
				}
			}

			GRAPHICDEVICE->PopScissorRect();
			Element::Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
		}
	}
	void InputField::OnMouseMove(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return;

		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = m_bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = m_bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

		Rectangle2D rBox = { iRenderX,iRenderY,iRenderWidth,iRenderHeight };

		m_bHover = psPosition->Inside(rBox) ? TRUE : FALSE;

		//Text Selected
		if (m_iSelectedTextPos > 0 && m_bSelectingText)
		{
			//Mouse Position
			Point2D *psPosition = pcMouse->GetPosition();

			int iDifference = psPosition->iX - (m_sSelectedTextBox.iX + GetX() + iX);
			int iCurrentWidth = 0;

			if (iDifference > 0)
			{
				for (size_t i = m_iSelectedTextPos; i < m_strText.length() + 1; i++)
				{
					wchar_t c = m_strText[i];

					iCurrentWidth += m_pFont ? m_pFont->GetWidthTextW(&c, 1) : 0;
					if (iCurrentWidth > iDifference)
					{
						m_iSelectedTextLength = i - m_iSelectedTextPos + 1;
						break;
					}
				}
			}
			else if (iDifference < 0)
			{
				for (size_t i = m_iSelectedTextPos; i > 0; i--)
				{
					wchar_t c = m_strText[i];

					iCurrentWidth += m_pFont ? m_pFont->GetWidthTextW(&c, 1) : 0;
					if (iCurrentWidth > abs(iDifference))
					{
						m_iSelectedTextLength = i - m_iSelectedTextPos - 1;
						break;
					}
				}
			}
		}
	}
	BOOL InputField::OnMouseClick(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return FALSE;

		if (ClickDownL != pcMouse->GetEvent())
		{
			m_bSelectingText = FALSE;
			return FALSE;
		}

		//Mouse Position
		Point2D *psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = m_bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = m_bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

		Rectangle2D rBox = { iRenderX,iRenderY,iRenderWidth,iRenderHeight };

		m_sSelectedTextBox = { 0,0,0,0 };
		m_iSelectedTextPos = 0;
		m_iSelectedTextLength = 0;
		m_bSelectingText = FALSE;

		//Inside Input
		if (rBox.Inside(psPosition))
		{
			if (m_bSelectType)
			{
				if (m_pGroup)
				{
					if (!m_bSelect)
						m_pGroup->SetIndexObject(GetID());
					else
					{
						m_iCurrPosition = m_strText.length();

						Rectangle2D sTextBox = { iRenderX,iRenderY,iRenderX + GetWidth(),iRenderY + GetHeight() };
						int iCurrentWidthAdd = 0;

						//Loop Text
						for (size_t i = 0; i < m_strText.length(); i++)
						{
							wchar_t c = m_strText[i];

							int iCharacterWidth = m_pFont ? m_pFont->GetWidthTextW(&c, 1) : 0;
							int iCharacterHeight = m_pFont ? m_pFont->GetHeightTextW(&c, RECT{ 0,0,0,0 }) : 0;

							Rectangle2D sDetectBox = { sTextBox.iX + iCurrentWidthAdd + 2,sTextBox.iY + 2,iCharacterWidth,iCharacterHeight };
							m_sSelectedTextBox = { iCurrentWidthAdd + 2,2,iCharacterWidth,iCharacterHeight };

							//Mouse inside letter bounding box
							if (sDetectBox.Inside(psPosition))
							{
								m_bSelectingText = TRUE;
								m_iCurrPosition = i;
								m_iSelectedTextPos = (i + 1);
								break;
							}

							m_bSelectingText = TRUE;
							m_iCurrPosition = m_strText.length();
							m_iSelectedTextPos = m_strText.length();

							iCurrentWidthAdd += iCharacterWidth;
						}
					}

					m_bSelect = TRUE;
				}
				else
					m_bSelect = m_bSelect ? FALSE : TRUE;
			}

			return TRUE;
		}

		return FALSE;
	}
	BOOL InputField::OnMouseScroll(class INPUTS::Mouse *pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsLinkObject())
			return FALSE;

		Point2D *psPosition = pcMouse->GetPosition();

		if (m_bSelect)
		{
			if (m_bIsNumber && GetCanScroll())
			{
				int iNum = atoi((char *)m_strText.c_str() + pcMouse->GetDistance());

				if (iNum > m_iMaxNum)
					iNum = m_iMaxNum;

				if (iNum < m_iMinNum)
					iNum = m_iMinNum;

				m_strText = ANSIToUnicode(FormatString("%d", iNum));

				return TRUE;
			}
		}
		return FALSE;
	}
	BOOL InputField::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
	{
		if (!IsOpen() || IsLinkObject())
			return FALSE;

		if (m_bSelect)
		{
			if (pcKeyboard->GetEvent() == KeyDown)
			{
				for (auto &vKeyboard : m_vBindActiveKeyboard)
				{
					if (pcKeyboard->GetKey() == vKeyboard.dwKey)
					{
						UI::Event::Invoke(vKeyboard.iEventID);
						return TRUE;
					}
				}
			}

			if (pcKeyboard->GetKey() == VK_RETURN && pcKeyboard->GetEvent() == KeyDown)
			{
				m_iSelectedTextLength = 0;
				m_bSelect = FALSE;
				return TRUE;
			}

			//Have a Text
			if (m_strText.length() > 0)
			{
				if (pcKeyboard->GetKey() == VK_RIGHT && pcKeyboard->GetEvent() == KeyDown)
				{
					if ((UINT)m_iCurrPosition < m_strText.length())
					{
						m_iCurrPosition ++;
					}
				}
				else if (pcKeyboard->GetKey() == VK_LEFT && pcKeyboard->GetEvent() == KeyDown)
				{
					if (m_iCurrPosition > 0)
					{
						m_iCurrPosition--;
					}
				}
				else if ((pcKeyboard->GetKey() == VK_HOME || pcKeyboard->GetKey() == VK_PRIOR) && pcKeyboard->GetEvent() == KeyDown)
				{
					m_iCurrPosition = 0;
					return TRUE;
				}
				else if ((pcKeyboard->GetKey() == VK_END || pcKeyboard->GetKey() == VK_NEXT) && pcKeyboard->GetEvent() == KeyDown)
				{
					m_iCurrPosition = m_strText.length();
					return TRUE;
				}
				else if (pcKeyboard->GetKey() == VK_DELETE && pcKeyboard->GetEvent() == KeyDown)
				{
					if (m_iSelectedTextLength > 0 && m_strText.length() > 0 && (UINT)m_iSelectedTextLength <= m_strText.length())
					{
						m_strText.erase(m_iSelectedTextPos - 1, m_iSelectedTextLength);
						m_iSelectedTextPos = 0;
						m_iSelectedTextLength = 0;
					}
					else if ((UINT)abs(m_iSelectedTextLength) <= m_strText.length() && m_iSelectedTextLength < 0 && m_strText.length() > 0)
					{
						m_strText.erase(m_iSelectedTextPos - abs(m_iSelectedTextLength), abs(m_iSelectedTextLength));
						m_iCurrPosition -= abs(m_iSelectedTextLength);
						m_iSelectedTextPos = 0;
						m_iSelectedTextLength = 0;
					}
					else if (m_strText.length() > 0 && m_iCurrPosition > 0 && (UINT)m_iCurrPosition <= m_strText.length())
					{
						m_strText.erase(m_iCurrPosition, 1);
					}

					return TRUE;
				}
			}

			return TRUE;
		}

		return FALSE;
	}
	BOOL InputField::OnKeyChar(class INPUTS::KeyBoard *pcKeyboard)
	{
		if (!IsOpen() || IsLinkObject())
			return FALSE;

		if (m_bSelect)
		{
			if (pcKeyboard->GetChar() == VK_BACK)
			{
				if (m_iSelectedTextLength > 0 && m_strText.length() > 0 && (UINT)m_iSelectedTextLength <= m_strText.length())
				{
					m_strText.erase(m_iSelectedTextPos - 1, m_iSelectedTextLength);
					m_iSelectedTextPos = 0;
					m_iSelectedTextLength = 0;
				}
				else if ((UINT)abs(m_iSelectedTextLength) <= m_strText.length() && m_iSelectedTextLength < 0 && m_strText.length() > 0)
				{
					m_strText.erase(m_iSelectedTextPos - abs(m_iSelectedTextLength), abs(m_iSelectedTextLength));
					m_iCurrPosition -= abs(m_iSelectedTextLength);
					m_iSelectedTextPos = 0;
					m_iSelectedTextLength = 0;
				}
				else if (m_strText.length() > 0 && m_iCurrPosition > 0 && (UINT)m_iCurrPosition <= m_strText.length())
				{
					m_strText.erase(m_iCurrPosition - 1, 1);
					m_iCurrPosition--;
				}

				return TRUE;
			}
			else if (pcKeyboard->GetChar() == VK_TAB)
			{
				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('V'))
			{
				AddInput(GetClipboardText());
				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('C'))
			{
				if (m_iSelectedTextLength > 0 && m_strText.length() > 0 && (UINT)m_iSelectedTextLength <= m_strText.length())
				{
					std::string str = UnicodeToANSI(m_strText.substr(m_iSelectedTextPos - 1, m_iSelectedTextLength));
					SetClipboardText((char *)str.c_str());
					m_iSelectedTextPos = 0;
					m_iSelectedTextLength = 0;
				}
				else if ((UINT)abs(m_iSelectedTextLength) <= m_strText.length() && m_iSelectedTextLength < 0 && m_strText.length() > 0)
				{
					std::string str = UnicodeToANSI(m_strText.substr(m_iSelectedTextPos - abs(m_iSelectedTextLength)));
					SetClipboardText((char *)str.c_str());
					m_iCurrPosition -= abs(m_iSelectedTextLength);
					m_iSelectedTextPos = 0;
					m_iSelectedTextLength = 0;
				}

				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_SHIFT) && pcKeyboard->IsKeyDown(VK_ESCAPE))
				return TRUE;
			else if (pcKeyboard->IsKeyDown(VK_ESCAPE))
				return TRUE;
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('Z'))
			{
				UndoAction();
				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('A'))
			{
				int iCharacterWidth = m_pFont ? m_pFont->GetWidthTextW(m_strText.c_str(), 1) : 0;
				int iCharacterHeight = m_pFont ? m_pFont->GetHeightTextW(m_strText.c_str(), RECT{ 0,0,0,0 }) : 0;

				m_sSelectedTextBox = { 2,2,iCharacterWidth,iCharacterHeight };

				m_iSelectedTextPos = 1;
				m_iSelectedTextLength = m_strText.length();
				m_iCurrPosition = 0;
				return TRUE;
			}
			else if (pcKeyboard->GetChar() == VK_SPACE)
			{
				AddInput(" ");
				return TRUE;
			}
			else if (m_strText.length() < (UINT)m_iTextLength)
			{
				std::stringstream ss;
				std::string s;

				char *c = pcKeyboard->GetWord();

				ss << c;
				ss >> s;

				int iNumOld = atoi((char *)m_strText.c_str());

				AddInput(s);

				int iNumNew = atoi((char *)m_strText.c_str());

				if (m_bIsNumber)
				{
					if (m_bIsNumber && m_strText.length() > 1 && atoi((char *)m_strText.c_str()) == 0)
						m_strText = L"";
					if (iNumOld == 0 && iNumNew < 10)
						m_strText = ANSIToUnicode(s);
					if (atoi((char *)m_strText.c_str()) > m_iMaxNum)
						m_strText = ANSIToUnicode(FormatString("%d", m_iMaxNum));
				}
			}

			return TRUE;
		}

		return FALSE;
	}
	void InputField::ClearInput()
	{
		m_iSelectedTextLength = 0;
		m_iCurrPosition = 0;
		m_strText.clear();
	}
	void InputField::SetFont(const char *pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		m_pFont = FONTHANDLE->MakeFont(pszFont, iHeight, iWidth, bItalic, bBold);
		m_iFontheight = iHeight;
		m_dwColorText = dwColor;
	}
	void InputField::UndoAction()
	{
		std::wstring strLastAction = m_vInputActives[m_vInputActives.size() - 1];
		std::size_t uPosition = m_strText.rfind(strLastAction);

		if (uPosition != std::wstring::npos && strLastAction.length() > 0)
		{
			m_iCurrPosition -= strLastAction.length();
			m_strText.erase(uPosition, strLastAction.length());
			m_vInputActives.pop_back();
		}
	}
	void InputField::AddInput(std::string str)
	{
		if (m_strText.length() >= (UINT)m_iTextLength)
			return;

		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());

		if (m_bIsNumber)
		{
			for (size_t i = 0; i < str.length(); i++)
			{
				char c = str.c_str()[i];

				if (c < 0x30 || c > 0x39)
					return;
			}
		}

		if (m_bAllowedRule)
		{
			BOOL bFound = FALSE;

			for (size_t i = 0; i < str.length(); i++)
			{
				char c = str.c_str()[i];

				if (m_bAllowedRule)
				{
					bFound = FALSE;

					for (auto v : m_strAllowed)
					{
						if (v == c)
						{
							bFound = TRUE;
							break;
						}
					}

					if (bFound == FALSE)
						return;
				}
			}
		}

		std::wstring strNew = L"";

		if (m_bRegex)
		{
			REGEX(m_strRegex.c_str(), str);
		}

		std::wstring wstr = ANSIToUnicode(str);

		if (m_strText.length() + wstr.length() > (UINT)m_iTextLength)
			strNew = wstr.substr(0, m_strText.length() + wstr.length() - m_iTextLength);
		else
			strNew = wstr;

		if ((UINT)m_iCurrPosition <= m_strText.length())
		{
			if (m_bPassword)
			{
				m_strPassword.insert(m_iCurrPosition, strNew);
				strNew.replace(0, strNew.length(), L"●");
			}
			m_strText.insert(m_iCurrPosition, strNew);
			m_iCurrPosition += strNew.length();

			m_vInputActives.push_back(strNew);
		}
	}
}