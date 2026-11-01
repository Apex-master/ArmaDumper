uintptr_t weapon_type_name_ptr;
PatternScan::Pattern weapon_type_name_pattern = { "48 8B 53 ?? 48 85 D2 74 16 F0 FF 0A 75 0D 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 50 18 48 89 6B 38 48 8D 4B 30 E8 ?? ?? ?? ?? 48 8B 53 30 48 85 D2 74 16 F0 FF 0A 75 0D 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 50 18 48 89 6B 30 48 8B 4B 20 48 85 C9 74 0B 48 8B 41 20 48 83 C1 20 FF 50 28 48 8B 74 24 ?? 48 89 6B 20 48 8B 6C 24 ?? 48 8D 05 ?? ?? ?? ??", 3, 1, 4, 1 };

uintptr_t weapon_type_type_ptr;
PatternScan::Pattern weapon_type_type_pattern = { "48 8B 53 ?? 48 85 D2 74 16 F0 FF 0A 75 0D 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 50 18 48 89 6B 40 48 8D 4B 38 E8 ?? ?? ?? ?? 48 8B 53 38 48 85 D2 74 16 F0 FF 0A 75 0D 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 50 18 48 89 6B 38 48 8D 4B 30 ", 3, 1, 4, 1 };


void ScanWeaponType()
{
	weapon_type_name_ptr = pattern_scanner.Scan(weapon_type_name_pattern, 1);
	weapon_type_type_ptr = pattern_scanner.Scan(weapon_type_type_pattern, 1);
}

void PrintWeaponType()
{
	printf("[WEAPONTABLE] weapon_mode_ptr: 0x0\n");
	printf("[WEAPONTABLE] weapon_type_ptr: 0x8\n");
	printf("[WEAPONTABLE] muzzle_type_ptr: 0x10\n");
	printf("[WEAPONTABLE] muzzle_state_ptr: 0x18\n");
}

void WriteWeapon()
{
	std::ofstream out_file("weapon.offset");
	if (out_file.is_open())
	{
		out_file << "#define STR_MERGE_IMPL(a, b) a##b\n";
		out_file << "#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)\n";
		out_file << "#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]\n";
		out_file << "#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }\n";

		out_file << "\nstruct WeaponTableStuct\n";
		out_file << "{\n";
		out_file << "	union\n";
		out_file << "	{\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, weapon_mode_ptr, 0x0);\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, weapon_type_ptr, 0x8);\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, muzzle_type_ptr, 0x10);\n";
		out_file << "		DEFINE_MEMBER_N(uintptr_t, muzzle_state_ptr, 0x18);\n";
		out_file << "	};\n";
		out_file << "};	WeaponTableStuct weapon_table_data = {};\n";
	}
	out_file.close();
	printf("[WEAPON] Weapon struct written to file: weapon.offset\n");
}
