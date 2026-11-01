uintptr_t inverted_view_right_offset;
PatternScan::Pattern inverted_view_right_pattern = { "8B 46 ?? 89 03 8B 46 ?? 89 43 ?? 8B 46 ?? 89 43 ?? 8B 46", 2, 1, 3, 1 };

uintptr_t inverted_view_up_offset;
PatternScan::Pattern inverted_view_up_pattern = { "0F 10 6E ?? 0F 10 4E ?? 0F 10 66 ?? 0F 28 C6", 3, 1, 4, 1 };

uintptr_t inverted_view_forward_offset;
PatternScan::Pattern inverted_view_forward_pattern = { "0F 10 66 ?? 0F 28 C6 0F 28 D6", 3, 1, 4, 1 };

uintptr_t inverted_view_translation_offset;
PatternScan::Pattern inverted_view_translation_pattern = { "8B 45 ?? 0F 28 C6 89 43", 2, 1, 3, 1 };

uintptr_t viewport_size_offset;
PatternScan::Pattern viewport_size_pattern = { "F3 0F 11 4E ?? 0F 5B C0", 4, 1, 5, 1 };

uintptr_t projection_d1_offset;
uintptr_t projection_d2_offset;
PatternScan::Pattern projection_d1_pattern = { "0F 11 86 ?? ?? ?? ?? 0F 10 44 24 ?? 0F 11 86 ?? ?? ?? ?? 0F 10 44 24 ?? 0F 11 86 ?? ?? ?? ?? 48 8B 06", 3, 4, 7, 1 };
void PrintCamera()
{
	printf("[CAMERA] inverted_view_right_offset: 0x%X\n", inverted_view_right_offset);
	printf("[CAMERA] inverted_view_up_offset: 0x%X\n", inverted_view_up_offset);
	printf("[CAMERA] inverted_view_forward_offset: 0x%X\n", inverted_view_forward_offset);
	printf("[CAMERA] inverted_view_translation_offset: 0x%X\n", inverted_view_translation_offset);
	printf("[CAMERA] viewport_size_offset: 0x%X\n", viewport_size_offset);
	printf("[CAMERA] projection_d1_offset: 0x%X\n", projection_d1_offset);
	printf("[CAMERA] projection_d2_offset: 0x%X\n", projection_d2_offset);
}

void ScanCamera()
{
	inverted_view_right_offset = pattern_scanner.Scan(inverted_view_right_pattern, 1);
	inverted_view_up_offset = pattern_scanner.Scan(inverted_view_up_pattern, 1);
	inverted_view_forward_offset = pattern_scanner.Scan(inverted_view_forward_pattern, 1);
	inverted_view_translation_offset = pattern_scanner.Scan(inverted_view_translation_pattern, 1);
	viewport_size_offset = pattern_scanner.Scan(viewport_size_pattern, 1);
	projection_d1_offset = pattern_scanner.Scan(projection_d1_pattern, 1);
	projection_d2_offset = projection_d1_offset + 0xC;
}

void WriteCamera()
{
	std::ofstream out_file("camera_struct.offset");
	if (out_file.is_open())
	{
		out_file << "#define STR_MERGE_IMPL(a, b) a##b\n";
		out_file << "#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)\n";
		out_file << "#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]\n";
		out_file << "#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }\n";

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
		out_file << "};	CameraStruct camera_data = {};\n";
	}
	out_file.close();
	printf("[CAM] Camera struct written to file: camera_struct.offset\n");
}
