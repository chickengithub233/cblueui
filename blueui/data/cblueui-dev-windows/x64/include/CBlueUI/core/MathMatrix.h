#ifndef CBLUEUI_UTILSMATRIX_CORE_PRO_BLXDY_INC_H_
#define CBLUEUI_UTILSMATRIX_CORE_PRO_BLXDY_INC_H_

#include <stdio.h>
#include <math.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/CCoreBasePro.h"
#define EPSILON 0.000001

class UI_EXP Point3
{
  public:
	Point3() { x = y = z = 0; }

	Point3(double x_, double y_, double z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	~Point3() {}

	const Point3& operator=(const Point3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Point3 operator+(const Point3& v) const { return Point3(x + v.x, y + v.y, z + v.z); }

	Point3 operator-(const Point3& v) const { return Point3(x - v.x, y - v.y, z - v.z); }

	Point3 operator*(double k) const { return Point3(x * k, y * k, z * k); }

	Point3 operator/(double k) const { return Point3(x / k, y / k, z / k); }

	const Point3& operator+=(const Point3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	const Point3& operator-=(const Point3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	const Point3& operator*=(double k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	const Point3& operator/=(double k)
	{
		x /= k;
		y /= k;
		z /= k;
		return *this;
	}

	static double Dot(const Point3& v1, const Point3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

	static Point3 Cross(const Point3& v1, const Point3& v2)
	{
		Point3 v;
		v.x = -(v1.y * v2.z - v1.z * v2.y);
		v.y = -(v1.z * v2.x - v1.x * v2.z);
		v.z = -(v1.x * v2.y - v1.y * v2.x);
		return v;
	}

	// 三角形表面法向量
	static Point3 SurfaceNVector(const Point3& p1, const Point3& p2, const Point3& p3) { return Cross(Point3(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z), Point3(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z)); }

	static void SurfacePlaneEquation(const Point3& p1, const Point3& p2, const Point3& p3, double& a, double& b, double& c, double& d)
	{
		// A*x + B*y + C*z + D = 0 欧几里得空间平面方程
		a = ((p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y));

		b = ((p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z));

		c = ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));

		d = (0 - (a * p1.x + b * p1.y + c * p1.z));
	}

	// 向量cos角度值
	static double VectorCos(const Point3& v1, const Point3& v2)
	{
		double len = v1.Length() * v2.Length();
		if (len != 0.0)
		{
			double num = Dot(v1, v2);
			return num / len;
		}
		return 1;
	}

	Point3 Normalized()
	{
		Point3 v;
		double length = Length();
		if (length > 0)
		{
			double k = 1.0 / length;
			v.x      = (k * x);
			v.y      = (k * y);
			v.z      = (k * z);
		}
		return v;
	}

	double Length() const
	{
		double num = x * x + y * y + z * z;
		return ::sqrt(num);
	}

  public:
	double x, y, z;
};

class UI_EXP Matrix4x4
{
  public:
	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
	double m30, m31, m32, m33;

  public:
	Matrix4x4() { Normal(); }

	Matrix4x4(double v11, double v12, double v13, double v14, double v21, double v22, double v23, double v24, double v31, double v32, double v33, double v34, double v41, double v42, double v43, double v44)
	{
		m00 = v11;
		m01 = v12;
		m02 = v13;
		m03 = v14;
		m10 = v21;
		m11 = v22;
		m12 = v23;
		m13 = v24;
		m20 = v31;
		m21 = v32;
		m22 = v33;
		m23 = v34;
		m30 = v41;
		m31 = v42;
		m32 = v43;
		m33 = v44;
	}

	// 单位化
	void Normal()
	{
		m00 = 1;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 1;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 1;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 1;
	}

	const Matrix4x4& operator=(const Matrix4x4& c)
	{
		m00 = c.m00;
		m01 = c.m01;
		m02 = c.m02;
		m03 = c.m03;
		m10 = c.m10;
		m11 = c.m11;
		m12 = c.m12;
		m13 = c.m13;
		m20 = c.m20;
		m21 = c.m21;
		m22 = c.m22;
		m23 = c.m23;
		m30 = c.m30;
		m31 = c.m31;
		m32 = c.m32;
		m33 = c.m33;
		return *this;
	}

	Matrix4x4 operator*(const Matrix4x4& c)
	{
		double m[4][4];

		m[0][0] = m00 * c.m00 + m01 * c.m10 + m02 * c.m20 + m03 * c.m30;
		m[0][1] = m00 * c.m01 + m01 * c.m11 + m02 * c.m21 + m03 * c.m31;
		m[0][2] = m00 * c.m02 + m01 * c.m12 + m02 * c.m22 + m03 * c.m32;
		m[0][3] = m00 * c.m03 + m01 * c.m13 + m02 * c.m23 + m03 * c.m33;
		m[1][0] = m10 * c.m00 + m11 * c.m10 + m12 * c.m20 + m13 * c.m30;
		m[1][1] = m10 * c.m01 + m11 * c.m11 + m12 * c.m21 + m13 * c.m31;
		m[1][2] = m10 * c.m02 + m11 * c.m12 + m12 * c.m22 + m13 * c.m32;
		m[1][3] = m10 * c.m03 + m11 * c.m13 + m12 * c.m23 + m13 * c.m33;
		m[2][0] = m20 * c.m00 + m21 * c.m10 + m22 * c.m20 + m23 * c.m30;
		m[2][1] = m20 * c.m01 + m21 * c.m11 + m22 * c.m21 + m23 * c.m31;
		m[2][2] = m20 * c.m02 + m21 * c.m12 + m22 * c.m22 + m23 * c.m32;
		m[2][3] = m20 * c.m03 + m21 * c.m13 + m22 * c.m23 + m23 * c.m33;
		m[3][0] = m30 * c.m00 + m31 * c.m10 + m32 * c.m20 + m33 * c.m30;
		m[3][1] = m30 * c.m01 + m31 * c.m11 + m32 * c.m21 + m33 * c.m31;
		m[3][2] = m30 * c.m02 + m31 * c.m12 + m32 * c.m22 + m33 * c.m32;
		m[3][3] = m30 * c.m03 + m31 * c.m13 + m32 * c.m23 + m33 * c.m33;

		return Matrix4x4(m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
	}

	Matrix4x4 Mul(double c) const
	{
		Matrix4x4 t;
		t.m00 = m00 * c;
		t.m01 = m01 * c;
		t.m02 = m02 * c;
		t.m03 = m03 * c;
		t.m10 = m10 * c;
		t.m11 = m11 * c;
		t.m12 = m12 * c;
		t.m13 = m13 * c;
		t.m20 = m20 * c;
		t.m21 = m21 * c;
		t.m22 = m22 * c;
		t.m23 = m23 * c;
		t.m30 = m30 * c;
		t.m31 = m31 * c;
		t.m32 = m32 * c;
		t.m33 = m33 * c;
		return t;
	}

	static Matrix4x4 Lookat(const Point3& eye, const Point3& center, const Point3& up)
	{
		Point3 f = (center - eye).Normalized();
		Point3 s = Point3::Cross(up, f).Normalized();
		Point3 u = Point3::Cross(f, s).Normalized();

		Matrix4x4 m(s.x, s.y, s.z, -Point3::Dot(s, eye), u.x, u.y, u.z, -Point3::Dot(u, eye), -f.x, -f.y, -f.z, Point3::Dot(f, eye), 0, 0, 0, 1);
		return m;
	}

	static Matrix4x4 Ortho(double left, double right, double bottom, double top, double zNear, double zFar)
	{

		Matrix4x4 Result;
		Result.m00 = static_cast<double>(2) / (right - left);
		Result.m11 = static_cast<double>(2) / (top - bottom);
		Result.m22 = -static_cast<double>(2) / (zFar - zNear);
		Result.m03 = -(right + left) / (right - left);
		Result.m13 = -(top + bottom) / (top - bottom);
		Result.m23 = -(zFar + zNear) / (zFar - zNear);
		return Result;
	}

	// 比例变换
	static Matrix4x4 Scale(double sx, double sy, double sz)
	{
		Matrix4x4 t(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
		return t;
	}

	// 绕X旋转 转角的方向满足右手螺旋法则：大拇指指向旋转轴正向，四指弯曲的方向为转角方向
	static Matrix4x4 RotateX(double angle)
	{
		double cosT = cos(angle);
		double sinT = sin(angle);
		Matrix4x4 t(1, 0, 0, 0, 0, cosT, -sinT, 0, 0, sinT, cosT, 0, 0, 0, 0, 1);
		return t;
	}

	// 旋转
	static Matrix4x4 RotateY(double angle)
	{
		double cosT = cos(angle);
		double sinT = sin(angle);
		Matrix4x4 t(cosT, 0, sinT, 0, 0, 1, 0, 0, -sinT, 0, cosT, 0, 0, 0, 0, 1);
		return t;
	}

	// 旋转
	static Matrix4x4 RotateZ(double angle)
	{
		double cosT = cos(angle);
		double sinT = sin(angle);
		Matrix4x4 t(cosT, -sinT, 0, 0, sinT, cosT, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		return t;
	}

	// 绕指定轴旋转
	static Matrix4x4 Rotate(const Matrix4x4& m, double angle, double x, double y, double z)
	{
		double const a = angle;
		double const c = cos(a);
		double const s = sin(a);

		double sq = sqrt(x * x + y * y + z * z);
		if (sq != 0)
		{
			x /= sq;
			y /= sq;
			z /= sq;
		}

		double temp[3];
		temp[0] = (1 - c) * x;
		temp[1] = (1 - c) * y;
		temp[2] = (1 - c) * z;

		double Rotate[3][3];
		Rotate[0][0] = c + temp[0] * x;
		Rotate[0][1] = temp[0] * y + s * z;
		Rotate[0][2] = temp[0] * z - s * y;

		Rotate[1][0] = temp[1] * x - s * z;
		Rotate[1][1] = c + temp[1] * y;
		Rotate[1][2] = temp[1] * z + s * x;

		Rotate[2][0] = temp[2] * x + s * y;
		Rotate[2][1] = temp[2] * y - s * x;
		Rotate[2][2] = c + temp[2] * z;

		Matrix4x4 Result;
		Result.m00 = m.m00 * Rotate[0][0] + m.m01 * Rotate[0][1] + m.m02 * Rotate[0][2];
		Result.m10 = m.m10 * Rotate[0][0] + m.m11 * Rotate[0][1] + m.m12 * Rotate[0][2];
		Result.m20 = m.m20 * Rotate[0][0] + m.m21 * Rotate[0][1] + m.m22 * Rotate[0][2];
		Result.m30 = m.m30 * Rotate[0][0] + m.m31 * Rotate[0][1] + m.m32 * Rotate[0][2];

		Result.m01 = m.m00 * Rotate[1][0] + m.m01 * Rotate[1][1] + m.m02 * Rotate[1][2];
		Result.m11 = m.m10 * Rotate[1][0] + m.m11 * Rotate[1][1] + m.m12 * Rotate[1][2];
		Result.m21 = m.m20 * Rotate[1][0] + m.m21 * Rotate[1][1] + m.m22 * Rotate[1][2];
		Result.m31 = m.m30 * Rotate[1][0] + m.m31 * Rotate[1][1] + m.m32 * Rotate[1][2];

		Result.m02 = m.m00 * Rotate[2][0] + m.m01 * Rotate[2][1] + m.m02 * Rotate[2][2];
		Result.m12 = m.m10 * Rotate[2][0] + m.m11 * Rotate[2][1] + m.m12 * Rotate[2][2];
		Result.m22 = m.m20 * Rotate[2][0] + m.m21 * Rotate[2][1] + m.m22 * Rotate[2][2];
		Result.m32 = m.m30 * Rotate[2][0] + m.m31 * Rotate[2][1] + m.m32 * Rotate[2][2];

		Result.m03 = m.m03;
		Result.m13 = m.m13;
		Result.m23 = m.m23;
		Result.m33 = m.m33;

		return Result;
	}

	// 反射变换
	//  X对称
	static Matrix4x4 MirrorX()
	{
		Matrix4x4 t(1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1);
		return t;
	}

	static Matrix4x4 MirrorY()
	{
		Matrix4x4 t(-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1);
		return t;
	}

	// 基于XoY平面反射
	static Matrix4x4 MirrorXOY()
	{
		Matrix4x4 t(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1);
		return t;
	}

	static Matrix4x4 MirrorYOZ()
	{
		Matrix4x4 t(-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		return t;
	}

	Matrix4x4 MirrorXOZ()
	{
		Matrix4x4 t(1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		t = (*this) * t;
		return t;
	}

	// 平移
	static Matrix4x4 Translate(double dx, double dy, double dz)
	{
		Matrix4x4 t(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, dx, dy, dz, 1);
		return t;
	}

	// 转置
	Matrix4x4 Transposition()
	{
		Matrix4x4 t = *this;
		double temp = 0.0;

		temp  = t.m10;
		t.m10 = t.m01;
		t.m01 = temp;

		temp  = t.m20;
		t.m20 = t.m02;
		t.m02 = temp;

		temp  = t.m30;
		t.m30 = t.m03;
		t.m03 = temp;

		temp  = t.m21;
		t.m21 = t.m12;
		t.m12 = temp;

		temp  = t.m31;
		t.m31 = t.m13;
		t.m13 = temp;

		temp  = t.m32;
		t.m32 = t.m23;
		t.m23 = temp;

		return t;
	}

	// 正交投影 XOY
	static Matrix4x4 ProjectionXoY()
	{
		Matrix4x4 t(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
		return t;
	}

	static Matrix4x4 ProjectionXoZ()
	{
		Matrix4x4 t(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		return t;
	}

	static Matrix4x4 ProjectionYoZ()
	{
		Matrix4x4 t(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		return t;
	}

	inline double Determinant() const
	{
		// 矩阵的行列式
		return (m00 * (m11 * m22 - m10 * m21) - m01 * (m10 * m22 - m10 * m20) + m02 * (m10 * m21 - m11 * m20));
	}

	// 逆矩阵
	Matrix4x4 Inverse() const
	{
		double det = Determinant();
		double _r11, _r12, _r13, _r14;
		double _r21, _r22, _r23, _r24;
		double _r31, _r32, _r33, _r34;
		double _r41, _r42, _r43, _r44;
		if (det <= EPSILON)
		{
			_r11 = 0;
			_r12 = 0;
			_r13 = 0;
			_r14 = 0;
			_r21 = 0;
			_r22 = 0;
			_r23 = 0;
			_r24 = 0;
			_r31 = 0;
			_r32 = 0;
			_r33 = 0;
			_r34 = 0;
			_r41 = 0;
			_r42 = 0;
			_r43 = 0;
			_r44 = 0;
		}
		else
		{
			_r11 = (m11 * m22 - m12 * m21) / det;
			_r12 = -(m01 * m22 - m02 * m21) / det;
			_r13 = (m01 * m12 - m02 * m11) / det;
			_r14 = 0.0;


			_r21 = -(m10 * m22 - m12 * m20) / det;
			_r22 = (m00 * m22 - m02 * m20) / det;
			_r23 = -(m00 * m12 - m02 * m10) / det;
			_r24 = 0.0;

			_r31 = (m10 * m21 - m11 * m20) / det;
			_r32 = -(m00 * m21 - m01 * m20) / det;
			_r33 = (m00 * m11 - m01 * m10) / det;
			_r34 = 0.0;

			_r41 = -(m30 * _r11 + m31 * _r21 + m32 * _r31) / det;
			_r42 = -(m30 * _r12 + m31 * _r22 + m32 * _r32) / det;
			_r43 = -(m30 * _r13 + m31 * _r23 + m32 * _r33) / det;
			_r44 = 1.0;
		}
		return Matrix4x4(_r11, _r12, _r13, _r14, _r21, _r22, _r23, _r24, _r31, _r32, _r33, _r34, _r41, _r42, _r43, _r44);
	}

	/**
	 * @brief 坐标转换，矩阵*向量坐标 = 结果向量坐标  A* p0 = p1
	 * | m00 m01 m02 m03|   |x0|    |x|
	 * | m10 m11 m12 m13|   |y0|    |y|
	 * | m20 m21 m22 m23| * |z0| =  |z|
	 * | m30 m31 m32 m33|   | 1|    |1|
	 */
	void Transform3D(double* x, double* y, double* z) const
	{
		double x0 = *x, y0 = *y, z0 = *z;
		double rx = 0, ry = 0, rz = 0;

		rx = x0 * m00 + y0 * m01 + z0 * m02 + m03;
		ry = x0 * m10 + y0 * m11 + z0 * m12 + m13;
		rz = x0 * m20 + y0 * m21 + z0 * m22 + m23;

		*x = rx;
		*y = ry;
		*z = rz;
		return;
	}
};



#endif
