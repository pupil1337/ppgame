# class_name DrawDebugUtils
# autoload
extends Node2D

var curr_time: float
var line_datas: Array[LineData]
var rect_datas: Array[RectData]


func _init() -> void:
	z_index = RenderingServer.CANVAS_ITEM_Z_MAX

func _process(delta: float) -> void:
	curr_time += delta
	queue_redraw()


func _draw() -> void:
	_draw_datas(line_datas)
	_draw_datas(rect_datas)


## 绘制Debug线
func draw_debug_line(p_from: Vector2, p_to: Vector2, p_time: float = 0.0, p_color: Color = Color.WHITE, p_width: float = -1.0, p_antialiased: bool = false) -> void:
	line_datas.push_back(LineData.new([p_from, p_to, p_color, p_width, p_antialiased], curr_time + p_time if p_time >= 0 else 10000.0))


## 绘制Debug矩形
func draw_debug_rect(p_rect: Rect2, p_time: float = 0.0, p_color: Color = Color.WHITE, p_filled: bool = true, p_width: float = -1.0, p_antialiased: bool = false) -> void:
	rect_datas.push_back(RectData.new([p_rect, p_color, p_filled, p_width, p_antialiased], curr_time + p_time if p_time >= 0 else 10000.0))


#region
class DrawDataBase extends Object:
	var data: Array
	var end_time: float
	func _init(p_data: Array, p_end_time: float) -> void:
		data = p_data
		end_time = p_end_time


class LineData extends DrawDataBase:
	func draw() -> void:
		@warning_ignore("unsafe_call_argument")
		DrawDebugUtils.draw_line(data[0], data[1], data[2], data[3], data[4])


class RectData extends DrawDataBase:
	func draw() -> void:
		@warning_ignore("unsafe_call_argument")
		DrawDebugUtils.draw_rect(data[0], data[1], data[2], data[3], data[4])


func _draw_datas(out_datas: Array) -> void:
	assert(out_datas.size() < 1000, "Debug线/形状 请求绘制的数量太多了")
	var datas_copy: Array = out_datas.duplicate()
	out_datas.clear()
	@warning_ignore("untyped_declaration")
	for data in datas_copy:
		@warning_ignore("unsafe_method_access")
		data.draw()
		if data["end_time"] > curr_time:
			out_datas.push_back(data)
		else:
			@warning_ignore("unsafe_method_access")
			data.free()
#endregion
