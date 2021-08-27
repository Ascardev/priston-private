#include "StdAfx.h"
#include "SkillBase.h"

namespace SKILL
{
	BOOL SkillData::IsActiveSkill()
	{
		switch (eID)
		{
			//Fighter
		case SKILLID_Raving:
		case SKILLID_Impact:
		case SKILLID_TripleImpact:
		case SKILLID_BrutalSwing:
		case SKILLID_RageofZecram:
		case SKILLID_AvengingCrash:
		case SKILLID_BoneCrash:
		case SKILLID_Destroyer:
		case SKILLID_CycloneStrike:
		case SKILLID_SeismicImpact:
		case SKILLID_Whirlwind:

			//Mechanician
		case SKILLID_MechanicBomb:
		case SKILLID_GreatSmash:
		case SKILLID_Spark:
		case SKILLID_GrandSmash:
		case SKILLID_Impulsion:
		case SKILLID_Rupture:
		case SKILLID_MagneticDischarge:

			//Archer
		case SKILLID_WindArrow:
		case SKILLID_PerfectAim:
		case SKILLID_ArrowofRage:
		case SKILLID_Avalanche:
		case SKILLID_ElementalShot:
		case SKILLID_BombShot:
		case SKILLID_Perforation:
		case SKILLID_PhoenixShot:
		case SKILLID_FierceWind:
		case SKILLID_Bombardment:

			//Pikeman 
		case SKILLID_PikeWind:
		case SKILLID_CriticalHit:
		case SKILLID_JumpingCrash:
		case SKILLID_Tornado:
		case SKILLID_Expansion:
		case SKILLID_ChainLance:
		case SKILLID_ChargingStrike:
		case SKILLID_ShadowMaster:

			//Atalanta 
		case SKILLID_BiggerSpear:
		case SKILLID_TwistJavelin:
		case SKILLID_FireJavelin:
		case SKILLID_SplitJavelin:
		case SKILLID_LightningJavelin:
		case SKILLID_StormJavelin:
		case SKILLID_ExtremeRage:
		case SKILLID_Vengeance:
		case SKILLID_ComboJavelin:
			//Knight 
		case SKILLID_SwordBlast:
		case SKILLID_DoubleCrash:
		case SKILLID_Brandish:
		case SKILLID_Piercing:
		case SKILLID_GrandCross:
		case SKILLID_SwordofJustice:
		case SKILLID_DivinePiercing:
		case SKILLID_DivineCross:
		case SKILLID_DivineInquisiton:

			//Magician 
		case SKILLID_Agony:
		case SKILLID_FireBolt:
		case SKILLID_FireBall:
		case SKILLID_Watornado:
		case SKILLID_DeathRay:
		case SKILLID_Diastrophism:
		case SKILLID_FlameWave:
		case SKILLID_Meteorite:
		case SKILLID_StoneSkin:
		case SKILLID_RedRay:
		case SKILLID_Cataclysm:

			//Priestess 
		case SKILLID_Healing:
		case SKILLID_HolyBolt:
		case SKILLID_MultiSpark:
		case SKILLID_DivineLightning:
		case SKILLID_GrandHealing:
		case SKILLID_VigorBall:
		case SKILLID_Ressurection:
		case SKILLID_GlacialSpike:
		case SKILLID_ChainLightning:
		case SKILLID_LightningSurge:
		case SKILLID_HeavenlyLight:

			//Assassin 
		case SKILLID_Stinger:
		case SKILLID_RunningHit:
		case SKILLID_VenomThorn:
		case SKILLID_SoreBlade:
		case SKILLID_GustSlash:
		case SKILLID_FrostWind:
		case SKILLID_NinjaShadow:
		case SKILLID_ShadowBlink:

			//Shaman 
		case SKILLID_DarkBolt:
		case SKILLID_DarkWave:
		case SKILLID_SpiritualFlare:
		case SKILLID_PhantomCall:
		case SKILLID_Scratch:
		case SKILLID_Judgement:
		case SKILLID_MourningPray:
		case SKILLID_PressDeity:
		case SKILLID_PhantomNail:
			return TRUE;
		}

		return FALSE;
	}
	BOOL SkillData::IsPassiveSkill()
	{
		switch (eID)
		{
			//Fighter
		case SKILLID_MeleeMastery:
		case SKILLID_FireAttribute:
		case SKILLID_BoostHealth:
		case SKILLID_SurvivalInstinct:

			//Mechanician
		case SKILLID_PoisonAttribute:
		case SKILLID_MechanicWeaponMastery:

			//Archer
		case SKILLID_ShootingMastery:
		case SKILLID_DionsEye:
		case SKILLID_EvasionMastery:

			//Pikeman 
		case SKILLID_IceAttribute:
		case SKILLID_WeaponDefenseMastery:
		case SKILLID_CriticalMastery:

			//Atalanta 
		case SKILLID_ThrowingMaster:
		case SKILLID_GoldenApple:

			//Knight 
		case SKILLID_PhysicalTraining:
		case SKILLID_SwordMastery:

			//Magician 
		case SKILLID_MetalMastery:

			//Priestess 
		case SKILLID_Meditation:

			//Assassin 
		case SKILLID_DualWieldMastery:
		case SKILLID_AttackMastery:
		case SKILLID_FatalMastery:

			//Shaman 
		case SKILLID_InnerPeace:
		case SKILLID_OccultLife:
			return TRUE;
		}

		return FALSE;
	}
	BOOL SkillData::IsDebuffSkill()
	{
		switch (eID)
		{
			//Fighter
		case SKILLID_Roar:

			//Mechanician
		case SKILLID_ParasitShot:

			//Archer
		case SKILLID_EntalingRoots:

			//Pikeman 
		case SKILLID_GroundPike:
		case SKILLID_VenomSpear:
		case SKILLID_AssassinsEye:
		case SKILLID_RingofSpears:

			//Atalanta 
		case SKILLID_ShieldStrike:
		case SKILLID_SoulSucker:
		case SKILLID_PlagueJavelin:

		case SKILLID_Distortion:

			//Priestess 
		case SKILLID_HolyMind:
		case SKILLID_Extinction:

			//Assassin 
		case SKILLID_Wisp:
		case SKILLID_SoulShock:
		case SKILLID_Polluted:

			//Shaman 
		case SKILLID_Inertia:
		case SKILLID_SpiritualManacle:
		case SKILLID_Haunt:
			return TRUE;
		}

		return FALSE;
	}
	BOOL SkillData::IsBuffSkill()
	{
		switch (eID)
		{
			//Fighter
		case SKILLID_Concentration:
		case SKILLID_SwiftAxe:
		case SKILLID_Berserker:
		case SKILLID_RuthlessofZecram:

			//Mechanician
		case SKILLID_ExtremeShield:
		case SKILLID_PhysicalAbsorb:
		case SKILLID_Maximize:
		case SKILLID_Automation:
		case SKILLID_MetalArmor:
		case SKILLID_SparkShield:
		case SKILLID_Compulsion:
		case SKILLID_MagneticSphere:
		case SKILLID_HardeningShield:

			//Archer
		case SKILLID_ScoutHawk:
		case SKILLID_Falcon:
		case SKILLID_GoldenFalcon:
		case SKILLID_ForceofNature:
		case SKILLID_LethalSight:

			//Pikeman 
		case SKILLID_Vanish:
		case SKILLID_Vague:

			//Atalanta 
		case SKILLID_Farina:
		case SKILLID_Windy:
		case SKILLID_TriumphofJavelin:
		case SKILLID_HallofValhalla:
		case SKILLID_FrostJavelin:

			//Knight 
		case SKILLID_HolyBody:
		case SKILLID_HolyValor:
		case SKILLID_DrasticSpirit:
		case SKILLID_DivineShield:
		case SKILLID_HolyIncantation:
		case SKILLID_GodlyShield:
		case SKILLID_GodsBlessing:
		case SKILLID_GloriousShield:
		case SKILLID_HolyConviction:

			//Magician 
		case SKILLID_Zenith:
		case SKILLID_EnchantWeapon:
		case SKILLID_EnergyShield:
		case SKILLID_SpiritElemental:
		case SKILLID_DancingSword:
		case SKILLID_WizardTrance:

			//Priestess 
		case SKILLID_HolyReflection:
		case SKILLID_VirtualLife:
		case SKILLID_RegenerationField:
		case SKILLID_SummonMuspell:
		case SKILLID_Consecration:

			//Assassin 
		case SKILLID_Alas:
		case SKILLID_Inpes:
		case SKILLID_Blind:

			//Shaman 
		case SKILLID_ChasingHunt:
		case SKILLID_AdventMigal:
		case SKILLID_Rainmaker:
		case SKILLID_AdventMidranda:
		case SKILLID_Creed:
			return TRUE;
		}

		return FALSE;
	}
	BOOL SkillData::IsSummonSkill()
	{
		switch (eID)
		{
			//Mechanician
		case SKILLID_MetalGolem:

			//Archer
		case SKILLID_RecallWolverine:

			//Atalanta
		case SKILLID_SummonTiger:

			//Priestess
		case SKILLID_IceElemental:

			//Magician
		case SKILLID_FireElemental:

			//Shaman
		case SKILLID_RecallHestian:
			return TRUE;
		}

		return FALSE;
	}
}