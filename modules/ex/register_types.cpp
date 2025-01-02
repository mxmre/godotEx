
#include "register_types.h"
#include "core/object/class_db.h"
void initialize_ex_module(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(ex::algorithm::noise::BasicNoise);
	GDREGISTER_CLASS(ex::algorithm::noise::ImprovedPerlinNoise);
	GDREGISTER_CLASS(ex::algorithm::noise::OpenSimplex);
	
}
void uninitialize_ex_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
		
	}
}
