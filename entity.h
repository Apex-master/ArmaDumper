uintptr_t current_visual_state_offset;
PatternScan::Pattern current_visual_state_pattern = { "48 8B 8B ?? ?? ?? ?? 48 85 C9 74 ?? 48 83 C1 ?? F0 FF 49 ?? 75 ?? 48 8B 01 FF 50 ?? 48 89 AB ?? ?? ?? ?? 48 8B 8B ?? ?? ?? ?? 48 85 C9 74 ?? F0 FF 49 ?? 75 ?? 48 8B 01 FF 50 ?? 48 89 AB ?? ?? ?? ?? 48 8B 8B ?? ?? ?? ?? 48 85 C9 74 ?? 48 8B 01", 3, 4, 7, 1 };

uintptr_t object_hidden_offset;
PatternScan::Pattern object_hidden_pattern = { "88 86 ?? ?? ?? ?? 45 84 ff", 2, 4, 6, 1 };

uintptr_t type_offset;
PatternScan::Pattern type_pattern = { "48 8B 97 ?? ?? ?? ?? 48 8D 8F ?? ?? ?? ?? 4C 8B 82 ?? ?? ?? ?? 48 8B 97 ?? ?? ?? ?? 48 81 C2 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 08 48 85 C9 74 ?? F0 FF 01 48 89 8C 24", 3, 4, 7, 1 };

uintptr_t class_offset;
PatternScan::Pattern class_pattern = { "48 83 B9 ?? ?? ?? ?? ?? 74 ?? 48 8B 81 ?? ?? ?? ?? C3", 3, 5, 8, 1 };

uintptr_t future_visual_state_offset;
PatternScan::Pattern future_visual_state_pattern = { "48 3B 91 ?? ?? ?? ?? 75 ?? 0F 57 C0", 3, 4, 7, 1 };

uintptr_t side_offset;
PatternScan::Pattern side_pattern = { "8B 86 ?? ?? ?? ?? 48 8B 5C 24 ?? 48 8B 6C 24", 2, 4, 6, 1 };

uintptr_t mount_offset;
PatternScan::Pattern mount_pattern = { "48 8B B3 ?? ?? ?? ?? 48 85 F6 74 ?? F0 FF 0E 75 ?? 48 85 F6 74 ?? 48 8B CE E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? 48 8B D6 48 8B 01 FF 50 ?? 48 89 AB ?? ?? ?? ?? 48 8B 93 ?? ?? ?? ?? 89 AB ?? ?? ?? ?? 48 85 D2 74 ?? 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 50 ?? 48 89 AB ?? ?? ?? ?? 89 AB ?? ?? ?? ?? 48 8D 8B", 3, 4, 7, 1 };

uintptr_t is_dead_offset;
PatternScan::Pattern is_dead_pattern = { "44 38 AF ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 44 89 AF", 3, 4, 7, 1 };

uintptr_t player_name_offset;
PatternScan::Pattern player_name_pattern = { "48 8B 81 ?? ?? ?? ?? 48 85 C0 74 ?? F0 FF 00 48 89 44 24 ?? 48 8B 81 ?? ?? ?? ?? 48 85 C0 74 ?? F0 FF 00 48 89 44 24 ?? 48 8B 81", 3, 4, 7, 1 };

uintptr_t weapon_list_size_offset;
PatternScan::Pattern weapon_list_size_pattern = { "48 8B 89 ?? ?? ?? ?? 41 0F B6 D8 48 8B F2", 3, 4, 7, 1 };

uintptr_t weapon_index_offset;
PatternScan::Pattern weapon_index_pattern = { "89 87 ?? ?? ?? ?? 84 DB 0F 84 ?? ?? ?? ??", 2, 4, 6, 1 };

uintptr_t weapon_table_offset;
PatternScan::Pattern weapon_table_pattern = { "48 8B 87 ?? ?? ?? ?? 48 8B 54 D0", 3, 4, 7, 1 };

uintptr_t entity_real_player_offset;
PatternScan::Pattern entity_real_player_pattern = { "4C 39 A7 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 48 8B 07", 3, 4, 7, 1 };

void PrintEntity()
{
	printf("[ENTITY] current_visual_state_offset: 0x%X\n", current_visual_state_offset);
	printf("[ENTITY] object_hidden_offset: 0x%X\n", object_hidden_offset);
	printf("[ENTITY] type_offset: 0x%X\n", type_offset);
	printf("[ENTITY] class_offset: 0x%X\n", class_offset);
	printf("[ENTITY] future_visual_state_offset: 0x%X\n", future_visual_state_offset);
	printf("[ENTITY] side_offset: 0x%X\n", side_offset);
	printf("[ENTITY] mount_offset: 0x%X\n", mount_offset);
	printf("[ENTITY] is_dead_offset: 0x%X\n", is_dead_offset);
	printf("[ENTITY] player_name_offset: 0x%X\n", player_name_offset);
	printf("[ENTITY] weapon_list_size_offset: 0x%X\n", weapon_list_size_offset);
	printf("[ENTITY] weapon_index_offset: 0x%X\n", weapon_index_offset);
	printf("[ENTITY] weapon_table_offset: 0x%X\n", weapon_table_offset);
	printf("[ENTITY] real_player_offset: 0x%X\n", entity_real_player_offset);
}

void ScanEntity()
{
	current_visual_state_offset = pattern_scanner.Scan(current_visual_state_pattern, 1);
	object_hidden_offset = pattern_scanner.Scan(object_hidden_pattern, 1);
	type_offset = pattern_scanner.Scan(type_pattern, 1);
	class_offset = pattern_scanner.Scan(class_pattern, 1);
	future_visual_state_offset = pattern_scanner.Scan(future_visual_state_pattern, 1);
	side_offset = pattern_scanner.Scan(side_pattern, 1);
	mount_offset = pattern_scanner.Scan(mount_pattern, 1);
	is_dead_offset = pattern_scanner.Scan(is_dead_pattern, 1);
	player_name_offset = pattern_scanner.Scan(player_name_pattern, 1);
	weapon_list_size_offset = pattern_scanner.Scan(weapon_list_size_pattern, 1);
	weapon_index_offset = pattern_scanner.Scan(weapon_index_pattern, 1);
	weapon_table_offset = pattern_scanner.Scan(weapon_table_pattern, 1);
	entity_real_player_offset = pattern_scanner.Scan(entity_real_player_pattern, 1);
}

void WriteEntity()
{
	std::ofstream out_file("entity_struct.offset");
	if (out_file.is_open())
	{
		out_file << "#define STR_MERGE_IMPL(a, b) a##b\n";
		out_file << "#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)\n";
		out_file << "#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]\n";
		out_file << "#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }\n";

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
		out_file << "};	EntityStruct entity_data = {};\n";
	}
	out_file.close();
	printf("[ENTITY] Entity struct written to file: entity_struct.offset\n\n");
}
