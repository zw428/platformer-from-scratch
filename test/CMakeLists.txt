SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(tests
	alive_test.cpp
	anim_handler_test.cpp
	anim_test.cpp
	attackable_test.cpp
	attack_box_test.cpp
	attack_manager_test.cpp
	attack_test.cpp
	block_test.cpp
	box_object_test.cpp
	box_test.cpp
	camera_test.cpp
	chunk_prop_test.cpp
	collide_functions_test.cpp
	collider_test.cpp
	delayed_action_test.cpp
	disabled_test.cpp
	friction_test.cpp
	gravity_affected_test.cpp
	image_test.cpp
	jumper_test.cpp
	keys_test.cpp
	knockback_test.cpp
	ledge_grabber_test.cpp
	level_loader_test.cpp
	manager_test.cpp
	map_test.cpp
	mover_test.cpp
	object_test.cpp
	player_test.cpp
	resource_manager_test.cpp
	shared_texture_test.cpp
	spawnable_test.cpp
	teleport_box_test.cpp
	teleporter_test.cpp
	test_main.cpp
	text_test.cpp
	trigger_test.cpp
	vel_accel_test.cpp
)

include(Catch)

target_link_libraries(tests Catch2::Catch2 base ${SDL_LIBS})
catch_discover_tests(tests)
