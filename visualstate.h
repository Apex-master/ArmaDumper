uintptr_t rotation_offset;
PatternScan::Pattern rotation_pattern = { "89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? C6 81", 2, 1, 3, 1 };

uintptr_t origin_offset;
PatternScan::Pattern origin_pattern = { "89 41 ?? 8B 42 ?? 89 41 ?? 8B 42 ?? 89 41 ?? C6 81 ?? ?? ?? ?? ?? C3 CC CC CC CC CC CC CC 88 91", 2, 1, 4, 1 };

uintptr_t velocity_offset;
PatternScan::Pattern velocity_pattern = { "F3 0F 11 53 ?? F3 0F 11 4B ?? F3 0F 11 43 ?? 39 93 ?? ?? ?? ?? 7E 43 8B CA 66 0F 1F 84 00 ?? ?? ?? ??", 4, 1, 5, 1 };

uintptr_t acceleration_offset;
PatternScan::Pattern acceleration_pattern = { "F3 0F 11 53 ?? F3 0F 11 4B ?? F3 0F 11 43 ?? F3 0F 10 56 ?? F3 0F 10 4E ?? F3 0F 10 46 ?? F3 0F 5C 57 ?? F3 0F 5C 4F ?? F3 0F 5C 47 ?? F3 0F 59 D6 F3 0F 59 CE F3 0F 59 C6 F3 0F 58 57 ?? F3 0F 58 4F ?? F3 0F 58 47 ?? F3 0F 11 53 ?? F3 0F 11 4B ?? F3 0F 11 43 ?? 39 93 ?? ?? ?? ?? 7E 43", 4, 1, 5, 1 };

uintptr_t inverse_rotation_offset;
PatternScan::Pattern inverse_rotation_pattern = { "89 8B ?? ?? ?? ?? 8B 4A ?? 89 8B ?? ?? ?? ?? 8B 4A ?? 89 8B ?? ?? ?? ?? 8B 4A ?? 89 8B ?? ?? ?? ?? 8B 4A", 2, 4, 6, 1 };

uintptr_t inverse_pos_offset;
PatternScan::Pattern inverse_pos_pattern = { "89 83 ?? ?? ?? ?? 8B 42 ?? 89 83 ?? ?? ?? ?? 8B 42 ?? 89 83 ?? ?? ?? ?? 48 83 C4 ?? 5B C3 CC", 2, 4, 6, 1 };

uintptr_t move_info_table_index1_offset;
PatternScan::Pattern move_info_table_index1_pattern = { "48 63 8A ?? ?? ?? ?? 83 F9 ?? 74 ?? 49 8B 81 ?? ?? ?? ?? 48 8B 80 ?? ?? ?? ?? 4C 8B 04 C8", 3, 4, 7, 1 };

uintptr_t move_info_table_index2_offset;
PatternScan::Pattern move_info_table_index2_pattern = { "48 63 8B ?? ?? ?? ?? 83 F9 ?? 74 ?? 48 8B 87 ?? ?? ?? ?? 48 8B 80 ?? ?? ?? ?? 48 8B 14 C8 48 85 D2 74 ?? 48 63 4E", 3, 4, 7, 1 };

uintptr_t animation_completion_offset;
PatternScan::Pattern animation_completion_pattern = { "0F 2F 82 ?? ?? ?? ?? 73 ?? 4D 85 C0", 3, 4, 7, 1 };

uintptr_t head_offset;
PatternScan::Pattern head_pattern = { "41 8B 80 ?? ?? ?? ?? 89 02 41 8B 80 ?? ?? ?? ?? 89 42 ?? 41 8B 80 ?? ?? ?? ?? 89 42 ?? 48 8B C3 48 8B 5C 24 ?? 48 83 C4 ?? 5F C3 CC CC CC CC CC ", 3, 4, 7, 1 };

uintptr_t chest_offset;
PatternScan::Pattern chest_pattern = { "44 89 87 ?? ?? ?? ?? 44 8B 40 ?? 44 89 87 ?? ?? ?? ?? 8B 40 ?? 4C 8B C3 89 87 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8D 54 24", 3, 4, 7, 1 };

uintptr_t inaccuracy_offset;
PatternScan::Pattern inaccuracy_pattern = { "F3 0F 11 87 ?? ?? ?? ?? F3 0F 10 0D ?? ?? ?? ?? F3 0F 11 8F ?? ?? ?? ?? F3 0F 10 05 ?? ?? ?? ?? F3 0F 11 87 ?? ?? ?? ?? F3 0F 10 0D ?? ?? ?? ?? F3 0F 11 8F ?? ?? ?? ?? F3 0F 10 05 ?? ?? ?? ?? F3 0F 11 87 ?? ?? ?? ?? F3 0F 10 0D ?? ?? ?? ?? F3 0F 11 8F ?? ?? ?? ?? C6 87 ?? ?? ?? ?? ?? E9 ?? ?? ?? ?? ", 4, 4, 8, 1 };


void PrintVisualState()
{
	printf("[VISUALSTATE] rotation offset: 0x%X\n", rotation_offset);
	printf("[VISUALSTATE] origin_offset: 0x%X\n", origin_offset);
	printf("[VISUALSTATE] velocity_offset: 0x%X\n", velocity_offset);
	printf("[VISUALSTATE] acceleration_offset: 0x%X\n", acceleration_offset);
	printf("[VISUALSTATE] inverse_rotation_offset: 0x%X\n", inverse_rotation_offset);
	printf("[VISUALSTATE] inverse_pos_offset: 0x%X\n", inverse_pos_offset);
	printf("[VISUALSTATE] move_info_table_index1_offset: 0x%X\n", move_info_table_index1_offset);
	printf("[VISUALSTATE] move_info_table_index2_offset: 0x%X\n", move_info_table_index2_offset);
	printf("[VISUALSTATE] animation_completion_offset: 0x%X\n", animation_completion_offset);
	printf("[VISUALSTATE] head_offset: 0x%X\n", head_offset);
	printf("[VISUALSTATE] chest_offset: 0x%X\n", chest_offset);
	printf("[VISUALSTATE] inaccuracy_offset: 0x%X\n", inaccuracy_offset);
}

void ScanVisualState()
{
	rotation_offset = pattern_scanner.Scan(rotation_pattern, 1);
	origin_offset = pattern_scanner.Scan(origin_pattern, 1);
	velocity_offset = pattern_scanner.Scan(velocity_pattern, 1);
	acceleration_offset = pattern_scanner.Scan(acceleration_pattern, 1);
	inverse_rotation_offset = pattern_scanner.Scan(inverse_rotation_pattern, 1);
	inverse_pos_offset = pattern_scanner.Scan(inverse_pos_pattern, 1);
	move_info_table_index1_offset = pattern_scanner.Scan(move_info_table_index1_pattern, 1);
	move_info_table_index2_offset = pattern_scanner.Scan(move_info_table_index2_pattern, 1);
	animation_completion_offset = pattern_scanner.Scan(animation_completion_pattern, 1);
	head_offset = pattern_scanner.Scan(head_pattern, 1);
	chest_offset = pattern_scanner.Scan(chest_pattern, 1);
	inaccuracy_offset = pattern_scanner.Scan(inaccuracy_pattern, 1);

}

void WriteVisualState()
{
	std::ofstream out_file("visualstate_struct.offset");
	if (out_file.is_open())
	{
		out_file << "#define STR_MERGE_IMPL(a, b) a##b\n";
		out_file << "#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)\n";
		out_file << "#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]\n";
		out_file << "#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }\n";

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
		out_file << "};	VisualStateStruct visualstate_data = {};\n";
	}
	out_file.close();
	printf("[VISUALSTATE] Visual State struct written to file: visualstate_struct.offset\n");
}
