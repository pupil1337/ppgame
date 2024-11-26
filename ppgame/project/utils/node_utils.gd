class_name NodeUtils extends Object

## 获得指定Script类型的最低父节点
static func get_parent_node_lowest_by_script(p_node: Node, p_script: Script) -> Node:
	if p_node:
		var parent: Node = p_node.get_parent()
		if parent:
			var target_script_name: StringName = p_script.get_global_name()
			@warning_ignore("unsafe_cast")
			var parent_script: Script = parent.get_script() as Script
			while parent_script:
				if parent_script.get_global_name() == target_script_name:
					return parent
				else:
					parent_script = parent_script.get_base_script()
			return get_parent_node_lowest_by_script(parent, p_script)
	return null
