
#include "register_types.h"
#include "core/object/class_db.h"

#include "algorithm/noise/basic_noise.h"
#include "algorithm/noise/improved_perlin_noise.h"
#include "algorithm/noise/open_simplex.h"
#include "algorithm/noise/summator.h"
void initialize_ex_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_ABSTRACT_CLASS(ex::algorithm::noise::BasicNoise);
	GDREGISTER_CLASS(ex::algorithm::noise::ImprovedPerlin);
	GDREGISTER_CLASS(ex::algorithm::noise::OpenSimplex);
	GDREGISTER_CLASS(Summator);
}
void uninitialize_ex_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
		
	}
}
