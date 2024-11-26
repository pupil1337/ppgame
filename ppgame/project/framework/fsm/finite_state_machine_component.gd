class_name FiniteStateMachineComponent extends Component

var curr_state: State
var states: Dictionary # { Script: State, ... }


func _notification(what: int) -> void:
	if what == NOTIFICATION_PARENTED:
		var owner_csm_component: ConcurrentStateMachineComponent = NodeUtils.get_parent_node_lowest_by_script(self, ConcurrentStateMachineComponent)
		owner_csm_component.add_fsm(self)


func add_state(p_state: State) -> void:
	@warning_ignore("unsafe_cast")
	var state_script: Script = p_state.get_script() as Script
	assert(not states.has(state_script), "已经添加过此状态")
	states[state_script] = p_state
	if p_state.is_default_state:
		assert(not curr_state, "设置了多个默认状态")
		curr_state = p_state


func on_start() -> void:
	curr_state.on_enter()


func on_process(p_delta: float) -> void:
	var new_state_script: Script = curr_state.on_process(p_delta)
	if new_state_script:
		_change_state(new_state_script)


func on_physics_process(p_delta: float) -> void:
	curr_state.on_physics_process(p_delta)


#region
func _change_state(p_state_script: Script) -> void:
	curr_state.on_exit()
	
	@warning_ignore("unsafe_cast")
	curr_state = states.get(p_state_script) as State
	assert(curr_state, "状态机返回了状态:"+p_state_script.get_global_name()+" 但是没有在场景中添加这个状态节点")
	curr_state.on_enter()
#endregion
