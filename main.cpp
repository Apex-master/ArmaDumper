#include "memory.h"
#include "patternscan.h"
PatternScan pattern_scanner;

#include "world.h"
#include "camera.h"
#include "entity.h"
#include "entity_type.h"
#include "weapon.h"
#include "visualstate.h"
#include "other.h"
#include "all.h"


int main()
{
	if (!mem.Initialize())
	{
		std::cout << "[-] Failed to initialize memory.\n";
	}

	printf("[+] Arma PID: %i\n", mem.game_pid);
	printf("[+] Arma Base Address: %llx\n\n", mem.game_base_address);

	pattern_scanner.Initialize(mem.game_base_address);
	{
		ScanWorld();
		ScanCamera();
		ScanEntity();
		ScanEntityType();

		ScanWeaponType();
		
		ScanVisualState();
		ScanOther();
		
		//	WriteWorld();
		//	WriteEntity();
		//	WriteVisualState();
		WriteAll();

		PrintWorld();
		PrintCamera();
		PrintEntity();
		PrintEntityType();

		PrintWeaponType();

		PrintVisualState();
		PrintOther();
	} 
	pattern_scanner.ClearBuffer();

	std::cin.get();
}