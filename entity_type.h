uintptr_t model_name_string_offset;
PatternScan::Pattern model_name_string_pattern = { "48 8B 40 ?? 48 85 C0 74 ?? F0 FF 00 48 89 44 24 ?? 48 8D 54 24", 3, 1, 4, 1 };

uintptr_t model_path_string_offset;
PatternScan::Pattern model_path_string_pattern = { "48 8B 83 ?? ?? ?? ?? 48 89 74 24 ?? 48 89 7C 24 ?? 48 85 C0", 3, 4, 7, 1 };

uintptr_t short_name_string_offset;
PatternScan::Pattern short_name_string_pattern = { "48 39 81 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 49 8B 06", 3, 4, 7, 1 };

uintptr_t entity_type_string_offset;
PatternScan::Pattern entity_type_string_pattern = { "48 8B 9B ?? ?? ?? ?? 48 85 DB 74 ?? F0 FF 03 40 38 7B", 3, 4, 7, 1 };

uintptr_t print_name_string_offset;
PatternScan::Pattern print_name_string_pattern = { "48 8B 81 ?? ?? ?? ?? 48 85 C0 74 ?? F0 FF 00 49 89 06", 3, 4, 7, 1 };

uintptr_t print_name_other_string_offset;
//	PatternScan::Pattern print_name_other_string_pattern = { "", 2, 4, 6, 1 };

uintptr_t move_types_ptr_offset;
PatternScan::Pattern move_types_ptr_pattern = { "48 83 B8 ?? ?? ?? ?? ?? 75 ?? 32 C0", 3, 5, 8, 1 };

void PrintEntityType()
{
	printf("[ENTITYTYPE] model_name_string_offset: 0x%X\n", model_name_string_offset);
	printf("[ENTITYTYPE] model_path_string_offset: 0x%X\n", model_path_string_offset);
	printf("[ENTITYTYPE] short_name_string_offset: 0x%X\n", short_name_string_offset);
	printf("[ENTITYTYPE] entity_type_string_offset: 0x%X\n", entity_type_string_offset);
	printf("[ENTITYTYPE] print_name_string_offset: 0x%X\n", print_name_string_offset);
	printf("[ENTITYTYPE] print_name_other_string_offset: 0x%X\n", print_name_other_string_offset);
	printf("[ENTITYTYPE] move_types_ptr_offset: 0x%X\n", move_types_ptr_offset);
}

void ScanEntityType()
{
	model_name_string_offset = pattern_scanner.Scan(model_name_string_pattern, 1);
	model_path_string_offset = pattern_scanner.Scan(model_path_string_pattern, 1);
	short_name_string_offset = pattern_scanner.Scan(short_name_string_pattern, 1);
	entity_type_string_offset = pattern_scanner.Scan(entity_type_string_pattern, 1);
	print_name_string_offset = pattern_scanner.Scan(print_name_string_pattern, 1);
	print_name_other_string_offset = print_name_string_offset + (0x8 * 3);
	move_types_ptr_offset = pattern_scanner.Scan(move_types_ptr_pattern, 1);
}

void WriteEntityType()
{
	std::ofstream out_file("entitytype_struct.offset");
	if (out_file.is_open())
	{
		out_file << "#define STR_MERGE_IMPL(a, b) a##b\n";
		out_file << "#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)\n";
		out_file << "#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]\n";
		out_file << "#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }\n";

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
	}
	out_file.close();
	printf("[ENTITYTYPE] EntityType struct written to file: entitytype_struct.offset\n\n");
}
