#pragma once

enum ESceneSky
{
	SCENESKY_None,
	SCENESKY_Rain,
	SCENESKY_Forest_Morning,
	SCENESKY_Forest_Noon,
	SCENESKY_Forest_Night,
	SCENESKY_Desert_Morning,
	SCENESKY_Desert_Noon,
	SCENESKY_Desert_Night,
	SCENESKY_Wasteland_Morning1,
	SCENESKY_Wasteland_Morning2,
	SCENESKY_Wasteland_Noon,
	SCENESKY_Wasteland_Night,
	SCENESKY_ForFAll_Morning,
	SCENESKY_ForFAll_Noon,
	SCENESKY_ForFAll_Night,
	SCENESKY_Iron_Morning,
	SCENESKY_Iron_Noon,
	SCENESKY_Iron_Night,
	SCENESKY_Iron_Aurora,
	SCENESKY_Iron_BOSS,
	SCENESKY_ICE1_Morning,
	SCENESKY_ICE1_Noon,
	SCENESKY_ICE1_Night,
	SCENESKY_ICE2_Morning,
	SCENESKY_ICE2_Noon,
	SCENESKY_ICE2_Night,
	SCENESKY_Lost1_Morning,
	SCENESKY_Lost1_Noon,
	SCENESKY_Lost1_Night,
	SCENESKY_Lost2_Morning,
	SCENESKY_Lost2_Noon,
	SCENESKY_Lost2_Night,
	SCENESKY_Battle_Event,
	SCENESKY_Battle_Moon,
	SCENESKY_Battle_Sun,
	SCENESKY_Battle_None,
};

namespace SCENE
{
	class Element
	{
		struct Model
		{
			std::string strFileName;
			BOOL bBip = FALSE;

			Model(const char *pszStr, BOOL b)
			{
				strFileName = pszStr;
				bBip = b;
			}
		};
	public:
		Element();
		virtual ~Element();

		void SetFileName(const char *pszName);
		void AddStaticModel(const char *pszFileName, BOOL bAnimation = FALSE);
		void AddModelEx(const char *pszFormat, ...);
		void SetBackgroundMusicID(EBackgroundMusicID eID);
	private:
		EBackgroundMusicID m_eBackgroundMusicID = BACKGROUNDMUSICID_TRIGGERED;
		std::string m_strFileName;
		std::vector<Model> m_vModel;
	};
}
