#pragma once

namespace SKILL
{
	namespace INFO
	{
		class Window
		{
		public:
			Window();
			virtual ~Window();

			void Init();
			void Shutdown();
			void AddString(int iSide, const std::string &strString, DWORD dwColor = -1, BOOL bBold = FALSE);
			void SetLineColor(DWORD dwColor, int iSide = -1, int iLineCount = -1);
			void AppendLineText(std::string str, int iSide = -1, int iLineCount = -1);
		protected:
			void FormatSkillInfo();
		private:
			// Images Box;
			UI::LPIMAGE m_pImageMaskLeftTop;
			UI::LPIMAGE m_pImageMaskRightTop;
			UI::LPIMAGE m_pImageMaskLeftBottom;
			UI::LPIMAGE m_pImageMaskRightBottom;

			UI::LPIMAGE m_pImageBorderLeftTop;
			UI::LPIMAGE m_pImageBorderRightTop;
			UI::LPIMAGE m_pImageBorderTop;
			UI::LPIMAGE m_pImageBorderLeftBottom;
			UI::LPIMAGE m_pImageBorderRightBottom;
			UI::LPIMAGE m_pImageBorderBottom;
			UI::LPIMAGE m_pImageBorderLeft;
			UI::LPIMAGE m_pImageBorderRight;

			UI::LPIMAGE m_pImageIconItems[12];

			DX::LPRENDERTARGET m_pRenderTargetMask = NULL;
			DX::LPEFFECT m_pEffectMask;

			std::vector<UI::LPTEXT> m_vLeftText, m_vRightText, m_vCompareText;

			Rectangle2D m_sSkillBox;
			SkillData m_cSkillWrapper;
			int m_iSkillInfoBoxHeight;
			UINT m_uSkillStatusPosition = 0;
			std::string m_strSkillNextLevelCost = "";
			BOOL m_bInfoBoxSkillTimer = FALSE;
			UINT m_uImageIconsItemsY = 0;
		};
	}
}
