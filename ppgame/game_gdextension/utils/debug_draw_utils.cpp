#include "debug_draw_utils.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/variant/vector2.hpp>

DebugDrawUtils* DebugDrawUtils::singleton = nullptr;

DebugDrawUtils::DebugDrawUtils() {
	singleton = this;
}

DebugDrawUtils::~DebugDrawUtils() {
	singleton = nullptr;
}

DebugDrawUtils* DebugDrawUtils::get_singleton() {
	return singleton;
}

void DebugDrawUtils::_process(double p_delta) {
	parent_type::_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		curr_time += p_delta;
		queue_redraw();
	}
}

#define CallDrawFunc(T, list)                                    \
	Vector<T> new_##list;                                        \
	for (int i = 0; i < list.size(); ++i) {                      \
		T data = list[i];                                        \
		if (data.end_time <= 0.0 || data.end_time > curr_time) { \
			data.draw(this);                                     \
			new_##list.push_back(data);                          \
		}                                                        \
	}                                                            \
	list = new_##list;

void DebugDrawUtils::_draw() {
	parent_type::_draw();

	CallDrawFunc(DrawLineData, lines);
	CallDrawFunc(DrawRectangleData, rectangles);
}

void DebugDrawUtils::draw_debug_line(const Vector2& p_from, const Vector2& p_to, const Color& p_color, float p_time /* = 0.0 */, double p_width /* = -1.0 */, bool p_antialiased /* = false */) {
	DebugDrawUtils* utils = get_singleton();

	DrawLineData data;
	data.from = p_from;
	data.to = p_to;
	data.color = p_color;
	data.width = p_width;
	data.antialiased = p_antialiased;
	data.end_time = p_time <= 0.0 ? p_time : utils->curr_time + p_time;
	utils->lines.append(data);
}

void DebugDrawUtils::draw_debug_rectangle(const Rect2& p_rect, const Color& p_color, float p_time /* = 0.0 */, bool p_filled /* = true */, double p_width /* = -1.0 */, bool p_antialiased /* = false */) {
	DebugDrawUtils* utils = get_singleton();

	DrawRectangleData data;
	data.rect = p_rect;
	data.color = p_color;
	data.filled = p_filled;
	data.width = p_width;
	data.antialiased = p_antialiased;
	data.end_time = p_time <= 0.0 ? p_time : utils->curr_time + p_time;
	utils->rectangles.append(data);
}
