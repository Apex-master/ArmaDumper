uintptr_t world_address;
PatternScan::Pattern world_pattern = { "48 8B 0D ?? ?? ?? ?? 8B D0 E8 ?? ?? ?? ?? 48 8B F8 8B 05", 3, 4, 7, 0 };

uintptr_t camera_offset;
PatternScan::Pattern camera_pattern = { "44 0F 29 B4 24 ?? ?? ?? ?? E8 ?? ?? ?? ?? 44 38 3D ?? ?? ?? ?? 49 8B 86 ?? ?? ?? ?? F2 0F 10 3D ?? ?? ?? ?? 48 8D 48 20 ", 24, 4, 28, 1 };

uintptr_t display_manager_offset;
PatternScan::Pattern display_manager_pattern = { "48 8B BB ?? ?? ?? ?? 0F 29 BC 24 ?? ?? ?? ?? 48 85 FF", 3, 4, 7, 1 };

uintptr_t end_game_offset;
PatternScan::Pattern end_game_pattern = { "44 39 B0 ?? ?? ?? ?? 75 6A", 3, 4, 7, 1 };

uintptr_t in_game_offset;
PatternScan::Pattern in_game_pattern = { "FF 0D ?? ?? ?? ?? 48 8B 89", 2, 4, 6 };

uintptr_t projectiles_offset;
PatternScan::Pattern projectiles_pattern = { "49 8B 85 ?? ?? ?? ?? 48 8B 1C 07 48 85 DB 74 2D 80 BB ?? ?? ?? ?? ??", 3, 4, 7, 1 };

uintptr_t near_table_offset;
PatternScan::Pattern near_table_pattern = { "48 8B 87 ?? ?? ?? ?? 48 8D 4D E7", 3, 4, 7, 1 };

uintptr_t close_table_offset;
PatternScan::Pattern close_table_pattern = { "48 8B 87 ?? ?? ?? ?? 48 8D 4D F7", 3, 4, 7, 1 };

uintptr_t far_table_offset;
PatternScan::Pattern far_table_pattern = { "48 8B 87 ?? ?? ?? ?? 48 8D 4D 07", 3, 4, 7, 1 };

uintptr_t camera_on_offset;
PatternScan::Pattern camera_on_pattern = { "C6 45 50 00 48 8B 81 ?? ?? ?? ??", 7, 4, 11, 1 };

uintptr_t player_on_offset;
PatternScan::Pattern player_on_pattern = { "4C 8B 05 ?? ?? ?? ?? 49 8B 80 ?? ?? ?? ??", 10, 4, 14, 1 };

uintptr_t real_player_offset;
PatternScan::Pattern real_player_pattern = { "48 8B 88 ?? ?? ?? ?? 48 8B 59 08 48 85 DB 75 08", 3, 4, 7, 1 };

uintptr_t terrain_grid_offset;
PatternScan::Pattern terrain_grid_pattern = { "F3 0F 10 81 ?? ?? ?? ?? 0F 2F C1 76 05", 4, 4, 8, 1 };

void PrintWorld()
{
	printf("[WORLD] address: 0x%llX\n", world_address);
	printf("[WORLD] camera_offset: 0x%X\n", camera_offset);
	printf("[WORLD] display_manager_offset: 0x%X\n", display_manager_offset);
	printf("[WORLD] end_game_offset: 0x%X\n", end_game_offset);
	printf("[WORLD] projectiles_table_offset: 0x%X\n", projectiles_offset);
	printf("[WORLD] near_table_offset: 0x%X\n", near_table_offset);
	printf("[WORLD] close_table_offset: 0x%X\n", close_table_offset);
	printf("[WORLD] far_table_offset: 0x%X\n", far_table_offset);
	printf("[WORLD] camera_on_offset: 0x%X\n", camera_on_offset);
	printf("[WORLD] player_on_offset: 0x%X\n", player_on_offset);
	printf("[WORLD] real_player_offset: 0x%X\n", real_player_offset);
	printf("[WORLD] terrain_grid_offset: 0x%X\n", terrain_grid_offset);
}

void ScanWorld()
{
	world_address = pattern_scanner.Scan(world_pattern, 1);
	camera_offset = pattern_scanner.Scan(camera_pattern, 1);
	display_manager_offset = pattern_scanner.Scan(display_manager_pattern, 1);
	end_game_offset = pattern_scanner.Scan(end_game_pattern, 1);
	projectiles_offset = pattern_scanner.Scan(projectiles_pattern, 1);
	near_table_offset = pattern_scanner.Scan(near_table_pattern, 1);
	close_table_offset = pattern_scanner.Scan(close_table_pattern, 1);
	far_table_offset = pattern_scanner.Scan(far_table_pattern, 1);
	camera_on_offset = pattern_scanner.Scan(camera_on_pattern, 1);
	player_on_offset = pattern_scanner.Scan(player_on_pattern, 1);
	real_player_offset = pattern_scanner.Scan(real_player_pattern, 1);
	terrain_grid_offset = pattern_scanner.Scan(terrain_grid_pattern, 1);
}

void WriteWorld()
{
	std::ofstream out_file("world_struct.offset");
	if (out_file.is_open())
	{
		out_file << "#define STR_MERGE_IMPL(a, b) a##b\n";
		out_file << "#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)\n";
		out_file << "#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]\n";
		out_file << "#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }\n";

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
		out_file << "};	WorldStruct world_data = {};\n";
	}
	out_file.close();
	printf("[WORLD] World struct written to file: world_struct.offset\n");
}
