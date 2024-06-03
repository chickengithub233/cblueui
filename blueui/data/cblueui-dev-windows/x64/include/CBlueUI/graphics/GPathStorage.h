#ifndef CBLUEUI_CPATHSTORAGE_H_INCLUDED_
#define CBLUEUI_CPATHSTORAGE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "core/CCoreBasePro.h"
#include "core/CGeometryStruct.h"
#include "cstring/String.h"
#include "cstring/StringA.h"
#include "GColor.h"

namespace BUI {

typedef struct Arrow
{
	double d1, d2, d3, d4;

} ArrowHead, ArrowTail;

struct BoundRect
{
	double left;
	double top;
	double right;
	double bottom;

	BoundRect()
	    : left(0)
	    , top(0)
	    , right(0)
	    , bottom(0)
	{}
};

// vertex point
template <class T> struct vertex_base_type
{
	typedef T value_type;
	T x, y;
	unsigned cmd;

	vertex_base_type() {}

	vertex_base_type(T x_, T y_, unsigned cmd_)
	    : x(x_)
	    , y(y_)
	    , cmd(cmd_)
	{}
};

typedef vertex_base_type<int> vertex_base_i;    //-----vertex_i
typedef vertex_base_type<float> vertex_base_f;  //-----vertex_f
typedef vertex_base_type<double> vertex_base_d; //-----vertex_d

/**
 * @brief 路径中点的变换运算类
 *
 */
class UI_EXP PathTransform
{
  public:
	PathTransform();
	virtual ~PathTransform();

	virtual void Transform(double* x, double* y);

	virtual void Transform2x2(double* x, double* y);

	virtual BOOL IsInPath(double x, double y); // 是否在坐标系内

	virtual double GetCoordinateWeight(double value); // 获得权重

	virtual BOOL IsCartesianSystem(); // 是否是笛卡尔坐标系
};



class GPathStorage;

struct TransAlongSinglePath
{
	UINT src_path_align;
	GPathStorage* src_path;
	PathConvType src_path_convt;
	GPathStorage* single_path;
	PathConvType single_path_convt;
	BOOL path_line_is_closed_path;

	double start;
	double src_path_width;
	int proximity_distance; // 靠近基线的距离

	TransAlongSinglePath()
	    : src_path_align(DT_CENTER | DT_TOP)
	    , src_path(NULL)
	    , single_path(NULL)
	    , path_line_is_closed_path(FALSE)
	    , src_path_convt(CONV_CURVE_DIV)
	    , single_path_convt(CONV_NONE)
	    , start(0)
	    , src_path_width(0)
	    , proximity_distance(0)
	{}
};

struct TransAlongDoublePath
{
	UINT src_path_align;
	GPathStorage* src_path;
	PathConvType src_path_convt;

	GPathStorage* single_path1;
	PathConvType single_path_convt1;

	GPathStorage* single_path2;
	PathConvType single_path_convt2;

	BOOL path_line_is_closed_path;

	double start;
	double src_path_width;
	double src_path_height;

	TransAlongDoublePath()
	    : src_path_align(DT_CENTER | DT_TOP)
	    , src_path(NULL)
	    , single_path1(NULL)
	    , single_path_convt1(CONV_NONE)
	    , single_path2(NULL)
	    , single_path_convt2(CONV_NONE)
	    , path_line_is_closed_path(FALSE)
	    , src_path_convt(CONV_CURVE_DIV)
	    , start(0)
	    , src_path_width(0)
	    , src_path_height(0)
	{}
};

/**
 * @brief 路径顶点源(在GPathStorage的世界里，椭圆,弧线,样条曲线都是由足够细腻的直线拟合的)
 *
 */
class UI_EXP GPathStorage
{
  public:
	enum CombinationPathFlag
	{
		combination_or,        // a | b  并集
		combination_and,       // a & b  交集
		combination_xor,       // a ^ b=(a | b) - (a & b). 去除公共部分的剩余部分
		combination_a_minus_b, // a - b  存在A，不存在B
		combination_b_minus_a  // b - a  存在B，不存在A
	};

  public:
	typedef vertex_base_f value_type;
	GPathStorage();
	virtual ~GPathStorage();

	unsigned vertex(double* x, double* y);

	unsigned last_command();
	unsigned last_vertex(double* x, double* y);
	unsigned prev_vertex(double* x, double* y);

	void rewind(unsigned path_id);
	void add_vertex(double x, double y, unsigned cmd);

	UINT size() const;

	void clear();

	value_type& operator[](unsigned int pos);

	void ConcatPath(GPathStorage& vs, unsigned path_id = 0);

	/**
	 * @brief 获得路径的矩形区域
	 *
	 * @param path_id 路径起始位置
	 * @param useTrans false:原始坐标点，true:变换后的坐标点
	 * @return BoundRect 矩形区域
	 */
	BoundRect PathBox(unsigned path_id = 0, bool useTrans = false);
	RECT PathBoxToRect(unsigned path_id = 0);
	BOOL IsClosed();

	int StartNewPath();

	unsigned PathIDCounts(); ///< 组合路径数量
	unsigned PathId();       ///< 当前的索引ID

	void ClosePath();

	void RelToAbs(double* x, double* y);
	void PathMoveTo(double x, double y);
	void PathLineTo(double x, double y);

	void PathHLineTo(double x);
	void PathVLineTo(double y);

	void Curve3(double x_to, double y_to);
	void Curve4(double x_ctrl2, double y_ctrl2, double x_to, double y_to);
	void PathCurve4(POINT pt[4]);
	void PathCurve3(POINT pt[3]);

	void PathCurve4WithDouble(GPointF pt[4]);
	void PathCurve3WithDouble(GPointF pt[3]);

	void PathBSpline(POINT* pt, int len);

	void ParseCmdData(const char* data);
	/**
	 * @brief PathArcTo
	 *
	 * @param a1 a2 基于三点方向顺时针的角度
	 * @param ccw  优弧顺时针方向为true，劣弧逆时针方向为false
	 */
	void PathArcTo(double x, double y, double rx, double ry, double a1, double a2, bool ccw = true);
	void PathJoinArcTo(double x, double y, double rx, double ry, double a1, double a2, bool ccw);
	void PathPie(double x0, double y0, double rx, double ry, double a1, double a2);              // 饼图路径
	void PathRing(double x0, double y0, double rx, double ry, double a1, double a2, double dis); // 环状路径
	void PathRingRound(double x0, double y0, double rx, double ry, double a1, double a2, double dis, double round = PI / 45);
	void PathEllipse(int cx, int cy, int rx, int ry);
	void PathRect(double x1, double y1, double w, double h, double rx1 = 0, double ry1 = 0, double rx2 = 0, double ry2 = 0, double rx3 = 0, double ry3 = 0, double rx4 = 0, double ry4 = 0);

	void SetTransform(PathTransform* trans);

	/**
	 * @brief 随机生成Y更新测试数据
	 */
	void UpdateYValue(double low, double hight);
	/**
	 * @brief 测试命中点
	 */
	BOOL HitTestPoint(double x, double y);

	/**
	 * @brief 将笛卡尔坐标系数据点，转换为极坐标系
	 */
	void ConvertToPolarCoordinate(double cx, double cy);
	/**
	 * @brief Create a Web Tab Path object
	 *
	 * @param angle 偏角大小
	 * @param dir 方向
	 * @param r 圆角尺寸
	 */
	void CreateWebTabPath(RECT rcBox, double angle, int dir, float r = 4, BOOL isBorder = TRUE);

	/**
	 * @brief  软件图标
	 *
	 */
	void generate_soft_icon(int R);

	/**
	 * @brief  生成G3曲率的圆角矩形
	 *
	 */
	void CreateG3RoundRectPath(RECT rcBox, int n);

	/**
	 * @brief  圆角五角星
	 *
	 */
	void generate_star_round(int R);

	/**
	 * @brief  五花瓣
	 *
	 */
	void generate_petal5(int R);

	/**
	 * @brief  齿轮
	 *
	 * @param R1  齿外边缘半径
	 * @param a1  齿外边缘弧度大小
	 * @param R2  齿内边缘半径
	 * @param a2  齿内边缘弧度大小
	 */
	void generate_gear_wheel(int R1, double a1, int R2, double a2);

	/**
	 * @brief  将图形沿单一路径变换
	 *
	 */
	void generate_along_with_single_path(TransAlongSinglePath& tap);

	/**
	 * @brief  将图形沿双路径变换
	 *
	 */
	void generate_along_with_double_path(TransAlongDoublePath& tap);

	/**
	 * @brief  矩形区域裁剪路径
	 *
	 */
	void clip_polygon(GPathStorage* result_path, int x1, int y1, int x2, int y2);

	static void generate_arrowhead(ArrowHead& head, int size);

	/**
	 * @brief  构建边缘路径
	 *
	 * @param isRoundRadiusDrawLine  TRUE：直线型， FALSE:圆角型
	 */
	static void build_radius_border_path(GPathStorage* path, RECT& rcRound, RoundRectRadius& radius, BOOL isRoundRadiusDrawLine, BOOL isRoundRadiusParl);


	static void build_radius_border_parl_path(GPathStorage* path, RECT& rcRound, RoundRectRadius& radius);
	/**
	 * @brief  路径组合操作
	 *
	 * @param result_path  输出结果路径
	 * @param path1
	 * @param path2
	 * @param cmp_op 合并操作
	 */
	static void combination_path(GPathStorage* result_path, GPathStorage* path1, GPathStorage* path2, CombinationPathFlag cmp_op);


  protected:
	virtual value_type& GetAt(unsigned int pos);
	virtual void push_back(const value_type& vx);
	unsigned get_transform_vertex(unsigned int pos, double* x, double* y);

  protected:
	unsigned int m_index;
	unsigned int m_num_vertices; // 顶点的个数
	std::vector<value_type> m_vertexs;
	PathTransform* m_transform;
};

class UI_EXP GPathRectStorage : public GPathStorage
{
  public:
	GPathRectStorage();
	GPathRectStorage(int x1, int y1, int w, int h, int rx1, int ry1, int rx2, int ry2, int rx3, int ry3, int rx4, int ry4);
	~GPathRectStorage();

	void init_path(int x1, int y1, int w, int h, int rx1, int ry1, int rx2, int ry2, int rx3, int ry3, int rx4, int ry4);
};

class UI_EXP GPathEllipseStorage : public GPathStorage
{
  public:
	GPathEllipseStorage();
	GPathEllipseStorage(int cx, int cy, int rx, int ry);
	~GPathEllipseStorage();

	void init_path(int cx, int cy, int rx, int ry);
};

class UI_EXP GPathBufferStorage : public GPathStorage
{
  public:
	GPathBufferStorage(value_type* src, int len);
	~GPathBufferStorage();

	/**
	 * @brief  构建直角三角行
	 *
	 * @param rect
	 * @param dir 方向 0(down) 1(up) 2(right) 3(left)
	 * @param size 尺寸
	 */
	void generate_triangle_right_angle_path(RECT rect, int dir, int size, double subpixel_offset = 0.0);

	/**
	 * @brief 根据径向规则，构建等腰三角形
	 *
	 * @param x0,y0 中心点
	 * @param r 半径
	 * @param deflection 在圆周上的角度
	 * @param angle  顶角角度，底角=(180-顶角)*0.5
	 * @param size 尺寸
	 * @param dir 0 外沿 1内沿
	 */
	void generate_triangle_path_with_radial(double x0, double y0, double r, double deflection, double angle, int size, int dir);

	/**
	 * @brief  构建滚动条箭头
	 *
	 * @param rect
	 * @param dir 方向 0(down) 1(up) 2(right) 3(left)
	 * @param size 尺寸
	 */
	void generate_triangle_scrollbar_path(RECT rect, int dir, int size, int fillsize, double subpixel_offset = 0.0);


	/**
	 * @brief  构建表格排序箭头
	 *
	 * @param rect
	 * @param dir 方向 0(down) 1(up) 2(right) 3(left)
	 * @param size 尺寸
	 */
	void generate_triangle_sort_path(RECT rect, int dir, int size, double subpixel_offset = 0.0);

	/**
	 * @brief  构建箭头边框
	 *
	 * @param rect
	 */
	void generate_triangle_path(UINT flag, RECT rc, int size);

	/**
	 * @brief  为路径生成箭头箭尾
	 *
	 */
	void generate_arrowhead_path(GPathStorage& vs, PathConvType type, ArrowHead* head = NULL, ArrowTail* tail = NULL);

	/**
	 * @brief  为路径生成箭头箭尾
	 *
	 */
	void generate_five_pointed_star(int x0, int y0, int r, double yAngle = 0.0);


	/* GPathStorage override methods:*/
	value_type& GetAt(unsigned int pos) override;
	void push_back(const value_type& vx) override;

  protected:
	value_type* m_bufVx; // 顶点缓存
	int m_buf_len;       // 顶点缓存容量
};

class UI_EXP GPathLinesStorage
{
  public:
	GPathLinesStorage();
	~GPathLinesStorage();

	GPathStorage* Path() const;

  public:
	GPathBufferStorage m_path;
	GPathBufferStorage::value_type m_points[16];
};

class UI_EXP GPathBigPointStorage
{
  public:
	GPathBigPointStorage();
	~GPathBigPointStorage();

	GPathStorage* Path() const;

  public:
	GPathBufferStorage m_path;
	GPathBufferStorage::value_type m_points[1024];
};


}
#endif
