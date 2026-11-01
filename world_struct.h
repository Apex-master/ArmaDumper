#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }
struct WorldStruct
{
	union
	{
		DEFINE_MEMBER_N(uintptr_t, camera, 0xC70);
		DEFINE_MEMBER_N(uintptr_t, display_manager, 0x1678);
		DEFINE_MEMBER_N(uintptr_t, projectiles_table, 0x1A80);
		DEFINE_MEMBER_N(uintptr_t, projectiles_table_size, 0x1A88);
		DEFINE_MEMBER_N(uintptr_t, near_table, 0x1B50);
		DEFINE_MEMBER_N(uintptr_t, close_table, 0x1C18);
		DEFINE_MEMBER_N(uintptr_t, far_table, 0x1CE0);
		DEFINE_MEMBER_N(uintptr_t, camera_on, 0x2B40);
		DEFINE_MEMBER_N(uintptr_t, player_on, 0x2B70);
		DEFINE_MEMBER_N(uintptr_t, real_player, 0x2B78);
		DEFINE_MEMBER_N(uintptr_t, terrain_grid, 0x3370);
	};
};	WorldStruct world_data = {};
