uintptr_t dlc_address;
PatternScan::Pattern dlc_pattern = { "48 8b 0d ?? ?? ?? ?? 8b d7 e8 ?? ?? ?? ?? 0f b6 d0", 3, 4, 7};

uintptr_t sway1_address;
PatternScan::Pattern sway1_pattern = { "F3 0F 59 0D ?? ?? ?? ?? F3 0F 11 4B ?? F3 0F 10 05 ?? ?? ?? ??", 4, 4, 8 };

uintptr_t sway2_address;
PatternScan::Pattern sway2_pattern = { "F3 0F 59 05 ?? ?? ?? ?? F3 0F 11 43 ?? F3 0F 10 05 ?? ?? ?? ?? F3 0F 10 0D ?? ?? ?? ?? F3 41 0F 59 C9 F3 0F 59 C7 F3 41 0F 58 C8 F3 0F 58 C8 F3 0F 59 CA F3 0F 59 0D ?? ?? ?? ?? F3 0F 11 4B ?? F3 0F 10 15 ?? ?? ?? ?? F3 0F 10 43 ??", 4, 4, 8 };

uintptr_t recoil_address;
PatternScan::Pattern recoil_pattern = { "F3 44 0F 10 05 ?? ?? ?? ?? 48 8B F9", 5, 4, 9 };


void PrintOther()
{
	printf("[OTHER] DLC address: 0x%llX\n", dlc_address);
	printf("[OTHER] Sway1 address: 0x%llX\n", sway1_address);
	printf("[OTHER] Sway2 address: 0x%llX\n", sway2_address);
	printf("[OTHER] Recoil address: 0x%llX\n", recoil_address);
}

void ScanOther()
{
	dlc_address = pattern_scanner.Scan(dlc_pattern, 1);
	sway1_address = pattern_scanner.Scan(sway1_pattern, 1);
	sway2_address = pattern_scanner.Scan(sway2_pattern, 1);
	recoil_address = pattern_scanner.Scan(recoil_pattern, 1);
}