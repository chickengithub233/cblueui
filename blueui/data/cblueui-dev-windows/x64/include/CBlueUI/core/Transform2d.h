
#ifndef CCBLUEUI_TRANS_AFFINE_INCLUDED
#define CCBLUEUI_TRANS_AFFINE_INCLUDED

#include <math.h>
#include "CCoreBasePro.h"

namespace BUI {

const double g_transform_epsilon = 1e-14;

/**
 * @brief 二维变换矩阵(简洁形式)
 *
 */
class UI_EXP Transform2d
{
  public:
	double sx, shy, shx, sy, tx, ty;

	// Identity matrix
	Transform2d();

	// Custom matrix. Usually used in derived classes
	Transform2d(double v0, double v1, double v2, double v3, double v4, double v5);

	// Custom matrix from m[6]
	explicit Transform2d(const double* m);

	// Rectangle to a parallelogram.
	Transform2d(double x1, double y1, double x2, double y2, const double* parl);

	// Parallelogram to a rectangle.
	Transform2d(const double* parl, double x1, double y1, double x2, double y2);

	// Arbitrary parallelogram transformation.
	Transform2d(const double* src, const double* dst);

	//---------------------------------- Parellelogram transformations
	// transform a parallelogram to another one. Src and dst are
	// pointers to arrays of three points (double[6], x1,y1,...) that
	// identify three corners of the parallelograms assuming implicit
	// fourth point. The arguments are arrays of double[6] mapped
	// to x1,y1, x2,y2, x3,y3  where the coordinates are:
	//        *-----------------*
	//       /          (x3,y3)/
	//      /                 /
	//     /(x1,y1)   (x2,y2)/
	//    *-----------------*
	const Transform2d& parl_to_parl(const double* src, const double* dst);

	const Transform2d& rect_to_parl(double x1, double y1, double x2, double y2, const double* parl);

	const Transform2d& parl_to_rect(const double* parl, double x1, double y1, double x2, double y2);


	//------------------------------------------ Operations
	// Reset - load an identity matrix
	const Transform2d& reset();

	// Direct transformations operations
	const Transform2d& translate(double x, double y);
	const Transform2d& rotate(double a);
	const Transform2d& scale(double s);
	const Transform2d& scale(double x, double y);

	// Multiply matrix to another one
	const Transform2d& multiply(const Transform2d& m);

	// Multiply "m" to "this" and assign the result to "this"
	const Transform2d& premultiply(const Transform2d& m);

	// Multiply matrix to inverse of another one
	const Transform2d& multiply_inv(const Transform2d& m);

	// Multiply inverse of "m" to "this" and assign the result to "this"
	const Transform2d& premultiply_inv(const Transform2d& m);

	// Invert matrix. Do not try to invert degenerate matrices,
	// there's no check for validity. If you set scale to 0 and
	// then try to invert matrix, expect unpredictable result.
	const Transform2d& invert();

	// Mirroring around X
	const Transform2d& flip_x();

	// Mirroring around Y
	const Transform2d& flip_y();

	// Multiply the matrix by another one
	const Transform2d& operator*=(const Transform2d& m);

	// Multiply the matrix by inverse of another one
	const Transform2d& operator/=(const Transform2d& m);

	// Multiply the matrix by another one and return
	// the result in a separete matrix.
	Transform2d operator*(const Transform2d& m);

	// Multiply the matrix by inverse of another one
	// and return the result in a separete matrix.
	Transform2d operator/(const Transform2d& m);

	// Calculate and return the inverse matrix
	Transform2d operator~() const;

	// Equal operator with default epsilon
	bool operator==(const Transform2d& m) const;

	// Not Equal operator with default epsilon
	bool operator!=(const Transform2d& m) const;

	//-------------------------------------------- Transformations
	// Direct transformation of x and y
	void transform(double* x, double* y) const;

	// Direct transformation of x and y, 2x2 matrix only, no translation
	void transform_2x2(double* x, double* y) const;

	// Inverse transformation of x and y. It works slower than the
	// direct transformation. For massive operations it's better to
	// invert() the matrix and then use direct transformations.
	void inverse_transform(double* x, double* y) const;

	//-------------------------------------------- Auxiliary
	// Calculate the determinant of matrix
	double determinant() const;

	// Calculate the reciprocal of the determinant
	double determinant_reciprocal() const;

	// Get the average scale (by X and Y).
	// Basically used to calculate the approximation_scale when
	// decomposinting curves into line segments.
	double scale() const;

	// Check to see if the matrix is not degenerate
	bool is_valid(double epsilon = g_transform_epsilon) const;

	// Check to see if it's an identity matrix
	bool is_identity(double epsilon = g_transform_epsilon) const;

	// Check to see if two matrices are equal
	bool is_equal(const Transform2d& m, double epsilon = g_transform_epsilon) const;

	// Determine the major parameters. Use with caution considering
	// possible degenerate cases.
	double rotation() const;
	void translation(double* dx, double* dy) const;
	void scaling(double* x, double* y) const;
	void scaling_abs(double* x, double* y) const;
};

//====================================================trans_affine_rotation
// Rotation matrix. sin() and cos() are calculated twice for the same angle.
// There's no harm because the performance of sin()/cos() is very good on all
// modern processors. Besides, this operation is not going to be invoked too
// often.
class UI_EXP Transform2dRotation : public Transform2d
{
  public:
	Transform2dRotation(double a);
};

//====================================================trans_affine_scaling
// Scaling matrix. x, y - scale coefficients by X and Y respectively
class UI_EXP Transform2dScaling : public Transform2d
{
  public:
	Transform2dScaling(double x, double y);
	Transform2dScaling(double s);
};

//================================================trans_affine_translation
// Translation matrix
class UI_EXP Transform2dTranslation : public Transform2d
{
  public:
	Transform2dTranslation(double x, double y);
};

//====================================================trans_affine_skewing
// Sckewing (shear) matrix
class UI_EXP Transform2dSkewing : public Transform2d
{
  public:
	Transform2dSkewing(double x, double y);
};

//===============================================trans_affine_line_segment
// Rotate, Scale and Translate, associating 0...dist with line segment
// x1,y1,x2,y2
class UI_EXP Transform2dLineSegment : public Transform2d
{
  public:
	Transform2dLineSegment(double x1, double y1, double x2, double y2, double dist);
};

//============================================trans_affine_reflection_unit
// Reflection matrix. Reflect coordinates across the line through
// the origin containing the unit vector (ux, uy).
// Contributed by John Horigan
class UI_EXP Transform2dReflectionUnit : public Transform2d
{
  public:
	Transform2dReflectionUnit(double ux, double uy);
};

//=================================================trans_affine_reflection
// Reflection matrix. Reflect coordinates across the line through
// the origin at the angle a or containing the non-unit vector (x, y).
// Contributed by John Horigan
class UI_EXP Transform2dReflection : public Transform2dReflectionUnit
{
  public:
	Transform2dReflection(double a);

	Transform2dReflection(double x, double y);
};


}
#endif
