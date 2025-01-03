#ifndef EX_PERLIN_NOISE_H
#define EX_PERLIN_NOISE_H
#include "core/math/math_funcs.h"
#include "basic_noise.h"
#include "../algorithm_f.h"
namespace ex::algorithm::noise
{
	class ImprovedPerlin : public BasicNoise
	{
	GDCLASS(ImprovedPerlin, BasicNoise);

	protected:
		static void _bind_methods();
		static real_t lerp(real_t t, real_t a, real_t b);
		static real_t fade(real_t t);
		static real_t grad(int8_t hash, real_t x, real_t y, real_t z);
		
		Vector<uint8_t> _permutations;
	public:
		static Ref<ImprovedPerlin> get_from_seed(uint64_t seed);
		ImprovedPerlin();
		ImprovedPerlin(uint64_t seed);
		virtual void init_noise();
		virtual real_t get_noise2d_at(real_t x, real_t y);
		virtual real_t get_noise3d_at(real_t x, real_t y, real_t z);
	};
}

#endif // EX_REGISTER_TYPES_H
