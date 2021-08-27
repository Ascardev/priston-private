#pragma once

#define MISC_DISTANCE	0x1000
#define MISC_DISTANCE_Y	0x8C

class Point2D;
class Point3D;
class Rectangle2D;
class Rectangle3D;
class Matrix4D;
class Matrix4DEx;
class Matrix4DF;
class Vector3DF;

class Point2D
{
public:
	int iX;
	int iY;

	Point2D() : iX(0), iY(0) {}
	Point2D( const Point2D & c ) : iX(c.iX), iY(c.iY) {}
	Point2D( int _iX, int _iY ) : iX(_iX), iY(_iY) {}

	bool				  Inside( const Rectangle2D * psRectangle2D ) const;
	bool				  Inside( const Rectangle2D & sRectangle2D ) const { return Inside( &sRectangle2D ); }
	bool				  Equals( const Point2D * psPoint2D ) const;
	int GetPTDistance(const Point2D & sCompare) const;

	Point2D operator	<<( int i );
	Point2D operator	>>( int i );

	void operator		+= (const Point2D & sOther);
	Point2D operator	+  (const Point2D & sOther) const;
	void operator		-= (const Point2D & sOther);
	Point2D operator	-  (const Point2D & sOther) const;
	void operator		*= (const int i);
	Point2D operator	* (int i) const;
};

class Point3D
{
public:
	int iX;
	int iY;
	int iZ;

	Point3D() : iX(0), iY(0), iZ(0) {}
	Point3D( const Point3D & c ) : iX(c.iX), iY(c.iY), iZ(c.iZ) {}
	Point3D( int _iX, int _iY, int _iZ ) : iX(_iX), iY(_iY), iZ(_iZ) {}

	int					  GetPTDistance( const Point3D & sCompare ) const;
	int					  GetPTDistanceXZ(const Point3D & sCompare) const;
	int					  GetPTDistanceXZ( const Point3D * psCompare, int & a, int & b, int & c ) const;
	int					  GetPTDistanceXZY( const Point3D * psCompare, int & a, int & b, int & c, int & d ) const;

	BOOL				  WithinPTDistance( const Point3D * psCompare, int iDistance, BOOL bFlatY = FALSE ) const;

	int					  GetLength() const;

	Point3D				  GetNormal(Point3D v1);

	void operator		= ( const Point3D & sOther );

	Point3D operator	<<( int i ) const;
	Point3D operator	>>( int i ) const;
	void operator		<<=( int i );
	void operator		>>=( int i );

	bool operator		== (const Point3D & sOther) const;
	bool operator		!= (const Point3D & sOther) const;

	void operator		+= (const Point3D & sOther);
	void operator		-= (const Point3D & sOther);

	void operator		/= (const Point3D & sOther);
	void operator		/= (const int i);
	void operator		*= (const int i);
	void operator		&= (const int i);

	Point3D operator + () const;
	Point3D operator - () const;

	Point3D operator	- (const Point3D & sOther) const;
	Point3D operator	+ (const Point3D & sOther) const;

	Point3D operator	/ (const Point3D & sOther) const;
	Point3D operator	/ (int i) const;
	Point3D operator	* (int i) const;
	Point3D operator	* (Matrix4D &c) const;
	Point3D operator	& (int i) const;

	operator Vector3DF() const;
	operator Matrix4D() const;
};
class Color4D
{
public:

	union
	{
		struct
		{
			int iR;
			int iG;
			int iB;
			int iA;
		};

		int sColor[4];
	};

	Color4D() : iR(255), iG(255), iB(255), iA(255) {}
	Color4D(const Color4D & c) : iR(c.iR), iG(c.iG), iB(c.iB), iA(c.iA) {}
	Color4D(int _iR, int _iG, int _iB) : iR(_iR), iG(_iG), iB(_iB), iA(255) {}
	Color4D(int _iR, int _iG, int _iB, int _iA) : iR(_iR), iG(_iG), iB(_iB), iA(_iA) {}

	void operator		= (const Color4D & sOther);
	Color4D operator	<<(int i) const;
	Color4D operator	>>(int i) const;
	void operator		<<=(int i);
	void operator		>>=(int i);

	bool operator		== (const Color4D & sOther) const;
	bool operator		!= (const Color4D & sOther) const;

	void operator		+= (const Color4D & sOther);
	void operator		-= (const Color4D & sOther);

	void operator		/= (const int i);
	void operator		*= (const int i);

	Color4D operator + () const;
	Color4D operator - () const;

	Color4D operator	- (const Color4D & sOther) const;
	Color4D operator	+ (const Color4D & sOther) const;

	Color4D operator	/ (int i) const;
	Color4D operator	* (int i) const;
};
class Matrix4D
{
public:
	int _11, _12, _13, _14;
	int _21, _22, _23, _24;
	int _31, _32, _33, _34;
	int _41, _42, _43, _44;
	Matrix4D();
	Matrix4D(const Matrix4D & c);
	void operator		= (const Matrix4D & sOther);
	Matrix4D operator	<<(int i) const;
	Matrix4D operator	>>(int i) const;
	void operator		<<=(int i);
	void operator		>>=(int i);
	Matrix4D operator	* (Matrix4D c) const;
	void operator		*= (const Matrix4D c);

	Matrix4D RotateX(int i) const;
	Matrix4D RotateY(int i) const;
	Matrix4D RotateZ(int i) const;

	Matrix4D Invert() const;

	Matrix4D Translate(Point3D s);

	Point3D GetPosition() const;
	Point3D GetPositionSwap() const;

	operator Matrix4DF() const;
};

class Matrix4DF
{
public:
	union
	{
		struct  
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};

	Matrix4DF();
	Matrix4DF(const Matrix4DF & c);
	void operator		= (const Matrix4DF & sOther);
	Matrix4DF operator	* (Matrix4DF c) const;
	void operator		*= (const Matrix4DF c);

	Matrix4DF RotateX(float fSin, float fCos) const;
	Matrix4DF RotateY(float fSin, float fCos) const;
	Matrix4DF RotateZ(float fSin, float fCos) const;

	Matrix4DF RotateX(int i) const;
	Matrix4DF RotateY(int i) const;
	Matrix4DF RotateZ(int i) const;

	Matrix4DF Invert() const;

	Matrix4DF Translate(Vector3DF s);

	operator Matrix4D() const;
	operator Matrix4DEx() const;
};
class Matrix4DEx
{
public:
	int _11, _12, _13, _14;
	int _21, _22, _23, _24;
	int _31, _32, _33, _34;
	int _41, _42, _43, _44;
	Matrix4DEx();
	Matrix4DEx(const Matrix4DEx & c);
	void operator		= (const Matrix4DEx & sOther);
	Matrix4DEx operator	<<(int i) const;
	Matrix4DEx operator	>>(int i) const;
	void operator		<<=(int i);
	void operator		>>=(int i);
	Matrix4DEx operator	* (Matrix4DEx c) const;
	void operator		*= (const Matrix4DEx c);

	Matrix4DEx RotateX(int i) const;
	Matrix4DEx RotateY(int i) const;
	Matrix4DEx RotateZ(int i) const;

	operator Matrix4D() const;
};

class Rectangle2D
{
public:
	int iX;
	int iY;
	int iWidth;
	int iHeight;

	Rectangle2D() : iX(0), iY(0), iWidth(0), iHeight(0) {}
	Rectangle2D( const Rectangle2D & c ) : iX(c.iX), iY(c.iY), iWidth(c.iWidth), iHeight(c.iHeight) {}
	Rectangle2D( int _iX, int _iY ) : iX(_iX), iY(_iY), iWidth(0), iHeight(0) {}
	Rectangle2D( int _iX, int _iY, int _iWidth, int _iHeight ) : iX(_iX), iY(_iY), iWidth(_iWidth), iHeight(_iHeight) {}

	bool				  Inside( const Point2D * psPosition, int iLowX = 0, int iLowY = 0 ) const;
	bool				  Equals( const Rectangle2D * psRectangle2D ) const;
	void				  CopyFrom( const Rectangle2D * psRectangle2D );
	bool				  Overlaps( const Rectangle2D * psRectangle2D ) const;
	bool				  Contains( const Rectangle2D * psRectangle2D ) const;

	Rectangle2D			  operator+( const Rectangle2D & sOther ) const;
	Rectangle2D			& operator+=( const Rectangle2D & sOther );
};

class Rectangle2DF
{
public:
	float fX;
	float fY;
	float fWidth;
	float fHeight;

	Rectangle2DF() : fX(0.0f), fY(0.0f), fWidth(0.0f), fHeight(0.0f) {}
	Rectangle2DF( const Rectangle2DF & c ) { *this = c; }
	Rectangle2DF( float _fX, float _fY ) : fX(_fX), fY(_fY), fWidth(0), fHeight(0) {}
	Rectangle2DF( float _fX, float _fY, float _fWidth, float _fHeight ) : fX(_fX), fY(_fY), fWidth(_fWidth), fHeight(_fHeight) {}
};

class Rectangle3D
{
public:
	int iX;
	int iY;
	int iZ;
	int iWidth;
	int iHeight;
	int iDepth;

	Rectangle3D();
	Rectangle3D( int x, int y, int z, int w, int h, int d ) : iX(x), iY(y), iZ(z), iWidth(w), iHeight(h), iDepth(d) {}

	bool				  Inside( const Point3D * psPosition ) const;
};
class Vector2DF
{
public:
	float fX;
	float fY;
	Vector2DF() : fX(0), fY(0) {};
	Vector2DF(const Vector2DF &c) : fX(c.fX), fY(c.fY) {};
	Vector2DF(float _fX, float _fY) : fX(_fX), fY(_fY) {};
};
class Vector3DF
{
public:
	float fX;
	float fY;
	float fZ;

	Vector3DF() : fX(0), fY(0), fZ(0) {};
	Vector3DF(const Vector3DF &c) : fX(c.fX), fY(c.fY), fZ(c.fZ) {};
	Vector3DF(float _fX, float _fY, float _fZ) : fX(_fX), fY(_fY), fZ(_fZ) {};

	float GetDistance(const Vector3DF & sCompare) const;
	float GetLength() const;

	void operator		= (const Vector3DF & sOther);

	bool operator		== (const Vector3DF & sOther) const;
	bool operator		!= (const Vector3DF & sOther) const;

	void operator		+= (const Vector3DF & sOther);
	void operator		-= (const Vector3DF & sOther);

	void operator		/= (const float f);
	void operator		*= (const float f);

	Vector3DF operator + () const;
	Vector3DF operator - () const;

	Vector3DF operator	- (const Vector3DF & sOther) const;
	Vector3DF operator	+ (const Vector3DF & sOther) const;

	Vector3DF operator	/ (float f) const;
	Vector3DF operator	* (float f) const;
	Vector3DF operator	* (Matrix4D &c) const;

	operator Point3D() const;
};

class Vector4DF
{
public:
	float fX;
	float fY;
	float fZ;
	float fW;

	Vector4DF() : fX( 0 ), fY( 0 ), fZ( 0 ), fW( 0 ) {};

	Vector4DF( float x, float y, float z, float w ) : fX( x ), fY( y ), fZ( z ), fW( w ) {};

	float				Dot( const Vector4DF & c ) const;

	void				Normalize();

	void				Scale( float f );

	void				Negative();

	

	Vector4DF			operator-( const Vector4DF & c ) const;
	Vector4DF			operator+( const Vector4DF & c ) const;
	void				operator=( const Vector4DF & c );
	Vector4DF			operator*( const float c ) const;

	operator Matrix4D() const;
	operator Matrix4DF() const;
};

class TextureRangle2D
{
public:
	float fU0;
	float fV0;
	float fU1;
	float fV1;

	TextureRangle2D() : fU0(0), fV0(0), fU1(1), fV1(1) {}
	TextureRangle2D(float _fU0, float _fV0, float _fU1, float _fV1) :fU0(_fU0), fV0(_fV0), fU1(_fU1), fV1(_fV1) {}
};

Vector4DF D3DMath_QuaternionSlerp(Vector4DF sVectorA, Vector4DF sVectorB, float fAlpha);
Point3D GetMoveLocation(int iX, int iY, int iZ, int iAngX, int iAngY, int iAngZ);
Point3D GetMoveLocation(Point3D sPosition, Point3D sAngle);
Point3D GetRadian3D(int iX, int iY, int iZ, int iAngX, int iAngY, int iAngZ);
Point3D GetRadian3D(Point3D sPosition, Point3D sAngle);