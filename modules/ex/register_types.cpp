
#include "register_types.h"
#include "core/object/class_db.h"

#include "algorithm/noise/basic_noise.h"
#include "algorithm/noise/rng_noise.h"
#include "algorithm/noise/shell_noise.h"
#include "algorithm/noise/fractal_noise.h"
#include "algorithm/noise/improved_perlin_noise.h"
#include "algorithm/noise/open_simplex_noise.h"

void initialize_ex_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_ABSTRACT_CLASS(ex::algorithm::noise::BasicNoise);
	GDREGISTER_ABSTRACT_CLASS(ex::algorithm::noise::RNGBasedNoise);
	GDREGISTER_ABSTRACT_CLASS(ex::algorithm::noise::ShellNoise);
	GDREGISTER_CLASS(ex::algorithm::noise::FractionalBrownianMotion);
	GDREGISTER_CLASS(ex::algorithm::noise::ImprovedPerlinNoise);
	GDREGISTER_CLASS(ex::algorithm::noise::OpenSimplexNoise);
}
void uninitialize_ex_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
		
	}
}
