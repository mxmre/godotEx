#ifndef EX_REGISTER_TYPES_H
#define EX_REGISTER_TYPES_H

#include "modules/register_module_types.h"
#include "algorithm/noise/basic_noise.h"
#include "algorithm/noise/improved_perlin_noise.h"
#include "algorithm/noise/open_simplex.h"

void initialize_ex_module(ModuleInitializationLevel p_level);
void uninitialize_ex_module(ModuleInitializationLevel p_level);

#endif // EX_REGISTER_TYPES_H
