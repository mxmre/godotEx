#pragma once
#include "core/math/math_funcs.h"
#include "rng_noise.h"
#include "../algorithm_f.h"
namespace ex::algorithm::noise
{
	//не работает :(
	class OpenSimplexNoise : public RNGBasedNoise
	{
	GDCLASS(OpenSimplexNoise, RNGBasedNoise);
	protected:
		static void _bind_methods();
		static constexpr double STRETCH_2D = -0.211324865405187;
		static constexpr double SQUISH_2D = 0.366025403784439;
		static constexpr double STRETCH_3D = -1.0 / 6.0;
		static constexpr double SQUISH_3D = 1.0 / 3.0;
		static constexpr int PSIZE = 2048;
		static constexpr int PMASK = 2047;

		static const double GRAD_2D[12][2];
		

		static const double GRAD_3D[12][3];
		
		Vector<int32_t> _permutations;
	public:
		static Ref<OpenSimplexNoise> get_from_seed(uint64_t seed);
		OpenSimplexNoise();
		OpenSimplexNoise(uint64_t seed);
		virtual void reset_noise();
		virtual real_t get_noise1d(real_t x);
		virtual real_t get_noise2d(real_t x, real_t y);
		virtual real_t get_noise3d(real_t x, real_t y, real_t z);
	};
}

