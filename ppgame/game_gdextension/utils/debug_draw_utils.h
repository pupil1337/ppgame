#ifndef DEBUG_DRAW_UTILS_H
#define DEBUG_DRAW_UTILS_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

//! DebugDraw工具
class DebugDrawUtils : public Node2D {
	GDCLASS(DebugDrawUtils, Node2D)

private:
	static DebugDrawUtils* singleton;

public:
	static DebugDrawUtils* get_singleton();

private:
	struct DrawBaseData {
		float end_time = 0.0;
	};
	struct DrawLineData : DrawBaseData {
		Vector2 from;
		Vector2 to;
		Color color;
		double width = -1.0;
		bool antialiased = false;
		void draw(DebugDrawUtils* utils) {
			utils->draw_line(from, to, color, width, antialiased);
		}
	};
	struct DrawRectangleData : DrawBaseData {
		Rect2 rect;
		Color color;
		bool filled = true;
		double width = -1.0;
		bool antialiased = false;
		void draw(DebugDrawUtils* utils) {
			utils->draw_rect(rect, color, filled, width, antialiased);
		}
	};

public:
	//! 绘制线条
	/*!
	 * \param p_from 起点
	 * \param p_to 终点
	 * \param p_color 颜色
	 * \param p_time 绘制时长, <= 0.0 则一直存在
	 * \param p_width 如果为负, 则将绘制一个两点图元而不是一个四点图元. 这意味着当缩放CanvasItem时, 线条将保持细长. 如果不需要此行为, 请传递一个正的width, 如1.0.
	 * \param p_antialiased 是否抗锯齿
	 */
	static void draw_debug_line(const Vector2& p_from, const Vector2& p_to, const Color& p_color, float p_time = 0.0, double p_width = -1.0, bool p_antialiased = false);

	//! 绘制矩形
	/*!
	 * \param p_rect 轴对齐矩形
	 * \param p_color 颜色
	 * \param p_time 绘制时长, <= 0.0 则一直存在
	 * \param p_filled 是否填充
	 * \param p_width 如果为负, 则将绘制一个两点图元而不是一个四点图元. 这意味着当缩放CanvasItem时, 线条将保持细长. 如果不需要此行为, 请传递一个正的width, 如1.0.
	 * \param p_antialiased 是否抗锯齿
	 */
	static void draw_debug_rectangle(const Rect2& p_rect, const Color& p_color, float p_time = 0.0, bool p_filled = true, double p_width = -1.0, bool p_antialiased = false);

public:
	DebugDrawUtils();
	~DebugDrawUtils();

private:
	double curr_time = 0.0;
	Vector<DrawLineData> lines; //!< 线条
	Vector<DrawRectangleData> rectangles; //!< 矩形

	// ------------------------------------------

public:
	virtual void _process(double p_delta) override;
	virtual void _draw() override;

protected:
	static void _bind_methods() {}
};

#endif // DEBUG_DRAW_UTILS_H
