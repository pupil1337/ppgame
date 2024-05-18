#include "world.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/transform2d.hpp>

#include "async_loader/async_loader.h"
#include "character/player/player.h"
#include "level/level.h"

// TODO Delete
// imgui test begin
#include <GLFW/glfw3.h>
#include <gl/gl.h>
#include <thirdpart/imgui/imgui.h>
#include <thirdpart/imgui/imgui_impl_glfw.h>
#include <thirdpart/imgui/imgui_impl_opengl3.h>
#include <cstdio>

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
// imgui test end

static AsyncLoader* async_loader = nullptr;

void World::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_POSTINITIALIZE) {
			async_loader = memnew(AsyncLoader);
		}
		if (p_what == NOTIFICATION_PREDELETE) {
			if (async_loader) {
				memdelete(async_loader);
			}
		}
	}
}

void World::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		// TODO Delete
		// imgui test begin
		glfwSetErrorCallback(glfw_error_callback);
		if (glfwInit()) {
			const char* glsl_version = "#version 130";
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
			// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

			// Create window with graphics context
			window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
			if (window != nullptr) {
				glfwMakeContextCurrent(window);
				glfwSwapInterval(1); // Enable vsync

				// Setup Dear ImGui context
				IMGUI_CHECKVERSION();
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();
				(void)io;
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

				// Setup Dear ImGui style
				ImGui::StyleColorsDark();
				//ImGui::StyleColorsLight();

				// Setup Platform/Renderer backends
				ImGui_ImplGlfw_InitForOpenGL(window, true);

				ImGui_ImplOpenGL3_Init(glsl_version);
			}
		}
		// imgui test end
	}
}

void World::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		player = Object::cast_to<Player>(AsyncLoader::get_singleton()->instance("res://character/player/player.tscn"));
		change_level("res://level/level_0.tscn", "PlayerStart0");
	}
}

void World::_process(double delta) {
	parent_type::_process(delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		// TODO Delete
		// imgui test begin
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		// imgui test end
	}
}

void World::_exit_tree() {
	parent_type::_exit_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		// TODO Delete
		// imgui test begin
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
		// imgui test end
	}
}

World* World::get_world(Node* p_inside_node) {
	if (p_inside_node->is_inside_tree()) {
		return p_inside_node->get_tree()->get_root()->get_node<World>("World");
	}

	return nullptr;
}

void World::change_level(const String& p_level, const String& p_player_start) {
	call_deferred(_STR(_change_level_internal), p_level, p_player_start);
}

void World::_change_level_internal(const String& p_level, const String& p_player_start) {
	AsyncLoader::get_singleton()->instance(p_level, callable_mp(this, &self_type::_level_instanced_callback).bind(p_player_start));
}

void World::_level_instanced_callback(Node* p_node, const String& p_player_start) {
	if (Level* level = Object::cast_to<Level>(p_node)) {
		// 删除当前关卡
		if (curr_level) {
			curr_level->remove_child(player);
			curr_level->set_process_mode(Node::PROCESS_MODE_DISABLED);
			remove_child(curr_level);
			curr_level->queue_free();
		}

		// 切换关卡
		curr_level = level;
		add_child(curr_level);

		// player传送
		curr_level->add_child(player);
		Marker2D* player_start = curr_level->get_node<Marker2D>(p_player_start);
		const Transform2D& player_start_x = player_start->get_transform();
		player->set_transform(player_start_x);
		PhysicsServer2D::get_singleton()->body_set_mode(player->get_rid(), PhysicsServer2D::BODY_MODE_STATIC);
		PhysicsServer2D::get_singleton()->body_set_state(player->get_rid(), PhysicsServer2D::BODY_STATE_TRANSFORM, player_start_x);
		PhysicsServer2D::get_singleton()->body_set_mode(player->get_rid(), PhysicsServer2D::BODY_MODE_KINEMATIC);
	}
}

// ----------------------------------------------------------------------------

void World::_bind_methods() {
	ClassDB::bind_method(D_METHOD(_STR(_change_level_internal), _STR(level), _STR(player_start)), &self_type::_change_level_internal);
}
