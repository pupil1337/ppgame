class_name ConcurrentStateMachineComponent extends Component

var fsms: Array[FiniteStateMachineComponent]
var condition: StateCondition


func _init(p_condition_script: Script) -> void:
	@warning_ignore("unsafe_method_access")
	condition = p_condition_script.new()


func _notification(what: int) -> void:
	if what == NOTIFICATION_PREDELETE:
		condition.free()


func _ready() -> void:
	super()
	# 所有状态赋值Condition指针
	for fsm: FiniteStateMachineComponent in fsms:
		for script: Script in fsm.states:
			@warning_ignore("unsafe_cast", "unsafe_property_access")
			(fsm.states[script] as State).condition = condition
	# 更新条件
	update_logic_condition()
	update_physics_condition()
	# 所有状态机开始
	for fsm: FiniteStateMachineComponent in fsms:
		fsm.on_start()


func _process(delta: float) -> void:
	super(delta)
	update_logic_condition()
	for fsm: FiniteStateMachineComponent in fsms:
		fsm.on_process(delta)


func _physics_process(delta: float) -> void:
	super(delta)
	for fsm: FiniteStateMachineComponent in fsms:
		fsm.on_physics_process(delta)
	update_physics_condition() # 因为物理帧率先执行, 而逻辑帧依赖物理条件, 所以物理帧后立即更新物理条件


func add_fsm(fsm: FiniteStateMachineComponent) -> void:
	fsms.push_back(fsm)


func update_logic_condition() -> void:
	pass


func update_physics_condition() -> void:
	pass
