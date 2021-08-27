#include "StdAfx.h"
#include "point.h"

bool Point2D::Inside( const Rectangle2D * psRectangle2D ) const
{
	if( (iX >= psRectangle2D->iX) && (iX < (psRectangle2D->iX + psRectangle2D->iWidth)) )
		if( (iY >= psRectangle2D->iY) && (iY < (psRectangle2D->iY + psRectangle2D->iHeight)) )
			return true;

	return false;
}

bool Point2D::Equals( const Point2D * psPoint2D ) const
{
	if( (iX == psPoint2D->iX) && (iY == psPoint2D->iY) )
		return true;

	return false;
}
int Point2D::GetPTDistance(const Point2D & sCompare) const
{
	int iXD = (sCompare.iX - iX) >> 8;
	int iYD = (sCompare.iY - iY) >> 8;

	int iXDM = iXD * iXD;
	int iYDM = iYD * iYD;

	return (iXD + iYDM);
}
Point2D Point2D::operator<<( int i )
{
	Point2D s;
	s.iX = iX << i;
	s.iY = iY << i;

	return s;
}

Point2D Point2D::operator>>( int i )
{
	Point2D s;
	s.iX = iX >> i;
	s.iY = iY >> i;

	return s;
}
void Point2D::operator+=(const Point2D & sOther)
{
	this->iX += sOther.iX;
	this->iY += sOther.iY;
}
Point2D Point2D::operator+(const Point2D & sOther) const
{
	Point2D sReturn = *this;
	sReturn += sOther;
	return sReturn;
}
void Point2D::operator-=(const Point2D & sOther)
{
	this->iX -= sOther.iX;
	this->iY -= sOther.iY;
}
Point2D Point2D::operator-(const Point2D & sOther) const
{
	Point2D sReturn = *this;
	sReturn -= sOther;
	return sReturn;
}
void Point2D::operator*=(int i)
{
	iX *= i;
	iY *= i;
}
Point2D Point2D::operator*(int i) const
{
	Point2D s;
	s.iX = iX * i;
	s.iY = iY * i;

	return s;
}

int Point3D::GetPTDistance( const Point3D & sCompare ) const
{
	int iXD = (sCompare.iX - iX) >> 8;
	int iZD = (sCompare.iZ - iZ) >> 8;
	int iYD = (sCompare.iY - iY) >> 8;

	iXD *= iXD;
	iZD *= iZD;
	iYD *= iYD;

	return (iXD + iZD + iYD);
}

int Point3D::GetPTDistanceXZ( const Point3D * psCompare, int & a, int & b, int & c ) const
{
	int iXD = (psCompare->iX - iX) >> 8;
	int iZD = (psCompare->iZ - iZ) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;

	a = (iXDM + iZDM);
	b = abs( iXD );
	c = abs( iZD );

	return a;
}
int Point3D::GetPTDistanceXZ(const Point3D & sCompare) const
{
	int iXD = (sCompare.iX - iX) >> 8;
	int iZD = (sCompare.iZ - iZ) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;

	return (iXDM + iZDM);
}

int Point3D::GetPTDistanceXZY( const Point3D * psCompare, int & a, int & b, int & c, int & d ) const
{
	int iXD = (psCompare->iX - iX) >> 8;
	int iZD = (psCompare->iZ - iZ) >> 8;
	int iYD = (psCompare->iY - iY) >> 8;

	int iXDM = iXD * iXD;
	int iZDM = iZD * iZD;
	int iYDM = iYD * iYD;

	a = (iXDM + iZDM + iYDM);
	b = abs( iXD );
	c = abs( iZD );
	d = abs( iYD );

	return a;
}

BOOL Point3D::WithinPTDistance( const Point3D * psCompare, int iDistance, BOOL bFlatY ) const
{
	int iDistanceA, iDistanceB, iDistanceC, iDistanceD;
	GetPTDistanceXZY( psCompare, iDistanceA, iDistanceB, iDistanceC, iDistanceD );

	if( bFlatY )
	{
		if( (iDistanceA < (iDistance * iDistance)) && (iDistanceB < MISC_DISTANCE) && (iDistanceC < MISC_DISTANCE) && (iDistanceD < (MISC_DISTANCE_Y >> 1)) )
			return TRUE;
	}
	else
	{
		if( (iDistanceA < (iDistance * iDistance)) && (iDistanceB < MISC_DISTANCE) && (iDistanceC < MISC_DISTANCE) && (iDistanceD < MISC_DISTANCE) )
			return TRUE;
	}

	return FALSE;
}

int Point3D::GetLength() const
{
	return (int)sqrt((float)((iX * iX) + (iY * iY) + (iZ * iZ)));
}

Point3D Point3D::GetNormal( Point3D v1 )
{
	const Point3D & v0 = *this;

	Point3D s;

	//Cross product
	s.iX = (v0.iY * v1.iZ) - (v0.iZ * v1.iY);
	s.iY = (v0.iZ * v1.iX) - (v0.iX * v1.iZ);
	s.iZ = (v0.iX * v1.iY) - (v0.iY * v1.iX);

	//Dot
	int i = s.GetLength();
	i += (i == 0 ? 1 : 0);


	//Normalize
	s.iX /= i;
	s.iY /= i;
	s.iZ /= i;

	return s;
}

void Point3D::operator=( const Point3D & sOther )
{
	this->iX	= sOther.iX;
	this->iY	= sOther.iY;
	this->iZ	= sOther.iZ;
}

Point3D Point3D::operator<<( int i ) const
{
	Point3D s;
	s.iX = iX << i;
	s.iY = iY << i;
	s.iZ = iZ << i;

	return s;
}

Point3D Point3D::operator>>( int i ) const
{
	Point3D s;
	s.iX = iX >> i;
	s.iY = iY >> i;
	s.iZ = iZ >> i;

	return s;
}

void Point3D::operator<<=( int i )
{
	iX <<= i;
	iY <<= i;
	iZ <<= i;
}

void Point3D::operator>>=( int i )
{
	iX >>= i;
	iY >>= i;
	iZ >>= i;
}

bool Point3D::operator==( const Point3D & sOther ) const
{
	if( this->iX == sOther.iX )
		if( this->iY == sOther.iY )
			if( this->iZ == sOther.iZ )
				return true;

	return false;
}

bool Point3D::operator!=( const Point3D & sOther ) const
{
	return !(*this == sOther);
}

void Point3D::operator+=( const Point3D & sOther )
{
	this->iX += sOther.iX;
	this->iY += sOther.iY;
	this->iZ += sOther.iZ;
}

void Point3D::operator-=( const Point3D & sOther )
{
	this->iX -= sOther.iX;
	this->iY -= sOther.iY;
	this->iZ -= sOther.iZ;
}

void Point3D::operator/=(const Point3D & sOther)
{
	this->iX /= sOther.iX;
	this->iY /= sOther.iY;
	this->iZ /= sOther.iZ;
}
void Point3D::operator/=(int i)
{
	this->iX /= i;
	this->iY /= i;
	this->iZ /= i;
}
void Point3D::operator*=(int i)
{
	iX *= i;
	iY *= i;
	iZ *= i;
}
void Point3D::operator&=(int i)
{
	iX &= i;
	iY &= i;
	iZ &= i;
}
Point3D Point3D::operator-() const
{
	Point3D sReturn = *this;

	sReturn.iX = -(sReturn.iX);
	sReturn.iY = -(sReturn.iY);
	sReturn.iZ = -(sReturn.iZ);
	return sReturn;
}

Point3D Point3D::operator+() const
{
	Point3D sReturn = *this;

	sReturn.iX = +(sReturn.iX);
	sReturn.iY = +(sReturn.iY);
	sReturn.iZ = +(sReturn.iZ);
	return sReturn;
}

Point3D Point3D::operator-( const Point3D & sOther ) const
{
	Point3D sReturn = *this;
	sReturn -= sOther;
	return sReturn;
}

Point3D Point3D::operator+( const Point3D & sOther ) const
{
	Point3D sReturn = *this;
	sReturn += sOther;
	return sReturn;
}

Point3D Point3D::operator/(const Point3D & sOther) const
{
	Point3D sReturn = *this;
	sReturn /= sOther;
	return sReturn;
}

Point3D Point3D::operator/(int i) const
{
	Point3D s;
	s.iX = iX / i;
	s.iY = iY / i;
	s.iZ = iZ / i;

	return s;
}

Point3D Point3D::operator*(int i) const
{
	Point3D s;
	s.iX = iX * i;
	s.iY = iY * i;
	s.iZ = iZ * i;

	return s;
}
Point3D Point3D::operator*(Matrix4D &c) const
{
	auto iXD = iX * c._11 + iY * c._21 + iZ * c._31;
	auto iYD = iX * c._12 + iY * c._22 + iZ * c._32;
	auto iZD = iX * c._13 + iY * c._23 + iZ * c._33;

	return Point3D(iXD, iYD, iZD) >> 8;
}
Point3D Point3D::operator&(int i) const
{
	Point3D s;
	s.iX = iX & i;
	s.iY = iY & i;
	s.iZ = iZ & i;

	return s;
}
Point3D::operator Vector3DF() const
{
	return Vector3DF((float)iX, (float)iY, (float)iZ);
}
Point3D::operator Matrix4D() const
{
	Matrix4D s;

	s._11 = iX; s._12 = 0; s._13 = 0; s._14 = 0;
	s._21 = 0; s._22 = iY; s._23 = 0; s._24 = 0;
	s._31 = 0; s._32 = 0; s._33 = iZ; s._34 = 0;
	s._41 = 0; s._42 = 0; s._43 = 0; s._44 = 256;

	return s;
}

void Color4D::operator=(const Color4D & sOther)
{
	this->iR = sOther.iR;
	this->iG = sOther.iG;
	this->iB = sOther.iB;
	this->iA = sOther.iA;
}

Color4D Color4D::operator<<(int i) const
{
	Color4D s;
	s.iR = iR << i;
	s.iG = iG << i;
	s.iB = iB << i;
	s.iA = iA << i;

	return s;
}

Color4D Color4D::operator>>(int i) const
{
	Color4D s;
	s.iR = iR >> i;
	s.iG = iG >> i;
	s.iB = iB >> i;
	s.iA = iA >> i;

	return s;
}

void Color4D::operator<<=(int i)
{
	iR <<= i;
	iG <<= i;
	iB <<= i;
	iA <<= i;
}

void Color4D::operator>>=(int i)
{
	iR >>= i;
	iG >>= i;
	iB >>= i;
	iA >>= i;
}

bool Color4D::operator==(const Color4D & sOther) const
{
	if (this->iR == sOther.iR)
		if (this->iG == sOther.iG)
			if (this->iB == sOther.iB)
				if (this->iA == sOther.iA)
					return true;

	return false;
}
bool Color4D::operator!=(const Color4D & sOther) const
{
	return !(*this == sOther);
}

void Color4D::operator+=(const Color4D & sOther)
{
	this->iR += sOther.iR;
	this->iG += sOther.iG;
	this->iB += sOther.iB;
	this->iA += sOther.iA;
}
void Color4D::operator-=(const Color4D & sOther)
{
	this->iR -= sOther.iR;
	this->iG -= sOther.iG;
	this->iB -= sOther.iB;
	this->iA -= sOther.iA;
}
void Color4D::operator/=(int i)
{
	this->iR /= i;
	this->iG /= i;
	this->iB /= i;
	this->iA /= i;
}
void Color4D::operator*=(int i)
{
	iR *= i;
	iG *= i;
	iB *= i;
	iA *= i;
}
Color4D Color4D::operator+() const
{
	Color4D sReturn = *this;

	sReturn.iR = +(sReturn.iR);
	sReturn.iG = +(sReturn.iG);
	sReturn.iB = +(sReturn.iB);
	sReturn.iA = +(sReturn.iA);
	return sReturn;
}
Color4D Color4D::operator-() const
{
	Color4D sReturn = *this;

	sReturn.iR = -(sReturn.iR);
	sReturn.iG = -(sReturn.iG);
	sReturn.iB = -(sReturn.iB);
	sReturn.iA = -(sReturn.iA);
	return sReturn;
}

Color4D Color4D::operator-(const Color4D & sOther) const
{
	Color4D sReturn = *this;
	sReturn -= sOther;
	return sReturn;
}

Color4D Color4D::operator+(const Color4D & sOther) const
{
	Color4D sReturn = *this;
	sReturn += sOther;
	return sReturn;
}

Color4D Color4D::operator/(int i) const
{
	Color4D s;
	s.iR = iR / i;
	s.iG = iG / i;
	s.iB = iB / i;
	s.iA = iA / i;

	return s;
}

Color4D Color4D::operator*(int i) const
{
	Color4D s;
	s.iR = iR * i;
	s.iG = iG * i;
	s.iB = iB * i;
	s.iA = iA * i;

	return s;
}
Matrix4D::Matrix4D()
{
	_11 = 256; _12 = 0; _13 = 0; _14 = 0;
	_21 = 0; _22 = 256; _23 = 0; _24 = 0;
	_31 = 0; _32 = 0; _33 = 256; _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 256;
}
Matrix4D::Matrix4D(const Matrix4D & c)
{
	_11 = c._11; _12 = c._12; _13 = c._13; _14 = c._14;
	_21 = c._21; _22 = c._22; _23 = c._23; _24 = c._24;
	_31 = c._31; _32 = c._32; _33 = c._33; _34 = c._34;
	_41 = c._41; _42 = c._42; _43 = c._43; _44 = c._44;
}
void Matrix4D::operator=(const Matrix4D & sOther)
{
	_11 = sOther._11; _12 = sOther._12; _13 = sOther._13; _14 = sOther._14;
	_21 = sOther._21; _22 = sOther._22; _23 = sOther._23; _24 = sOther._24;
	_31 = sOther._31; _32 = sOther._32; _33 = sOther._33; _34 = sOther._34;
	_41 = sOther._41; _42 = sOther._42; _43 = sOther._43; _44 = sOther._44;
}
Matrix4D Matrix4D::operator<<(int i) const
{
	Matrix4D s;

	s._11 = _11 << i; s._12 = _12 << i; s._13 = _13 << i; s._14 = _14 << i;
	s._21 = _21 << i; s._22 = _22 << i; s._23 = _23 << i; s._24 = _24 << i;
	s._31 = _31 << i; s._32 = _32 << i; s._33 = _33 << i; s._34 = _34 << i;
	s._41 = _41 << i; s._42 = _42 << i; s._43 = _43 << i; s._44 = _44 << i;

	return s;
}

Matrix4D Matrix4D::operator>>(int i) const
{
	Matrix4D s;

	s._11 = _11 >> i; s._12 = _12 >> i; s._13 = _13 >> i; s._14 = _14 >> i;
	s._21 = _21 >> i; s._22 = _22 >> i; s._23 = _23 >> i; s._24 = _24 >> i;
	s._31 = _31 >> i; s._32 = _32 >> i; s._33 = _33 >> i; s._34 = _34 >> i;
	s._41 = _41 >> i; s._42 = _42 >> i; s._43 = _43 >> i; s._44 = _44 >> i;

	return s;
}

void Matrix4D::operator<<=(int i)
{
	_11 <<= i; _12 <<= i; _13 <<= i; _14 <<= i;
	_21 <<= i; _22 <<= i; _23 <<= i; _24 <<= i;
	_31 <<= i; _32 <<= i; _33 <<= i; _34 <<= i;
	_41 <<= i; _42 <<= i; _43 <<= i; _44 <<= i;
}

void Matrix4D::operator>>=(int i)
{
	_11 >>= i; _12 >>= i; _13 >>= i; _14 >>= i;
	_21 >>= i; _22 >>= i; _23 >>= i; _24 >>= i;
	_31 >>= i; _32 >>= i; _33 >>= i; _34 >>= i;
	_41 >>= i; _42 >>= i; _43 >>= i; _44 >>= i;
}
Matrix4D Matrix4D::operator*(Matrix4D c) const
{
	Matrix4D s;

	int *sc = (int *)this;
	int *sd = (int *)&c;
	int ss[16] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				ss[4 * j + i] += (sc[4 * j + k] * sd[4 * k + i]) >> 8;
			}
		}
	}
	
	CopyMemory(&s, ss, sizeof(Matrix4D));

	return s;
}
void Matrix4D::operator*=(const Matrix4D c)
{
	int *sc = (int *)this;
	int *sd = (int *)&c;
	int ss[16] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				ss[4 * j + i] += (sc[4 * j + k] * sd[4 * k + i]) >> 8;
			}
		}
	}

	CopyMemory(this, ss, sizeof(Matrix4D));
}
Matrix4D Matrix4D::RotateX(int i) const
{
	auto sCos = GetCos[i] >> 8;
	auto sSin = GetSin[i] >> 8;

	Matrix4D s = *this;

	s._22 = +sCos; s._23 = +sSin;
	s._32 = -sSin; s._33 = +sCos;

	return s;
}
Matrix4D Matrix4D::RotateY(int i) const
{
	auto sCos = GetCos[i] >> 8;
	auto sSin = GetSin[i] >> 8;

	Matrix4D s = *this;

	s._11 = +sCos; s._13 = -sSin;
	s._31 = +sSin; s._33 = +sCos;

	return s;
}
Matrix4D Matrix4D::RotateZ(int i) const
{
	auto sCos = GetCos[i] >> 8;
	auto sSin = GetSin[i] >> 8;

	Matrix4D s = *this;

	s._11 = +sCos; s._12 = +sSin;
	s._21 = -sSin; s._22 = +sCos;

	return s;
}
Matrix4D Matrix4D::Invert() const
{
	Matrix4D sRet, s = *this;

	if (abs(s._14) > 1 || abs(s._24) > 1 || abs(s._34) > 1 || abs(s._44 - 256) > 1) return sRet;

	int iInv = ((s._11 * ((s._22 * s._33 - s._23 * s._32) >> 8)) - (s._12 * ((s._21 * s._33 - s._23 * s._31) >> 8)) + (s._13 * ((s._21 * s._32 - s._22 * s._31) >> 8))) >> 8;

	iInv = iInv ? (256 << 8) / iInv : iInv;

	sRet._11 = +(iInv * ((s._22 * s._33 - s._23 * s._32) >> 8) >> 8);
	sRet._12 = -(iInv * ((s._12 * s._33 - s._13 * s._32) >> 8) >> 8);
	sRet._13 = +(iInv * ((s._12 * s._23 - s._13 * s._22) >> 8) >> 8);
	sRet._14 = 0;

	sRet._21 = -(iInv * ((s._21 * s._33 - s._23 * s._31) >> 8) >> 8);
	sRet._22 = +(iInv * ((s._11 * s._33 - s._13 * s._31) >> 8) >> 8);
	sRet._23 = -(iInv * ((s._11 * s._23 - s._13 * s._21) >> 8) >> 8);
	sRet._24 = 0;

	sRet._31 = +(iInv * ((s._21 * s._32 - s._22 * s._31) >> 8) >> 8);
	sRet._32 = -(iInv * ((s._11 * s._32 - s._12 * s._31) >> 8) >> 8);
	sRet._33 = +(iInv * ((s._11 * s._22 - s._12 * s._21) >> 8) >> 8);
	sRet._34 = 0;

	sRet._41 = -((s._41 * sRet._11 + s._42 * sRet._21 + s._43 * sRet._31) >> 8);
	sRet._42 = -((s._41 * sRet._12 + s._42 * sRet._22 + s._43 * sRet._32) >> 8);
	sRet._43 = -((s._41 * sRet._13 + s._42 * sRet._23 + s._43 * sRet._33) >> 8);
	sRet._44 = 256;

	return sRet;
}
Matrix4D Matrix4D::Translate(Point3D s)
{
	Matrix4D sRet = *this;

	sRet._41 = s.iX << 8; sRet._42 = s.iY << 8; sRet._43 = s.iZ << 8;

	return sRet;
}
Point3D Matrix4D::GetPosition() const
{
	return Point3D(_41, _42, _43);
}
Point3D Matrix4D::GetPositionSwap() const
{
	return Point3D(_41, _43, _42);
}
Matrix4D::operator Matrix4DF() const
{
	Matrix4DF s;

	s._11 = (float)(_11) / 256.0f; s._12 = (float)(_12) / 256.0f; s._13 = (float)(_13) / 256.0f; s._14 = (float)(_14) / 256.0f;
	s._21 = (float)(_21) / 256.0f; s._22 = (float)(_22) / 256.0f; s._23 = (float)(_23) / 256.0f; s._24 = (float)(_24) / 256.0f;
	s._31 = (float)(_31) / 256.0f; s._32 = (float)(_32) / 256.0f; s._33 = (float)(_33) / 256.0f; s._34 = (float)(_34) / 256.0f;
	s._41 = (float)(_41) / 256.0f; s._42 = (float)(_42) / 256.0f; s._43 = (float)(_43) / 256.0f; s._44 = (float)(_44) / 256.0f;

	return s;
}
Matrix4DF::Matrix4DF()
{
	_11 = 1.0f; _12 = 0; _13 = 0; _14 = 0;
	_21 = 0; _22 = 1.0f; _23 = 0; _24 = 0;
	_31 = 0; _32 = 0; _33 = 1.0f; _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 1.0f;
}
Matrix4DF::Matrix4DF(const Matrix4DF & c)
{
	_11 = c._11; _12 = c._12; _13 = c._13; _14 = c._14;
	_21 = c._21; _22 = c._22; _23 = c._23; _24 = c._24;
	_31 = c._31; _32 = c._32; _33 = c._33; _34 = c._34;
	_41 = c._41; _42 = c._42; _43 = c._43; _44 = c._44;
}
void Matrix4DF::operator=(const Matrix4DF & sOther)
{
	_11 = sOther._11; _12 = sOther._12; _13 = sOther._13; _14 = sOther._14;
	_21 = sOther._21; _22 = sOther._22; _23 = sOther._23; _24 = sOther._24;
	_31 = sOther._31; _32 = sOther._32; _33 = sOther._33; _34 = sOther._34;
	_41 = sOther._41; _42 = sOther._42; _43 = sOther._43; _44 = sOther._44;
}
Matrix4DF Matrix4DF::operator*(Matrix4DF c) const
{
	Matrix4DF s;

	float *sc = (float *)this;
	float *sd = (float *)&c;
	float ss[16] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				ss[4 * j + i] += (sc[4 * j + k] * sd[4 * k + i]);
			}
		}
	}

	CopyMemory(&s, ss, sizeof(Matrix4DF));

	return s;
}
void Matrix4DF::operator*=(const Matrix4DF c)
{
	float *sc = (float *)this;
	float *sd = (float *)&c;
	float ss[16] = { 0 };

	for (WORD i = 0; i < 4; i++)
	{
		for (WORD j = 0; j < 4; j++)
		{
			for (WORD k = 0; k < 4; k++)
			{
				ss[4 * j + i] += (sc[4 * j + k] * sd[4 * k + i]);
			}
		}
	}

	CopyMemory(this, ss, sizeof(Matrix4DF));

}
Matrix4DF Matrix4DF::RotateX(float fSin, float fCos) const
{
	Matrix4DF s = *this;

	s._22 = +fCos; s._23 = +fSin;
	s._32 = -fSin; s._33 = +fCos;

	return s;
}
Matrix4DF Matrix4DF::RotateY(float fSin, float fCos) const
{
	Matrix4DF s = *this;

	s._11 = +fCos; s._13 = -fSin;
	s._31 = +fSin; s._33 = +fCos;

	return s;
}
Matrix4DF Matrix4DF::RotateZ(float fSin, float fCos) const
{
	Matrix4DF s = *this;

	s._11 = +fCos; s._12 = +fSin;
	s._21 = -fSin; s._22 = +fCos;

	return s;
}

Matrix4DF Matrix4DF::RotateX(int i) const
{
	Matrix4DF s = *this;

	float fCos = (float)dbGetCos[i];
	float fSin = (float)dbGetSin[i];

	s._22 = +fCos; s._23 = +fSin;
	s._32 = -fSin; s._33 = +fCos;

	return s;
}
Matrix4DF Matrix4DF::RotateY(int i) const
{
	Matrix4DF s = *this;

	float fCos = (float)dbGetCos[i];
	float fSin = (float)dbGetSin[i];

	s._11 = +fCos; s._13 = -fSin;
	s._31 = +fSin; s._33 = +fCos;

	return s;
}
Matrix4DF Matrix4DF::RotateZ(int i) const
{
	Matrix4DF s = *this;

	float fCos = (float)dbGetCos[i];
	float fSin = (float)dbGetSin[i];

	s._11 = +fCos; s._12 = +fSin;
	s._21 = -fSin; s._22 = +fCos;

	return s;
}

Matrix4DF Matrix4DF::Invert() const
{
	Matrix4DF sRet, s = *this;

	if (fabs(s._14) > .001f || fabs(s._24) > .001f || fabs(s._34) > .001f || fabs(s._44 - 1.0f) > .001f) return sRet;

	float fInv = 1.0f / (s._11 * (s._22 * s._33 - s._23 * s._32) - s._12 * (s._21 * s._33 - s._23 * s._31) + s._13 * (s._21 * s._32 - s._22 * s._31));

	sRet._11 = +fInv * (s._22 * s._33 - s._23 * s._32);
	sRet._12 = -fInv * (s._12 * s._33 - s._13 * s._32);
	sRet._13 = +fInv * (s._12 * s._23 - s._13 * s._22);
	sRet._14 = 0.0f;

	sRet._21 = -fInv * (s._21 * s._33 - s._23 * s._31);
	sRet._22 = +fInv * (s._11 * s._33 - s._13 * s._31);
	sRet._23 = -fInv * (s._11 * s._23 - s._13 * s._21);
	sRet._24 = 0.0f;

	sRet._31 = +fInv * (s._21 * s._32 - s._22 * s._31);
	sRet._32 = -fInv * (s._11 * s._32 - s._12 * s._31);
	sRet._33 = +fInv * (s._11 * s._22 - s._12 * s._21);
	sRet._34 = 0.0f;

	sRet._41 = -(s._41 * sRet._11 + s._42 * sRet._21 + s._43 * sRet._31);
	sRet._42 = -(s._41 * sRet._12 + s._42 * sRet._22 + s._43 * sRet._32);
	sRet._43 = -(s._41 * sRet._13 + s._42 * sRet._23 + s._43 * sRet._33);
	sRet._44 = 1.0f;

	return sRet;
}
Matrix4DF Matrix4DF::Translate(Vector3DF s)
{
	Matrix4DF sRet = *this;

	sRet._41 = s.fX; sRet._42 = s.fY; sRet._43 = s.fZ;

	return sRet;
}
Matrix4DF::operator Matrix4D() const
{
	Matrix4D s;

	s._11 = (int)(_11 * 256.f); s._12 = (int)(_12 * 256.f); s._13 = (int)(_13 * 256.f); s._14 = (int)(_14 * 256.f);
	s._21 = (int)(_21 * 256.f); s._22 = (int)(_22 * 256.f); s._23 = (int)(_23 * 256.f); s._24 = (int)(_24 * 256.f);
	s._31 = (int)(_31 * 256.f); s._32 = (int)(_32 * 256.f); s._33 = (int)(_33 * 256.f); s._34 = (int)(_34 * 256.f);
	s._41 = (int)(_41 * 256.f); s._42 = (int)(_42 * 256.f); s._43 = (int)(_43 * 256.f); s._44 = (int)(_44 * 256.f);

	return s;
}
Matrix4DF::operator Matrix4DEx() const
{
	Matrix4DEx s;

	s._11 = (int)(_11 * 32768.f); s._12 = (int)(_12 * 32768.f); s._13 = (int)(_13 * 32768.f); s._14 = (int)(_14 * 32768.f);
	s._21 = (int)(_21 * 32768.f); s._22 = (int)(_22 * 32768.f); s._23 = (int)(_23 * 32768.f); s._24 = (int)(_24 * 32768.f);
	s._31 = (int)(_31 * 32768.f); s._32 = (int)(_32 * 32768.f); s._33 = (int)(_33 * 32768.f); s._34 = (int)(_34 * 32768.f);
	s._41 = (int)(_41 * 32768.f); s._42 = (int)(_42 * 32768.f); s._43 = (int)(_43 * 32768.f); s._44 = (int)(_44 * 32768.f);

	return s;
}

Matrix4DEx::Matrix4DEx()
{
	_11 = 32768; _12 = 0; _13 = 0; _14 = 0;
	_21 = 0; _22 = 32768; _23 = 0; _24 = 0;
	_31 = 0; _32 = 0; _33 = 32768; _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 32768;
}
Matrix4DEx::Matrix4DEx(const Matrix4DEx & c)
{
	_11 = c._11; _12 = c._12; _13 = c._13; _14 = c._14;
	_21 = c._21; _22 = c._22; _23 = c._23; _24 = c._24;
	_31 = c._31; _32 = c._32; _33 = c._33; _34 = c._34;
	_41 = c._41; _42 = c._42; _43 = c._43; _44 = c._44;
}
void Matrix4DEx::operator=(const Matrix4DEx & sOther)
{
	_11 = sOther._11; _12 = sOther._12; _13 = sOther._13; _14 = sOther._14;
	_21 = sOther._21; _22 = sOther._22; _23 = sOther._23; _24 = sOther._24;
	_31 = sOther._31; _32 = sOther._32; _33 = sOther._33; _34 = sOther._34;
	_41 = sOther._41; _42 = sOther._42; _43 = sOther._43; _44 = sOther._44;
}
Matrix4DEx Matrix4DEx::operator<<(int i) const
{
	Matrix4DEx s;

	s._11 = _11 << i; s._12 = _12 << i; s._13 = _13 << i; s._14 = _14 << i;
	s._21 = _21 << i; s._22 = _22 << i; s._23 = _23 << i; s._24 = _24 << i;
	s._31 = _31 << i; s._32 = _32 << i; s._33 = _33 << i; s._34 = _34 << i;
	s._41 = _41 << i; s._42 = _42 << i; s._43 = _43 << i; s._44 = _44 << i;

	return s;
}

Matrix4DEx Matrix4DEx::operator>>(int i) const
{
	Matrix4DEx s;

	s._11 = _11 >> i; s._12 = _12 >> i; s._13 = _13 >> i; s._14 = _14 >> i;
	s._21 = _21 >> i; s._22 = _22 >> i; s._23 = _23 >> i; s._24 = _24 >> i;
	s._31 = _31 >> i; s._32 = _32 >> i; s._33 = _33 >> i; s._34 = _34 >> i;
	s._41 = _41 >> i; s._42 = _42 >> i; s._43 = _43 >> i; s._44 = _44 >> i;

	return s;
}

void Matrix4DEx::operator<<=(int i)
{
	_11 <<= i; _12 <<= i; _13 <<= i; _14 <<= i;
	_21 <<= i; _22 <<= i; _23 <<= i; _24 <<= i;
	_31 <<= i; _32 <<= i; _33 <<= i; _34 <<= i;
	_41 <<= i; _42 <<= i; _43 <<= i; _44 <<= i;
}

void Matrix4DEx::operator>>=(int i)
{
	_11 >>= i; _12 >>= i; _13 >>= i; _14 >>= i;
	_21 >>= i; _22 >>= i; _23 >>= i; _24 >>= i;
	_31 >>= i; _32 >>= i; _33 >>= i; _34 >>= i;
	_41 >>= i; _42 >>= i; _43 >>= i; _44 >>= i;
}
Matrix4DEx Matrix4DEx::operator*(Matrix4DEx c) const
{
	Matrix4DEx s;

	int *sc = (int *)this;
	int *sd = (int *)&c;
	int ss[16] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				ss[4 * j + i] += (sc[4 * j + k] * sd[4 * k + i]) >> 15;
			}
		}
	}

	CopyMemory(&s, ss, sizeof(Matrix4DEx));

	return s;
}
void Matrix4DEx::operator*=(const Matrix4DEx c)
{
	int *sc = (int *)this;
	int *sd = (int *)&c;
	int ss[16] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				ss[4 * j + i] += (sc[4 * j + k] * sd[4 * k + i]) >> 15;
			}
		}
	}

	CopyMemory(this, ss, sizeof(Matrix4DEx));
}
Matrix4DEx Matrix4DEx::RotateX(int i) const
{
	auto sCos = sdGetCos[i];
	auto sSin = sdGetSin[i];

	Matrix4DEx s = *this;

	s._22 = +sCos; s._23 = +sSin;
	s._32 = -sSin; s._33 = +sCos;

	return s;
}
Matrix4DEx Matrix4DEx::RotateY(int i) const
{
	auto sCos = sdGetCos[i];
	auto sSin = sdGetSin[i];

	Matrix4DEx s = *this;

	s._11 = +sCos; s._13 = -sSin;
	s._31 = +sSin; s._33 = +sCos;

	return s;
}
Matrix4DEx Matrix4DEx::RotateZ(int i) const
{
	auto sCos = sdGetCos[i];
	auto sSin = sdGetSin[i];

	Matrix4DEx s = *this;

	s._11 = +sCos; s._12 = +sSin;
	s._21 = -sSin; s._22 = +sCos;

	return s;
}
Matrix4DEx::operator Matrix4D() const
{
	Matrix4D s;

	s._11 = _11 >> 4; s._12 = _12 >> 4; s._13 = _13 >> 4; s._14 = _14 >> 4;
	s._21 = _21 >> 4; s._22 = _22 >> 4; s._23 = _23 >> 4; s._24 = _24 >> 4;
	s._31 = _31 >> 4; s._32 = _32 >> 4; s._33 = _33 >> 4; s._34 = _34 >> 4;
	s._41 = _41 >> 4; s._42 = _42 >> 4; s._43 = _43 >> 4; s._44 = _44 >> 4;

	return s;
}

bool Rectangle2D::Inside( const Point2D * psPosition, int iLowX, int iLowY ) const
{
	if( ((psPosition->iX - iLowX) >= iX) && ((psPosition->iX - iLowX) < (iX + iWidth)) )
		if( ((psPosition->iY - iLowY) >= iY) && ((psPosition->iY - iLowY) < (iY + iHeight)) )
			return true;

	return false;
}

bool Rectangle2D::Equals( const Rectangle2D * psRectangle2D ) const
{
	if( (iX == psRectangle2D->iX) && (iY == psRectangle2D->iY) )
		if( (iWidth == psRectangle2D->iWidth) && (iHeight == psRectangle2D->iHeight) )
			return true;

	return false;
}

void Rectangle2D::CopyFrom( const Rectangle2D * psRectangle2D )
{
	iX = psRectangle2D->iX;
	iY = psRectangle2D->iY;
	iWidth = psRectangle2D->iWidth;
	iHeight = psRectangle2D->iHeight;
}

bool Rectangle2D::Overlaps( const Rectangle2D * psRectangle2D ) const
{
	int iX11 = iX;
	int iX12 = iX + iWidth;
	int iY11 = iY;
	int iY12 = iY + iHeight;
	int iX21 = psRectangle2D->iX;
	int iX22 = psRectangle2D->iX + psRectangle2D->iWidth;
	int iY21 = psRectangle2D->iY;
	int iY22 = psRectangle2D->iY + psRectangle2D->iHeight;

	bool noOverlap = iX11 >= iX22 ||
		iX21 >= iX12 ||
		iY11 >= iY22 ||
		iY21 >= iY12;

	return !noOverlap;
}

bool Rectangle2D::Contains( const Rectangle2D * psRectangle2D ) const
{
	if( (psRectangle2D->iX >= iX) && (psRectangle2D->iX + psRectangle2D->iWidth) <= (iX + iWidth) )
		if( (psRectangle2D->iY >= iY) && (psRectangle2D->iY + psRectangle2D->iHeight) <= (iY + iHeight) )
			return true;

	return false;
}

Rectangle2D Rectangle2D::operator+( const Rectangle2D & sOther ) const
{
	Rectangle2D sReturn;

	sReturn.iX			= iX + sOther.iX;
	sReturn.iY			= iY + sOther.iY;
	sReturn.iWidth		= high( iWidth, sOther.iWidth );
	sReturn.iHeight		= high( iHeight, sOther.iHeight );

	return sReturn;
}

Rectangle2D & Rectangle2D::operator+=( const Rectangle2D & sOther )
{
	iX			+= sOther.iX;
	iY			+= sOther.iY;
	iWidth		+= sOther.iWidth;
	iHeight		+= sOther.iHeight;

	return *this;
}

bool Rectangle3D::Inside( const Point3D * psPosition ) const
{
	if( (psPosition->iX >= iX) && (psPosition->iX < (iX + iWidth)) )
		if( (psPosition->iY >= iY) && (psPosition->iY < (iY + iHeight)) )
			if( (psPosition->iZ >= iZ) && (psPosition->iZ < (iZ + iDepth)) )
				return true;

	return false;
}

float Vector3DF::GetDistance(const Vector3DF & sCompare) const
{
	float fXD = (sCompare.fX - fX) / 256.f;
	float fZD = (sCompare.fZ - fZ) / 256.f;
	float fYD = (sCompare.fY - fY) / 256.f;

	fXD *= fXD;
	fZD *= fZD;
	fYD *= fYD;

	return (fXD + fZD + fYD);
}

float Vector3DF::GetLength() const
{
	float f = (float)sqrt((float)((fX * fX) + (fY * fY) + (fZ * fZ)));

	return f == 0 ? 1.0f : f;
}

void Vector3DF::operator=(const Vector3DF & sOther)
{
	this->fX = sOther.fX;
	this->fY = sOther.fY;
	this->fZ = sOther.fZ;
}

bool Vector3DF::operator==(const Vector3DF & sOther) const
{
	if (this->fX == sOther.fX)
		if (this->fY == sOther.fY)
			if (this->fZ == sOther.fZ)
				return true;

	return false;
}

bool Vector3DF::operator!=(const Vector3DF & sOther) const
{
	return !(*this == sOther);
}

void Vector3DF::operator+=(const Vector3DF & sOther)
{
	this->fX += sOther.fX;
	this->fY += sOther.fY;
	this->fZ += sOther.fZ;
}

void Vector3DF::operator-=(const Vector3DF & sOther)
{
	this->fX -= sOther.fX;
	this->fY -= sOther.fY;
	this->fZ -= sOther.fZ;
}
void Vector3DF::operator/=(float f)
{
	this->fX /= f;
	this->fY /= f;
	this->fZ /= f;
}
void Vector3DF::operator*=(float f)
{
	fX *= f;
	fY *= f;
	fZ *= f;
}
Vector3DF Vector3DF::operator-() const
{
	Vector3DF sReturn = *this;

	sReturn.fX = -(sReturn.fX);
	sReturn.fY = -(sReturn.fY);
	sReturn.fZ = -(sReturn.fZ);
	return sReturn;
}
Vector3DF Vector3DF::operator+() const
{
	Vector3DF sReturn = *this;

	sReturn.fX = +(sReturn.fX);
	sReturn.fY = +(sReturn.fY);
	sReturn.fZ = +(sReturn.fZ);
	return sReturn;
}

Vector3DF Vector3DF::operator-(const Vector3DF & sOther) const
{
	Vector3DF sReturn = *this;
	sReturn -= sOther;
	return sReturn;
}

Vector3DF Vector3DF::operator+(const Vector3DF & sOther) const
{
	Vector3DF sReturn = *this;
	sReturn += sOther;
	return sReturn;
}

Vector3DF Vector3DF::operator/(float f) const
{
	Vector3DF s;
	s.fX = fX / f;
	s.fY = fY / f;
	s.fZ = fZ / f;

	return s;
}

Vector3DF Vector3DF::operator*(float f) const
{
	Vector3DF s;
	s.fX = fX * f;
	s.fY = fY * f;
	s.fZ = fZ * f;

	return s;
}
Vector3DF Vector3DF::operator*(Matrix4D &c) const
{
	auto fXD = fX * (float)c._11 + fY * (float)c._21 + fZ * (float)c._31;
	auto fYD = fX * (float)c._12 + fY * (float)c._22 + fZ * (float)c._32;
	auto fZD = fX * (float)c._13 + fY * (float)c._23 + fZ * (float)c._33;

	return Vector3DF(fXD, fYD, fZD);
}
Vector3DF::operator Point3D() const
{
	return Point3D((int)fX, (int)fY, (int)fZ);
}

float Vector4DF::Dot( const Vector4DF & c ) const
{
	float fReturn = fX * c.fX;
	fReturn += fY * c.fY;
	fReturn += fZ * c.fZ;
	fReturn += fW * c.fW;

	return fReturn;
}

void Vector4DF::Normalize()
{
	float f = (float)sqrt( (fX * fX) + (fY * fY) + (fZ * fZ) + (fW * fW) );

	float inverse = 1.0f / f;

	if ( inverse != 0.0f )
	{
		fX *= inverse;
		fY *= inverse;
		fZ *= inverse;
		fW *= inverse;
	}
}

void Vector4DF::Scale( float f )
{
	fX *= f;
	fY *= f;
	fZ *= f;
	fW *= f;
}

void Vector4DF::Negative()
{
	fX = -fX;
	fY = -fY;
	fZ = -fZ;
	fW = -fW;
}

Vector4DF Vector4DF::operator-( const Vector4DF & c ) const
{
	Vector4DF s;

	s.fX = fX - c.fX;
	s.fY = fY - c.fY;
	s.fZ = fZ - c.fZ;
	s.fW = fW - c.fW;

	return s;
}

Vector4DF Vector4DF::operator+( const Vector4DF & c ) const
{
	Vector4DF s;

	s.fX = fX + c.fX;
	s.fY = fY + c.fY;
	s.fZ = fZ + c.fZ;
	s.fW = fW + c.fW;

	return s;
}

void Vector4DF::operator=( const Vector4DF & c )
{
	this->fX = c.fX;
	this->fY = c.fY;
	this->fZ = c.fZ;
	this->fW = c.fW;
}

Vector4DF Vector4DF::operator*( const float c ) const
{
	Vector4DF s;

	s.fX = fX * c;
	s.fY = fY * c;
	s.fZ = fZ * c;
	s.fW = fW * c;

	return s;
}

Vector4DF::operator Matrix4D() const
{
	int xx = (int)(fX * fX * 256); int yy = (int)(fY * fY * 256); int zz = (int)(fZ * fZ * 256);
	int xy = (int)(fX * fY * 256); int xz = (int)(fX * fZ * 256); int yz = (int)(fY * fZ * 256);
	int wx = (int)(fW * fX * 256); int wy = (int)(fW * fY * 256); int wz = (int)(fW * fZ * 256);

	Matrix4D s;

	s._11 = 256 - 2 * (yy + zz); s._12 = 2 * (xy - wz); s._13 = 2 * (xz + wy); s._14 = 0;
	s._21 = 2 * (xy + wz); s._22 = 256 - 2 * (xx + zz); s._23 = 2 * (yz - wx); s._24 = 0;
	s._31 = 2 * (xz - wy); s._32 = 2 * (yz + wx); s._33 = 256 - 2 * (xx + yy); s._34 = 0;
	s._41 = s._42 = s._43 = 0; s._44 = 256;

	return s;
}

Vector4DF::operator Matrix4DF() const
{
	float xx = fX * fX; float yy = fY * fY; float zz = fZ * fZ;
	float xy = fX * fY; float xz = fX * fZ; float yz = fY * fZ;
	float wx = fW * fX; float wy = fW * fY; float wz = fW * fZ;

	Matrix4DF s;

	s._11 = 1 - 2 * (yy + zz); s._12 = 2 * (xy - wz); s._13 = 2 * (xz + wy); s._14 = 0;
	s._21 = 2 * (xy + wz); s._22 = 1 - 2 * (xx + zz); s._23 = 2 * (yz - wx); s._24 = 0;
	s._31 = 2 * (xz - wy); s._32 = 2 * (yz + wx); s._33 = 1 - 2 * (xx + yy); s._34 = 0;
	s._41 = s._42 = s._43 = 0; s._44 = 1;

	return s;
}
Point3D GetMoveLocation(int iX, int iY, int iZ, int iAngX, int iAngY, int iAngZ)
{
	iAngX &= 4095;
	iAngY &= 4095;
	iAngZ &= 4095;

	int iSinX = sdGetSin[iAngX] >> 2;
	int iSinY = sdGetSin[iAngY] >> 2;
	int iSinZ = sdGetSin[iAngZ] >> 2;
	int iCosX = sdGetCos[iAngX] >> 2;
	int iCosY = sdGetCos[iAngY] >> 2;
	int iCosZ = sdGetCos[iAngZ] >> 2;

	int iRotS = (iX * iCosZ - iY * iSinZ) >> 13;
	int iRatS = (iX * iSinZ + iY * iCosZ) >> 13;

	int iRatY = (iRatS * iCosX - iZ * iSinX) >> 13;
	int iRetS = (iRatS * iSinX + iZ * iCosX) >> 13;

	int iRatX = (iRetS * iSinY + iRotS * iCosY) >> 13;
	int iRatZ = (iRetS * iCosY - iRotS * iSinY) >> 13;

	return Point3D(iRatX, iRatY, iRatZ);
}
Point3D GetMoveLocation(Point3D sPosition, Point3D sAngle)
{
	return GetMoveLocation(sPosition.iX, sPosition.iY, sPosition.iZ, sAngle.iX, sAngle.iY, sAngle.iZ);
}
Point3D GetRadian3D(int iX, int iY, int iZ, int iAngX, int iAngY, int iAngZ)
{
	int iFlag = 0;

	if (iX > iAngX)
	{
		iFlag |= 0x0001;
		iX ^= iAngX;
		iAngX ^= iX;
		iX ^= iAngX;
	}

	if (iZ > iAngZ)
	{
		iFlag |= 0x0002;
		iZ ^= iAngZ;
		iAngZ ^= iZ;
		iZ ^= iAngZ;
	}

	iAngX -= (iX - 1);
	iAngZ -= (iZ - 1);

	if (iAngZ > iAngX)
	{
		iFlag |= 0x0004;
		iAngZ ^= iAngX;
		iAngX ^= iAngZ;
		iAngZ ^= iAngX;
	}

	iAngZ <<= 8;
	iAngZ /= iAngX;

	int iMapY = (iAngZ * ANGLE_45);
	iMapY >>= 8;

	iAngZ = zDCos(iMapY) >> 8;

	(!iAngZ) ? iAngZ = 1 : iAngZ = iAngZ;

	iZ = ((iAngX << 8) / iAngZ);

	iAngX ^= iAngX;

	if (iY > iAngY)
	{
		iAngX |= 0x0001;
		iY ^= iAngY;
		iAngY ^= iY;
		iY ^= iAngY;
	}

	iAngZ = iAngY - (iY - 1);

	if (iAngZ > iZ)
	{
		iAngX |= 0x0002;
		iAngZ ^= iZ;
		iZ ^= iAngZ;
		iAngZ ^= iZ;
	}

	switch (iFlag)
	{
	case 0:iMapY = ANGLE_90 - iMapY; break;
	case 1:iMapY = ANGLE_270 + iMapY; break;
	case 2:iMapY = ANGLE_90 + iMapY; break;
	case 3:iMapY = ANGLE_270 - iMapY; break;
	case 5:iMapY = ANGLE_360 - iMapY; break;
	case 6:iMapY = ANGLE_180 - iMapY; break;
	case 7:iMapY = ANGLE_180 + iMapY; break;
	}

	iAngZ <<= 8;
	iAngZ /= iZ;
	int iMapX = (iAngZ * ANGLE_45);
	iMapX >>= 8;

	switch (iAngX)
	{
	case 0:iMapX = (ANGLE_360 - iMapX); break;
	case 2:iMapX = (ANGLE_270 + iMapX); break;
	case 3:iMapX = (ANGLE_90 - iMapX); break;
	}

	return Point3D(iMapX, iMapY, 0);
}
Point3D GetRadian3D(Point3D sPosition, Point3D sAngle)
{
	return GetRadian3D(sPosition.iX, sPosition.iY, sPosition.iZ, sAngle.iX, sAngle.iY, sAngle.iZ);
}
