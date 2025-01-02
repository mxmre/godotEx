#pragma once
#include "core/math/math_funcs.h"
#include "basic_noise.h"
#include "../algorithm_f.h"
namespace ex::algorithm::noise
{
	class OpenSimplex : public BasicNoise
	{
	GDCLASS(OpenSimplex, BasicNoise);
		static const int64_t PSIZE = 2048;
		static const int64_t PMASK = 2047;
		
	protected:
		static void _bind_methods();
		virtual void _init_noise();
		Vector<int32_t> _permutations;
		// Градиенты для 2D
		static const Vector<real_t> GRAD_2D;
		// Градиенты для 3D
		static const Vector<real_t> GRAD_3D;
		// Константы для 2D
		static constexpr real_t STRETCH_2D = -0.211324865405187;
		static constexpr real_t SQUISH_2D = 0.366025403784439;
		// Константы для 3D
		static constexpr real_t STRETCH_3D = -1.0 / 6.0;
		static constexpr real_t SQUISH_3D = 1.0 / 3.0;
	public:
		static Ref<OpenSimplex> get_from_seed(uint64_t seed);
		OpenSimplex();
		OpenSimplex(uint64_t seed);
		virtual real_t get_noise2d_at(real_t x, real_t y);
		virtual real_t get_noise3d_at(real_t x, real_t y, real_t z);
	};
}

