#include "StdAfx.h"
#include "SkillInfoWindow.h"

namespace SKILL
{
	namespace INFO
	{
		void Window::Init()
		{
			//Load Images
			m_pImageMaskLeftTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\topleft.png");
			m_pImageMaskRightTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\topright.png");
			m_pImageMaskLeftBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\bottomleft.png");
			m_pImageMaskRightBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\bottomright.png");

			//Load Border Images
			m_pImageBorderLeftTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\topleft.png");
			m_pImageBorderRightTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\topright.png");
			m_pImageBorderTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\top.png");
			m_pImageBorderRightBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\bottomright.png");
			m_pImageBorderLeftBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\bottomleft.png");
			m_pImageBorderBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\bottom.png");
			m_pImageBorderLeft = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\left.png");
			m_pImageBorderRight = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\right.png");

			m_pRenderTargetMask = GRAPHICDEVICE->MakeRenderTarget(5001, 600, 600);
			m_pEffectMask = GRAPHICDEVICE->GetEffectFactory()->MakeEffect("Resources\\Shaders\\UI\\InfoBox.fx");

			for (int i = 0; i < 12; i++)
			{
				m_pImageIconItems[i] = UI::ImageLoader::LoadImage_("Resources\\UI\\Skill\\WeaponIcon\\%d.bmp", i + 1);
			}
		}
		void Window::AddString(int iSide, const std::string &strString, DWORD dwColor, BOOL bBold)
		{
			//Find breakline in String 
			BOOL bMultiLine = FALSE;
			if (strString.find('\n') != std::string::npos)
				bMultiLine = TRUE;

			switch (iSide)
			{
			case 0: //Left Side
				//Is Multiline?
				if (bMultiLine)
				{
					size_t n = std::count(strString.begin(), strString.end(), '\n');
					m_iSkillInfoBoxHeight += 14 * n;
				}
				else
				{
					UI::LPTEXT pText = std::make_shared<UI::Text>(strString, Rectangle2D(14, m_iSkillInfoBoxHeight, 208, 0), bBold, dwColor);
					pText->SetText(trim((std::string)strString));
					pText->SetMultiLine(TRUE);
					pText->SetWordWrap(TRUE);
					m_iSkillInfoBoxHeight += pText->GetHeightText();
					m_vLeftText.push_back(pText);
				}
				break;
			case 1: //Right Side
			{
				UI::LPTEXT pText = std::make_shared<UI::Text>(strString, Rectangle2D(14 + m_vLeftText[m_vLeftText.size() - 1]->GetWidthText() + 6, m_iSkillInfoBoxHeight - m_vLeftText[m_vLeftText.size() - 1]->GetHeightText(), 208, 20), bBold, dwColor);
				pText->SetText(trim((std::string)strString));
				pText->SetMultiLine(TRUE);
				pText->SetWordWrap(TRUE);
				m_vRightText.push_back(pText);
				break;
			}
			case 2:
			{
				UINT uIndex = m_uSkillStatusPosition + m_vCompareText.size();

				if ((uIndex < m_vLeftText.size()) && (uIndex < m_vRightText.size()))
				{
					UI::LPTEXT pText = std::make_shared<UI::Text>(strString, Rectangle2D(m_vLeftText[uIndex]->GetWidthText() + m_vRightText[uIndex]->GetWidthText() + 24, m_vLeftText[uIndex]->GetY(), 208, 0), bBold, dwColor);
					pText->SetText(trim((std::string)strString));
					pText->SetMultiLine(TRUE);
					pText->SetWordWrap(TRUE);
					m_vCompareText.push_back(pText);
				}
				break;
			}
			}
		}
		void Window::SetLineColor(DWORD dwColor, int iSide, int iLineCount)
		{
			int iSetColor = iLineCount < 0 ? m_vLeftText.size() - 1 : iLineCount;

			switch (iSide)
			{
			case -1:
				m_vLeftText[iSetColor]->SetColor(dwColor);
				m_vRightText[iSetColor]->SetColor(dwColor);
				break;
			case 0:
				m_vLeftText[iSetColor]->SetColor(dwColor);
				break;
			case 1:
				m_vRightText[iSetColor]->SetColor(dwColor);
				break;
			}
		}
		void Window::FormatSkillInfo()
		{
			m_uSkillStatusPosition = m_vLeftText.size();
			UINT uSkillLevel = m_cSkillWrapper.iLevel - 1;

			if (m_cSkillWrapper.iLevel == 0)
				uSkillLevel = 0;

			switch (m_cSkillWrapper.eID)
			{
			case SKILLID_ExtremeShield:
				AddString(0, "Shield Block Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT11ShieldBlockBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMechT11Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMechT11ShieldBlockBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMechT11Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MechanicBomb:
				AddString(0, "Static Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT12StaticDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT12AddAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT12Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaMeshT12StaticDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaMeshT12AddAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT12Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_PhysicalAbsorb:
				AddString(0, "Absorption Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT13AbsorptionBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT13Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaMeshT13AbsorptionBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT13Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_PoisonAttribute:
				AddString(0, "Poison Resistance Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("+%d", iaMeshT14PoisonInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(+%d)", iaMeshT14PoisonInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_GreatSmash:
				AddString(0, "Calculated Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT21CalculatedDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMechT21Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMechT21CalculatedDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMechT21Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Maximize:
				AddString(0, "Add Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT22AddAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT22AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT22Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT22AddAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaMeshT22AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT22Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Automation:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT23DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Attack Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMechT23AtkSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.1f", faMechT23MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.1f", faMechT23SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT23Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMechT23DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMechT23AtkSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%.1f)", faMechT23MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%.1f)", faMechT23SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT23Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Spark:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT24DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT24Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT24DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT24Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MetalArmor:
				AddString(0, "Armor Defense Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT31ArmorDefenseRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT31Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT31ArmorDefenseRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT31Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GrandSmash:
				AddString(0, "Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT32AttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT32DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT32AttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaMeshT32DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MechanicWeaponMastery:
				AddString(0, "Base Attack Power Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT33BaseAttackPowerInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaMeshT33BaseAttackPowerInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_SparkShield:
				AddString(0, "Spark Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT34SparkDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Defense Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT34AddDefenceRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT34Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT34SparkDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT34AddDefenceRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT34Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Impulsion:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT41DamgeBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT41Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Max. Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT41Hits[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT41DamgeBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT41Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT41Hits[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Compulsion:
				AddString(0, "Increase Absorption:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT42IncAbsorption[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Boost Absorption:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT42BoostAbsorption[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Monster Sight Range Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT42RangeInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT42Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaMeshT42IncAbsorption[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaMeshT42BoostAbsorption[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT42RangeInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT42Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MagneticSphere:
				AddString(0, "Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMeshT43SpheresDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT43SpheresAttackRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Delay:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMeshT43SpheresAttackDelay[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMeshT43Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMeshT43SpheresDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT43SpheresAttackRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMeshT43SpheresAttackDelay[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMeshT43Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MetalGolem:
				AddString(0, "Pet Settings:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%s", /*SKILLMANAGERHANDLER->IsAgressive(SKILLID_SummonTiger) ? "Automatic" :*/ "Manual"), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saMetalGolemAtkDmg[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMetalGolemAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "HP:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMetalGolemHP[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Defense:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMetalGolemDefense[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaMetalGolemDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d-%d)", saMetalGolemAtkDmg[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMetalGolemAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMetalGolemHP[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMetalGolemDefense[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaMetalGolemDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Rupture:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaMechT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_ParasitShot:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Poison Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaMechT52PoisonTimeDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMechT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaMechT52PoisonTimeDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HardeningShield:
				AddString(0, "Damage Reduction:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT53DMGReduction[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "WP ATK Rate Reduction:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT53WPAtkRateRed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaMechT53DMGReduction[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaMechT53WPAtkRateRed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MagneticDischarge:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaMechT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaMechT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
				//Fighter
			case SKILLID_MeleeMastery:
				AddString(0, "Weapon Attack Power Add:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT11WeaponAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaFighterT11WeaponAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_FireAttribute:
				AddString(0, "Fire Resistance Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT12FireResistanceInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d)", iaFighterT12FireResistanceInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_Raving:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT13DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT13NumberHit[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "HP Decrease:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.1f", faFighterT13HPDecrease[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT13DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT13NumberHit[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%.1f)", faFighterT13HPDecrease[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Impact:
				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT14AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT14DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaFighterT14AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT14DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_TripleImpact:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT21DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT21NumberHit[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT21DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT21NumberHit[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_BrutalSwing:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT22DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Added Critical:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT22AddCritical[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT22DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT22AddCritical[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Roar:
				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT23Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaFighterT23Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaFighterT23Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaFighterT23Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_RageofZecram:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT24DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT24Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT24DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT24Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Concentration:
				AddString(0, "Added Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT31AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaFighterT31Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT31AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaFighterT31Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_AvengingCrash:
				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT32AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT32DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaFighterT32AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT32DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SwiftAxe:
				AddString(0, "Attack Speed Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT33AttackSpeedBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaFighterT33Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT33AttackSpeedBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaFighterT33Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_BoneCrash:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT34DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost vs. Demons:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT34DamageBoostDemons[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT34DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT34DamageBoostDemons[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Destroyer:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT41DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Added Critical:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT41AddCritical[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT41DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT41AddCritical[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Berserker:
				AddString(0, "Add Base Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT42AddBaseAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Decrease Absorption:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT42DecAbsorption[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaFighterT42Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT42AddBaseAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT42DecAbsorption[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaFighterT42Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_CycloneStrike:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT43DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Maximum Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT43MaxHits[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT43Range[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT43DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT43MaxHits[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT43Range[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_BoostHealth:
				AddString(0, "HP Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT44HPInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d)", iaFighterT44HPInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_SurvivalInstinct:
				AddString(0, "Add HP Regen:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.1f", faFighterT51AddHPRegen[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add HP Potion Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT51AddHPPotionBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add HP Boost Health:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT51BoostHealthBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%.1f)", faFighterT51AddHPRegen[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT51AddHPPotionBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT51BoostHealthBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SeismicImpact:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT52Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT52Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_RuthlessofZecram:
				AddString(0, "HP Decrease:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.1f%%", faFighterT53HPDec[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Hits for boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT53HitsBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Final DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT53DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%.1f%%)", faFighterT53HPDec[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT53HitsBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaFighterT53DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Whirlwind:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaFighterT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT54Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT54MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaFighterT54SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaFighterT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT54Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT54MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaFighterT54SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
				//Pikeman
			case SKILLID_PikeWind:
				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saPikemanT11AttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Pushback Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPikemanT11PushBackRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d-%d)", saPikemanT11AttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPikemanT11PushBackRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_IceAttribute:
				AddString(0, "Frost Resistance Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPikemanT12FrostResistanceInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d)", iaPikemanT12FrostResistanceInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_CriticalHit:
				AddString(0, "Add Critical Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT13AddCriticalDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaPikemanT13AddCriticalDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_JumpingCrash:
				AddString(0, "Weapon Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT14WPAttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT14DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT14WPAttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT14DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GroundPike:
				AddString(0, "Freeze Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPikemanT21FreezeDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Freeze Attack:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saPikemanT21FreezeAttack[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Freeze Attack Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPikemanT21FreezeAttackRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%dsec)", iaPikemanT21FreezeDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d-%d)", saPikemanT21FreezeAttack[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPikemanT21FreezeAttackRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Tornado:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT22DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPikemanT22Range[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT22DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPikemanT22Range[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_WeaponDefenseMastery:
				AddString(0, "Weapon Current Block Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT23WeaponCurrentBlockBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaPikemanT23WeaponCurrentBlockBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_Expansion:
				AddString(0, "Add Size:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT24AddSize[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT24DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT24AddSize[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT24DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_VenomSpear:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT31DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of spears:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dspears", iaPikemanT31NumberSpears[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Effect Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPikemanT31Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Effect Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPikemanT31Range[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT31DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dspears)", iaPikemanT31NumberSpears[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPikemanT31Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPikemanT31Range[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Vanish:
				AddString(0, "After Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT32AfterDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Monster Sight Decrease:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT32SightDec[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPikemanT32Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT32AfterDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT32SightDec[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPikemanT32Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_CriticalMastery:
				AddString(0, "Weapon Critical Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT33WPCriticalRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaPikemanT33WPCriticalRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_ChainLance:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT34DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaPikemanT34DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_AssassinsEye:
				AddString(0, "Add Critical Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT41AddCriticalDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Target Critical Decrease:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT41TargetCriticalDec[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Debuff Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPikemanT41Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT41AddCriticalDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT41TargetCriticalDec[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPikemanT41Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ChargingStrike:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT42DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Charged Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT42ChargedDamgeBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Raise Charging Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT42RaiseSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT42DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT42ChargedDamgeBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT42RaiseSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Vague:
				AddString(0, "Add Evasion:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT43AddEvasion[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPikemanT43Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT43AddEvasion[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPikemanT43Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ShadowMaster:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT44DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dhit", iaPikemanT44NumberHits[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT44DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dhit)", iaPikemanT44NumberHits[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_RingofSpears:
				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPikemanT51Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%dsec)", iaPikemanT51Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_Focus:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT52DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Cooldown:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.2fsec", faPikemanT52Cooldown[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT52DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%.2fsec)", faPikemanT52Cooldown[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_DeathMaster:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT53DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "WP ATK Rate Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT53ATKRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPikemanT53DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPikemanT53ATKRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Twister:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPikemanT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaPikemanT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
				//Archer
			case SKILLID_ScoutHawk:
				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT11AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Hawk Rotation:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%drounds", iaArcherT11HawkRotation[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT11AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%drounds)", iaArcherT11HawkRotation[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ShootingMastery:
				AddString(0, "Add Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT12AddAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaArcherT12AddAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_WindArrow:
				AddString(0, "Add Attack Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT13AddAttackSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT13DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT13AddAttackSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT13DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_PerfectAim:
				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT14AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT14DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT14AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT14DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_DionsEye:
				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT21AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaArcherT21AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_Falcon:
				AddString(0, "Static Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT22StaticDamge[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Formula Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT22FormulaDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaArcherT22Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT22StaticDamge[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT22FormulaDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaArcherT22Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ArrowofRage:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT23DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT23Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT23DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT23Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Avalanche:
				AddString(0, "Add Attack Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT24AddAttackSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT24DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Arrows:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT24NumberArrow[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT24AddAttackSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT24DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT24NumberArrow[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ElementalShot:
				AddString(0, "Fire Damage Static:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT31FireDamageStatic[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Fire Damage Calculated:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT31FireDamageCalculated[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Lightning Damage Static:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT31LightningDamageStatic[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Lightning Damage Calculated:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT31LightningDamageCalculated[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT31FireDamageStatic[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT31FireDamageCalculated[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT31LightningDamageStatic[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT31LightningDamageCalculated[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GoldenFalcon:
				AddString(0, "Falcon Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT32FalconDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "HP Regen:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.01f", faArcherT32HPRegen[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaArcherT32Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT32FalconDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%.01f)", faArcherT32HPRegen[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaArcherT32Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_BombShot:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT33DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost VS Demons:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT33DamageBoostDemon[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT33Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT33DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT33DamageBoostDemon[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT33Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Perforation:
				AddString(0, "Increased Shot Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT34IncShotRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT34DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT34IncShotRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT34DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_RecallWolverine:
				AddString(0, "Pet Settings:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%s", /*SKILLMANAGERHANDLER->IsAgressive(SKILLID_SummonTiger) ? "Automatic" :*/ "Manual"), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saWolverineAtkDmg[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaWolverineAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "HP:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaWolverineHP[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Defense:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaWolverineDefense[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaWolverineDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d-%d)", saWolverineAtkDmg[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaWolverineAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaWolverineHP[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaWolverineDefense[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaWolverineDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_EvasionMastery:
				AddString(0, "Increase Evasion:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT42IncEvasion[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaArcherT42IncEvasion[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_PhoenixShot:
				AddString(0, "Shot Range Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT43ShotRangeInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT43DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Charge Raise Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%.1fsec", faArcherT43ChargeRaiseSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT43ShotRangeInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT43DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%.1fsec)", faArcherT43ChargeRaiseSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ForceofNature:
				AddString(0, "Add Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT44AddAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT44AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaArcherT44Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT44AddAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT44AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaArcherT44Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_LethalSight:
				AddString(0, "Range Add:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT51RangeAdd[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Critical Rate:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT51CritRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "After Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaArcherT51RangeAdd[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT51CritRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_FierceWind:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Critical DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT52CDMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaArcherT52CDMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_EntalingRoots:
				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT53Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d)", iaArcherT53Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_Bombardment:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaArcherT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT54Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT54MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaArcherT54SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaArcherT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT54Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT54MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaArcherT54SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
				//Knight
			case SKILLID_SwordBlast:
				AddString(0, "Static Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT11StaticDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT11DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Linear Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT11Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaKnightT11StaticDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT11DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaKnightT11Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyBody:
				AddString(0, "Damage Boost vs. Undead Monsters:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT12DamageBoostToUndead[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT12Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT12DamageBoostToUndead[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT12Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_PhysicalTraining:
				AddString(0, "SP Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT13SPBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaKnightT13SPBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_DoubleCrash:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT14DemageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Added Critical:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT14AddCritical[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT14DemageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT14AddCritical[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyValor:
				AddString(0, "Party Area:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT21PartyArea[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Final Damage Boost vs. Undead Enemies:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT21DamageBoostToUndead[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT21Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaKnightT21PartyArea[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT21DamageBoostToUndead[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT21Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Brandish:
				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT22Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT22DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaKnightT22Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT22DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Piercing:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT23DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT23Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Pierce Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT23PierceRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT23DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaKnightT23Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaKnightT23PierceRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_DrasticSpirit:
				AddString(0, "Defense Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT24DefenseBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT24Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT24DefenseBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT24Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SwordMastery:
				AddString(0, "Base Attack Power Increase:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT31BaseAttackPowerInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaKnightT31BaseAttackPowerInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_DivineShield:
				AddString(0, "Add Block Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT32AddBlockRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Monster Damage Into HP:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT32ToHPConversion[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT32Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaKnightT32AddBlockRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT32ToHPConversion[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT32Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyIncantation:
				AddString(0, "Success Rate:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT33SuccessRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Increase Undead HP:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT33IncUndeadHP[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Enslave Effect Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT33Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT33SuccessRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT33IncUndeadHP[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT33Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GrandCross:
				AddString(0, "Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT34AttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT34DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost vs. Undead Enemies:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT34UnDeadDMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT34AttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT34DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT34UnDeadDMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SwordofJustice:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT41DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT41Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT41DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaKnightT41Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GodlyShield:
				AddString(0, "Shield Absorption Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT42ShieldAbsorptionBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT42Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT42ShieldAbsorptionBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT42Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GodsBlessing:
				AddString(0, "Add Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT43AddAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaKnightT43Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT43AddAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaKnightT43Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_DivinePiercing:
				AddString(0, "Add Critical:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT44AddCritical[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT44DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT44NumberHits[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT44AddCritical[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT44DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaKnightT44NumberHits[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyConviction:
				AddString(0, "Undead DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaKnightT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_DivineInquisiton:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaKnightT52Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Undead Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT52UndeadDMG[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaKnightT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaKnightT52Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaKnightT52UndeadDMG[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GloriousShield:
				AddString(0, "Shield Def Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT53DefBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaKnightT53DefBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_DivineCross:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaKnightT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaKnightT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
				//Atalanta
			case SKILLID_ShieldStrike:
				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saAtaT11AttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d-%d)", saAtaT11AttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_Farina:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT12DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Attack Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT12AddAttackSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d+lv", iaAtaT12AddAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT12DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaAtaT12AddAttackSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d+lv)", iaAtaT12AddAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ThrowingMaster:
				AddString(0, "Add Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT13AddAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaAtaT13AddAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_BiggerSpear:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT14DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaAtaT14DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
				break;
			case SKILLID_Windy:
				AddString(0, "Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT21AttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT21AddRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaAtaT21Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT21AttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaAtaT21AddRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaAtaT21Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_TwistJavelin:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT22DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT22AttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT22DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaAtaT22AttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SoulSucker:
				AddString(0, "Monster Life Absorption:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT23LifeAbsorption[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaAtaT23LifeAbsorption[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_FireJavelin:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT24DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaAtaT24DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
				break;
			case SKILLID_SplitJavelin:
				AddString(0, "Number of Hits:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT31NumberHits[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT31DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT31AttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaAtaT31NumberHits[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaAtaT31DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaAtaT31AttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_TriumphofJavelin:
				AddString(0, "Max Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT32MaxAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaAtaT32Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaAtaT32MaxAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaAtaT32Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_LightningJavelin:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT33DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaAtaT33DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_StormJavelin:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT34DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
					AddString(2, FormatString("(%d%%)", iaAtaT34DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				break;
			case SKILLID_HallofValhalla:
				AddString(0, "Add Evasion:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT41AddEvasion[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaAtaT41Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT41AddEvasion[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaAtaT41Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ExtremeRage:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT42DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Area of Effect:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT42Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT42DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaAtaT42Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_FrostJavelin:
				AddString(0, "Add Attack :", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saAtaT43AddAttack[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Target Running Speed Reduction:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT43TargetRunningSpeedReduction[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Target Freeze Effect Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaAtaT43FreezeTime[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaAtaT43Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d-%d)", saAtaT43AddAttack[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaAtaT43TargetRunningSpeedReduction[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaAtaT43FreezeTime[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaAtaT43Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Vengeance:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT44DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT44AddRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT44DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaAtaT44AddRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SummonTiger:
				AddString(0, "Pet Settings:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%s", /*SKILLMANAGERHANDLER->IsAgressive(SKILLID_SummonTiger) ? "Automatic" :*/ "Manual"), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saSummonTigerAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaSummonTigerAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "HP:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaSummonTigerHP[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaSummonTigerDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString(""), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d-%d)", saSummonTigerAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaSummonTigerAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaSummonTigerHP[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaSummonTigerDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GoldenApple:
				AddString(0, "Speed:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT52Speed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Evade:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT52Evade[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT52Speed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaAtaT52Evade[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_PlagueJavelin:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT53DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Targets:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaAtaT53Targets[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Poison Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaAtaT53PoisonDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaAtaT53DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaAtaT53Targets[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaAtaT53PoisonDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ComboJavelin:

				break;
				//Priestess
			case SKILLID_Healing:
				AddString(0, "Formula Based Life Recovery:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT11FormulaBasedLifeRecovery[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power Based Life Recovery:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT1134AttackPowerBasedLifeRecovery[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaPrsT11FormulaBasedLifeRecovery[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT1134AttackPowerBasedLifeRecovery[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyBolt:
				AddString(0, "Formula Based Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT12FormulaBasedDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT12DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaPrsT12FormulaBasedDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT12DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_MultiSpark:
				AddString(0, "Formula Based Damage per Hit:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT13FormulaBasedDamageperHit[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power Based Damage per Hit:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT13AttackPowerBasedDamageperHit[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Sparks:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saPrsT13NumberofSparks[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaPrsT13FormulaBasedDamageperHit[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT13AttackPowerBasedDamageperHit[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d-%d)", saPrsT13NumberofSparks[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyMind:
				AddString(0, "Target Reduce Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT14TargetReduceDamage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Effect Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT14Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT14TargetReduceDamage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT14Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Meditation:
				AddString(0, "Add MP Potion Boost Recovery:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT21AddMPPotionBoostRecovery[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add MP Regeneration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT21AddMPRegeneration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT21AddMPPotionBoostRecovery[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT21AddMPRegeneration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_DivineLightning:
				AddString(0, "Attack Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT22AttackRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT22DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Bolts:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT22NumberofBolts[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaPrsT22AttackRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT22DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT22NumberofBolts[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_HolyReflection:
				AddString(0, "Monster Damage Reflected:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT23MonsterDamageReflected[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT23Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT23MonsterDamageReflected[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT23Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GrandHealing:
				AddString(0, "Formula Based Life Recovery:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT24FormulaBasedLifeRecovery[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power Based Life Recovery:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT24AttackPowerBasedLifeRecovery[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaPrsT24FormulaBasedLifeRecovery[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT24AttackPowerBasedLifeRecovery[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_VigorBall:
				AddString(0, "Attack Rating Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT31AttackRatingBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT31DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT31AttackRatingBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT31DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Ressurection:
				AddString(0, "Attainable Success Rate:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT32AttainableSuccessRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Max Players Resurrected:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT32MaxPlayersResurrected[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT32AttainableSuccessRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT32MaxPlayersResurrected[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_Extinction:
				AddString(0, "Attainable Success Rate:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT33AttainableSuccessRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Monster Health Reduction:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT33MonsterHealthReduction[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT33AttainableSuccessRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT33MonsterHealthReduction[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_VirtualLife:
				AddString(0, "Increase Life:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT34IncreaseLife[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT34Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT34IncreaseLife[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT34Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_GlacialSpike:
				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d-%d", saPrsT41AttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT41AttackRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Freeze Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT41Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d-%d)", saPrsT41AttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT41AttackRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT41Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_RegenerationField:
				AddString(0, "Add HP Regen:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT42AddHPRegen[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add MP Regen:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT42AddMPRegen[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT42Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT42Range[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d)", iaPrsT42AddHPRegen[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT42AddMPRegen[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT42Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT42Range[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_ChainLightning:
				AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT43DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Number of Bolts:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT43NumberofBolts[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Range:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d", iaPrsT43Range[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT43DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT43NumberofBolts[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d)", iaPrsT43Range[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_SummonMuspell:
				AddString(0, "Muspell Damage:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT44Damage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%-%d%%", saPrsT44AttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Virtual Life Effect Reduction:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT44LifeReduction[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Muspell Attack Delay:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT44AttackDelay[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Undead Absorption:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT44AddUndeadAbsorption[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Add Evasion:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%d%%", iaPrsT44AddEvasion[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
				AddString(1, FormatString("%dsec", iaPrsT44Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

				if (m_cSkillWrapper.iLevel < 10)
				{
					AddString(2, FormatString("(%d%%)", iaPrsT44Damage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%-%d%%)", saPrsT44AttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT44LifeReduction[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT44AttackDelay[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT44AddUndeadAbsorption[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%d%%)", iaPrsT44AddEvasion[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
					AddString(2, FormatString("(%dsec)", iaPrsT44Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				}
				break;
			case SKILLID_IceElemental:
				break;
			case SKILLID_LightningSurge:
				break;
			case SKILLID_HeavenlyLight:
				break;
			case SKILLID_Consecration:
				break;
				//Magician
			case SKILLID_Agony:
				break;
			case SKILLID_FireBolt:
				break;
			case SKILLID_Zenith:
				break;
			case SKILLID_FireBall:
				break;
			case SKILLID_MetalMastery:
				break;
			case SKILLID_Watornado:
				break;
			case SKILLID_EnchantWeapon:
				break;
			case SKILLID_DeathRay:
				break;
			case SKILLID_EnergyShield:
				break;
			case SKILLID_Diastrophism:
				break;
			case SKILLID_SpiritElemental:
				break;
			case SKILLID_DancingSword:
				break;
			case SKILLID_FireElemental:
				break;
			case SKILLID_FlameWave:
				break;
			case SKILLID_Distortion:
				break;
			case SKILLID_Meteorite:
				break;
			case SKILLID_WizardTrance:
				break;
			case SKILLID_StoneSkin:
				break;
			case SKILLID_RedRay:
				break;
			case SKILLID_Cataclysm:
				break;
				//Assassin
			case SKILLID_Stinger:
				break;
			case SKILLID_RunningHit:
				break;
			case SKILLID_DualWieldMastery:
				break;
			case SKILLID_Wisp:
				break;
			case SKILLID_VenomThorn:
				break;
			case SKILLID_Alas:
				break;
			case SKILLID_SoulShock:
				break;
			case SKILLID_AttackMastery:
				break;
			case SKILLID_SoreBlade:
				break;
			case SKILLID_GustSlash:
				break;
			case SKILLID_Inpes:
				break;
			case SKILLID_Blind:
				break;
			case SKILLID_FrostWind:
				break;
			case SKILLID_FatalMastery:
				break;
			case SKILLID_Polluted:
				break;
			case SKILLID_NinjaShadow:
				break;
			case SKILLID_ShadowBlink:
				break;
			case SKILLID_RisingSlash:
				break;
			case SKILLID_ViolentStub:
				break;
			case SKILLID_ShadowStorm:
				break;
				//Shaman
			case SKILLID_DarkBolt:
				break;
			case SKILLID_DarkWave:
				break;
			case SKILLID_Inertia:
				break;
			case SKILLID_InnerPeace:
				break;
			case SKILLID_SpiritualFlare:
				break;
			case SKILLID_SpiritualManacle:
				break;
			case SKILLID_ChasingHunt:
				break;
			case SKILLID_AdventMigal:
				break;
			case SKILLID_Rainmaker:
				break;
			case SKILLID_PhantomCall:
				break;
			case SKILLID_Haunt:
				break;
			case SKILLID_Scratch:
				break;
			case SKILLID_RecallHestian:
				break;
			case SKILLID_Judgement:
				break;
			case SKILLID_AdventMidranda:
				break;
			case SKILLID_Creed:
				break;
			case SKILLID_PressDeity:
				break;
			case SKILLID_PhantomNail:
				break;
			case SKILLID_OccultLife:
				break;
			}
		}
	}
}