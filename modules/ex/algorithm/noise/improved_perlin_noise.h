#ifndef EX_PERLIN_NOISE_H
#define EX_PERLIN_NOISE_H
#include "core/math/math_funcs.h"
#include "rng_noise.h"
#include "../algorithm_f.h"
namespace ex::algorithm::noise
{
	class ImprovedPerlinNoise : public RNGBasedNoise
	{
	GDCLASS(ImprovedPerlinNoise, RNGBasedNoise);

	protected:
		static void _bind_methods();
		static real_t lerp(real_t t, real_t a, real_t b);
		static real_t fade(real_t t);
		static real_t grad(int16_t hash, real_t x, real_t y, real_t z);
		
		Vector<int16_t> _permutations;
	public:
		static Ref<ImprovedPerlinNoise> get_from_seed(uint64_t seed);
		ImprovedPerlinNoise();
		ImprovedPerlinNoise(uint64_t seed);
		virtual void reset_noise();
		virtual real_t get_noise1d(real_t x);
		virtual real_t get_noise2d(real_t x, real_t y);
		virtual real_t get_noise3d(real_t x, real_t y, real_t z);
	};
}

#endif // EX_REGISTER_TYPES_H
