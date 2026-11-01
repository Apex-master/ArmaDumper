void WriteAll()
{
	std::ofstream out_file("all.offset");
	if (out_file.is_open())
	{
		out_file << "\nstruct WorldStruct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, camera, 0x" << std::hex << std::uppercase << camera_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, display_manager, 0x" << std::hex << std::uppercase << display_manager_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, projectiles_table, 0x" << std::hex << std::uppercase << projectiles_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint32_t, projectiles_table_size, 0x" << std::hex << std::uppercase << (projectiles_offset + 0x8) << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, near_table, 0x" << std::hex << std::uppercase << near_table_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, close_table, 0x" << std::hex << std::uppercase << close_table_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, far_table, 0x" << std::hex << std::uppercase << far_table_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, camera_on, 0x" << std::hex << std::uppercase << camera_on_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, player_on, 0x" << std::hex << std::uppercase << player_on_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, real_player, 0x" << std::hex << std::uppercase << real_player_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, terrain_grid, 0x" << std::hex << std::uppercase << terrain_grid_offset << ");\n";
		out_file << "	};\n";
		out_file << "};\n";

		out_file << "\nstruct CameraStruct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, inverted_view_right, 0x" << std::hex << std::uppercase << inverted_view_right_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, inverted_view_up, 0x" << std::hex << std::uppercase << inverted_view_up_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, inverted_view_forward, 0x" << std::hex << std::uppercase << inverted_view_forward_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, inverted_view_translation, 0x" << std::hex << std::uppercase << inverted_view_translation_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, viewport_size, 0x" << std::hex << std::uppercase << viewport_size_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, projection_d1, 0x" << std::hex << std::uppercase << projection_d1_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(Vector3, projection_d2, 0x" << std::hex << std::uppercase << projection_d2_offset << ");\n";
		out_file << "	};\n";
		out_file << "};\n";

		out_file << "\nstruct EntityStruct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, current_visual_state, 0x" << std::hex << std::uppercase << current_visual_state_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint8_t, object_hidden, 0x" << std::hex << std::uppercase << object_hidden_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, type, 0x" << std::hex << std::uppercase << type_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, class, 0x" << std::hex << std::uppercase << (class_offset + 0x8) << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, future_visual_state, 0x" << std::hex << std::uppercase << future_visual_state_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint8_t, side, 0x" << std::hex << std::uppercase << side_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, mount, 0x" << std::hex << std::uppercase << mount_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint8_t, is_dead, 0x" << std::hex << std::uppercase << is_dead_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, player_name, 0x" << std::hex << std::uppercase << player_name_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint32_t, weapon_list_size, 0x" << std::hex << std::uppercase << weapon_list_size_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint32_t, weapon_index, 0x" << std::hex << std::uppercase << weapon_index_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, weapon_table, 0x" << std::hex << std::uppercase << weapon_table_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, real_player, 0x" << std::hex << std::uppercase << entity_real_player_offset << ");\n";
		out_file << "	};\n"; 
		out_file << "};\n";


		out_file << "\nstruct EntityTypeStruct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, model_name_string, 0x" << std::hex << std::uppercase << model_name_string_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint8_t, model_path_string, 0x" << std::hex << std::uppercase << model_path_string_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, short_name_string, 0x" << std::hex << std::uppercase << short_name_string_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, entity_type_string, 0x" << std::hex << std::uppercase << entity_type_string_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, print_name_string, 0x" << std::hex << std::uppercase << print_name_string_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint8_t, print_name_other_string, 0x" << std::hex << std::uppercase << print_name_other_string_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint8_t, move_types_ptr, 0x" << std::hex << std::uppercase << move_types_ptr_offset << ");\n";
		out_file << "	};\n";
		out_file << "};	EntityTypeStruct EntityTypeData = {};\n";

		out_file << "\nstruct VisualStateStruct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, rotation, 0x" << std::hex << std::uppercase << rotation_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, origin, 0x" << std::hex << std::uppercase << origin_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, velocity, 0x" << std::hex << std::uppercase << velocity_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uint32_t, acceleration, 0x" << std::hex << std::uppercase << acceleration_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, inverse_rotation, 0x" << std::hex << std::uppercase << inverse_rotation_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, inverse_pos, 0x" << std::hex << std::uppercase << inverse_pos_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, move_info_table_index1, 0x" << std::hex << std::uppercase << move_info_table_index1_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, move_info_table_index2, 0x" << std::hex << std::uppercase << move_info_table_index2_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, animation_completion, 0x" << std::hex << std::uppercase << animation_completion_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, head, 0x" << std::hex << std::uppercase << head_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, chest, 0x" << std::hex << std::uppercase << chest_offset << ");\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, inaccuracy, 0x" << std::hex << std::uppercase << inaccuracy_offset << ");\n";
		out_file << "	};\n";
		out_file << "};\n";

		// STATIC
		out_file << "\nstruct WeaponTableStruct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, weapon_mode_ptr, 0x00);\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, weapon_type_ptr, 0x08);\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, muzzle_type_ptr, 0x10);\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, muzzle_state_ptr, 0x18);\n";
		out_file << "	};\n";
		out_file << "};\n";
	}
	out_file.close();
	printf("[ALL] All structs written to file: all.offset\n");
}
