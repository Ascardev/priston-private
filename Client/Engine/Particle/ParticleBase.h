#pragma once

enum EParticleVisualType
{
	PARTICLEVISUALTYPE_None,
	PARTICLEVISUALTYPE_Billboard,
	PARTICLEVISUALTYPE_BillboardRotation,
	PARTICLEVISUALTYPE_BillboardHorizontal,
	PARTICLEVISUALTYPE_BillboardHorizontalRotation,
	PARTICLEVISUALTYPE_BillboardVertical,
	PARTICLEVISUALTYPE_BillboardVerticalRotation,
};

enum EParticleType
{
	PARTICLETYPE_None,
	PARTICLETYPE_Free,
	PARTICLETYPE_Follow,
};

enum EParticleModifierGroupType;

namespace PARTICLE
{
	class ModifierGroup;

	class Particle
	{
		friend class ModifierGroup;
		friend class Emitter;
		friend class Factory;
		friend class System;
		friend class Event;

	public:
		struct Int
		{
			Int() : low(0), high(0), value(0) {}
			Int(Int &c) { low = c.low; high = c.high; value = c.value; }
			Int(int v) : low(v), high(v), value(v) {}
			Int(int l, int h) : low(l), high(h), value(0) {}

			void Birth() { value = RandomI(low, high); }
			Int operator <<(const int i) { Int r; r.low = low << i; r.high = high << i; r.value = value << i; return r; }

			int low;
			int high;
			int value;
		};

		struct Dbl
		{
			Dbl() : low(0), high(0), value(0) {}
			Dbl(Dbl & c) { low = c.low; high = c.high; value = c.value; }
			Dbl(double v) : low(v), high(v), value(v) {}
			Dbl(double l, double h) : low(l), high(h), value(0) {}

			void Birth() { value = RandomD(low, high); }
			Dbl operator * (const double f) { Dbl r; r.low = low * f; r.high = high * f; r.value = value * f; return r; }

			double low;
			double high;
			double value;
		};

		struct Color
		{
			void Birth() { a.Birth(); r.Birth(); g.Birth(); b.Birth(); }

			Int a;
			Int r;
			Int g;
			Int b;
		};

		struct Size
		{
			Size() : bWH(FALSE) {}
			Size(Size & c) { bWH = c.bWH; s = c.s; w = c.w; h = c.h; }

			void Birth() { if (bWH) { w.Birth(); h.Birth(); } else { s.Birth(); } }
			int GetW() { return bWH ? w.value : s.value; }
			int GetH() { return bWH ? h.value : s.value; }

			BOOL bWH;

			Int s;
			Int w;
			Int h;
		};

		struct Point
		{
			Point() : x(0), y(0), z(0) {}

			void Birth() { x.Birth(); y.Birth(); z.Birth(); }

			void operator += (const Point &pos) { x.value += pos.x.value; y.value += pos.y.value; z.value += pos.z.value; }
			Point operator * (const double f) { Point pos; pos.x.value = int(x.value * f); pos.y.value = int(y.value * f); pos.z.value = int(z.value * f); return pos; }
			Point operator / (const double f) { Point pos; pos.x.value = int(x.value / f); pos.y.value = int(y.value / f); pos.z.value = int(z.value / f); return pos; }

			Int x;
			Int y;
			Int z;
		};

		struct Rotation
		{
			Rotation() : p(0),y(0),r(0) {}
			void Birth() { p.Birth(); y.Birth(); r.Birth(); }

			void operator += (const Rotation &rot) { p.value += rot.p.value; y.value += rot.y.value; r.value += rot.r.value; }
			Rotation operator * (const double f) { Rotation rot; rot.p.value = p.value * f; rot.y.value = y.value * f; rot.r.value = r.value * f; return rot; }
			Dbl p;
			Dbl y;
			Dbl r;
		};

		struct Time
		{
			void Birth() { t.Birth(); }
			double Get() { return t.value; }
			void Set(double f) { t.value = f; }

			void operator = (const Time & p) { t.low = p.t.low; t.high = p.t.high; t.value = p.t.value; }
			void operator = (const double f) { t.low = f; t.high = f; t.value = f; }
			Dbl t;
		};
	public:
		Particle();
		Particle(Particle & c);

		virtual ~Particle();
		virtual Particle *Clone();
		virtual void Birth();
		virtual BOOL Update(double fTime);
		virtual void Loop(double fBegin, double fEnd);
		virtual void Modify();
		virtual void Render();

		void SetActive(BOOL b) { m_bActive = b; }

		void SetName(std::string _str) { m_strName = _str; }
		void SetNameType(std::string _str) { m_strNameType = _str; }

		void SetOwner(ENGINE::ObjectOwner *pNewOwner) { m_pOwner = pNewOwner->Clone(); }

		void SetVelocity(Point sNewVelocity) { m_sVelocity = sNewVelocity; }

		void SetColor(Color sNewColor) { m_sColor = sNewColor; }
		void SetSize(Size sNewSize) { m_sSize = sNewSize; }

		BOOL IsActive() { return m_bActive; }

		std::string GetName() { return m_strName; }
		std::string GetNameType() { return m_strNameType; }

		EParticleType GetType() { return m_eType; }
		EParticleVisualType GetVisualType() { return m_eVisualType; }

		EBlendType GetSourceBlendMode() { return m_eSourceBlendMode; }

		void AddParticleModifierGroup(ModifierGroup *pcParticleModifierGroup);
		ModifierGroup * GetParticleModifierGroup(EParticleModifierGroupType eType);
	protected:
		virtual void Apply(double fTime);
		virtual void ApplyVelocity(Point &sVelo, double fTime);
		virtual void ApplyAngularVelocity(Rotation &sAnguVelo, double fTime);
	protected:
		BOOL m_bActive = FALSE;

		std::string m_strName;
		std::string m_strNameType;

		EParticleType m_eType;
		EParticleVisualType m_eVisualType;

		EBlendType m_eSourceBlendMode;
		
		UINT m_uTextureID;
		Color m_sColor;
		Size m_sSize;

		Point m_sPosition;
		Point m_sVelocity;

		Rotation m_sRotation;
		Rotation m_sAngularVelocity;

		Time m_sCurLifeTime;
		Time m_sMaxLifeTime;

		BOOL m_bLoop;

		double m_fLoopAt, m_fLoopTime;

		std::vector<Event*> m_vParticleEvents;
		std::vector<ModifierGroup *> m_vParticleModifierGroups;

		ENGINE::ObjectOwner *m_pOwner;
	};
}
